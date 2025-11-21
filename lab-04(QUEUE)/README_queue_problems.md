# Queue Problems Solutions

This folder contains solutions to common queue problems implemented using the provided `CircularQueue` and `SimpleQueue` classes.

## Files

- `q_reverse_first_k.cpp` — Reverse first K elements of a queue (uses an auxiliary stack)
- `q_interleave_halves.cpp` — Interleave the first half and second half of the queue
- `q_generate_binary.cpp` — Generate binary numbers from 1 to n using a queue
- `q_hot_potato.cpp` — Hot potato (Josephus-like) game simulation
- `q_time_to_buy_tickets.cpp` — Time needed to buy tickets (LeetCode 2073)
- `q_first_non_repeating_stream.cpp` — First non-repeating character in a character stream
- `maze_bfs.cpp` — Bonus: BFS shortest path in a maze using a queue

## How to build and run (Windows, g++)

Open PowerShell in the folder and run any of these commands:

```powershell
# Reverse first K
g++ -o output\q_reverse_first_k.exe q_reverse_first_k.cpp && output\q_reverse_first_k.exe

# Interleave halves
g++ -o output\q_interleave_halves.exe q_interleave_halves.cpp && output\q_interleave_halves.exe

# Generate binary numbers
g++ -o output\q_generate_binary.exe q_generate_binary.cpp && output\q_generate_binary.exe

# Hot potato
g++ -o output\q_hot_potato.exe q_hot_potato.cpp && output\q_hot_potato.exe

# Time to buy tickets
g++ -o output\q_time_to_buy_tickets.exe q_time_to_buy_tickets.cpp && output\q_time_to_buy_tickets.exe

# First non-repeating character in stream
g++ -o output\q_first_non_repeating_stream.exe q_first_non_repeating_stream.cpp && output\q_first_non_repeating_stream.exe

# BFS Maze (bonus)
g++ -o output\maze_bfs.exe maze_bfs.cpp && output\maze_bfs.exe
```

If `output` folder doesn't exist, create it or change the output path.

## Notes
- All programs use `queue.h` and, where needed, `Stack.h` already present in this project.
- Adjust input values in `main()` to test other cases.
