#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>
#include <stdexcept>

namespace structures {
template<typename T>
class ArrayStack {
 public:
    ArrayStack();
    explicit ArrayStack(std::size_t max);
    ~ArrayStack();
    void push(const T& data);
    T pop();
    T& top();
    void clear();
    std::size_t size();
    std::size_t max_size();
    bool empty();
    bool full();
 private:
    T* contents;
    int top_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif

template<typename T>
structures::ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    top_ = -1;
}

template<typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    top_ = -1;
}

template<typename T>
structures::ArrayStack<T>::~ArrayStack() {
    delete[] contents;
}

template<typename T>
void structures::ArrayStack<T>::push(const T& data) {
    if (full()) {
        throw std::out_of_range("Pilha cheia");
    } else {
        contents[++top_] = data;
    }
}

template<typename T>
T structures::ArrayStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Pilha vazia");
    } else {
        T element = contents[top_--];
        return element;
    }
}

template<typename T>
T& structures::ArrayStack<T>::top() {
    return contents[top_];
}

template<typename T>
void structures::ArrayStack<T>::clear() {
    top_ = -1;
}

template<typename T>
std::size_t structures::ArrayStack<T>::size() {
    return top_ + 1;
}

template<typename T>
std::size_t structures::ArrayStack<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayStack<T>::empty() {
    return top_ == -1;
}

template<typename T>
bool structures::ArrayStack<T>::full() {
    return top_ == (static_cast<int>(max_size()) - 1);
}
