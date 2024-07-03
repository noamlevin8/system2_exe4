//
// Created by noaml on 30/06/2024.
//
// ID: 326662574
// MAIL: noamlevin11@gmail.com

#pragma once

#include <vector>

using namespace std;

template <typename T>
 class Node {
    public:
            // Fields
            T value;
            Node* parent;
            vector<Node<T>*> children;

            // Functions
            Node(const T& value) : value(value), parent(nullptr) {} // Constructor

            inline T& get_value() { return this->value; } // Getting the data

            inline vector<Node<T>*>& getChildren() { return this->children; } // Getting the children vector

            inline void setData(T& value) { this->value = value; } // Setting the data

            inline void add_child(Node<T>& child) { this->children.push_back(&child); child.parent = this; } // Adding a child

            inline void clear_children() { this->children.clear(); } // Clearing the children vector
 };