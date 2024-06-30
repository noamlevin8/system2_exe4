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
            T data;
            Node* parent;
            vector<Node<T>*> children;

            // Functions
            Node(T& data) : data(data), parent(nullptr) {} // Constructor

            inline T& getData() const { return this->data; }; // Getting the data

            inline vector<Node<T>*>& getChildren() const { return this->children; }; // Getting the children vector

            inline void setData(T& data) { this->data = data; }; // Setting the data

            inline void add_child(Node<T>& child) { this->childrens.pop_back(&child); child.parent = this; }; // Adding a child

            inline void clear_children() { this->children.clear(); }; // Clearing the children vector
 };