#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "/home/mlmonesc/PRA_2425_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {

private:
    int n;            
    int max;                
    ListLinked<TableEntry<V>>* table; 

    int h(std::string key) {
        int sum = 0;
        for (char c : key) {
            sum += static_cast<int>(c);
        }
        return sum % max;
    }

public:
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];
    }

    ~HashTable() {
        delete[] table;
    }

    int capacity() {
        return max;
    }

    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
        for (int i = 0; i < th.max; ++i) {
            out << "Cubeta " << i << ": ";
            if (th.table[i].size() == 0) {
                out << "Vacía";
            } else {
                for (const auto& entry : th.table[i]) {
                    out << entry << " ";
                }
            }
            out << std::endl;
        }
        return out;
    }

    V operator[](std::string key) {
        return search(key);
    }

    void insert(std::string key, V value) override {
        int index = h(key);
        TableEntry<V> entry(key, value);
        if (table[index].contains(entry)) {
            throw std::runtime_error("Key already exists");
        }
        table[index].insert(entry);
        ++n;
    }

    V search(std::string key) override {
        int index = h(key);
        TableEntry<V> entry(key);
        if (!table[index].contains(entry)) {
            throw std::runtime_error("Key not found");
        }
        return table[index].get(entry)->value;
    }

    V remove(std::string key) override {
        int index = h(key);
        TableEntry<V> entry(key);
        if (!table[index].contains(entry)) {
            throw std::runtime_error("Key not found");
        }
        table[index].remove(entry);
        --n;
        return entry.value;
    }

    int entries() override {
        return n;
    }
};

#endif
