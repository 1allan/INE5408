// Copyright 2021 Allan Soares Silva
#include <algorithm>
#include "array_list.h"


namespace structures {

template<typename T>
class AVLTree {
public:
    AVLTree() = default;

    ~AVLTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    int height() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

private:
    struct Node {
        explicit Node(const T& data_) :
            data{data_},
            height_{0},
            left{nullptr},
            right{nullptr}
        {}

        T data;
        int height_;
        Node* left;
        Node* right;

        void insert(const T& data_) {
            if (data_ < this->data) {
                Node* rotated = nullptr;
                if (this->left->height - this->right->right > 1) {
                    if (data_ < this->left->data) {
                        rotated = simpleLeft(this);
                    } else {
                        rotated = doubleLeft(this);
                    }
                }
                if (pai->left == this) {
                    pai->left = rotated
                } else {
                    pai->right = rotated
                }
            } else {
                this->height_ = max(this->left->height, this->right->height+1)
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

        void updateHeight(const int& height) {
            if (this->left != nullptr || this->rigth != nullptr) {
                this->heigth++;
            }
        }

        Node* simpleLeft(Node* k2) {
            Node* k1;
            k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            k2->updateHeight(max(k2->left->height(), k2->right->height()));
            k1->updateHeight(max(k1->left->height(), k2->height()));
            return k1;
        }

        Node* simpleRight(Node* k2) {
            Node* k1;
            k1 = k2->right;
            k2->right = k1->left;
            k1->left = k2;
            k2->updateHeight(max(k2->right->height(), k2->left->height()));
            k1->updateHeight(max(k1->right->height(), k2->height()));
            return k1;
        }

        Node* doubleLeft(Node* k3) {
            k3->left = simpleRight(k3->left);
            return simpleLeft(k3);
        }

        Node* doubleRight(Node* k3) {
            k3->right = simpleLeft(k3->right);
            return simpleRight(k3);
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

        int height() {
            return height_;
        }
    };

    Node* root{nullptr};
    std::size_t size_{0};
};
}  // namespace structures

// -----

template<typename T>
structures::AVLTree<T>::~AVLTree() {
    size_ = 0;
    delete root;
}

template<typename T>
void structures::AVLTree<T>::insert(const T& data) {
    if (size_ == 0) {
        root = new Node(data);
    } else {
        root->insert(data);
    }
    size_++;
}

template<typename T>
void structures::AVLTree<T>::remove(const T& data) {
    if (size_ == 0) {
        throw std::out_of_range("Empty tree.");
    }

    if (contains(data)) {
        root->remove(data);
    }
    size_--;
}

template<typename T>
bool structures::AVLTree<T>::contains(const T& data) const {
    bool output = false;

    if (size_ > 0) {
        output = root->contains(data);
    }

    return output;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
    structures::ArrayList<T> output{};

    if (size_ > 0) {
        root->post_order(output);
    }

    return output;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
    structures::ArrayList<T> output{};

    if (size_ > 0) {
        root->in_order(output);
    }

    return output;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
    structures::ArrayList<T> output{};

    if (size_ > 0) {
        root->pre_order(output);
    }

    return output;
}

template<typename T>
bool structures::AVLTree<T>::empty() const {
    return size_ == 0;
}

template<typename T>
std::size_t structures::AVLTree<T>::size() const {
    return size_;
}

template<typename T>
int structures::AVLTree<T>::height() const {
    return root->height();
}
