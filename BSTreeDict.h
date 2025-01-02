#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

using namespace std;

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

    int entries() override {
        return tree->size();
    }

    void insert(string key, V value) override {
        TableEntry<V> entry(key, value);
        tree->insert(entry);
    }

    V search(string key) override {
        TableEntry<V> entry(key);
        return tree->search(entry).value;
    }

    V remove(string key) override {
        TableEntry<V> entry(key);
        V value = tree->search(entry).value;
        tree->remove(entry);
        return value;
    }

    V operator[](string key) {
        return search(key);
    }

    friend ostream& operator<<(ostream& out, const BSTreeDict<V>& bs) {
        out << *(bs.tree);
        return out;
    }
};

#endif
