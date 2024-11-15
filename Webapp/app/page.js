// app/page.js
"use client";

import TemperatureDisplay from "./components/TemperatureDisplay";
import VibrationNoiseDisplay from "./components/VibrationNoiseDisplay";

// The main page of the app that renders the TemperatureDisplay and VibrationNoiseDisplay components
export default function HomePage() {
  return (
    <main className="flex min-h-screen flex-col items-center justify-center bg-[hsl(var(--background))] text-[hsl(var(--foreground))]">
      <h1 className="text-2xl font-bold mb-4">
        Recent Data
      </h1>
      <div className="flex flex-col md:flex-row space-y-4 md:space-y-0 md:space-x-4">
        <TemperatureDisplay /> 
        <VibrationNoiseDisplay />
      </div> 
    </main>
  );
}
