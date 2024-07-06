/**
 * Demo app for Ex4
 */
#include <iostream>
#include <string>
#include "Node.hpp"
#include "Tree.hpp"
#include "Complex.hpp"

using namespace std;

int main()
{

    // Binary tree
    Node<double> root_node(1.1);
    Tree<double> tree;
    tree.add_root(root_node);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    cout << "Binary PreOrder: ";
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    cout << "\n" << endl;

    cout << "Binary PostOrder: ";
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1

    cout << "\n" << endl;

    cout << "Binary InOrder: ";
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    cout << "\n" << endl;

    cout << "Binary BFS: ";
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << "\n" << endl;

    cout << "Binary regular loop: ";
    for (auto node : tree)
    {
        cout << node << " ";
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << "\n" << endl;

    tree.showTree(); // Should print the graph using GUI.

    root_node.clear_children();
    n1.clear_children();
    n2.clear_children();

    // 3-ary tree
    Tree<double,3> three_ary_tree;
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */

    cout << "3-ary PreOrder: ";
    for (auto node = three_ary_tree.begin_pre_order(); node != three_ary_tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.1 1.2 1.5 1.3 1.6 1.4

    cout << "\n" << endl;

    cout << "3-ary PostOrder: ";
    for (auto node = three_ary_tree.begin_post_order(); node != three_ary_tree.end_post_order(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.1 1.2 1.5 1.3 1.6 1.4

    cout << "\n" << endl;

    cout << "3-ary InOrder: ";
    for (auto node = three_ary_tree.begin_in_order(); node != three_ary_tree.end_in_order(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.1 1.2 1.5 1.3 1.6 1.4

    cout << "\n" << endl;

    cout << "3-ary BFS: ";
    for (auto node = three_ary_tree.begin_bfs_scan(); node != three_ary_tree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.1 1.2 1.3 1.4 1.5 1.6

    cout << "\n" << endl;

    cout << "3-ary regular loop: ";
    for (auto node : three_ary_tree)
    {
        cout << node << " ";
    } // prints: 1.1 1.2 1.5 1.3 1.6 1.4

    cout << "\n" << endl;

    cout << "3-ary Heap: ";
    for (auto node = three_ary_tree.my_heap_begin(); node != three_ary_tree.my_heap_end(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.1 1.2 1.5 1.3 1.6 1.4

    cout << "\n" << endl;

    three_ary_tree.showTree();

    // Complex tree
    Node<Complex> root_cmp(Complex(1.1, 1.1));
    Tree<Complex> cmpTree;
    cmpTree.add_root(root_cmp);
    Node<Complex> one(Complex(2.2, -2.2));
    Node<Complex> two(Complex(-3.3, 3.3));
    Node<Complex> three(Complex(-4.4, -4.4));
    Node<Complex> four(Complex(5.5, 5.5));
    Node<Complex> five(Complex(6.6, 6.6));

    cmpTree.add_sub_node(root_cmp, one);
    cmpTree.add_sub_node(root_cmp, two);
    cmpTree.add_sub_node(one, three);
    cmpTree.add_sub_node(one, four);
    cmpTree.add_sub_node(two, five);

    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    2.2      -3.3
     *   /  \      /
     * -4.4  5.5  6.6
     */

    cout << "Complex PreOrder: ";
    for (auto node = cmpTree.begin_pre_order(); node != cmpTree.end_pre_order(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.1 2.2 -4.4 5.5 -3.3 6.6

    cout << "\n" << endl;

    cout << "Complex PostOrder: ";
    for (auto node = cmpTree.begin_post_order(); node != cmpTree.end_post_order(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: -4.4 5.5 2.2 6.6 -3.3 1.1

    cout << "\n" << endl;

    cout << "Complex InOrder: ";
    for (auto node = cmpTree.begin_in_order(); node != cmpTree.end_in_order(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: -4.4 2.2 5.5 1.1 6.6 -3.3

    cout << "\n" << endl;

    cout << "Complex DFS: ";
    for (auto node = cmpTree.begin_dfs_scan(); node != cmpTree.end_dfs_scan(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.1 2.2 -4.4 5.5 -3.3 6.6

    cout << "\n" << endl;

    cout << "Complex BFS: ";
    for (auto node = cmpTree.begin_bfs_scan(); node != cmpTree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.1 2.2 -3.3 -4.4 5.5 6.6

    cout << "\n" << endl;

    cout << "Complex regular loop: ";
    for (auto node : cmpTree)
    {
        cout << node << " ";
    } // prints: 1.1 2.2 -3.3 -4.4 5.5 6.6

    cout << "\n" << endl;

    cout << "Complex Heap: ";
    for (auto node = cmpTree.my_heap_begin(); node != cmpTree.my_heap_end(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.1 2.2 -3.3 -4.4 5.5 6.6

    cout << "\n" << endl;

    cmpTree.showTree();

    return 0;
}