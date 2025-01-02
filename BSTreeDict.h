#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include <vector>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>>* tree;

public:
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    ~BSTreeDict() {
        delete tree;
    }

    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
        out << *bs.tree;
        return out;
    }

    V operator[](std::string key) {
        return search(key);
    }

    std::vector<TableEntry<V>> entries() const {
        std::vector<TableEntry<V>> entries;
        inorder_entries(entries, tree->root);
        return entries;
    }

    void insert(std::string key, V value) {
        TableEntry<V> entry(key, value);
        tree->insert(entry);
    }

    V search(std::string key) const {
        TableEntry<V> entry(key, V());
        TableEntry<V> found = tree->search(entry);
        return found.value;
    }

    void remove(std::string key) {
        TableEntry<V> entry(key, V());
        tree->remove(entry);
    }

private:
    void inorder_entries(std::vector<TableEntry<V>>& entries, BSNode<TableEntry<V>>* node) const {
        if (node == nullptr) return;
        inorder_entries(entries, node->left);
        entries.push_back(node->elem);
        inorder_entries(entries, node->right);
    }
};

#endif

