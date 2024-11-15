// app/components/theme-provider.js
"use client";

import React from "react";
import { ThemeProvider as NextThemesProvider } from "next-themes";

// A custom ThemeProvider component that wraps the NextThemesProvider and provides the light and dark themes
export function ThemeProvider({ children }) {
  return (
    <NextThemesProvider attribute="class" themes={["light", "dark"]} defaultTheme="light">
      {children}
    </NextThemesProvider>
  );
}
