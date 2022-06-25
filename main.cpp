#include <iostream>
#include <string>
#include "chash.h"
#include "ohash.h"

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

void ejemplo_close_hash() {
    close_hash_table<string, int> ch(10);
    auto result = ch.insert({"A", 1});
    if (result.second)
        cout << "Valor Ingresado: {" << result.first->first << ", " << result.first->second << "}\n";
    else
        cout << "No ingresado\n";

    result =  ch.insert({"A", 20});
    if (result.second)
        cout << "Valor Ingresado: {" << result.first->first << ", " << result.first->second << "}\n";
    else
        cout << "No ingresado\n";

    ch.insert({"B", 2});
    ch.insert({"C", 3});

    result = ch.find("A");
    if (result.second)
        cout << "Valor Encontrado: {" << result.first->first << ", " << result.first->second << "}\n";
    else
        std::cout << "No encontrado\n";

    auto removed = ch.remove("A");
    if (removed)
        std::cout << "Removido\n";

    result = ch.find("A");
    if (result.second)
        cout << "Valor Encontrado: {" << result.first->first << ", " << result.first->second << "}\n";
    else
        std::cout << "No encontrado\n";
}

void ejemplo_open_hash() {
    close_hash_table<string, int> oh(10);
    auto result = oh.insert({"A", 1});
    if (result.second)
        cout << "Valor Ingresado: {" << result.first->first << ", " << result.first->second << "}\n";
    else
        cout << "No ingresado\n";

    result =  oh.insert({"A", 20});
    if (result.second)
        cout << "Valor Ingresado: {" << result.first->first << ", " << result.first->second << "}\n";
    else
        cout << "No ingresado\n";

    oh.insert({"B", 2});
    oh.insert({"C", 3});

    result = oh.find("A");
    if (result.second)
        cout << "Valor Encontrado: {" << result.first->first << ", " << result.first->second << "}\n";
    else
        std::cout << "No encontrado\n";

    auto removed = oh.remove("A");
    if (removed)
        std::cout << "Removido\n";

    result = oh.find("A");
    if (result.second)
        cout << "Valor Encontrado: {" << result.first->first << ", " << result.first->second << "}\n";
    else
        std::cout << "No encontrado\n";
}

int main() {
//    ejemplo_funciones_hash();
    ejemplo_close_hash();
    cout << "-------\n";
    ejemplo_close_hash();
    return 0;
}
