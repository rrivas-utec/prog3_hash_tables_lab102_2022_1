#include <iostream>
#include <functional>
#include <string>

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
    return 0;
}
