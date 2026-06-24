# My Budget

A modern C++ personal finance management application designed with clean architecture principles, testability, and future scalability in mind.

## Overview

Spending Manager is a personal budgeting and expense tracking system written in **C++17**. The project aims to help users manage their finances by tracking income and expenses, organizing transactions into categories, defining budgets, and generating financial summaries.

The application follows a layered architecture with clear separation of concerns between:

* Models
* Services
* Repositories
* Validators
* Session management
* Unit tests

The project is currently in the early development stage, with authentication and core domain models already implemented.

---

## Current Features

### User Management

* User registration
* User login
* Session management
* Login and password validation
* Duplicate account prevention

### Domain Models

Implemented models:

* User
* Transaction
* Category
* Budget
* Session

### Transaction Support

The transaction model already supports:

* Income and expense tracking
* Transaction categories
* Descriptions and titles
* Transaction dates
* Recurring transactions

  * Daily
  * Weekly
  * Yearly

### Repository Layer

Currently implemented:

* Repository abstraction (`IUserRepository`)
* In-memory user repository (`InMemoryUserRepository`)

This approach allows easy replacement with database-backed repositories in the future.

### Validation Layer

Implemented:

* User login validation
* User password validation

### Testing

Unit tests are implemented using **Google Test**.

Current test coverage includes:

* User validation
* User registration
* Login process
* Authentication service

---

## Project Structure

```text
include/
├── enums/
├── models/
├── repositories/
├── services/
└── validators/

src/
├── repositories/
├── services/
└── validators/

tests/
├── services/
└── validators/
```

The project is built using **CMake** and follows a modular architecture to simplify maintenance and future expansion.

---

## Building the Project

### Requirements

* CMake 3.15+
* C++17 compatible compiler
* Google Test (downloaded automatically through CMake)

### Build

```bash
mkdir build
cd build

cmake ..
cmake --build .
```

### Run Tests

```bash
ctest
```

---

## Current Development Status

### Implemented

* Core domain models
* Authentication service
* Session management
* User validation
* In-memory user repository
* Unit testing setup
* CMake build system

### In Progress

The project architecture already includes placeholders for several modules that are planned but not yet implemented.

---

## Roadmap

### Transaction Management

* Add transactions
* Edit transactions
* Remove transactions
* Transaction validation
* Transaction repository
* Transaction service

### Category Management

* Custom user categories
* Category repository
* Category service
* Category validation

### Budget Management

* Monthly budgets
* Budget limits per category
* Budget monitoring
* Budget repository
* Budget service
* Budget validation

### Reporting and Analytics

* Monthly summaries
* Expense breakdown by category
* Income vs expense reports
* Budget utilization reports
* Financial statistics

### Data Persistence

Replace in-memory storage with:

* SQLite
* PostgreSQL (optional future support)

### User Interface

Planned CLI interface:

* Authentication views
* Transaction views
* Budget views
* Reporting views

Potential future extensions:

* Desktop GUI
* Web API
* Mobile integration

### Security Improvements

* Password hashing
* Secure authentication
* User data protection

### Testing Expansion

Additional test coverage for:

* Repositories
* Transaction services
* Budget services
* Reporting services
* Integration testing

---

## Design Goals

The main objectives of this project are:

* Clean Architecture
* SOLID principles
* High testability
* Separation of concerns
* Easy database integration
* Future extensibility

---

## Technologies

* C++17
* CMake
* Google Test

---

## Author

Developed as a learning and portfolio project focused on modern C++ software design, clean architecture, and test-driven development practices.
