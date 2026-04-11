# Newegg Stock Alerter

A C++ program that monitors a Newegg product page and alerts you when an item is in stock.

## What it does
- Fetches a Newegg product page using libcurl
- Searches the HTML for stock availability
- Prints whether the item is in stock or not

## Dependencies
- [libcurl](https://curl.se/libcurl/)
- MinGW / MSYS2 (Windows)

## How to compile
```bash
g++ main.cpp -IC:\vcpkg\installed\x64-mingw-dynamic\include -LC:\vcpkg\installed\x64-mingw-dynamic\lib -lcurl -o prog
```

## How to run
```bash
./prog
```

## Work in progress
- [X] Auto-repeat checking on an interval
- [X] Sound/desktop alert when item comes in stock
- [ ] Support for multiple items
