// app/layout.js
"use client";

import "./globals.css";
import { ThemeProvider } from "@/components/theme-provider";
import DarkModeButton from "./components/DarkModeButton.js";
import { useState, useEffect } from "react";
import Loading from "./components/Loading";

// The root layout of the app that wraps the entire app with the ThemeProvider and DarkModeButton
export default function RootLayout({ children }) {
  const [mounted, setMounted] = useState(false);

  useEffect(() => {
    setMounted(true);
  }, []);

  return (
    <html lang="en">
      <head>
        <meta name="viewport" content="width=device-width, initial-scale=1" />
      </head>
      <body className="bg-[hsl(var(--background))] text-[hsl(var(--foreground))]">
        {mounted ? (
          <ThemeProvider attribute="class" defaultTheme="light">
            <header className="flex items-center justify-between p-4 bg-blue-600 text-white">
              <h1 className="text-xl font-semibold">Dynamic LED Matrix</h1>
              <DarkModeButton />
            </header>
            <main className="flex flex-col items-center justify-center min-h-screen p-4">
              {children}
            </main>
          </ThemeProvider>
        ) : (
          <div>
            <Loading />
          </div>
        )}
      </body>
    </html>
  );
}
