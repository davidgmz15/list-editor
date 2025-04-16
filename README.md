List & TextBuffer Editor Project
-----------------------------------
This project implements a doubly‑linked, double‑ended List<T> and a TextBuffer class that together form 
the core of a simple text editor. You can switch between using the custom List<T> or std::list<char> by 
adjusting the aliases in TextBuffer.hpp.

**Features**

Custom List implementation (List.hpp)
- Doubly‑linked, double‑ended list with O(1) front/back insertion and removal
- Bidirectional Iterator supporting ++, --, *, ->, ==, and !=
- Constant‐time size() via internal counter

TextBuffer (TextBuffer.hpp / TextBuffer.cpp)
- Cursor with position tracking (row, column, index)
- insert(char), remove(), forward(), backward()
- Line‐oriented movements: move_to_row_start(), move_to_row_end(), move_to_column(int)
- Vertical navigation: up(), down()
- stringify() to retrieve full buffer contents as a std::string

Getting Started

Prerequisites
- C++11 (or later) compiler (e.g. g++, clang++)
- Make (optional)

Build Instructions
- A simple g++ command:

# Compile List tests
g++ -std=c++11 -Wall -Werror -I. ListTests.cpp -o list_tests

# Compile TextBuffer tests
g++ -std=c++11 -Wall -Werror -I. TextBufferTests.cpp TextBuffer.cpp -o textbuffer_tests

Alternatively, create a Makefile with targets list_tests and textbuffer_tests.

Running Tests

./list_tests
./textbuffer_tests

All unit tests are written with unit_test_framework.hpp.

Usage
In your editor application, include TextBuffer.hpp:

#include "TextBuffer.hpp"

int main() {
    TextBuffer buffer;
    buffer.insert('H');
    buffer.insert('i');
    buffer.insert('\n');
    buffer.insert('!');
    std::cout << buffer.stringify(); // prints "Hi\n!"
}

File Structure

├── List.hpp               # Custom doubly-linked list
├── TextBuffer.hpp         # TextBuffer class declaration
├── TextBuffer.cpp         # TextBuffer implementation
├── unit_test_framework.hpp# Simple unit test harness
├── ListTests.cpp          # Unit tests for List<T>
└── TextBufferTests.cpp    # Unit tests for TextBuffer

Switching to std::list

By default, TextBuffer.hpp uses using CharList = std::list<char>;. To switch to List<char>, uncomment:

// using CharList = List<char>;
// using Iterator = List<char>::Iterator;

and comment out the std::list aliases.

Contributing

Please fork the repository, make your changes, and submit a pull request. Ensure all tests pass with -Wall -Werror enabled.

License

This project is released under the MIT License. Feel free to use and modify as needed.

