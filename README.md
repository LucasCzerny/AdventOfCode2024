# Advent of Code 2024 in C++

My happiness levels for each solution from 1-5: &nbsp; 🤨 😐 🙂 😀 😄

|                                                | Part 1 Solution                                                                | Part 2 Solution                                                               | Notes                                                                                                                     |
|:-----------------------------------------------|:-------------------------------------------------------------------------------|:------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------|
| [Day 01](https://adventofcode.com/2024/day/1)  | [part1.cpp](Day%2001/part1.cpp) - [0.253929ms](Day%2001/output_part1.txt) - 😄 | [part2.cpp](Day%2001/part2.cpp) - [0.338325ms](Day%2001/output_part2.txt) - 😄 | [hihi](https://www.reddit.com/r/adventofcode/comments/1h3w7mc/2024_day_1_no_llms_here/)                                   |
| [Day 02](https://adventofcode.com/2024/day/2)  | [part1.cpp](Day%2002/part1.cpp) - [0.272486ms](Day%2002/output_part1.txt) - 😄 | [part2.cpp](Day%2002/part2.cpp) - [0.445645ms](Day%2002/output_part2.txt) - 😀 | Kinda brute force-y but meh                                                                                               |
| [Day 03](https://adventofcode.com/2024/day/3)  | [part1.cpp](Day%2003/part1.cpp) - [0.342503ms](Day%2003/output_part1.txt) - 😄 | [part2.cpp](Day%2003/part2.cpp) - [0.906545ms](Day%2003/output_part2.txt) - 😀 | Def did not let chat gpt generate the regex                                                                               |
| [Day 04](https://adventofcode.com/2024/day/4)  | [part1.cpp](Day%2004/part1.cpp) - [0.239705ms](Day%2004/output_part1.txt) - 😄 | [part2.cpp](Day%2004/part2.cpp) - [0.063468ms](Day%2004/output_part2.txt) - 😄 | Kinda brute force-y but meh                                                                                               |
| [Day 05](https://adventofcode.com/2024/day/5)  | [part1.cpp](Day%2005/part1.cpp) - [1.099130ms](Day%2005/output_part1.txt) - 🙂 | [part2.cpp](Day%2005/part2.cpp) - [2.204660ms](Day%2005/output_part2.txt) - 🙂 | Wasn't a huge fan of this day; part 2 is kinda scuffed because I'm using Bubble Sort lol                                  |
| [Day 06](https://adventofcode.com/2024/day/6)  | [part1.cpp](Day%2006/part1.cpp) - [0.597761ms](Day%2006/output_part1.txt) - 😀 | [part2.cpp](Day%2006/part2.cpp) - [2504.730ms](Day%2006/output_part2.txt) - 😐 | Part 2 could def be better, there's no need to start from the starting position every time f.e.                           |
| [Day 07](https://adventofcode.com/2024/day/7)  | [part1.cpp](Day%2007/part1.cpp) - [0.600864ms](Day%2007/output_part1.txt) - 😀 | [part2.cpp](Day%2007/part2.cpp) - [16.03820ms](Day%2007/output_part2.txt) - 🙂 | Not too bad, could be optimized but [I don't have the time](https://media.tenor.com/pBxKoe4krm0AAAAj/noooo-emote.gif)     |
| [Day 08](https://adventofcode.com/2024/day/8)  | [part1.cpp](Day%2008/part1.cpp) - [0.064820ms](Day%2008/output_part1.txt) - 😄 | [part2.cpp](Day%2008/part2.cpp) - [0.179963ms](Day%2008/output_part2.txt) - 😄 | Figured out how to use a custom Position struct with a set instead of std::pair                                           |
| [Day 09](https://adventofcode.com/2024/day/9)  | [part1.cpp](Day%2009/part1.cpp) - [0.109518ms](Day%2009/output_part1.txt) - 😄 | [part2.cpp](Day%2009/part2.cpp) - [1204.123ms](Day%2009/output_part2.txt) - 😐 | tfw when the datatype for the checksum is too small and you spend 30min figuring out why your answer is wrong             |
| [Day 10](https://adventofcode.com/2024/day/10) | [part1.cpp](Day%2010/part1.cpp) - [1.292020ms](Day%2010/output_part1.txt) - 😄 | [part2.cpp](Day%2010/part2.cpp) - [0.563295ms](Day%2010/output_part2.txt) - 😄 | [Solved part2 before part2](https://www.reddit.com/r/adventofcode/comments/1hauw4v/2024_d10_solved_part_2_before_part_2/) |
| [Day 11](https://adventofcode.com/2024/day/11) | [part1.cpp](Day%2011/part1.cpp) - [0.691646ms](Day%2011/output_part1.txt) - 😀 | [part2.cpp](Day%2011/part2.cpp) - [23.68010ms](Day%2011/output_part2.txt) - 😀 | [me rn](https://www.reddit.com/r/adventofcode/comments/1h7v1ys/ill_start_studying_tomorrow_maybe/)                        |

&nbsp;

![Advent of Code 2024 Art](art11.png)

## How to run

*NOTE:* I am using C++20 with gcc version 15.0.0 ([built from source](https://gcc.gnu.org/install/index.html)). It might not compile on other compilers.

### cmake

Run the following commands to build the executables:

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

Then, run them with:

```bash
./Part1
```

or

```bash
./Part2
```

### For VsCode users

- Install the CMake extensions
- Open the Day xx folder in VsCode
- Run `CMake: Configure` if it's not already configured
- You can set the target (part1 or part2) with `CMake: Set Launch/Debug Target`
- If you want to switch between Debug and Release mode, run `CMake: Select Variant`
- Press `Shift+F5` to run

## Notes

Each Day xx folder consists of the following files:
- `part[1,2].cpp`: The code for each part
- `output_part[1,2].txt`: The output for the each part
- `sample_input.txt`: The sample input given in the task description

  OR `sample_input_part[1,2].txt` if there are multiple sample inputs given
  
- `CMakeLists.txt`: The CMake build instructions

There is also a `lib` folder at the root of the repository with utility functions like `read_file()` and `average_time()` for timing.

Note that I'm using `std::chrono::high_resolution_clock`, which, despite it's name, is not very accurate (it usually just uses the system clock, but it depends on the implementation).
It's also going to vary due to interrupts and task switches.
For the first couple of days where the execution time is < 1ms, the timer isn't that useful. However, I still think it's going to be a nice estimate for the later days.
