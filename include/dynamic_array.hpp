#pragma once
#include <stdexcept>
#include <vector>

#define VOLUME_COEFFICIENT 1.5

template <typename value_t>
class Array {
public:
    Array(unsigned int volume) {
        this->size = 0;
        this->volume = volume;
        arr = new value_t[volume];
    }

    value_t at(unsigned int pos) {
        if (pos < this->size)
            return this->arr[pos];
        else
            throw std::out_of_range("Index out of range");
    }

    void push_back(value_t val) {
        this->size++;
        if (this->size >= volume) {
            volume *= VOLUME_COEFFICIENT;
            value_t *new_arr = new value_t[volume];
            for (unsigned int i = 0; i < this->size; i++) {
                new_arr[i] = this->arr[i];
            }
            delete[] this->arr;
            this->arr = new_arr;
        }
        this->arr[size-1] = val;
    }

    unsigned int get_size(void) {
        return this->size;
    }

    value_t pop(unsigned int pos) {
        value_t retval = this->at(pos);
        size--;
        for (unsigned int i = pos; i < size; i++) {
            arr[i] = arr[i+1];
        }
        return retval;
    }

    void pop(std::vector<unsigned int> &pos_pool) {
        std::sort(pos_pool.begin(), pos_pool.end());
        for (unsigned int i = 1; i < pos_pool.size(); i++) {
            pos_pool[i] -= i;
        }
        for (auto pos : pos_pool) {
            this->pop(pos);
        }
        return;
    }

    void insert(value_t val, unsigned int pos) {
        this->push_back(arr[size-1]);
        for (unsigned int i = size-2; i > pos; i--)
            arr[i] = arr[i-1];
        arr[pos] = val;
        return;
    }

private:
    value_t *arr;
    unsigned int size;
    unsigned int volume;
};