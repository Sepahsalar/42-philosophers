# 42 Philosophers

This repository contains the "Philosophers" project from the 42 school curriculum, which explores concurrent programming concepts through the classic Dining Philosophers Problem.

---

## Table of Contents

1. [Introduction](#introduction)
2. [Installation](#installation)
3. [Usage](#usage)
4. [Project Structure](#project-structure)
5. [License](#license)

---

## Introduction

The Dining Philosophers Problem is a classic synchronization problem that illustrates challenges in concurrent algorithm design. It involves philosophers sitting at a table, each needing two forks to eat. The problem demonstrates issues like deadlock and resource starvation. This project aims to provide a solution using multithreading and synchronization mechanisms.

---

## Installation

1. **Clone the Repository**

	```bash
	git clone https://github.com/Sepahsalar/42-philosophers.git
	```

2. **Navigate to the Project Directory**

	```bash
	cd 42-philosophers
	```

3. **Compile the Program**

	```bash
	make
	```

---

## **Usage**

After compilation, run the program with the following syntax:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

**Parameters**:

- `number_of_philosophers`: Total number of philosophers and forks.
- `time_to_die`: Time in milliseconds a philosopher can go without eating before dying.
- `time_to_eat`: Time in milliseconds a philosopher takes to eat.
- `time_to_sleep`: Time in milliseconds a philosopher spends sleeping.
- `number_of_times_each_philosopher_must_eat` (optional): If specified, the simulation stops after each philosopher has eaten at least this many times.

**Examples**:

```bash
# Example 1: Run with 5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep
./philo 5 800 200 200

# Example 2: Run with 4 philosophers, 410ms to die, 200ms to eat, 200ms to sleep, each must eat at least 7 times
./philo 4 410 200 200 7
```

---

## **Project Structure**
The project is structured as follows:

```bash
42-philosophers/
├── src/            # Source code files
├── includes/       # Header files
├── Makefile        # Build configuration
├── README.md       # Project documentation
└── LICENSE         # License information
```

---

## **License**
This project is licensed under the MIT License. See the [License](https://github.com/Sepahsalar/42-philosophers/blob/main/LICENSE) file for details.
