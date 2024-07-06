# Trees - STL, Templates, and Iterators

## Overview

A tree is a connected graph without cycles. A k-ary tree is a tree where each node has at most k children. For example, a binary tree is a 2-ary tree. Trees can contain keys of any type (e.g., numbers, strings, classes). By default, the tree is a binary tree, meaning k = 2.

To construct and traverse trees in various ways, the following iterators have been implemented:

### Iterators

1. **Pre-Order Iterator**: Traverses the tree in the order: current node -> left subtree -> right subtree. This iterator works for binary trees only.
2. **Post-Order Iterator**: Traverses the tree in the order: left subtree -> right subtree -> current node. This iterator works for binary trees only.
3. **In-Order Iterator**: Traverses the tree in the order: left subtree -> current node -> right subtree. This iterator works for binary trees only.
4. **BFS Iterator**: Breadth-First Search traversal (left to right). This iterator works for general trees.
5. **DFS Iterator**: Depth-First Search traversal. This iterator works for general trees.
6. **Heap Iterator**: Converts a binary tree into a min-heap.

## Class Hierarchy

- **Complex**: A class representing a complex number object.
- **Node**: A class representing the nodes of the tree.
- **Tree**: A class representing the entire tree.
- **Iterators**: A class representing all different types of iterators.
- **Demo**: A class demonstrating three different types of trees.
- **Test**: A class for testing all functions that operate on trees.

## Usage

### Building the Project

Use the provided `Makefile` to compile and run the project. The following targets are available:

- `all`: Compiles the demo and test executables.
- `demo`: Compiles the demo executable.
- `test`: Compiles the test executable.
- `tidy`: Runs `clang-tidy` for code analysis and cleanup.
- `valgrind`: Runs `valgrind` to check for memory leaks.
- `clean`: Removes all generated object files and executables.

To compile and run the demo and tests:

```bash
make all
./demo
./test
```

## Conclusion

This project provides a robust implementation of trees with various traversal methods and supports complex number nodes. The class hierarchy and iterators make it flexible and easy to use for different types of trees and traversal requirements.
