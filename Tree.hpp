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
#include <SFML/Graphics.hpp>
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

            ~Tree() {} // Deconstructor

            // Functions
            inline void addRoot(Node<T>& root) { // Adding a root
                // If the root is empty, set the root to the given root
                if (this->root == nullptr){
                    this->root = &root;
                }
                else{
                    cout << "Root already exists" << endl;
//                    throw std::runtime_error("Root already exists");
                }
            };

            inline void add_sub_node(Node<T>& parent, Node<T>& child) { // Adding a sub node
                // If the parent has less than n children, add the child to the parent
                if (parent.children.size() < n){
                    parent.add_child(child);
                }
                else{
                    cout << "Parent has already n children" << endl;
//                    throw std::runtime_error("Parent has already n children");
                }
            };


};
