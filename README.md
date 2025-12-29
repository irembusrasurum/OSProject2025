# OSProject2025

# Parallel Sorting Farm (Multithreaded Programming Project)

## Project Overview
This project is a multithreaded sorting application developed for the Operating Systems course.  
The goal of the project is to demonstrate the use of threads, synchronization mechanisms, and shared memory while avoiding race conditions and measuring performance.

The application divides a large array into smaller parts and sorts them concurrently using multiple threads.

---

## Features
- Uses multiple threads to perform parallel sorting
- Demonstrates shared memory usage
- Prevents race conditions using a mutex
- Measures execution time of the parallel algorithm
- Simple and clear design focused on OS concepts

---

## Technologies Used
- C Programming Language
- POSIX Threads (pthreads)
- Mutex for synchronization

---

## Thread Design
- **Number of threads:** 4  
- Each thread is responsible for sorting a distinct portion of the array.
- Threads operate concurrently to improve performance.

---

## Synchronization Mechanism
A mutex is used to protect a shared variable (`total_swaps`) that counts the total number of swap operations performed by all threads.

This prevents race conditions when multiple threads attempt to update the shared variable simultaneously.

---

## How the Program Works
1. A global array is filled with random numbers.
2. The array is divided into equal-sized chunks.
3. Each thread sorts its assigned portion of the array.
4. A mutex ensures safe access to shared data.
5. Execution time is measured and displayed.

---

## Compilation and Execution

### Compile
```bash
gcc main.c -o sort -lpthread
