#include <iostream>

#include "dynamic_array.hpp"

void print_array(Array<int> &array) {
    for (int i = 0; i < array.get_size(); i++) {
        std::cout << array.at(i) << ' ';
    } std::cout << '\n';
    return;
}

int main() {
    Array<int> array(5);
    for (int i = 0; i < 10; i++) {
        array.push_back(i);
    }

    print_array(array);

    std::cout << array.get_size() << '\n';

    std::vector<unsigned int> to_delete = { 2, 4, 6 };
    array.pop(to_delete);
    print_array(array);

    array.insert(10, 0);
    print_array(array);

    array.insert(20, 4);
    print_array(array);

    array.push_back(30);
    print_array(array);

    return 0;
}