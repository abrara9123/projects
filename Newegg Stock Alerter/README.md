# Newegg Stock Alerter

A C++ program that monitors multiple Newegg product pages simultaneously and alerts you when an item comes in stock.

## What it does
- Fetches multiple Newegg product pages simultaneously using libcurl
- Searches the HTML for stock availability
- Checks stock status every 60 seconds automatically
- Uses multithreading to monitor multiple items at the same time
- Uses mutex locks to prevent race conditions between threads
- Plays a sound alert when stock status changes
- Opens a terminal popup when item comes in stock
- Logs all status changes with timestamps to `newegg_log.txt`

## Project Structure
- `main.cpp` — entry point, URL list and thread management
- `checker.hpp` — curl logic and stock checking loop
- `alerts.hpp` — sound and terminal popup alerts
- `logger.hpp` — timestamp generation and file logging

## Dependencies
- [libcurl](https://curl.se/libcurl/)
- MinGW / MSYS2 (Windows)

## How to compile and run
```bash
# Build and run in one command
make run

# Build only
make

# Clean compiled files
make clean
```

Or manually:
```bash
g++ main.cpp -IC:\vcpkg\installed\x64-mingw-dynamic\include -LC:\vcpkg\installed\x64-mingw-dynamic\lib -lcurl -o prog
./prog
```

## Work in progress
- [x] Auto-repeat checking on an interval
- [x] Sound alert when item comes in stock
- [x] Terminal popup alert
- [x] Timestamp logging to file
- [x] Support for multiple items
- [x] Multithreading with mutex locks
- [x] Modular code structure with header files
- [ ] Email alert
- [ ] Error handling for connection failures
- [ ] Deploy to cloud to run 24/7
