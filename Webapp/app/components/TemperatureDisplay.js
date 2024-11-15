"use client";

import AreaChartComponent from "./AreaChart";
import Loading from "./Loading";
import { useEffect, useState } from "react";
import { ref, query, orderByKey, limitToLast, get, onValue } from "firebase/database";
import { database } from "../../firebaseConfig";

// Component that fetches the last 100 temperature sensor readings and displays them in an AreaChart
export default function TemperatureDisplay() {
  const [lastSync, setLastSync] = useState(null);
  const [temperatureData, setTemperatureData] = useState(null);

  useEffect(() => {
    const lastSyncRef = ref(database, "last-sync-timestamp");

    const unsubscribeLastSync = onValue(lastSyncRef, (snapshot) => {
      setLastSync(snapshot.val());
    });

    // Fetches the last 100 temperature sensor readings
    async function fetchLastTimestamps() {
      const timestampRef = ref(database, "temperature-sensor");

      const lastFiveQuery = query(timestampRef, orderByKey(), limitToLast(100));
      const snapshot = await get(lastFiveQuery);

      // If there are some temperature readings, fetch the temperature data
      if (snapshot.exists()) {
        const timestamps = Object.keys(snapshot.val());
        fetchTemperatureData(timestamps);
      }
    }

    // Fetches the temperature data for the given timestamps
    async function fetchTemperatureData(timestamps) {
      const temperatureEntries = [];

      for (const timestamp of timestamps) {
        const tempRef = ref(database, `temperature-sensor/${timestamp}`);
        const tempSnapshot = await get(tempRef);

        if (tempSnapshot.exists()) {
          const time = new Date(parseInt(timestamp));
          const formattedTime = `${time.getHours().toString().padStart(2, "0")}:${time.getMinutes().toString().padStart(2, "0")}`;

          temperatureEntries.push({
            time: formattedTime,
            temp: tempSnapshot.val(),
          });
        }
      }

      const sortedEntries = temperatureEntries.sort(
        (a, b) => parseInt(a.month) - parseInt(b.month)
      );

      setTemperatureData(sortedEntries);
    }

    fetchLastTimestamps();

    return () => {
      unsubscribeLastSync();
    };
  }, []);

  return (
    <>
      {lastSync === null || !temperatureData ? (
        <Loading />
      ) : (
        <AreaChartComponent chartData={temperatureData} />
      )}
    </>
  );
}
