# 📚 Philosophers - 42 Campus Project

The philosophers project, part of the 42 Campus curriculum, is an exploration of multithreading and synchronization in programming. This repository does not include the bonus part of the project, it's focused on the primary problem statement.

## 🎯 Project Goals

The goal is to simulate the behavior of a number of philosophers sitting at a round table, doing one of three things: eating, sleeping, or thinking. The philosophers share a finite number of forks and they need two forks to eat. They can't do anything else while they're eating. If a philosopher doesn't eat within a certain amount of time, they die.

The project aims to teach the following:

- Understanding of threads and how they work
- Understanding of mutexes and their utilization
- To avoid common pitfalls in synchronization like deadlock and race conditions

## 📜 Problem Statement

- There are a number of philosophers sitting at a round table doing one of three things: eating, sleeping, or thinking.
- The philosophers need two forks to eat.
- If a philosopher doesn't start eating `time_to_die` milliseconds after the start of their last meal or the beginning of the simulation, they die.
- Each philosopher is assigned a number from 1 to `number_of_philosophers`. Philosopher 1 sits next to philosopher `number_of_philosophers`. Any other philosopher N will sit between philosopher N - 1 and philosopher N + 1.
- The simulation stops when a philosopher dies or when each philosopher has eaten at least `number_of_times_each_philosopher_must_eat` times.

## 🧠 Understanding Race Conditions

A race condition is a situation in a multi-threaded or concurrent environment where the outcome of the operation depends on the relative order or timing in which threads are scheduled. This leads to erroneous and unpredictable results, as the same operation can have different outcomes based on the sequence of execution.

To avoid race conditions, synchronization techniques like mutexes are used. These ensure that only one thread can access shared data at a given time, hence preventing concurrent access and modification.

## 👨‍🏫 Test with checker

## Installation

```Bash
git clone https://github.com/MichelleJiam/LazyPhilosophersTester.git
```

## Example:
./test.sh - the LazyPhilosophersTester executable file.
../philos - the Philosophers executable file

```bash
./test.sh ../philo
```



## 🔗 Useful Links

- [LazyPhilosophersTester](https://github.com/MichelleJiam/LazyPhilosophersTester) - A semi-automatic tester for checking this project.
- [TommyJD93's Philosophers Guide](https://github.com/TommyJD93/Philosophers) - A comprehensive guide on how to approach this project.
