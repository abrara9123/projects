# Newegg Stock Alerter

A C++ program that monitors a Newegg product page and alerts you when an item is in stock.

## What it does
- Fetches a Newegg product page using libcurl
- Searches the HTML for stock availability
- Checks stock status every 60 seconds automatically
- Plays a sound alert when stock status changes
- Opens a terminal popup when item comes in stock
- Logs all status changes with timestamps to `newegg_log.txt`

## Dependencies
- [libcurl](https://curl.se/libcurl/)
- MinGW / MSYS2 (Windows)

## How to compile
```bash
make
```
Or manually:
```bash
g++ main.cpp -IC:\vcpkg\installed\x64-mingw-dynamic\include -LC:\vcpkg\installed\x64-mingw-dynamic\lib -lcurl -o prog
```

## How to run
```bash
./prog
```

## Work in progress
- [x] Auto-repeat checking on an interval
- [x] Sound alert when item comes in stock
- [x] Terminal popup alert
- [x] Timestamp logging to file
- [ ] Support for multiple items
- [ ] Email alert
- [ ] Error handling for connection failures
