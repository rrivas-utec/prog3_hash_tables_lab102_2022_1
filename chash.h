//
// Created by rudri on 6/22/2022.
//

#ifndef PROG3_HASH_TABLES_LAB102_2022_1_CHASH_H
#define PROG3_HASH_TABLES_LAB102_2022_1_CHASH_H

#include <functional>
#include <forward_list>
#include <optional>

// Template de hash
template<typename T>
size_t hash_function(T key, size_t m) {
    std::hash<T> pre_hash_fun;
    auto numeric_key = pre_hash_fun(key);
    return numeric_key % m;
}

// Template de Alias de tipos
template<typename KeyType, typename ValueType>
using item_t = std::pair<KeyType, ValueType>;

template<typename KeyType, typename ValueType>
using chain_t = std::forward_list<item_t<KeyType, ValueType>>;

template<typename KeyType, typename ValueType>
class close_hash_table {
    size_t m = 0;
    chain_t<KeyType, ValueType>* table = nullptr;
public:
    // Constructor por parameters
    explicit close_hash_table(size_t m) : m(m) {
        table = new chain_t<KeyType, ValueType>[m];
    }

    // Destructor
    ~close_hash_table() {
        delete [] table;
    }

    // Constructor copia
    close_hash_table(const close_hash_table<KeyType, ValueType> &other)
            : m(other.m) {
        table = new chain_t<KeyType, ValueType>[m];
        copy(other.table, other.table + m, table);
    }

    // Operador asignación copia
    close_hash_table<KeyType, ValueType> &operator=(const close_hash_table<KeyType, ValueType> &other) {
        if (&other == this) return *this;
        delete[] table;
        m = other.m;
        table = new chain_t<KeyType, ValueType>[m];
        copy(other.table, other.table + m, table);
        return *this;
    }

    // Solo funciona en escritura (variable)
    std::pair<item_t<KeyType, ValueType>*, bool> insert(const item_t<KeyType, ValueType> &item) {
        // Indice del slot
        auto index_slot = hash_function(item.first, m);
        // La cadena dentro del slot
        auto& chain = table[index_slot];
        // Busca el key dentro de la cadena
        auto it = find_if(begin(chain), end(chain),
                          [item](auto current) {
                              return item.first == current.first;
                          });
        // Si NO lo ha encontrado inserta el valor y return el par ordenado
        if (it == end(chain)) {
            chain.push_front(item);
            return {&chain.front(), true};
        }
        // Si lo ha encontrado entonces retorna falso
        return {nullptr, false};
    }

    std::pair<item_t<KeyType, ValueType>*, bool> find(const KeyType &key) {
        // Indice del slot
        auto index_slot = hash_function(key, m);
        // La cadena dentro del slot
        auto& chain = table[index_slot];
        // Busca el key dentro de la cadena
        auto it = find_if(begin(chain), end(chain),
                          [key](auto current) {
                              return key == current.first;
                          });
        // Si lo encuentra retorna el valor
        if (it != end(chain)) {
            return {&(*it), true};
        }
        // Si no lo encuentra retorna falso
        return {nullptr, false};
    }

    bool remove(const KeyType &key) {
        // Indice del slot
        auto index_slot = hash_function(key, m);
        // La cadena dentro del slot
        auto &chain = table[index_slot];
        // Remuevo el valor
        auto old_size = std::distance(begin(chain), end(chain));
        chain.remove_if(
                [key](auto current) {
                    return key == current.first;
                });
        auto new_size = std::distance(begin(chain), end(chain));
        return new_size < old_size;
    }
};


#endif //PROG3_HASH_TABLES_LAB102_2022_1_CHASH_H
