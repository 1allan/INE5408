#include <stdexcept>

#include "array_list.h"


namespace structures {

template<typename T>
class BinaryTree {
public:
    BinaryTree() = default;

    ~BinaryTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    structures::ArrayList<T> pre_order() const;

    structures::ArrayList<T> in_order() const;

    structures::ArrayList<T> post_order() const;

private:
    struct Node {
         explicit Node(const T& data_) :
            data{data_},
            left{nullptr},
            right{nullptr}
        {}

        T data;
        Node* left{nullptr};
        Node* right{nullptr};

        void insert(const T& data_) {
            if (data_ > this->data) {
                if (this->right != nullptr) {
                    this->right->insert(data_);
                } else {
                    this->right = new Node(data_);
                }
            } else {
                if (this->left != nullptr) {
                    this->left->insert(data_);
                } else {
                    this->left = new Node(data_);
                }
            }
        }

        bool remove(const T& data_) {
            Node* next = nullptr;
            bool went_right = false;
            if (data_ > this->data) {
                next = this->right;
                went_right = true;
            } else {
                next = this->left;
            }
            if (next != nullptr) {
                if (next->data == data_) {
                    auto left_node = next->left;
                    auto right_node = next->right;
                    if (left_node == nullptr) {
                        delete next;
                        if (went_right) {
                            this->right = right_node;
                        } else {
                            this->left = right_node;
                        }
                    } else if (right_node == nullptr) {
                        delete next;
                        if (went_right) {
                            this->right = left_node;
                        } else {
                            this->left = left_node;
                        }
                    } else {
                        auto subtree = right_node;
                        auto subsubtree = subtree;
                        while (subtree->left != nullptr) {
                            subsubtree = subtree;
                            subtree = subtree->left;
                        }
                        subsubtree->left = subtree->right;
                        next->data = subtree->data;
                        delete subtree;
                    }
                    return true;
                } else {
                    next->remove(data_);
                }
            }
            return false;
        }

        bool contains(const T& data_) const {
            bool output = false;

            if (data_ == this->data) {
                return true;
            } else {
                if (data_ > this->data && this->right != nullptr) {
                    output = right->contains(data_);
                } else if (data_ < this->data && this->left != nullptr) {
                    output = left->contains(data_);
                }
            }

            return output;
        }

        void pre_order(structures::ArrayList<T>& v) const {
            v.push_back(this->data);

            if (this->left != nullptr) {
                left->pre_order(v);
            }

            if (this->right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(structures::ArrayList<T>& v) const {
            if (this->left != nullptr) {
                left->in_order(v);
            }

            v.push_back(this->data);

            if (this->right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(structures::ArrayList<T>& v) const {
            if (this->left != nullptr) {
                left->post_order(v);
            }

            if (this->right != nullptr) {
                right->post_order(v);
            }

            v.push_back(this->data);
        }
    };

    Node* root{nullptr};
    std::size_t size_{0};
};

}  // namespace structures


template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    size_ = 0;
    delete root;
}

template<typename T>
void structures::BinaryTree<T>::insert(const T& data) {
    if (empty()) {
        root = new Node(data);
    } else {
        root->insert(data);
    }
    size_++;
}

template<typename T>
void structures::BinaryTree<T>::remove(const T& data) {
    if (size_ == 0) {
        throw std::out_of_range("Empty tree");
    }

    if (root->remove(data)) {
        size_--;
    }
}

template<typename T>
bool structures::BinaryTree<T>::contains(const T& data) const {
    bool output = false;

    if (!empty()) {
        output = root->contains(data);
    }
    return output;
}

template<typename T>
bool structures::BinaryTree<T>::empty() const {
    return size_ == 0;
}

template<typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    structures::ArrayList<T> output{};

    if (size_ > 0) {
        root->pre_order(output);
    }

    return output;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    structures::ArrayList<T> output{};

    if (size_ > 0) {
        root->in_order(output);
    }

    return output;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    structures::ArrayList<T> output{};

    if (size_ > 0) {
        root->post_order(output);
    }

    return output;
}