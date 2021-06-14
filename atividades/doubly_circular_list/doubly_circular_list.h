namespace structures {

template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList();
    ~DoublyCircularList();
    void clear();

    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);

    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);

    bool empty() const;
    bool contains(const T& data) const;

    T& at(std::size_t index);
    const T& at(std::size_t index) const;

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

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }

        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
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
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

    Node* node_at(std::size_t index) {
        Node* it = head;
        for (std::size_t i = 0; i < index; ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    Node* tail{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {}

template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

template<typename T>
void structures::DoublyCircularList<T>::clear() {
    Node* last = head;
    for (std::size_t i = 0; i < size_; i++) {
        Node* next = last->next();
        delete last;
        last = next;
    }
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    Node* new_node = new Node(data);
    if (size_ == 0) {
        head = new_node;
    } else {
        tail->next(new_node);
        new_node->prev(tail);
        new_node->next(head);
        head->prev(new_node);
    }
    tail = new_node;
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node* new_node = new Node(data, head);
    if (size_ > 0) {
        head->prev(new_node);
    }
    head = new_node;
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::insert(
                                         const T& data, std::size_t index) {
    if (index < 0 || index > size_) {
        throw std::out_of_range("invalid index");
    } else if (index == 0) {
        push_front(data);
    } else {
        Node* current = node_at(index);
        Node* new_node = new Node(data, current->prev(), current);
        current->prev()->next(new_node);
        size_++;
    }
}

template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
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
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (size_ == 0) {
        throw std::out_of_range("the list is empty");
    }
    if (index < 0 || index >= size_) {
        throw std::out_of_range("invalid index");
    } else if (index == 0) {
        return pop_front();
    }
    Node* popped = node_at(index);
    Node* previous = popped->prev();
    Node* following = popped->next();
    if (following != nullptr) {
        following->prev(previous);
    }
    previous->next(following);

    T data = popped->data();
    delete popped;
    size_--;
    return data;
}

template<typename T>
T structures::DoublyCircularList<T>::pop_back() {
    return pop(size_ - 1);
}

template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    if (size_ == 0) {
        throw std::out_of_range("the list is empty");
    }
    T data = head->data();
    Node* new_head = head->next();
    delete head;
    size_--;
    head = new_head;
    return data;
}

template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
    pop(find(data));
}


template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
    return find(data) != size_;
}

template<typename T>
T& structures::DoublyCircularList<T>::at(std::size_t index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("invalid index");
    }
    return node_at(index)->data();
}

template<typename T>
const T& structures::DoublyCircularList<T>::at(std::size_t index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("invalid index");
    }
    return node_at(index)->data();
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
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
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}
