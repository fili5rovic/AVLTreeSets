# AVL Tree Set Implementation

This C++ project implements sets using AVL trees, ensuring efficient management of ordered data with self-balancing binary search trees. The AVL tree properties are meticulously maintained during dynamic set operations to achieve optimal balance, providing O(log n) complexity for standard set operations.

> The primary objective of this project centered on gaining practical experience with AVL trees, specifically focusing on executing various set operations within the tree. Throughout the course of the project, I became proficient in performing tasks such as inserting elements into the AVL tree and carrying out rotations and balancing to maintain its properties.
> >
> This project was developed as the [first university assignment](instructions.pdf) for "Algorithms and Data Structures 2", University of Belgrade School of Electrical Engineering majoring Software Engineering.

## Features

- **Self-Balancing Trees:** Each set is represented as an AVL tree, which self-balances to maintain a height of O(log n) for all operations.
- **Unique Set Identifiers:** Every set is created with a unique character identifier, allowing for clear and easy reference.
- **Element Management:** Seamlessly add new elements to any set, with the AVL tree automatically handling the balancing.
- **Existence Query:** Provides the ability to check if a specific value exists within a set, offering immediate feedback on membership.
- **Set Operations:** Supports set subtraction, enabling users to find the difference between two sets.
- **Visual Representation:** Displays the tree structure of each set visually, including balance factors and tree height.
- **Clean Up:** Sets can be deleted when no longer needed, which cleans up all associated resources from memory.

## Getting Started

### Prerequisites

- C++ compiler (C++11 or higher)
- Make (optional for building)

### Building the Project

To build the project, you can use the provided Makefile or compile the source manually with your C++ compiler.
