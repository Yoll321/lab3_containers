#pragma once
#include <stdexcept>
#include <vector>

#define VOLUME_COEFFICIENT 1.5

template <typename value_t>
class Array {
public:
    Array(unsigned int volume) {
        this->size_val = 0;
        this->volume = volume;
        arr = new value_t[volume];
    }

    void clear(void) {
        delete[] arr;
    }

    Array(Array&& other)
        : arr(other.arr), size_val(other.size_val), volume(other.volume) {
        other.arr = nullptr;
        other.size_val = 0;
        other.volume = 0;
    }

    Array& operator=(Array&& other) {
        if (this != other) {
            clear();
            arr = other.arr;
            size_val = other.size_val;
            volume = other.volume;

            other.arr = nullptr;
            other.size_val = 0;
            other.volume = 0;
        }

        return *this;
    }

    ~Array(void) {
        clear();
    }

    value_t at(unsigned int pos) {
        if (pos < this->size_val)
            return this->arr[pos];
        else
            throw std::out_of_range("Index out of range");
    }

    void push_back(value_t val) {
        this->size_val++;
        if (this->size_val >= volume) {
            volume *= VOLUME_COEFFICIENT;
            value_t *new_arr = new value_t[volume];
            for (unsigned int i = 0; i < this->size_val; i++) {
                new_arr[i] = this->arr[i];
            }
            delete[] this->arr;
            this->arr = new_arr;
        }
        this->arr[size_val-1] = val;
    }

    unsigned int size(void) {
        return this->size_val;
    }

    value_t pop(unsigned int pos) {
        value_t retval = this->at(pos);
        size_val--;
        for (unsigned int i = pos; i < size_val; i++) {
            arr[i] = arr[i+1];
        }
        return retval;
    }

    void pop(std::vector<unsigned int> pos_pool) {
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
        this->push_back(arr[size_val-1]);
        for (unsigned int i = size_val-2; i > pos; i--)
            arr[i] = arr[i-1];
        arr[pos] = val;
        return;
    }

    value_t operator[](unsigned int pos) {
        return arr[pos];
    }

private:
    value_t *arr;
    unsigned int size_val;
    unsigned int volume;
};