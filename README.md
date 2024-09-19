# BigInt - C++ Implementation for Large Integer Arithmetic

## Overview

**BigInt** is a custom C++ class designed to handle and perform arithmetic operations on large integers that exceed the standard data types' limits in C/C++. This implementation supports a variety of arithmetic operations, string manipulation, and is designed with efficiency and flexibility in mind.

## Features

- **Custom Data Type**: Manage integers of arbitrary size using the `BigInt` class.
- **Operator Overloading**: Natural syntax for arithmetic operations (`+`, `-`, `*`, `/`, `%`, etc.).
- **Exception Handling**: Basic error handling for invalid operations.
- **String Conversion**: Seamless conversion between `BigInt` and string representations.
- **Efficient Arithmetic Algorithms**: Implemented to ensure performance for operations on large numbers.

## Tools and Technologies Used

### C++ Standard Library:
- **`#include <iostream>`**: For input and output operations via `cin` and `cout`.
- **`#include <vector>`**: Manages dynamic arrays, especially for handling the digits of the `BigInt`.
- **`#include <string>`**: Provides support for string manipulation, used for representing and manipulating large numbers as strings.
- **`#include <cstring>`**: Supports operations on C-style strings (used in one of the constructors).

### Object-Oriented Programming (OOP):
- **Class `BigInt`**: Encapsulates data and methods for managing large integers, leveraging OOP principles for data abstraction, encapsulation, and reusability.

### Operator Overloading:
- Overloaded operators for arithmetic and comparison (`+`, `-`, `*`, `/`, `%`, `++`, `--`, `==`, `!=`, `<`, `>`, `<=`, `>=`, `+=`, `-=`, `*=`, `/=`, `%=`, `^=`, `<<`, `>>`).

### Standard Template Library (STL) Containers:
- **`std::vector<int>`**: Used for dynamic arrays to store digits of the large integers.

### String Manipulation:
- Conversion between strings and `BigInt` objects.
- Efficient handling of digits stored in reverse order for arithmetic operations.

### Arithmetic Algorithms:
- Basic operations: addition, subtraction, multiplication, division, modulo.
- Additional operations: power calculation, square root computation, factorial calculation.

### Exception Handling:
- Simple error handling via `throw` statements for invalid operations like division by zero.

## Getting Started

### Prerequisites
- A C++ compiler (GCC, Clang, MSVC, etc.)
- Basic understanding of C++ programming and OOP concepts

### Compilation
To compile the `BigInt` class, use the following command in your terminal:

```bash
g++ -o BigInt BigInt.cpp
