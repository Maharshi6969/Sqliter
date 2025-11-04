# SQLiter

### A Lightweight SQLite Clone Built From Scratch in C

---

## Overview

**SQLiter** is a fully functional, lightweight relational database engine written in C, designed as a from-scratch clone of SQLite.
It implements core database components such as paging, B-tree indexing, serialization, and persistent file storage — all without external libraries.
This project was built for learning low-level database internals and exploring how real databases like SQLite manage data structures, disk I/O, and queries.

---

## Features

* **Custom Pager System** — Handles reading and writing fixed-size pages to disk.
* **B-Tree Storage Engine** — Implements leaf and internal nodes for efficient data lookup.
* **Row Serialization** — Translates rows between in-memory and on-disk formats.
* **Meta Commands** — Includes debugging tools like `.btree` and `.constants`.
* **REPL Interface** — Simple terminal interface for inserting and selecting data.
* **Persistent Storage** — All data is stored in a binary file (`*.db`).

---

## Current Commands

### SQL Commands

| Command                          | Description                            |
| -------------------------------- | -------------------------------------- |
| `insert <id> <username> <email>` | Inserts a new record into the database |
| `select`                         | Displays all stored records            |

### Meta Commands

| Command      | Description                                      |
| ------------ | ------------------------------------------------ |
| `.btree`     | Prints the current B-tree structure              |
| `.constants` | Displays internal memory and page constants      |
| `.exit`      | Safely closes the database and exits the program |

---

## Example Usage

```bash
$ gcc main.c -o sqliter
$ ./sqliter mydata.db

mydata > insert 1 alice alice@mail.com
Executed.
mydata > insert 2 bob bob@mail.com
Executed.
mydata > select
(1, alice, alice@mail.com)
(2, bob, bob@mail.com)
mydata > .btree
- leaf (size 2)
  - 1
  - 2
mydata > .exit
```

---

## Project Structure

| File                    | Description                                   |
| ----------------------- | --------------------------------------------- |
| `main.c`                | Core implementation of SQLiter                |
| `test.db`               | Example database file generated after running |
| `Makefile` *(optional)* | Can be added to simplify compilation          |

---

## Technical Highlights

* **Page-based storage:** Each page is 4096 bytes, mimicking SQLite’s pager.
* **B+ Tree implementation:** Uses internal nodes for indexing and leaf nodes for storing data.
* **Binary Search:** Efficient key lookups within leaf nodes.
* **File-backed persistence:** Changes are written directly to the `.db` file.
* **Dynamic Splitting:** Automatically handles leaf and internal node splits when full.

---

## Future Plans

* Support for **DDL commands** (`CREATE TABLE`, `DROP TABLE`, etc.)
* Add **UPDATE** and **DELETE** statements.
* Implement **multiple table support**.
* Develop a **Python-based TUI** for visual interaction.

---

## Build Instructions

1. Clone the repository

   ```bash
   git clone https://github.com/yourusername/sqliter.git
   cd sqliter
   ```
2. Compile

   ```bash
   gcc main.c pager.c btree.c table.c parser.c executor.c layout.c -o main
   ```
3. Run

   ```bash
   ./main mydata.db
   ```

---

## Notes

* SQLiter currently supports a single table model for simplicity.
* The prompt automatically removes the `.db` extension giving a smooth experience.
* This project is intended for **educational purposes** and **database engine experimentation**.

---

