# 📚 Philosophers

> This repository contains a "Philosophers" project that is part of the École 42 curriculum.

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
## 🏎 Test Data Races

- [Data Races Guide](https://github.com/MichelleJiam/LazyPhilosophersTester)
you can use this flag to check data races
```bash
gcc -fsanitize=thread -g3
```

## 🤯 Project Evaluation

## Introduction

Please comply with the following rules:
Remain polite, courteous, respectful and constructive throughout the
evaluation process. The well-being of the community depends on it.

Identify with the student or group whose work is evaluated the possible
dysfunctions in their project. Take the time to discuss and debate the
problems that may have been identified.

You must consider that there might be some differences in how your peers
might have understood the project's instructions and the scope of its
functionalities. Always keep an open mind and grade them as honestly as
possible. The pedagogy is useful only and only if the peer-evaluation is
done seriously.

## Guidelines

Only grade the work that was turned in the Git repository of the evaluated
student or group.

Double-check that the Git repository belongs to the student(s). Ensure that
the project is the one expected. Also, check that 'git clone' is used in an
empty folder.

Check carefully that no malicious aliases was used to fool you and make you
evaluate something that is not the content of the official repository.

To avoid any surprises and if applicable, review together any scripts used
to facilitate the grading (scripts for testing or automation).

If you have not completed the assignment you are going to evaluate, you have
to read the entire subject prior to starting the evaluation process.

Use the available flags to report an empty repository, a non-functioning
program, a Norm error, cheating, and so forth.
In these cases, the evaluation process ends and the final grade is O,
or -42 in case of cheating. However, except for cheating, student are
strongly encouraged to review together the work that was turned in, in order
to identify any mistakes that shouldn't be repeated in the future.

Remember that for the duration of the defense, no segfault, no other
unexpected, premature, uncontrolled or unexpected termination of the
program, else the final grade is O. Use the appropriate flag.
You should never have to edit any file except the configuration file if it
exists. If you want to edit a file, take the time to explicit the reasons
with the evaluated student and make sure both of you are okay with this.

You must verify the absence of data races.
You are allowed to use any of the different tools available on the computer,
such as valgrind with "--tool helgrind" and "--tool=drd". In case of any
data-race, the evaluation stops here.

You must also verify the absence of memory leaks. Any memory allocated on
the heap must be properly freed before the end of execution. You are
allowed to use any of the different tools available on the computer, such
as leaks, valgrind, or e_fence. In case of memory leaks, tick the
appropriate flag.

## Mandatory Part

**Error Handling:**

This project is to be coded in C, following the Norm.
Any crash, undefined behavior, memory leak, or norm error means O to
the project.
On some slow hardware, the project might not work properly. If some tests
don't work on your machine try to discuss it honestly before counting it
as false.

**Global variables:**

Check if there is any global variable which is used to manage the shared
resources among the philosophers.
If you find such a nasty thing, the evaluation stops here. You can go on
and check the code, but do not grade the exercises.

**philo code:**

Ensure the code of philo complies with the following requirements and ask for explanations.

Check there is one thread per philosopher.

Check there is only one fork per philosopher.

Check if there is a mutex per fork and that it's used to check the fork value and/or change it.

Check the outputs are never mixed up.

Check how the death of a philosopher is verified and if there is a mutex to prevent a philosopher from dying and starting eating at the same time.

**philo testing:**

Do not test with more than 200 philosophers.

Do not test with time_to_die or time_to_eat or time_to_sleep set to values lower than 60 ms.

Test 1 800 200 200. The philosopher should not eat and should die.

Test 5 800 200 200. No philosopher should die.

Test 5 800 200 200 7 . No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.

Test 4 410 200 200. No philosopher should die.

Test 4 310 200 100. One philosopher should die.

Test with 2 philosophers and check the different times: a death delayed by more than 10 ms is unacceptable.

Test with any values of your choice to verify all the requirements. Ensure philosophers die at the right time,that they don't steal forks, and so forth.

## 🔗 Useful Links

- [LazyPhilosophersTester](https://github.com/MichelleJiam/LazyPhilosophersTester) - A semi-automatic tester for checking this project.
- [TommyJD93's Philosophers Guide](https://github.com/TommyJD93/Philosophers) - A comprehensive guide on how to approach this project.
