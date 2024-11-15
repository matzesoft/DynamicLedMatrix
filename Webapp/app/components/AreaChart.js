"use client";

import { CartesianGrid, Line, LineChart, XAxis, YAxis } from "recharts";
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
  temp: {
    label: "Temperature",
    color: "hsl(var(--chart-1))",
  },
};

// AreaChartComponent component from shadcn/ui
export default function AreaChartComponent({ chartData }) {
  return (
    <Card className ="aspect-square w-[400px] h-[400px] max-w-[400px] max-h-[400px]">
      <CardHeader>
        <CardTitle>Time - Temperature</CardTitle>
        <CardDescription>Last 100 entries</CardDescription>
      </CardHeader>
      <CardContent className="w-full h-full">
        <ChartContainer config={chartConfig} className="w-full h-[80%]">
          <LineChart
            accessibilityLayer
            data={chartData}
            margin={false}
          >
            <CartesianGrid vertical={false} />
            <XAxis
              dataKey="time"
              tickLine={false}
              axisLine={false}
              tickMargin={8}
              tickFormatter={(value) => value}
            />
            <YAxis
              dataKey="temp"
              tickLine={false}
              axisLine={false}
              tickMargin={30}
              fontSize={11}
              tickFormatter={(value) => `${value}°C`}
            />
            <ChartTooltip
              cursor={false}
              content={<ChartTooltipContent indicator="line" />}
            />
            <Line
              dataKey="temp"
              type="natural"
              stroke="var(--color-temp)"
              strokeWidth={2}
              dot={false}
              activeDot={false}
            >
            </Line>
          </LineChart>
        </ChartContainer>
      </CardContent>
    </Card>
  );
}