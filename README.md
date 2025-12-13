# philosophers 🍝🧠

Rebuild the classic Dining Philosophers problem in C: threads, mutexes, timing, and the constant fear of deadlocks 😅  

## 🛠️ Build
```bash
make
# (usually also)
make clean
make fclean
make re
```

## ▶️ Usage
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

# all times are in milliseconds
# simulation stops when:
# - a philosopher dies, OR
# - everyone has eaten N times (if the optional arg is provided)
```

### Args
- `number_of_philosophers` (N): how many philosophers/forks
- `time_to_die` (ms): max time without eating before dying
- `time_to_eat` (ms): how long eating takes
- `time_to_sleep` (ms): how long sleeping takes
- `number_of_times_each_philosopher_must_eat` (optional): stop when all have eaten this many times ✅

## 💡 Examples
```bash
# “classic” stable-ish run (should not instantly explode)
./philo 5 800 200 200

# stop after everyone eats 3 times
./philo 4 800 200 200 3

# edge case: 1 philosopher (can’t take 2 forks -> should die)
./philo 1 800 200 200

# stress-ish: tight time_to_die (deaths should happen cleanly)
./philo 4 310 200 200
```

## 📝 Notes
- Output format is typically:
  ```text
  <timestamp_ms> <philo_id> <action>
  # e.g. "123 2 is eating"
  ```
- **Exactly one** “died” line should appear, and after that the sim should shut up (no extra actions printed) ☠️
- Your job is basically:
  - no deadlocks 🔒
  - no data races 🧵
  - correct timing logic (don’t “pause” death checks just because someone is mid-`usleep`) ⏱️
- Handy torture tools (if you’re in debugging hell):
  ```bash
  valgrind --tool=helgrind ./philo 4 800 200 200 5
  valgrind --tool=drd      ./philo 4 800 200 200 5
  ```
