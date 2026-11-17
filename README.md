# Prime Numbers with Threads (pthreads)

Assignment for the **Operating Systems** course, IFRS Campus Canoas, 2026/1.
Professor: Gustavo Neuberger.
Student: *[your name here]*

## About

A C program that uses the **pthreads** library to find which numbers from **1 to N** are prime. The work is split among **T threads** running in parallel.

- At startup, the user enters how many numbers to check (**N**) and how many threads to create (**T**).
- Each thread takes the next available number, checks whether it is prime, and prints the result along with its ID.
- At the end, the main program prints the total number of primes found.

## How it works

### Shared variables

| Variable | Purpose |
|---|---|
| `proximo` | The next number to be processed by the next available thread |
| `totalPrimos` | The total number of primes found |
| `mutex` | Ensures only one thread at a time accesses the variables above |

### Synchronization

Since all threads access `proximo` and `totalPrimos`, access to these variables is protected by a **mutex** (`pthread_mutex_lock` / `pthread_mutex_unlock`). This prevents **race conditions**, such as two threads processing the same number or an increment being lost from the total.

The code has two **critical sections**:

1. Taking the next number and incrementing `proximo`.
2. Incrementing `totalPrimos` when a prime is found.

The primality test runs **outside** the mutex, so the threads actually work in parallel.

### Program flow

1. `main` reads N and T, allocates the arrays, and initializes the mutex.
2. It creates T threads with `pthread_create`, passing each one its ID (0, 1, 2…).
3. Each thread runs the `trabalho` function in a loop until there are no numbers left.
4. `main` waits for all threads to finish with `pthread_join`.
5. `main` prints the total number of primes, frees the memory, and destroys the mutex.

### Primality check

The `isPrimo` function tests divisors from 2 up to the square root of n (`i * i <= n`). If a divisor is found, the number is not prime.

## Building and running

### Dev-C++

1. Open the `.c` file in Dev-C++.
2. Go to **Tools → Compiler Options**.
3. Check **"Add the following commands when calling the linker"** and type `-lpthread`.
4. Press **F11** to compile and run.

> If you get an error saying `pthread.h` was not found, use **Embarcadero Dev-C++**, which includes pthreads support.

### Terminal (GCC)

```bash
gcc primos_threads.c -o primos -lpthread
./primos
```

## Sample run

The program's messages are in Portuguese.

```
Digite a quantidade de números a processar: 10
Digite a quantidade de threads a criar: 3
Thread 0: O numero 1 nao é primo
Thread 1: O numero 2 é primo
Thread 2: O numero 3 é primo
Thread 0: O numero 4 nao é primo
Thread 1: O numero 5 é primo
Thread 2: O numero 6 nao é primo
Thread 0: O numero 7 é primo
Thread 1: O numero 8 nao é primo
Thread 2: O numero 9 nao é primo
Thread 0: O numero 10 nao é primo
O número total de números primos encontrados foi: 4
```

> The order of the messages may change on every run, because the operating system's scheduler decides which thread runs at each moment. The **total number of primes is always the same**.

## Concepts covered

- **Threads**: multiple execution flows inside the same process, sharing its memory.
- **Critical section**: code that accesses shared data.
- **Mutual exclusion (mutex)**: ensures only one thread at a time runs a critical section.
- **Race condition**: the error the mutex prevents.
- **pthread_join**: makes the main program wait for the threads to finish.
