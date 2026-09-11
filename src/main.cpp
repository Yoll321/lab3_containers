#include <iostream>
#include <utility>

#include "dynamic_array.hpp"
#include "node_list.hpp"
#include "node_list2.hpp"

#define NODE_LIST_TYPE NodeList2

void print_array(Array<int> &array) {
    for (int i = 0; i < array.size(); i++) {
        std::cout << array.at(i) << ' ';
    } std::cout << '\n';
    return;
}

void print_node_list(NodeList<int> &node_list) {
    auto i = node_list.begin();
    while (i != node_list.end()) {
        std::cout << *i << ' ';
        ++i;
    } std::cout << '\n';
    return;
}

void print_node_list(NodeList2<int> &node_list) {
    auto i = node_list.begin();
    while (i != node_list.end()) {
        std::cout << *i << ' ';
        ++i;
    } std::cout << '\n';
    return;
}

int main() {
    std::cout << "~~~~~~~~~~~~~~~~~~\n";
    std::cout << "Array testing:\n";
    std::cout << "~~~~~~~~~~~~~~~~~~\n";
    
    Array<int> array(5);
    for (int i = 0; i < 10; i++) {
        array.push_back(i);
    }

    print_array(array);

    std::cout << array.size() << '\n';

    std::vector<unsigned int> to_delete = { 2, 4, 6 };
    array.pop(to_delete);
    print_array(array);

    array.insert(10, 0);
    print_array(array);

    array.insert(20, 4);
    print_array(array);

    array.push_back(30);
    print_array(array);

    std::cout << "~~~~~~~~~~~~~~~~~~\n";
    std::cout << "NodeList testing:\n";
    std::cout << "~~~~~~~~~~~~~~~~~~\n";

    NODE_LIST_TYPE<int> node_list;
    for (int i = 0; i < 10; i++) {
        node_list.push_back(i);
    }
    print_node_list(node_list);

    std::cout << node_list.size() << '\n';

    node_list.erase(to_delete);
    print_node_list(node_list);

    node_list.insert(10, 0);
    print_node_list(node_list);

    node_list.insert(20, 4);
    print_node_list(node_list);

    node_list.insert(30, node_list.size());
    print_node_list(node_list);

    std::cout << "~~~~~~~~~~~~~~~~~~\n";
    std::cout << "New List:\n";
    std::cout << "~~~~~~~~~~~~~~~~~~\n";
    NODE_LIST_TYPE<int> new_list = std::move(node_list);
    print_node_list(new_list);

    std::cout << "~~~~~~~~~~~~~~~~~~\n";
    std::cout << "New Array:\n";
    std::cout << "~~~~~~~~~~~~~~~~~~\n";
    Array<int> new_array = std::move(array);
    print_array(new_array);

    return 0;
}