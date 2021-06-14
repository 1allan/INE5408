#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class LinkedList {
 public:
    LinkedList();
    ~LinkedList();
    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T& at(std::size_t index);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* node_at(std::size_t index) {
        auto it = head;
        for (auto i = 0u; i < index; ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}

#endif

template<typename T>
structures::LinkedList<T>::LinkedList() {}

template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
void structures::LinkedList<T>::clear() {
    Node* last = head;
    for (std::size_t i = 0; i < size_; i++) {
        Node* next = last->next();
        delete[] last;
        last = next;
    }
    size_ = 0;
}

template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    insert(data, size_);
}

template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node* new_node = new Node(data, head);
    head = new_node;
    size_++;
}

template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index < 0 || index > size_) {
        throw std::out_of_range("invalid index");
    } else if (index == 0) {
        push_front(data);
    } else {
        Node* previous = node_at(index - 1);
        Node* following = previous->next();
        Node* new_node = new Node(data, following);
        previous->next(new_node);
        size_++;
    }
}

template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    Node* current = head;

    for (std::size_t i = 0; i < size_; i++) {
        if (data <= current->data()) {
            insert(data, i);
            return;
        }
        current = current->next();
    }
    push_back(data);
}

template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("invalid index");
    }
    return node_at(index)->data();
}

template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    if (size_ == 0) {
        throw std::out_of_range("the list is empty");
    }
    if (index < 0 || index >= size_) {
        throw std::out_of_range("invalid index");
    } else if (index == 0) {
        return pop_front();
    }
    Node* previous = node_at(index - 1);
    Node* popped = previous->next();
    previous->next(popped->next());

    T data = popped->data();
    delete[] popped;
    size_--;
    return data;
}

template<typename T>
T structures::LinkedList<T>::pop_back() {
    return pop(size_ - 1);
}

template<typename T>
T structures::LinkedList<T>::pop_front() {
    if (size_ == 0) {
        throw std::out_of_range("the list is empty");
    }
    T data = head->data();
    Node* new_head = head->next();
    delete[] head;
    size_--;
    head = new_head;
    return data;
}

template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    pop(find(data));
}

template<typename T>
bool structures::LinkedList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    return find(data) != size_;
}

template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    Node* current = head;
    for (std::size_t i = 0; i < size_; i++) {
        if (data == current->data()) {
            return i;
        }
        current = current->next();
    }
    return size_;
}

template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}
