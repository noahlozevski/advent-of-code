// read in the file from test-input.txt
import { readFileSync } from "fs";

const input = readFileSync("input.txt", "utf8").split("\n");

const seen = new Set();

let head = [0, 0];
let tail = [0, 0];

function step(x: number, y: number) {
  head[0] += x;
  head[1] += y;

  const dx = head[0] - tail[0];
  const dy = head[1] - tail[1];

  if (dx > 1) {
    tail = [head[0] - 1, head[1]];
  } else if (dx < -1) {
    tail = [head[0] + 1, head[1]];
  } else if (dy > 1) {
    tail = [head[0], head[1] - 1];
  } else if (dy < -1) {
    tail = [head[0], head[1] + 1];
  }
  seen.add(tail.join(","));
}

input.forEach((line: string) => {
  const [dir, count] = line.split(" ");
  for (let i = 0; i < parseInt(count); i++) {
    switch (dir) {
      case "U":
        step(0, 1);
        break;
      case "D":
        step(0, -1);
        break;
      case "L":
        step(-1, 0);
        break;
      case "R":
        step(1, 0);
        break;
    }
  }
});

console.log(`Part 1: ${seen.size}`);
