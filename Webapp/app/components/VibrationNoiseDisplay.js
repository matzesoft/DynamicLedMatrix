"use client";

import BarChartComponent from "./BarChart";
import Loading from "./Loading";
import { useEffect, useState } from "react";
import { ref, query, orderByKey, limitToLast, get, onValue } from "firebase/database";
import { database } from "../../firebaseConfig";

// Component that fetches the last 30 noise and vibration sensor readings and displays them in a BarChart
export default function VibrationNoiseDisplay() {
  const [combinedData, setCombinedData] = useState(null);

  useEffect(() => {

    // Fetches the last 30 noise and vibration sensor readings
    async function fetchLastTimestamps() { 
      const noiseRef = ref(database, "noise-detection");
      const vibrationRef = ref(database, "vibration-detection");

      const noiseQuery = query(noiseRef, orderByKey(), limitToLast(30));
      const vibrationQuery = query(vibrationRef, orderByKey(), limitToLast(30));

      const [noiseSnapshot, vibrationSnapshot] = await Promise.all([
        get(noiseQuery),
        get(vibrationQuery),
      ]);
      
      // If there are some noise and vibration readings, fetch the combined data
      if (noiseSnapshot.exists() && vibrationSnapshot.exists()) {
        const noiseTimestamps = Object.keys(noiseSnapshot.val());
        const vibrationTimestamps = Object.keys(vibrationSnapshot.val());

        fetchCombinedData(noiseTimestamps, vibrationTimestamps);
      }
    }

    /* 
      Fetches the combined data for the given noise and vibration timestamps
      The combined data is an object with the time as the key and the noise and vibration count as the values.
      The BarChartComponent needs the data in the given format to display the data correctly for both noise and vibration.
    */
    async function fetchCombinedData(noiseTimestamps, vibrationTimestamps) {

      const dataByTime = {};

      for (const timestamp of noiseTimestamps) {
        const noiseRef = ref(database, `noise-detection/${timestamp}`);
        const noiseSnapshot = await get(noiseRef);

        if (noiseSnapshot.exists()) {
          const time = new Date(parseInt(timestamp));
          const formattedTime = `${time.getHours().toString().padStart(2, "0")}:${time.getMinutes().toString().padStart(2, "0")}`;

          if (!dataByTime[formattedTime]) {
            dataByTime[formattedTime] = { time: formattedTime, noise: 0, vibration: 0 };
          }

          dataByTime[formattedTime].noise += 1;
        }
      }

      for (const timestamp of vibrationTimestamps) {
        const vibrationRef = ref(database, `vibration-detection/${timestamp}`);
        const vibrationSnapshot = await get(vibrationRef);

        if (vibrationSnapshot.exists()) {
          const time = new Date(parseInt(timestamp));
          const formattedTime = `${time.getHours().toString().padStart(2, "0")}:${time.getMinutes().toString().padStart(2, "0")}`;

          if (!dataByTime[formattedTime]) {
            dataByTime[formattedTime] = { time: formattedTime, noise: 0, vibration: 0 };
          }

          dataByTime[formattedTime].vibration += 1;
        }
      }

      const sortedEntries = Object.values(dataByTime).sort(
        (a, b) => new Date(a.time) - new Date(b.time)
      );

      setCombinedData(sortedEntries);
    }

    fetchLastTimestamps();
  }, []);

  return (
    <>
      {!combinedData ? (
        <Loading />
      ) : (
        console.log(combinedData),
        <BarChartComponent barchartData={combinedData} />
      )}
    </>
  );
}
