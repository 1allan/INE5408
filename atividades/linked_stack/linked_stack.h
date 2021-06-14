namespace structures {

template<typename T>
class LinkedStack {
 public:
    LinkedStack();
    ~LinkedStack();
    void clear();
    void push(const T& data);
    T pop();
    T& top() const;
    bool empty() const;
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

        void next(Node* next) {
            next_ = next;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* top_{nullptr};
    std::size_t size_{0u}
};

}  // namespace structures

template<typename T>
structures::LinkedStack<T>::LinkedStack() {}

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

template<typename T>
void structures::LinkedStack<T>::clear() {
    Node* last = top_;
    for (std::size_t i = 0; i < size_; i++) {
        Node* next = last->next();
        delete last;
        last = next;
    }
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node* new_node = new Node(data, top_);
    top_ = new_node;
    size_++;
}

template<typename T>
T structures::LinkedStack<T>::pop() {
    if (size_ == 0) {
        throw std::out_of_range("the stack is empty");
    }
    Node* popped = top_;
    T data = popped->data();
    top_ = popped->next();
    delete popped;
    size_--;
    return data;
}

template<typename T>
T& structures::LinkedStack<T>::top() const {
    if (size_ == 0) {
        throw std::out_of_range("the stack is empty");
    }
    return top_->data();
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
    return size_ == 0;
}

template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}
