//
// Created by noaml on 30/06/2024.
//
// ID: 326662574
// MAIL: noamlevin11@gmail.com

#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
//#include <SFML/Graphics.hpp>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "Node.hpp"
#include "Iterators.hpp"

using namespace std;

template <typename T, size_t n = 2>
class Tree {
    private:
            // Fields
            Node<T>* root;

    public:
            Tree() : root(nullptr) {} // Constructor

            ~Tree() { // Deconstructor
                vector<Node<T>*> nodes;

                for (auto it = begin_bfs_scan(); it != end_bfs_scan(); ++it) {
                    nodes.push_back(it.operator->());
                }

                for (auto it = nodes.begin(); it != nodes.end(); ++it) {
                    (*it)->clear_children();
                }

                root = nullptr;
            }

            // Functions
            inline void add_root(Node<T>& root) { // Adding a root
                // If the root is empty, set the root to be the given root
                if (this->root == nullptr){
                    this->root = &root;
                }
                else{
                    cout << "Root already exists" << endl;
//                    throw std::runtime_error("Root already exists");
                }
            }

            inline void add_sub_node(Node<T>& root_node, Node<T>& sub_node) { // Adding a sub node
                // If the parent has less than n children, add the child to the parent
                if (root_node.children.size() < n){
                    root_node.add_child(sub_node);
                }
                else{
                    cout << "Root node has already n children" << endl;
//                    throw std::runtime_error("Parent has already n children");
                }
            }

            // Iterators for general trees (only DFS/BFS)
            inline DFSIterator<T> begin_pre_order() { return DFSIterator<T>(root); }
            inline DFSIterator<T> end_pre_order() { return DFSIterator<T>(nullptr); }

            inline DFSIterator<T> begin_post_order() { return DFSIterator<T>(root); }
            inline DFSIterator<T> end_post_order() { return DFSIterator<T>(nullptr); }

            inline DFSIterator<T> begin_in_order() { return DFSIterator<T>(root); }
            inline DFSIterator<T> end_in_order() { return DFSIterator<T>(nullptr); }

            inline BFSIterator<T> begin_bfs_scan() { return BFSIterator<T>(root); }
            inline BFSIterator<T> end_bfs_scan() { return BFSIterator<T>(nullptr); }

            inline DFSIterator<T> begin_dfs_scan() { return DFSIterator<T>(root); }
            inline DFSIterator<T> end_dfs_scan() { return DFSIterator<T>(nullptr); }

            inline DFSIterator<T> my_heap_begin() { return DFSIterator<T>(root); }
            inline DFSIterator<T> my_heap_end() { return DFSIterator<T>(nullptr); }

            inline BFSIterator<T> begin() { return BFSIterator<T>(root); }
            inline BFSIterator<T> end() { return BFSIterator<T>(nullptr); }
};

template <typename T>
class Tree<T, 2> {
    private:
            // Fields
            Node<T>* root;

    public:
            Tree() : root(nullptr) {} // Constructor

            ~Tree() { // Deconstructor
                vector<Node<T>*> nodes;
                for (auto it = begin_bfs_scan(); it != end_bfs_scan(); ++it) {
                    nodes.push_back(it.operator->());
                }

                for (auto it : nodes) {
                    it->clear_children();
                }

                root = nullptr;
            }

            // Functions
            inline void add_root(Node<T>& root) { // Adding a root
                // If the root is empty, set the root to be the given root
                if (this->root == nullptr){
                    this->root = &root;
                }
                else{
                    cout << "Root already exists" << endl;
                    //                    throw std::runtime_error("Root already exists");
                }
            }

            inline void add_sub_node(Node<T>& root_node, Node<T>& sub_node) { // Adding a sub node
                // If the parent has less than n children, add the child to the parent
                if (root_node.getChildren().size() < 2){
                    root_node.add_child(sub_node);
                }
                else{
                    cout << "Root node has already n children" << endl;
                    //                    throw std::runtime_error("Parent has already n children");
                }
            }

            // Iterators for a binary tree
            inline PreOrderIterator<T> begin_pre_order() { return PreOrderIterator<T>(root); }
            inline PreOrderIterator<T> end_pre_order() { return PreOrderIterator<T>(nullptr); }

            inline PostOrderIterator<T> begin_post_order() { return PostOrderIterator<T>(root); }
            inline PostOrderIterator<T> end_post_order() { return PostOrderIterator<T>(nullptr); }

            inline InOrderIterator<T> begin_in_order() { return InOrderIterator<T>(root); }
            inline InOrderIterator<T> end_in_order() { return InOrderIterator<T>(nullptr); }

            inline BFSIterator<T> begin_bfs_scan() { return BFSIterator<T>(root); }
            inline BFSIterator<T> end_bfs_scan() { return BFSIterator<T>(nullptr); }

            inline DFSIterator<T> begin_dfs_scan() { return DFSIterator<T>(root); }
            inline DFSIterator<T> end_dfs_scan() { return DFSIterator<T>(nullptr); }

            inline HeapIterator<T> my_heap_begin() { return HeapIterator<T>(root); }
            inline HeapIterator<T> my_heap_end() { return HeapIterator<T>(nullptr); }

            inline BFSIterator<T> begin(){ return BFSIterator<T>(root); }
            inline BFSIterator<T> end() { return BFSIterator<T>(nullptr); }
};