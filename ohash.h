//
// Created by rudri on 6/25/2022.
//

#ifndef PROG3_HASH_TABLES_LAB102_2022_1_OHASH_H
#define PROG3_HASH_TABLES_LAB102_2022_1_OHASH_H

#include <functional>
#include <vector>
#include <memory>

// Template de Alias de tipos
template<typename KeyType, typename ValueType>
using item_t = std::pair<KeyType, ValueType>;

template<typename KeyType, typename ValueType>
using bucket_t = std::vector<std::shared_ptr<item_t<KeyType, ValueType>>>;

template<typename KeyType, typename ValueType>
class open_hash_table {
    size_t m = 0;
    bucket_t<KeyType, ValueType> table;

    size_t linear_probing(KeyType key, size_t i) {
        std::hash<KeyType> pre_hash_fun;
        return (pre_hash_fun(key) + 1) % m;
    }
public:
    // Constructor por parametro
    explicit open_hash_table(size_t m): m(m), table(m) {}
    // No se necesita: destructor, constructor copia, operador asignación-copia

    // Insertar
    std::pair<std::shared_ptr<item_t<KeyType, ValueType>>, bool>
        insert(const item_t<KeyType, ValueType> &item) {
        size_t i = 0, idx;
        do {
            // Indice inicial
            idx = linear_probing(item.first, i++);
            // Validación del límite de i
            if (i >= m) return {nullptr, false};
            // Si existe el Key entonces me detengo de buscarlo
            if (table[idx] && table[idx]->first == item.first) return {nullptr, false};
        } while (table[idx]);
        // Si no existe el key dentro del hash, insertarlo
        table[idx] = std::make_shared<item_t<KeyType, ValueType>>(item);
        return {table[idx], true};
    }

    // Buscar
    std::pair<std::shared_ptr<item_t<KeyType, ValueType>>, bool>
        find(const KeyType& key) {
        size_t i = 0, idx;
        do {
            // Indice inicial
            idx = linear_probing(key, i++);
            // Validación del límite de i
            if (i >= m) return {nullptr, false};
            // Si existe el Key lo retorno
            if (table[idx] && table[idx]->first == key) return {table[idx], true};
        } while (table[idx]);
        return {nullptr, false};
    }
    // Remover
    bool remove(const KeyType& key) {
        size_t i = 0, idx;
        // Buscar el valor que va borrar
        do {
            // Indice inicial
            idx = linear_probing(key, i++);
            // Validación del límite de i
            if (i >= m) return false;
        } while (table[idx] && table[idx]->first != key);
        // Si lo encuentra
        if (table[idx] && table[idx]->first == key)
            table[idx] = nullptr;
        else
            return false;
        // Si lo encuentra debe reubicar el resto de valores
        auto next_idx = linear_probing(key, i);
        do {
            if (i >= m) return true;
            if (table[next_idx] && next_idx == linear_probing(table[next_idx]->first, i++)) {
                swap(table[idx], table[next_idx]);
                idx = next_idx;
            }
            next_idx = linear_probing(key, i);
        } while (table[next_idx]);
        return true;
    }
};

#endif //PROG3_HASH_TABLES_LAB102_2022_1_OHASH_H
