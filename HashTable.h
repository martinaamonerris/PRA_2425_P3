#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"
#include "/home/mlmonesc/PRA_2425_P1/ListLinked.h"  

using namespace std;

template <typename V>
class HashTable : public Dict<V> {
private:
    int n; 
    int max;
    ListLinked<TableEntry<V>>* table; 

    int h(const string& key) const {
        int sum = 0;
        for (char ch : key) {
            sum += static_cast<int>(ch);
        }
        return sum % max; 
    }

public:
    HashTable(int size) : n(0), max(size) {
        if (size <= 0) {
            throw invalid_argument("El tamaño de la tabla debe ser mayor que 0.");
        }
        table = new ListLinked<TableEntry<V>>[size]; 
    }

    ~HashTable() {
        delete[] table; 
    }

    int capacity() const { 
        return max; 
    }

    int entries() override {
        return n; 
    }

    void insert(string key, V value) override {
        try {
            search(key); 
        } catch (const runtime_error&) {
            table[h(key)].prepend(TableEntry<V>(key, value)); 
            n++;
            return;
        }
        throw runtime_error("La clave '" + key + "' ya existe.");
    }

    V search(string key) override {
        int bucket = h(key);
        for (int i = 0; i < table[bucket].size(); i++) {
            if (table[bucket].get(i).key == key) {
                return table[bucket].get(i).value; 
            }
        }
        throw runtime_error("La clave '" + key + "' no se encontró.");
    }

    V remove(string key) override {
        int bucket = h(key);
        for (int i = 0; i < table[bucket].size(); i++) {
            if (table[bucket].get(i).key == key) {
                TableEntry<V> removed = table[bucket].remove(i);
                n--;
                return removed.value;
            }
        }
        throw runtime_error("La clave '" + key + "' no se encontró.");
    }

    V operator[](string key) {
        return search(key);
    }

    friend ostream& operator<<(ostream &out, const HashTable<V> &th) {
        out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]" << std::endl;
        out << "==============" << endl << endl;
        for (int i = 0; i < th.max; i++) {
            out << "== Cubeta " << i << " ==" << std::endl << std::endl;
            out << "List => [";
            if (th.table[i].size() != 0) {
                out << endl;
                for (int j = 0; j < th.table[i].size(); j++) {
                    out << "  ('" << th.table[i].get(j).key << "' => " << th.table[i].get(j).value << ")" << endl;
                }
            }
            out << "]" << endl << endl;
        }
        out << "==============" << endl;
        return out;
    }
};

#endif
