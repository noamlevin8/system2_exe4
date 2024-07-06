//
// Created by noaml on 30/06/2024.
//
// ID: 326662574
// MAIL: noamlevin11@gmail.com

#include "doctest.h"
#include "Tree.hpp"
#include "Node.hpp"
#include "Complex.hpp"

using namespace std;

TEST_CASE("Check node operations"){
    Node<int> node1(1);
    CHECK(node1.get_value() == 1); // Checking value of regular node

    Complex cmp1(1.1, 1.1);
    Complex cmp2(2.2, 2.2);
    Node<Complex> node2(cmp1);
    Node<Complex> node3(cmp2);

    node2.add_child(node3);
    CHECK(node2.getChildren()[0]->get_value() == node3.get_value()); // Checking value of child

    node1.set_value(3);
    CHECK(node1.get_value() == 3); // Checking value after set

    CHECK(!node2.getChildren().empty()); // Checking size before clear
    node2.clear_children();
    CHECK(node2.getChildren().empty()); // Checking size after clear
}

TEST_CASE("Check add_sub_node and add_root"){
    Node<string> root_node("Noam");
    Node<string> n1("Omer");
    Node<string> n2("Adi");
    Tree<string, 3> tree;

    tree.add_root(root_node);
    CHECK(tree.getRoot()->getChildren().size() == 0); // Checking size before adding
    tree.add_sub_node(root_node, n1);
    CHECK(tree.getRoot()->getChildren().size() == 1); // Checking size after adding 1
    tree.add_sub_node(root_node, n2);
    CHECK(tree.getRoot()->getChildren().size() == 2); // Checking size after adding another one

    Node<Complex> node1(Complex(1.1, 1.1));
    Node<Complex> node2(Complex(2.2, 2.2));
    Tree<Complex> cmp_tree;

    cmp_tree.add_root(node1);
    CHECK(cmp_tree.getRoot()->getChildren().size() == 0); // Checking size before adding
    cmp_tree.add_sub_node(node1, node2);

    CHECK(cmp_tree.getRoot()->getChildren().size() == 1); // Checking size after adding 1
}

TEST_CASE("Check invalid number of children"){
    Node<double> root_node(2.5);
    Tree<double> tree;
    tree.add_root(root_node);

    Node<double> n1(1.1);
    Node<double> n2(2.2);
    Node<double> n3(3.3);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);

    CHECK_THROWS(tree.add_sub_node(root_node, n3)); // Checking on Binary tree

    Node<double> root_node2(2.5);
    Node<double> n4(1.1);
    Node<double> n5(2.2);
    Node<double> n6(3.3);
    Node<double> n7(4.4);
    Node<double> n8(5.5);
    Tree<double, 3> tree2;

    tree2.add_root(root_node2);
    tree2.add_sub_node(root_node2, n4);
    tree2.add_sub_node(root_node2, n5);
    tree2.add_sub_node(root_node2, n6);

    CHECK_THROWS(tree2.add_sub_node(root_node2, n7)); // Checking on 3-ary tree
}

TEST_CASE("Traverse on an integer tree"){
    Node<int> root(20);
    Node<int> child1(12);
    Node<int> child2(30);
    Node<int> child3(8);
    Node<int> child4(15);
    Node<int> child5(25);
    Node<int> child6(40);
    Tree<int> tree;

    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);
    tree.add_sub_node(child2, child5);
    tree.add_sub_node(child2, child6);

    SUBCASE("PreOrder Traversal") {
        vector<int> expected = {20, 12, 8, 15, 30, 25, 40};
        vector<int> result;
        for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("PostOrder Traversal") {
        vector<int> expected = {8, 15, 12, 25, 40, 30, 20};
        vector<int> result;
        for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("InOrder Traversal") {
        vector<int> expected = {8, 12, 15, 20, 25, 30, 40};
        vector<int> result;
        for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("BFS Traversal") {
        vector<int> expected = {20, 12, 30, 8, 15, 25, 40};
        vector<int> result;
        for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("DFS Traversal") {
        vector<int> expected = {20, 12, 8, 15, 30, 25, 40};
        vector<int> result;
        for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("Heap Traversal") {
        vector<int> expected = {8, 12, 25, 20, 15, 30, 40};
        vector<int> result;
        for (auto it = tree.my_heap_begin(); it != tree.my_heap_end(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }
}

TEST_CASE("Traverse on a complex tree"){
    Node<Complex> root(Complex(20, 20));
    Node<Complex> child1(Complex(12, 12));
    Node<Complex> child2(Complex(30, 30));
    Node<Complex> child3(Complex(8, 8));
    Node<Complex> child4(Complex(15, 15));
    Node<Complex> child5(Complex(25, 25));
    Node<Complex> child6(Complex(40, 40));
    Tree<Complex> cmp_tree;

    cmp_tree.add_root(root);
    cmp_tree.add_sub_node(root, child1);
    cmp_tree.add_sub_node(root, child2);
    cmp_tree.add_sub_node(child1, child3);
    cmp_tree.add_sub_node(child1, child4);
    cmp_tree.add_sub_node(child2, child5);
    cmp_tree.add_sub_node(child2, child6);

    SUBCASE("PreOrder Traversal") {
        vector<Complex> expected = {Complex(20, 20), Complex(12, 12), Complex(8, 8), Complex(15, 15), Complex(30, 30), Complex(25, 25), Complex(40, 40)};
        vector<Complex> result;
        for (auto it = cmp_tree.begin_pre_order(); it != cmp_tree.end_pre_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("PostOrder Traversal") {
        vector<Complex> expected = {Complex(8, 8), Complex(15, 15), Complex(12, 12), Complex(25, 25), Complex(40, 40), Complex(30, 30), Complex(20, 20)};
        vector<Complex> result;
        for (auto it = cmp_tree.begin_post_order(); it != cmp_tree.end_post_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("InOrder Traversal") {
        vector<Complex> expected = {Complex(8, 8), Complex(12, 12), Complex(15, 15), Complex(20, 20), Complex(25, 25), Complex(30, 30), Complex(40, 40)};
        vector<Complex> result;
        for (auto it = cmp_tree.begin_in_order(); it != cmp_tree.end_in_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("BFS Traversal") {
        vector<Complex> expected = {Complex(20, 20), Complex(12, 12), Complex(30, 30), Complex(8, 8), Complex(15, 15), Complex(25, 25), Complex(40, 40)};
        vector<Complex> result;
        for (auto it = cmp_tree.begin_bfs_scan(); it != cmp_tree.end_bfs_scan(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("DFS Traversal") {
        vector<Complex> expected = {Complex(20, 20), Complex(12, 12), Complex(8, 8), Complex(15, 15), Complex(30, 30), Complex(25, 25), Complex(40, 40)};
        vector<Complex> result;
        for (auto it = cmp_tree.begin_dfs_scan(); it != cmp_tree.end_dfs_scan(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("Heap Traversal") {
        vector<Complex> expected = {Complex(8, 8), Complex(12, 12), Complex(25, 25), Complex(20, 20), Complex(15, 15), Complex(30, 30), Complex(40, 40)};
        vector<Complex> result;
        for (auto it = cmp_tree.my_heap_begin(); it != cmp_tree.my_heap_end(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }
}

TEST_CASE("Traverse on an integer 3-ary tree"){
    Node<int> root(10);
    Node<int> child1(20);
    Node<int> child2(30);
    Node<int> child3(40);
    Node<int> child4(50);
    Node<int> child5(60);
    Node<int> child6(70);
    Node<int> child7(80);
    Node<int> child8(90);
    Node<int> child9(100);
    Tree<int, 3> three_ary_tree;

    three_ary_tree.add_root(root);
    three_ary_tree.add_sub_node(root, child1);
    three_ary_tree.add_sub_node(root, child4);
    three_ary_tree.add_sub_node(root, child7);
    three_ary_tree.add_sub_node(child1, child2);
    three_ary_tree.add_sub_node(child1, child3);
    three_ary_tree.add_sub_node(child4, child5);
    three_ary_tree.add_sub_node(child4, child6);
    three_ary_tree.add_sub_node(child7, child8);
    three_ary_tree.add_sub_node(child7, child9);

    SUBCASE("PreOrder Traversal") {
        vector<int> expected = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        vector<int> result;
        for (auto it = three_ary_tree.begin_pre_order(); it != three_ary_tree.end_pre_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("PostOrder Traversal") {
        vector<int> expected = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        vector<int> result;
        for (auto it = three_ary_tree.begin_post_order(); it != three_ary_tree.end_post_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("InOrder Traversal") {
        vector<int> expected = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        vector<int> result;
        for (auto it = three_ary_tree.begin_in_order(); it != three_ary_tree.end_in_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("BFS Traversal") {
        vector<int> expected = {10, 20, 50, 80, 30, 40, 60, 70, 90, 100};
        vector<int> result;
        for (auto it = three_ary_tree.begin_bfs_scan(); it != three_ary_tree.end_bfs_scan(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("DFS Traversal") {
        vector<int> expected = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        vector<int> result;
        for (auto it = three_ary_tree.begin_dfs_scan(); it != three_ary_tree.end_dfs_scan(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("Heap Traversal") {
        vector<int> expected = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        vector<int> result;
        for (auto it = three_ary_tree.my_heap_begin(); it != three_ary_tree.my_heap_end(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }
}

TEST_CASE("Traverse on a Complex 3-ary tree"){
    Node<Complex> root(Complex(10.1, 10.1));
    Node<Complex> n1(Complex(-20.2, 20.2));
    Node<Complex> n2(Complex(30.3, -30.3));
    Node<Complex> n3(Complex(-40.4, -40.4));
    Node<Complex> n4(Complex(50.5, 50.5));
    Node<Complex> n5(Complex(60.6, 60.6));
    Node<Complex> n6(Complex(70.7, -70.7));
    Node<Complex> n7(Complex(80.8, 80.8));
    Node<Complex> n8(Complex(-90.9, 90.9));
    Node<Complex> n9(Complex(100.10, 100.10));
    Tree<Complex, 3> three_ary_tree;

    three_ary_tree.add_root(root);
    three_ary_tree.add_sub_node(root, n1);
    three_ary_tree.add_sub_node(root, n4);
    three_ary_tree.add_sub_node(root, n7);
    three_ary_tree.add_sub_node(n1, n2);
    three_ary_tree.add_sub_node(n1, n3);
    three_ary_tree.add_sub_node(n4, n5);
    three_ary_tree.add_sub_node(n4, n6);
    three_ary_tree.add_sub_node(n4, n8);
    three_ary_tree.add_sub_node(n7, n9);

    SUBCASE("PreOrder Traversal") {
        vector<Complex> expected = {Complex(10.1, 10.1), Complex(-20.2, 20.2), Complex(30.3, -30.3), Complex(-40.4, -40.4), Complex(50.5, 50.5), Complex(60.6, 60.6), Complex(70.7, -70.7), Complex(-90.9, 90.9), Complex(80.8, 80.8), Complex(100.10, 100.10)};
        vector<Complex> result;
        for (auto it = three_ary_tree.begin_pre_order(); it != three_ary_tree.end_pre_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("PostOrder Traversal") {
        vector<Complex> expected = {Complex(10.1, 10.1), Complex(-20.2, 20.2), Complex(30.3, -30.3), Complex(-40.4, -40.4), Complex(50.5, 50.5), Complex(60.6, 60.6), Complex(70.7, -70.7), Complex(-90.9, 90.9), Complex(80.8, 80.8), Complex(100.10, 100.10)};
        vector<Complex> result;
        for (auto it = three_ary_tree.begin_post_order(); it != three_ary_tree.end_post_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("InOrder Traversal") {
        vector<Complex> expected = {Complex(10.1, 10.1), Complex(-20.2, 20.2), Complex(30.3, -30.3), Complex(-40.4, -40.4), Complex(50.5, 50.5), Complex(60.6, 60.6), Complex(70.7, -70.7), Complex(-90.9, 90.9), Complex(80.8, 80.8), Complex(100.10, 100.10)};
        vector<Complex> result;
        for (auto it = three_ary_tree.begin_in_order(); it != three_ary_tree.end_in_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("BFS Traversal") {
        vector<Complex> expected = {Complex(10.1, 10.1), Complex(-20.2, 20.2), Complex(50.5, 50.5), Complex(80.8, 80.8), Complex(30.3, -30.3), Complex(-40.4, -40.4), Complex(60.6, 60.6), Complex(70.7, -70.7), Complex(-90.9, 90.9), Complex(100.10, 100.10)};
        vector<Complex> result;
        for (auto it = three_ary_tree.begin_bfs_scan(); it != three_ary_tree.end_bfs_scan(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("DFS Traversal") {
        vector<Complex> expected = {Complex(10.1, 10.1), Complex(-20.2, 20.2), Complex(30.3, -30.3), Complex(-40.4, -40.4), Complex(50.5, 50.5), Complex(60.6, 60.6), Complex(70.7, -70.7), Complex(-90.9, 90.9), Complex(80.8, 80.8), Complex(100.10, 100.10)};
        vector<Complex> result;
        for (auto it = three_ary_tree.begin_dfs_scan(); it != three_ary_tree.end_dfs_scan(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("Heap Traversal") {
        vector<Complex> expected = {Complex(10.1, 10.1), Complex(-20.2, 20.2), Complex(30.3, -30.3), Complex(-40.4, -40.4), Complex(50.5, 50.5), Complex(60.6, 60.6), Complex(70.7, -70.7), Complex(-90.9, 90.9), Complex(80.8, 80.8), Complex(100.10, 100.10)};
        vector<Complex> result;
        for (auto it = three_ary_tree.my_heap_begin(); it != three_ary_tree.my_heap_end(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }
}