import { readFileSync } from "fs";

let cycle = 0;
const cycles: number[] = [];
let signalStrength = 0;

const specialCycles = [20, 60, 100, 140, 180, 220];

readFileSync("test-input.txt", "utf8")
  .split("\n")
  .forEach((line: string) => {
    const lastCycle = cycles[cycles.length - 1] ?? 1;
    console.log(`Cycle ${cycle}: lastCycle = ${lastCycle}, line = ${line}`);

    if (specialCycles.includes(cycle)) {
      const incr = cycle * lastCycle;
      signalStrength += incr;
      console.log(
        `Cycle ${cycle}: signalStrength = ${signalStrength}, incr = ${incr}`
      );
    }

    if (line.includes("noop")) {
      cycles.push(lastCycle);
      cycle++;
      return;
    } else {
      const [op, arg] = line.split(" ");
      const num = parseInt(arg);
      cycles.push(lastCycle);
      cycle++;

      if (specialCycles.includes(cycle)) {
        const incr = cycle * lastCycle;
        signalStrength += incr;
        console.log(
          `Cycle ${cycle}: signalStrength = ${signalStrength}, incr = ${incr}`
        );
      }

      cycles.push(lastCycle + num);
      cycle++;
    }
  });

console.log(`Part 1: ${signalStrength}`);
console.log(`Cycles: ${cycles}`);
