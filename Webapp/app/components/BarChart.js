"use client";

import { Bar, BarChart, CartesianGrid, XAxis, YAxis } from "recharts";

import {
  Card,
  CardContent,
  CardDescription,
  CardHeader,
  CardTitle,
} from "@/components/ui/card";

import {
  ChartContainer,
  ChartTooltip,
  ChartTooltipContent,
} from "@/components/ui/chart";

const chartConfig = {
  vibration: {
    label: "vibration",
    color: "hsl(var(--chart-1))",
  },
  noise: {
    label: "noise",
    color: "hsl(var(--chart-2))",
  },
};

// BarChartComponent component from shadcn/ui
export default function BarChartComponent({ barchartData }) {
  return (
    <Card className="aspect-square w-[400px] h-[400px] max-w-[400px] max-h-[400px]">
      <CardHeader>
        <CardTitle>Time - Vibration/Noise count</CardTitle>
        <CardDescription>Last 30 entries</CardDescription>
      </CardHeader>
      <CardContent className="w-full h-full">
        <ChartContainer config={chartConfig} className="w-full h-[80%]">
          <BarChart accessibilityLayer data={barchartData}>
            <CartesianGrid vertical={false} />
            <XAxis
              dataKey="time"
              tickLine={false}
              tickMargin={10}
              axisLine={false}
              tickFormatter={(value) => value.slice(0, 5)}
            />
            <YAxis
              dataKey="noise"
              tickLine={false}
              axisLine={false}
              tickMargin={40}
              fontSize={12}
              tickFormatter={(value) => `${value}`}
            />
            <ChartTooltip
              cursor={false}
              content={<ChartTooltipContent indicator="dashed" />}
            />
            <Bar dataKey="noise" fill="var(--color-noise)" radius={4} />
            <Bar dataKey="vibration" fill="var(--color-vibration)" radius={4} />
          </BarChart>
        </ChartContainer>
      </CardContent>
    </Card>
  );
}
