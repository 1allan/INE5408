namespace structures {


template<typename T>
class LinkedQueue {
 public:
    LinkedQueue();
    ~LinkedQueue();
    void clear();
    void enqueue(const T& data);
    T dequeue();
    T& front() const;
    T& back() const;
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

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* head{nullptr};
    Node* tail{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures


template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {}

template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
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
void structures::LinkedQueue<T>::enqueue(const T& data) {
    Node* new_node = new Node(data);
    if (size_ == 0) {
        head = new_node;
    } else {
        tail->next(new_node);
    }
    tail = new_node;
    size_++;
}

template<typename T>
T structures::LinkedQueue<T>::dequeue() {
    if (size_ == 0) {
        throw std::out_of_range("the stack is empty");
    }
    Node* popped = head;
    T data = popped->data();
    head = popped->next();
    delete popped;
    size_--;
    return data;
}

template<typename T>
T& structures::LinkedQueue<T>::front() const {
    if (size_ == 0) {
        throw std::out_of_range("the stack is empty");
    }
    return head->data();
}

template<typename T>
T& structures::LinkedQueue<T>::back() const {
    if (size_ == 0) {
        throw std::out_of_range("the stack is empty");
    }
    return tail->data();
}

template<typename T>
bool structures::LinkedQueue<T>::empty() const {
    return size_ == 0;
}

template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    return size_;
}
