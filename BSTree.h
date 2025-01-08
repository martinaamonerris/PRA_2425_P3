#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    int nelem;        
    BSNode<T>* root;  

public:
    BSTree() : nelem(0), root(nullptr) {}

    ~BSTree() {
        delete_cascade(root);
    }

    int size() const {
        return nelem;
    }

    T search(T e) const {
        BSNode<T>* found = search(root, e);
        if (found) {
            return found->elem;
        }
        throw std::runtime_error("Elemento no encontrado");
    }

    T operator[](T e) const {
        return search(e);
    }

    void insert(T e) {
        root = insert(root, e);
    }

    void remove(T e) {
        root = remove(root, e);
    }

    friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }

private:
    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr) {
            return nullptr;
        }
        if (e < n->elem) {
            return search(n->left, e);
        } else if (e > n->elem) {
            return search(n->right, e);
        } else {
            return n;
        }
    }

    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) {
            nelem++;
            return new BSNode<T>(e);  
        }
        if (e < n->elem) {
            n->left = insert(n->left, e);
        } else if (e > n->elem) {
            n->right = insert(n->right, e);
        } else {
            throw std::runtime_error("Elemento ya existe");
        }
        return n;
    }

    void print_inorder(std::ostream &out, BSNode<T>* n) const {
        if (n == nullptr) return;
        print_inorder(out, n->left);
        out << n->elem << " ";
        print_inorder(out, n->right);
    }

    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (n == nullptr) {
            throw std::runtime_error("Elemento no encontrado");
        }

        if (e < n->elem) {
            n->left = remove(n->left, e);
        } else if (e > n->elem) {
            n->right = remove(n->right, e);
        } else {  
            if (n->left == nullptr) {
                BSNode<T>* temp = n->right;
                delete n;
                nelem--;
                return temp;
            } else if (n->right == nullptr) {
                BSNode<T>* temp = n->left;
                delete n;
                nelem--;
                return temp;
            }
            T max_value = max(n->left);  
            n->elem = max_value;  
            n->left = remove(n->left, max_value);  
        }
        return n;
    }

    T max(BSNode<T>* n) const {
        while (n->right != nullptr) {
            n = n->right;
        }
        return n->elem;
    }

    BSNode<T>* remove_max(BSNode<T>* n) {
        if (n->right == nullptr) {
            BSNode<T>* temp = n->left;
            delete n;
            nelem--;
            return temp;
        }
        n->right = remove_max(n->right);
        return n;
    }

    void delete_cascade(BSNode<T>* n) {
        if (n == nullptr) return;
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }
};

#endif
