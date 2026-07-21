# Mini Programming Language Compiler

<<<<<<< HEAD
A compiler front-end for a custom programming language developed for the **Compiler Construction Lab** at **Metropolitan University, Bangladesh**.

The project implements the core stages of a compiler, including lexical analysis, syntax analysis, semantic analysis, Abstract Syntax Tree (AST) construction, symbol table management, and Three Address Code (TAC) generation. A lightweight Django-based web interface is included for interactive code compilation and testing.

## ✨ Features

- **Lexical Analysis (Flex):** Tokenizes source code into keywords, identifiers, constants, operators, and delimiters while ignoring comments and whitespace.
- **Syntax Analysis (Bison):** Validates program structure using a Context-Free Grammar (CFG).
- **Abstract Syntax Tree (AST):** Builds a hierarchical representation of the parsed program.
- **Symbol Table & Scope Management:** Supports nested scopes and tracks variable declarations and data types (`int`, `float`, `bool`).
- **Semantic Analysis:** Detects undeclared variables, redeclarations, and type mismatches.
- **Three Address Code (TAC):** Generates intermediate code for valid programs.
- **Django Web Interface:** Provides a browser-based editor to compile source code and display compiler output in real time.

## 🛠 Prerequisites

- GCC
- Flex
- Bison
- Make
- Python 3
- Django

## 🚀 Build & Run

### Compile the Compiler

```bash
make clean
make
```

### Run the Web Interface

```bash
cd webapp
python manage.py runserver
```

Open your browser and visit:

```text
http://localhost:8000
```

### Run from the Terminal

```bash
./my_compiler tests/sample_program.txt
```

## 📁 Project Structure

```text
project-root/
├── src/
│   ├── lexer/
│   ├── parser/
│   ├── ast/
│   ├── semantic/
│   └── symbol_table/
├── webapp/
├── docs/
├── tests/
├── examples/
├── Makefile
└── README.md
```

=======
### A Mini Compiler for a Simplified Statically-Typed Language using Flex & Bison

**Course:** Compiler Construction Lab  
**Department:** Computer Science and Engineering  
**University:** Metropolitan University, Sylhet, Bangladesh

---

# Project Goal

Syntax Studio is a mini compiler developed using **Flex** and **Bison**. It implements the complete front-end of a compiler, including lexical analysis, syntax analysis, abstract syntax tree (AST) construction, semantic analysis, and Three Address Code (TAC) generation.

The project follows the compiler design principles taught in the Compiler Construction Lab course.

---

# Team

## Nazmul Hasan

Primary Responsibilities

- Project Foundation & Architecture
- Build System (Makefile)
- Lexical Analyzer (Flex)
- Syntax Analyzer (Bison)
- Abstract Syntax Tree (AST)
- Module Integration

---

## Mahdi Hasan Mehedi

Primary Responsibilities

- Symbol Table
- Semantic Analysis
- Type Checking
- Three Address Code (TAC) Generation

---

# Compiler Pipeline

```
Source Program
      │
      ▼
Lexical Analyzer (Flex)
      │
      ▼
Syntax Analyzer (Bison)
      │
      ▼
Abstract Syntax Tree (AST)
      │
      ▼
Semantic Analysis
      │
      ▼
Three Address Code (TAC)
```

---

# Supported Language Features

## Data Types

- int
- float
- bool

## Statements

- Variable Declaration
- Assignment
- Arithmetic Expressions
- Relational Expressions
- Logical Expressions
- if
- if-else
- while
- print

## Operators

### Arithmetic

```
+  -  *  /  %
```

### Relational

```
<  >  <=  >=  ==  !=
```

### Logical

```
&&  ||  !
```

## Other Features

- Nested Blocks `{ ... }`
- Proper Scope Handling
- Single-line Comments (`//`)
- Multi-line Comments (`/* ... */`)

---

# Project Structure

```
syntax-studio/
│
├── src/
│   ├── lexer/
│   ├── parser/
│   ├── ast/
│   ├── symbol_table/
│   ├── semantic/
│   ├── codegen/
│   └── main.c
│
├── tests/
│   ├── valid/
│   └── invalid/
│
├── examples/
│
├── docs/
│   ├── report/
│   └── images/
│
├── Makefile
├── README.md
└── LICENSE
```

---

# Requirements

- Ubuntu / Linux / WSL2
- GCC
- Flex
- Bison
- Make
- Git

Install dependencies:

```bash
sudo apt update
sudo apt install -y build-essential flex bison make git
```

---

# Build

```bash
make
```

Clean and rebuild:

```bash
make clean
make
```

---

# Run

```bash
./compiler
```

Later, the compiler will also support:

```bash
./compiler examples/sample.src
```

---

# Development Status

| Module | Status |
|---------|--------|
| Project Structure | ✅ Completed |
| Build System | ✅ Completed |
| Lexer | 🔄 In Progress |
| Parser | ⏳ Pending |
| AST | ⏳ Pending |
| Symbol Table | ⏳ Pending |
| Semantic Analysis | ⏳ Pending |
| TAC Generation | ⏳ Pending |
| Testing | ⏳ Pending |
| Documentation | ⏳ Pending |

---

# Technologies Used

- C
- Flex
- GNU Bison
- GCC
- Make
- Git
- Ubuntu (WSL2)

---

# Learning Objectives

This project demonstrates the implementation of the major phases of a compiler:

- Lexical Analysis
- Syntax Analysis
- Abstract Syntax Tree Construction
- Symbol Table Management
- Semantic Analysis
- Intermediate Code Generation (Three Address Code)

---

# License

This project was developed as part of the **Compiler Construction Lab** course at **Metropolitan University, Sylhet**.
>>>>>>> e0594bc (Improve project documentation)
