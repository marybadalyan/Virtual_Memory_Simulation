Thanks for the heads-up! The updated README content with your program explanation is here:

---

# Virtual vs Physical Memory Explained

## 📌 What is Physical Memory?

**Physical Memory (RAM)** is the actual hardware memory installed in your machine. It consists of DRAM chips that store data and instructions currently in use. Examples:

* 8 GB, 16 GB, or 32 GB RAM modules.
* Very fast, directly accessed by the CPU.
* Limited in size.

## 📌 What is Virtual Memory?

**Virtual Memory** is an abstraction provided by the operating system to give each program the illusion of a large, continuous block of memory, even if physical RAM is limited.

* Programs operate within **virtual address spaces**.
* Virtual addresses are translated to physical addresses by the OS and hardware (MMU).
* Enables features like process isolation, memory overcommitment, and swapping.

## 📌 What Are Page Tables?

**Page Tables** are data structures used by the OS and CPU to map virtual addresses to physical addresses.

* Managed by the **Memory Management Unit (MMU)**.
* Translate **virtual pages** to **physical page frames**.
* Usually hierarchical (e.g., 4-level page tables in x86\_64).
* Support **paging** and efficient memory mapping.

### Example:

```
Virtual Address (0x7ffde1234000)
 → Page Table Lookup
 → Physical Frame (e.g., 0x1a334000 in RAM)
```

## 📌 Pages vs Page Frames

| Concept              | Virtual Memory (Pages)                  | Physical Memory (Page Frames) |
| -------------------- | --------------------------------------- | ----------------------------- |
| **Definition**       | Divisions of virtual address space      | Divisions of physical RAM     |
| **User Perspective** | Programs see virtual pages              | OS & hardware manage frames   |
| **Size**             | 4 KB (common), or hugepages (2MB, 1GB)  | Same size as pages            |
| **Purpose**          | Simplify programming, process isolation | Efficient RAM management      |

## 📌 How They Interact

* The OS **splits virtual memory into pages** and **physical memory into frames**.
* **Page tables map virtual pages to physical frames**.
* The **MMU handles the translation dynamically**.
* Programs never directly see physical addresses.

### Visual Summary:

```
[Virtual Address Space (Pages)]
     ↓ Page Tables
[Physical Memory (Page Frames)]
```

## 📌 Why It Matters

* Programs get **process isolation** and **large address spaces**.
* The OS can **move memory** around without the program knowing.
* Efficient use of RAM with **paging**, **swapping**, and **caching**.
* Tools like `pmap`, `vmmap`, or `/proc/self/maps` help visualize memory usage.

## 📌 Example Program Explanation

The following C++ program demonstrates the effects of virtual memory, page faults, and the impact of memory access patterns:

### Key Features of the Program:

* **Allocates 32GB of virtual memory** using `malloc()`.
* **Sequential write and read** of the allocated memory to measure performance.
* **Random read** to showcase how random access causes different memory access patterns, affecting performance.
* **Touches every 4KB page** to ensure pages are committed and page faults are triggered.
* **Reports page fault statistics** (minor/major faults on Linux, total page faults and swap usage on Windows).

### Purpose:

* Show how the program can allocate more memory than physical RAM using virtual memory.
* Measure **sequential vs. random access performance**.
* Observe **page faults** when memory usage exceeds available RAM, leading to swapping.

This example helps visualize how **virtual pages are mapped to physical frames**, how **page faults** occur, and how **access patterns** (sequential vs random) impact performance and swapping.


---

## Build & Run Instructions  

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/main 
```

## Example output

```
Sequential read duration: 100 nanoseconds
Random read duration: 100 nanoseconds
Page Fault Count: 1140
Amount of virtual memory backed by swap: 1122304
```


## ✅ Summary Checklist:

* [x] **Physical Memory** = Real RAM.
* [x] **Virtual Memory** = OS abstraction.
* [x] **Page Tables** = Mapping mechanism.
* [x] **Pages** = Virtual memory chunks.
* [x] **Page Frames** = Physical RAM chunks.
* [x] **MMU** handles translation transparently.
* [x] **Example program** demonstrates real-world behavior of paging and page faults.