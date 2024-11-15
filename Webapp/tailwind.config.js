/** @type {import('tailwindcss').Config} */

import { content as _content } from "flowbite-react/tailwind";

export const darkMode = ["class"];
export const content = ["./app/**/*.{js,ts,jsx,tsx,mdx}", _content()];
export const theme = {
  extend: {
    colors: {
      background: 'var(--background)',
      foreground: 'var(--foreground)',
      'custom-blue': '#2420e2',
    },
    borderRadius: {
      lg: 'var(--radius)',
      md: 'calc(var(--radius) - 2px)',
      sm: 'calc(var(--radius) - 4px)',
    }
  }
};
export const plugins = [
  require("flowbite/plugin")({
    charts: true,
  }),
  require("tailwindcss-animate")
];

export const safelist = [
];
