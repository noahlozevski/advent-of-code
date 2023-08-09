// read in the file from test-input.txt
import { readFileSync } from "fs";

const input = readFileSync("test-input2.txt", "utf8").split("\n");

const seen = new Set();
type dir = [number, number];

const segments: dir[] = [];
for (let i = 0; i < 9; i++) {
  segments.push([0,0]);
}

function step(x: number, y: number) {
  for (let i = 0; i < 8; i++) {
    stepSegment(x, y, segments[i], segments[i + 1]);
  }
  const tail = segments[segments.length - 1];
  seen.add(tail);
}

function stepSegment(x: number, y: number, head: dir, tail: dir) {
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

console.log(`Part 2: ${seen.size}`);
