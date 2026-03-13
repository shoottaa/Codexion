*This project has been created as part of the 42 curriculum by [egaudich].*

# Codexion

## Description

Codexion is a concurrency simulation inspired by the classic Dining Philosophers problem, reimagined in a 42 school context. Coders sit in a circle, each needing two USB dongles (left and right) to compile. If a coder fails to compile within `time_to_burnout` milliseconds, they burn out and the simulation stops. The goal is to manage shared resources (dongles) between concurrent threads without deadlock, starvation, or race conditions, while supporting two scheduling policies: FIFO and EDF (Earliest Deadline First).

## Instructions

### Compilation

```bash
make
```

### Execution

```bash
./codexion num_coders time_to_burnout time_to_compile time_to_debug time_to_refactor num_compiles_required dongle_cooldown scheduler
```

| Argument | Description |
|---|---|
| `num_coders` | Number of coders sitting in the circle |
| `time_to_burnout` | Time in ms before a coder burns out if they haven't compiled |
| `time_to_compile` | Time in ms to compile |
| `time_to_debug` | Time in ms to debug |
| `time_to_refactor` | Time in ms to refactor |
| `num_compiles_required` | Number of compiles each coder must complete |
| `dongle_cooldown` | Time in ms a dongle is unavailable after being released |
| `scheduler` | Scheduling policy: `fifo` or `edf` |

### Example

```bash
./codexion 4 800 200 150 120 3 50 fifo
./codexion 5 250 50 50 50 6 6 edf
```

### Cleanup

```bash
make clean   # remove object files
make fclean  # remove object files and binary
make re      # recompile from scratch
```

## Blocking Cases Handled

### Deadlock Prevention
A deadlock occurs when every coder holds one dongle and waits for another, forming a circular dependency where no one can proceed. This is prevented by breaking the symmetry of dongle acquisition: even-numbered coders take their left dongle first, then their right; odd-numbered coders take their right first, then their left. This ensures the circular wait condition (one of Coffman's four necessary conditions for deadlock) can never form.

### Starvation Prevention
Starvation occurs when a coder never gets access to the dongles because others always take priority. This is prevented using a per-dongle priority queue (min-heap). Every coder registers in the queue when requesting a dongle and can only take it when they are at the front. In FIFO mode, priority is the arrival timestamp, guaranteeing first-come-first-served access. In EDF mode, priority is the coder's deadline, ensuring the most urgent coder is always served first.

### Cooldown Handling
After releasing a dongle, it enters a cooldown period during which it cannot be acquired. This is tracked with a `cooldown` timestamp per dongle. Coders waiting for a dongle use `pthread_cond_timedwait` with a 2ms timeout, waking up periodically to recheck whether the cooldown has expired, without requiring an explicit signal.

### Burnout Detection
A dedicated monitor thread checks every millisecond whether any coder has exceeded their deadline (`get_time_ms() > coder->deadline`). Upon detection, it logs the burnout and sets the global `flag` to 1, which causes all threads to exit gracefully at their next loop iteration.

### Log Serialization
All log output is protected by a dedicated `mutex_logging` to prevent interleaved output from concurrent threads. The monitor flag is also checked before logging to avoid printing messages after a burnout has been detected.

## Thread Synchronization Mechanisms

### `pthread_mutex_t`
Three mutexes are used:
- `dongle->mutex` — protects access to each dongle's state (`is_used`, `cooldown`, `waiters`). Acquired before any read or write to these fields.
- `sim->mutex_flag` — protects the global `flag` variable, which is written by the monitor and read by all coder threads. Without this mutex, a coder could read a stale value of `flag` and continue running after a burnout — a classic race condition.
- `sim->mutex_logging` — serializes all `printf` calls to prevent garbled output when multiple threads log simultaneously.

### `pthread_cond_t`
Each dongle has a condition variable `dongle->cond`. Coders waiting for a dongle call `pthread_cond_timedwait`, which atomically releases the dongle mutex and suspends the thread. When a dongle is released, `pthread_cond_broadcast` wakes all waiting coders so each can recheck the conditions. `broadcast` is used instead of `signal` because multiple coders may be waiting on the same dongle, and the correct one to proceed is determined by the priority queue, not by which thread happens to be woken.

### `pthread_cond_timedwait`
Rather than `pthread_cond_wait`, which blocks indefinitely until signaled, `pthread_cond_timedwait` is used with a 2ms timeout. This is necessary to handle the cooldown period: after a dongle is released, no signal is sent during the cooldown. Without the timeout, coders would sleep forever. The timeout is built from `gettimeofday` (current time + 2ms), converted to the `struct timespec` format required by the function.

### Race Condition Prevention
All shared state is accessed exclusively within a mutex lock/unlock pair. For example, a coder reading `sim->flag` in `is_sim_active` always locks `mutex_flag` first, ensuring it cannot read a partially written value. Similarly, `dongle->is_used` is only read or written while holding `dongle->mutex`.

### Monitor and Coder Coordination
The monitor thread runs independently and never blocks on dongle acquisition. It loops every 1ms, checking burnout and compile completion. When it sets `flag = 1`, coder threads detect this at their next call to `is_sim_active` and exit their main loop cleanly. This design ensures the monitor remains responsive regardless of the state of individual coders.

## Resources

### Classic References
- [POSIX Threads Programming — Lawrence Livermore National Laboratory](https://hpc-tutorials.llnl.gov/posix/)
- [The Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Coffman Conditions — Wikipedia](https://en.wikipedia.org/wiki/Deadlock#Coffman_conditions)
- [Earliest Deadline First Scheduling — Wikipedia](https://en.wikipedia.org/wiki/Earliest_deadline_first_scheduling)
- [pthread_cond_timedwait — Linux man page](https://man7.org/linux/man-pages/man3/pthread_cond_timedwait.3p.html)

### Use of AI
Claude (Anthropic) was used throughout this project as a learning and debugging assistant. Specifically:
- To understand and implement the min-heap priority queue used for FIFO and EDF scheduling
- To debug synchronization issues in `take_one_dongle`, particularly around `pthread_cond_timedwait` and cooldown handling
- To understand the difference between `pthread_cond_wait` and `pthread_cond_timedwait` and why a timeout was necessary
- To review the overall thread architecture and identify potential race conditions
- To prepare for the evaluation by explaining concepts such as deadlock, starvation, race conditions, and the sift-down algorithm