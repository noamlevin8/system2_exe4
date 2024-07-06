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

            // Function for the GUI
            string formatingValue(const T& value, int precision = 5) { // Precision for number values
                stringstream strstream;
                strstream << fixed << setprecision(precision) << value;
                return strstream.str();
            }

            string truncateText(const sf::Text& text, float maxLen) { // Truncate text if necessary
                string str = text.getString();
                string truncatedString = str;
                sf::Text tempText = text;

                if (text.getLocalBounds().width > maxLen) {
                    for (size_t i = 0; i < str.size(); ++i) {
                        truncatedString = str.substr(0, i) + "...";
                        tempText.setString(truncatedString);

                        if (tempText.getLocalBounds().width > maxLen) { //if the text is too long, truncate it
                            truncatedString = str.substr(0, i - 1) + "...";
                            break;
                        }
                    }
                }
                return truncatedString;
            }

            // Helper function to calculate the max len of a subTree.
            // This function is used to prevent overlapping of nodes in the GUI.
            float subTreeLen(Node<T>*  node, float xOffset) {
                if (!node || node->getChildren().empty())
                    return 0.0f;

                float totalLen = 0.0f;

                for (auto& child : node->getChildren()) {
                    totalLen += subTreeLen(child, xOffset) + xOffset;
                }

                totalLen -= (2 * xOffset); // Removing unnecessary offset from last child

                return max(totalLen, xOffset);
            }

            void drawTree(sf::RenderWindow &window, Node<T>* node, float x, float y, float xOffset, float yOffset, int level) {
                if (!node)
                    return;

                // Drawing the node
                sf::CircleShape circle(30);
                circle.setFillColor(sf::Color::Blue);
                circle.setPosition(x, y);

                // Getting the font
                sf::Font font;
                if (!font.loadFromFile("ArielFont.ttf")) {
                    cerr << "Failed to load font\n";
                    return;
                }

                // Formating value
                std::string nodeValueStr = formatingValue(node->get_value());

                // Creating text
                sf::Text text;
                text.setFont(font);
                text.setString(nodeValueStr);
                text.setCharacterSize(15);
                text.setFillColor(sf::Color::Black);

                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

                // Calculating the node's center
                float circleCenterX = x + circle.getRadius();
                float circleCenterY = y + circle.getRadius();

                text.setPosition(circleCenterX, circleCenterY);

                // Truncate the text if it doesn't fit within the node
                float maxTextLen = circle.getRadius() * 2.0f - 10.0f;
                string truncatedTextString = truncateText(text, maxTextLen);
                text.setString(truncatedTextString);

                // Updating after truncate
                textRect = text.getLocalBounds();
                text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

                text.setPosition(circleCenterX, circleCenterY);

                // Drawing the node and the text
                window.draw(circle);
                window.draw(text);

                // Calculating the positions of the children
                int numOfChildren = node->getChildren().size();
                if (numOfChildren > 0) {
                    float subtreeLen = subTreeLen(node, xOffset);

                    float startX = x + circle.getRadius() - subtreeLen / 2.0f;

                    for (size_t i = 0; i < numOfChildren; ++i) {
                        float childX = startX + i * (subtreeLen / numOfChildren);
                        float childY = y + yOffset;

                        sf::Vertex line[] = {
                                sf::Vertex(sf::Vector2f(circleCenterX, circleCenterY), sf::Color::Black),
                                sf::Vertex(sf::Vector2f(childX + circle.getRadius(), childY + circle.getRadius()), sf::Color::Black)};
                        window.draw(line, 2, sf::Lines);

                        drawTree(window, node->getChildren()[i], childX, childY, xOffset / 1.2f, yOffset, level + 1);
                    }
                }
            }

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
                    throw std::runtime_error("Root already exists");
                }
            }

            inline void add_sub_node(Node<T>& root_node, Node<T>& sub_node) { // Adding a sub node
                // If the parent has less than n children, add the child to the parent
                if (root_node.getChildren().size() < n){
                    root_node.add_child(sub_node);
                }
                else{
                    throw std::runtime_error("Parent has already n children");
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

            inline void showTree() { // GUI function
                sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization");

                while (window.isOpen()) {
                    sf::Event event;

                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                            window.close();
                    }

                    window.clear(sf::Color::White);

                    drawTree(window, root, 400, 50, 150, 100, 0);

                    window.display();
                }
            }

            inline Node<T>* getRoot() { return this->root; }
};

template <typename T>
class Tree<T, 2> {
    private:
            // Fields
            Node<T>* root;

            // Function for the GUI
            string formatingValue(const T& value, int precision = 5) { // Precision for number values
                stringstream strstream;
                strstream << fixed << setprecision(precision) << value;
                return strstream.str();
            }

            string truncateText(const sf::Text& text, float maxLen) { // Truncate text if necessary
                string str = text.getString();
                string truncatedString = str;
                sf::Text tempText = text;

                if (text.getLocalBounds().width > maxLen) {
                    for (size_t i = 0; i < str.size(); ++i) {
                        truncatedString = str.substr(0, i) + "...";
                        tempText.setString(truncatedString);

                        if (tempText.getLocalBounds().width > maxLen) { //if the text is too long, truncate it
                            truncatedString = str.substr(0, i - 1) + "...";
                            break;
                        }
                    }
                }
                return truncatedString;
            }

            // Helper function to calculate the max len of a subTree.
            // This function is used to prevent overlapping of nodes in the GUI.
            float subTreeLen(Node<T>*  node, float xOffset) {
                if (!node || node->getChildren().empty())
                    return 0.0f;

                float totalLen = 0.0f;

                for (auto& child : node->getChildren()) {
                    totalLen += subTreeLen(child, xOffset) + xOffset;
                }

                totalLen -= (2 * xOffset); // Removing unnecessary offset from last child

                return max(totalLen, xOffset);
            }

            void drawTree(sf::RenderWindow &window, Node<T>* node, float x, float y, float xOffset, float yOffset, int level) {
                if (!node)
                    return;

                // Drawing the node
                sf::CircleShape circle(30);
                circle.setFillColor(sf::Color::Blue);
                circle.setPosition(x, y);

                // Getting the font
                sf::Font font;
                if (!font.loadFromFile("ArielFont.ttf")) {
                    cerr << "Failed to load font\n";
                    return;
                }

                // Formating value
                std::string nodeValueStr = formatingValue(node->get_value());

                // Creating text
                sf::Text text;
                text.setFont(font);
                text.setString(nodeValueStr);
                text.setCharacterSize(15);
                text.setFillColor(sf::Color::Black);

                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

                // Calculating the node's center
                float circleCenterX = x + circle.getRadius();
                float circleCenterY = y + circle.getRadius();

                text.setPosition(circleCenterX, circleCenterY);

                // Truncate the text if it doesn't fit within the node
                float maxTextLen = circle.getRadius() * 2.0f - 10.0f;
                string truncatedTextString = truncateText(text, maxTextLen);
                text.setString(truncatedTextString);

                // Updating after truncate
                textRect = text.getLocalBounds();
                text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

                text.setPosition(circleCenterX, circleCenterY);

                // Drawing the node and the text
                window.draw(circle);
                window.draw(text);

                // Calculating the positions of the children
                int numOfChildren = node->getChildren().size();
                if (numOfChildren > 0) {
                    float subtreeLen = subTreeLen(node, xOffset);

                    float startX = x + circle.getRadius() - subtreeLen / 2.0f;

                    for (size_t i = 0; i < numOfChildren; ++i) {
                        float childX = startX + i * (subtreeLen / numOfChildren);
                        float childY = y + yOffset;

                        sf::Vertex line[] = {
                                sf::Vertex(sf::Vector2f(circleCenterX, circleCenterY), sf::Color::Black),
                                sf::Vertex(sf::Vector2f(childX + circle.getRadius(), childY + circle.getRadius()), sf::Color::Black)};
                        window.draw(line, 2, sf::Lines);

                        drawTree(window, node->getChildren()[i], childX, childY, xOffset / 1.2f, yOffset, level + 1);
                    }
                }
            }

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
                    throw std::runtime_error("Root already exists");
                }
            }

            inline void add_sub_node(Node<T>& root_node, Node<T>& sub_node) { // Adding a sub node
                // If the parent has less than n children, add the child to the parent
                if (root_node.getChildren().size() < 2){
                    root_node.add_child(sub_node);
                }
                else{
                    throw std::runtime_error("Parent has already n children");
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

            inline void showTree() { // GUI function
                sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization");

                while (window.isOpen()) {
                    sf::Event event;

                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                            window.close();
                    }

                    window.clear(sf::Color::White);

                    drawTree(window, root, 400, 50, 150, 100, 0);

                    window.display();
                }
            }

            inline Node<T>* getRoot() { return this->root; }
};