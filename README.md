# Philosophers 🧠🍝

A concurrent programming project written in **C**, developed as part of the 42 curriculum.
The goal is to simulate the **Dining Philosophers Problem**, a classic exercise in concurrency and synchronization.

This project focuses on managing **multiple threads**, ensuring **data integrity**, and preventing **deadlocks** and **race conditions** through careful use of mutexes and timing control.

## 🔧 Features

* Simulation of the *Dining Philosophers Problem* using **POSIX threads (pthreads)**
* Fine-grained control of **mutexes** for shared resource protection
* Deadlock prevention and starvation handling
* Precise **timing and synchronization** logic for concurrent actions
* Custom logging system for thread-safe output

## 🧠 Key Learnings

Through this project, I gained experience in:

* **Multithreading and synchronization** in C
* Detecting and avoiding **race conditions** and **deadlocks**
* Working with **mutexes** and **conditional timing**
* Designing efficient concurrent simulations

## 🚀 How to Run

```bash
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [optional_number_of_meals]
```

Example:

```bash
./philo 5 800 200 200
```

## 📚 Technologies

* Language: **C**
* Libraries: **pthread**, **time.h**
* Tools: **Makefile**, **Git**

The Philosophers project was an in-depth exploration of **parallelism and synchronization**, teaching how to build reliable, efficient concurrent systems that behave deterministically even under high contention.
