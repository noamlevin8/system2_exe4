//
// Created by noaml on 30/06/2024.
//
// ID: 326662574
// MAIL: noamlevin11@gmail.com

#pragma once

#include <vector>
#include <stack>
#include <queue>
#include "Node.hpp"

using namespace std;

// Pre-Order iterator class for a tree
template <typename T>
class PreOrderIterator {
    private:
            // Fields
            stack<Node<T>*> NodeStack;

    public:
            PreOrderIterator(Node<T>* root) { // Constructor
                if(root != nullptr)
                    this->NodeStack.push(root);
            }

            // Operator "==" overload
            inline bool operator==(const PreOrderIterator& other) {
                if(this->NodeStack.empty() && other.NodeStack.empty()) // Both empty
                    return true;

                if(this->NodeStack.empty() != other.NodeStack.empty()) // Only one empty
                    return false;

                return this->NodeStack.top() == other.NodeStack.top(); // Compression between the top of both
            }

            // Operator "!=" overload
            inline bool operator!=(const PreOrderIterator& other) {
                return !(*this == other);
            }

            // Operator "++" overload
            inline PreOrderIterator& operator++() {
                Node<T>* currentNode = this->NodeStack.top();
                this->NodeStack.pop();

                for (int i = currentNode->getChildren().size() - 1; i >= 0; i--){ // Pushing to the stack in reverse
                    this->NodeStack.push(currentNode->getChildren()[(size_t)i]);
                }

                return *this;
            }

            // Operator "*" overload
            inline T& operator*() {
                return this->NodeStack.top()->get_value();
            }

            // Operator "->" overload
            inline Node<T>* operator->() {
                return this->NodeStack.top();
            }
};

// Post-Order iterator class for a tree
template <typename T>
class PostOrderIterator {
    private:
            // Fields
            vector<Node<T>*> NodeStack;

            // Help function for the constructor to travers the tree in Post-Order
            inline vector<Node<T>*> traverse(Node<T> *root) {
                vector<Node<T>*> result;

                if (root == nullptr)
                    return result;

                for (Node<T>* child : root->getChildren()){
                    vector<Node<T>*> temp = traverse(child);
                    result.insert(result.end(), temp.begin(), temp.end());
                }

                result.push_back(root);
                return result;
            }

    public:
            PostOrderIterator(Node<T>* root) { // Constructor
                if(root != nullptr)
                    this->NodeStack = traverse(root);
            }

            // Operator "==" overload
            inline bool operator==(const PostOrderIterator& other) {
                if(this->NodeStack.empty() && other.NodeStack.empty()) // Both empty
                    return true;

                if(this->NodeStack.empty() != other.NodeStack.empty()) // Only one empty
                    return false;

                return this->NodeStack.front() == other.NodeStack.front(); // Compression between the top of both
            };

            // Operator "!=" overload
            inline bool operator!=(const PostOrderIterator& other) {
                return !(*this == other);
            }

            // Operator "++" overload
            PostOrderIterator& operator++() {
                if (!this->NodeStack.empty()){
                    this->NodeStack.erase(this->NodeStack.begin());
                }

                return *this;
            }

            // Operator "*" overload
            inline T& operator*() {
                return this->NodeStack.top()->get_value();
            }

            // Operator "->" overload
            inline Node<T>* operator->() {
                return this->NodeStack.front();
            }
};

// In-Order iterator class for a tree
template <typename T>
class InOrderIterator {
    private:
            // Fields
            stack<Node<T>*> NodeStack;

    public:
            InOrderIterator(Node<T>* root) { // Constructor
                this->NodeStack.push(nullptr);

                while (root != nullptr){
                    this->NodeStack.push(root);

                    if(root->getChildren().size() > 0){
                        root = root->getChildren()[0];
                    } else
                        root = nullptr;
                }
            }

            // Operator "==" overload
            inline bool operator==(const InOrderIterator& other) {
                if(this->NodeStack.empty() && other.NodeStack.empty()) // Both empty
                    return true;

                if(this->NodeStack.empty() != other.NodeStack.empty()) // Only one empty
                    return false;

                return this->NodeStack.top() == other.NodeStack.top(); // Compression between the top of both
            };

            // Operator "!=" overload
            inline bool operator!=(const InOrderIterator& other) {
                return !(*this == other);
            }

            // Operator "++" overload
            inline InOrderIterator& operator++() {
                Node<T>* currentNode = this->NodeStack.top();
                this->NodeStack.pop();

                if (currentNode->getChildren().size() == 2) { // If the current node has a right child we push it to the stack
                    this->NodeStack.push(currentNode->getChildren()[1]);
                    Node<T> *temp = currentNode->getChildren()[1];

                    while (temp->getChildren().size() > 0) { // Then, we push the left branch of the right child into the stack
                        this->NodeStack.push(temp->getChildren()[0]);
                        temp = temp->getChildren()[0];
                    }
                }

                return *this;
            }

            // Operator "*" overload
            inline T& operator*() {
                return this->NodeStack.top()->get_value();
            }

            // Operator "->" overload
            inline Node<T>* operator->() {
                return this->NodeStack.top();
            }
};

template <typename T>
class BFSIterator {
    private:
            // Fields
            queue<Node<T>*> NodeQueue;

    public:
            BFSIterator(Node<T>* root) { // Constructor
                if (root != nullptr)
                    this->NodeQueue.push(root);
            }

            // Operator "==" overload
            inline bool operator==(const BFSIterator& other) const {
                if (this->NodeQueue.empty() && other.NodeQueue.empty())
                    return true;

                if (this->NodeQueue.empty() != other.NodeQueue.empty())
                    return false;

                return this->NodeQueue.front() == other.NodeQueue.front();
            }

            // Operator "!=" overload
            inline bool operator!=(const BFSIterator& other) const {
                return !(*this == other);
            }

            // Operator "++" overload
            inline BFSIterator& operator++() {
                if (this->NodeQueue.empty())
                    return *this;

                Node<T>* currentNode = this->NodeQueue.front();
                this->NodeQueue.pop();

                for(auto& child : currentNode->getChildren()) {
                    this->NodeQueue.push(child);
                }
                return *this;
            }

            // Operator "*" overload
            inline T& operator*() {
                return this->NodeQueue.front()->get_value();
            }

            // Operator "*" overload (const)
            inline const T& operator*() const {
                return this->NodeQueue.front()->get_value();
            }

            // Operator "->" overload
            inline Node<T>* operator->() {
                return this->NodeQueue.front();
            }
};

template <typename T>
class DFSIterator {
    private:
            stack<Node<T>*> NodeStack;

    public:
            DFSIterator(Node<T> *root) {
                if (root != nullptr)
                    this->NodeStack.push(root);
            }

            // Operator "==" overload
            inline bool operator==(const DFSIterator& other) const {
                if (this->NodeStack.empty() && other.NodeStack.empty())
                    return true;

                if (this->NodeStack.empty() != other.NodeStack.empty())
                    return false;

                return this->NodeStack.top() == other.NodeStack.top();
            }

            // Operator "!=" overload
            inline bool operator!=(const DFSIterator& other) const {
                return !(*this == other);
            }

            // Operator "++" overload
            inline DFSIterator& operator++() {
                Node<T>* currentNode = this->NodeStack.top();
                this->NodeStack.pop();

                for (int i = currentNode->getChildren().size() - 1; i >= 0; i--) {
                    this->NodeStack.push(currentNode->getChildren()[(size_t)i]);
                }

                return *this;
            }

            // Operator "*" overload
            inline T& operator*() {
                return this->NodeStack.top()->get_value();
            }

            // Operator "->" overload
            inline Node<T>* operator->() {
                return this->NodeStack.top();
            }
};

template <typename T>
class HeapIterator {
    private:
            vector<Node<T>*> NodeHeap;
    public:
            HeapIterator(Node<T>* root) { // Constructor
                if (root != nullptr) {
                    for (auto node = BFSIterator<T>(root); node != BFSIterator<T>(nullptr); ++node) {
                        this->NodeHeap.push_back(node.operator->());
                    }

                    make_heap(this->NodeHeap.begin(), this->NodeHeap.end(), [](Node <T>* a, Node <T>* b) {
                        return a->get_value() > b->get_value(); });
                }
            }

            // Operator "==" overload
            inline bool operator==(const HeapIterator& other) const {
                if (this->NodeHeap.empty() && other.NodeHeap.empty()) {
                    return true;
                }

                if (this->NodeHeap.empty() != other.NodeHeap.empty()) {
                    return false;
                }

                return this->NodeHeap.front() == other.NodeHeap.front();
            }

            // Operator "!=" overload
            inline bool operator!=(const HeapIterator& other) const {
                return !(*this == other);
            }

            // Operator "++" overload
            HeapIterator& operator++() {
                if(!this->NodeHeap.empty()){
                    this->NodeHeap.erase(this->NodeHeap.begin());
                }

                return *this;
            }

            // Operator "*" overload
            inline T& operator*() {
                return this->NodeHeap.front()->get_value();
            }

            // Operator "->" overload
            inline Node<T>* operator->() {
                return this->NodeHeap.front();
            }
};