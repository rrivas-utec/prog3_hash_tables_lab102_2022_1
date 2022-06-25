#include <iostream>
#include <functional>
#include <string>
#include "chash.h"

using namespace std;

void ejemplo_funciones_hash() {

    hash<string> hash_string_fun;
    hash<bool> hash_bool_fun;
    hash<char> hash_char_fun;

    string nombre = "Enrique Vivanco";
    cout << hash_string_fun(nombre) << endl;
    cout << hash_bool_fun(true) << endl;
    cout << hash_bool_fun(true) << endl;
    cout << hash_bool_fun(false) << endl;
    cout << hash_bool_fun(false) << endl;
    cout << hash_char_fun('A') << endl;
    cout << hash_char_fun('B') << endl;
}

int main() {
    ejemplo_funciones_hash();
    close_hash_table<string, int> ht(10);
    ht.insert({"A", 1});
    ht.insert({"B", 2});
    ht.insert({"C", 3});

    auto [item, found] = ht.find("A");
    if (found)
        std::cout << item->second << std::endl;
    else
        std::cout << "Not Found\n";

    auto removed = ht.remove("A");
    if (removed)
        std::cout << "Removido\n";

    auto [item2, found2] = ht.find("A");
    if (found2)
        std::cout << item->second << std::endl;
    else
        std::cout << "Not Found\n";

    return 0;
}
