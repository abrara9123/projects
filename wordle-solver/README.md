# Wordle Solver — BSTSet

A C++ application that recommends optimal Wordle guesses using a custom-built Binary Search Tree (BST) set data structure.

## Overview

This project has two components:
- **BSTSet** — a templated binary search tree implementing the set ADT from scratch
- **Wordle Recommender** — an application built on top of BSTSet that filters and ranks possible Wordle words based on guess patterns

## Features

- Templated BST supporting insert, search, removal, and in-order traversal
- Parent-pointer tracking for efficient tree navigation
- Iterator support via `begin()` and `next()` for sequential access
- Wordle pattern matching engine that eliminates invalid words after each guess
- Word recommender that suggests the best next guess from remaining candidates
- Fully memory-safe — no leaks, verified with AddressSanitizer and Valgrind

## How to Run

### Build & Test
```bash
make bstset_tests
make test_bst_all
```

### Run the Wordle Recommender (CLI)
```bash
make wordle_main
make run_wordle
```

### Run the Wordle Recommender (Web App)
```bash
make wordle_server
make run_server
```

## Project Structure

```
bstset/
├── bstset.h          # Templated BST implementation
├── bstset_tests.cpp  # Unit tests
├── wordle.cpp        # Wordle recommender logic
├── wordle_main.cpp   # CLI entry point
└── Makefile
```

## Technologies

C++ · Binary Search Trees · Templates · AddressSanitizer · Valgrind · Make
