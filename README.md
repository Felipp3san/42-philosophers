# Philosophers

A multithreaded simulation of the **Dining Philosophers Problem** in C, built as part of the 42 School curriculum. This project explores concurrency, synchronization, and deadlock prevention using threads and mutexes.

## Features

- **Simulates multiple philosophers** sitting at a table
- **Philosophers can think, eat, and sleep** in cycles
- **Uses mutexes** to control access to forks
- **Prevents deadlocks** and starvation
- **Time tracking** for precise action simulation
- **Command-line arguments** for number of philosophers, times, and cycles

## Tech Stack

- **C** – Core language
- **POSIX Threads (pthread)** – For multithreading
- **Mutexes** – For synchronization
- **Makefile** – Build and manage project

## Installation

1. Clone the repository:

```bash
git clone https://github.com/Felipp3san/philosophers.git
cd philosophers
```

2. Compile the project:

```bash
make
```

3. Run the executable with arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```bash
./philo 5 800 200 200 7
```

## Usage

- **Arguments:**
  - `number_of_philosophers` – total philosophers at the table
  - `time_to_die` – max time (ms) before a philosopher dies without eating
  - `time_to_eat` – time (ms) a philosopher spends eating
  - `time_to_sleep` – time (ms) a philosopher spends sleeping
  - `number_of_times_each_philosopher_must_eat` (optional) – how many times each philosopher must eat

- **Observe philosopher actions:** thinking, taking forks, eating, sleeping
- **Program terminates** when all philosophers have eaten enough or a philosopher dies

## Compilation

- Build the executable:

```bash
make
```

- Remove object files:

```bash
make clean
```

- Remove all binaries and rebuild:

```bash
make re
```


## License

Educational project under 42 School academic policy.
