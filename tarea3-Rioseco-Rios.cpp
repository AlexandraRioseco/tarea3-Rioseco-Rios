#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct cuenta {
    string rol, nombre, descripcion; // El rol es el identificador de la persona, el nombre y la descripcion son valores asociados al rol
    bool ocupado; // Valor bool si la cuenta está ocupada o no
    cuenta() : ocupado(false) {} // La cuenta no está ocupada en un principio
};

class registro_cuentas {
private:
    float factor_de_carga = 0.0;
    cuenta *tabla; // Aca se almacenaran los elementos de la tabla
    int ranuras = 15; // Cuantas ranuras tiene la tabla hash (inicialmente)
    int numElementos = 0; // El número de elementos en la tabla

    /*****
    * int hash
    ******
    * Calcula el valor hash para un rol dado
    ******
    * Input:
    * string rol : El rol para el cual se calculará el valor hash
    ******
    * Returns:
    * unsigned int hash_value: El índice de la ranura que se consulta.
    *****/

    int hash(string rol) { // Se obtiene el hash dado el rol
        unsigned int hash_value = 0;
        for (char c : rol) {
            hash_value = (hash_value * 31 + c) % ranuras;
        }
        return hash_value;
    }

    /*****
     * int p
    ******
    * Calcula la ranura a revisar en caso de colisión.
    ******
    * Input:
    * string rol : El rol a insertar o buscar.
    * int i : El intento actual de resolución de colisión.
    ******
    * Returns:
    * int (hash(rol) + i) % ranuras: El valor de la ranura a revisar
    *****/

    int p(string rol, int i) { // Se otiene la ranura a revisar en caso de colisión dado el rol y el intento i
        return (hash(rol) + i) % ranuras;
    } 

public:

    /*****
    * registro_cuentas::registro_cuentas
    ******
    * Constructor de la clase registro_cuentas.
    ******
    * Input:
    * No tiene input como tal, solo construye una tabla.
    ******
    * Returns:
    * Void, no hace un return como tal.
    *****/

    registro_cuentas() {
        tabla = new cuenta[ranuras];
    }

    /*****
    * registro_cuentas::~registro_cuentas
    ******
    * Destructor de la clase registro_cuentas.
    ******
    * Input:
    * No tiene input como tal, solo destruye la tabla actual
    ******
    * Returns:
    * Void, no hace un return como tal.
    *****/

    ~registro_cuentas() {
        delete[] tabla;
    }

    /*****
    * cuenta obtener
    ******
    * Busca y devuelve la cuenta correspondiente a un rol.
    ******
    * Input:
    * string rol : El rol a buscar.
    ******
    * Returns:
    * cuenta, La cuenta correspondiente al rol. Si no se encuentra, se devuelve una cuenta vacía.
    *****/

    cuenta obtener(string rol) { // Dado el rol, devuelve la cuenta con ese rol
        for (int i = 0; i < ranuras; i++) {
            int idx = p(rol, i);
            if (tabla[idx].ocupado && tabla[idx].rol == rol) {
                return tabla[idx];
            }
        }
        return cuenta(); // Cuenta vacía si no se encuentra
    }

    void agregar(cuenta c) {
        // Verificar si el rol ya existe
        for (int i = 0; i < ranuras; ++i) {
            int idx = p(c.rol, i);
            if (tabla[idx].ocupado && tabla[idx].rol == c.rol) {
                cout << "Rol ya existente" << endl;
                return;
            }
        }
        // Si no existe, agregar el nuevo rol
        int i = 0;
        while (tabla[p(c.rol, i)].ocupado) {
            i++;
        }
        tabla[p(c.rol, i)] = c;
        tabla[p(c.rol, i)].ocupado = true;
        numElementos++;
        if ((float)numElementos / ranuras > 0.7) {
            redimensionar(ranuras * 2);
        }
    }

    void eliminar(string rol) {
        for (int i = 0; i < ranuras; i++) {
            int idx = p(rol, i);
            if (tabla[idx].ocupado && tabla[idx].rol == rol) {
                tabla[idx].ocupado = false;
                numElementos--;
                return;
            }
        }
    }

    void modificar(string rol, string descripcion) {
        for (int i = 0; i < ranuras; i++) {
            int idx = p(rol, i);
            if (tabla[idx].ocupado && tabla[idx].rol == rol) {
                tabla[idx].descripcion = descripcion;
                return;
            }
        }
    }

    void redimensionar(int n) {
        cuenta* nuevaTabla = new cuenta[n];
        int prevSize = ranuras;
        ranuras = n;
        for (int i = 0; i < prevSize; i++) {
            if (tabla[i].ocupado) {
                int j = 0;
                while (nuevaTabla[p(tabla[i].rol, j)].ocupado) {
                    j++;
                }
                nuevaTabla[p(tabla[i].rol, j)] = tabla[i];
            }
        }
        delete[] tabla;
        tabla = nuevaTabla;
    }

    void estadisticas() {
        float factor_de_carga = (float)numElementos / ranuras;
        cout << "RANURAS OCUPADAS: " << numElementos << endl;
        cout << "RANURAS TOTALES: " << ranuras << endl;
        cout << "FACTOR DE CARGA: " << factor_de_carga << endl;
    }
};

int main() {
    registro_cuentas registro;
    ifstream archivo("pruebas.txt");
    string linea;

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo pruebas.txt" << endl;
        return 1;
    }

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string comando;
        ss >> comando;
        if (comando == "AGREGAR") {
            string rol, nombre, descripcion;
            ss >> rol >> nombre;
            getline(ss, descripcion);
            cuenta c;
            c.rol = rol;
            c.nombre = nombre;
            c.descripcion = descripcion;
            registro.agregar(c);
        }
        else if (comando == "MODIFICAR") {
            string rol, descripcion;
            ss >> rol;
            getline(ss, descripcion);
            registro.modificar(rol, descripcion);
        }
        else if (comando == "QUITAR") {
            string rol;
            ss >> rol;
            registro.eliminar(rol);
        }
        else if (comando == "OBTENER") {
            string rol;
            ss >> rol;
            cuenta c = registro.obtener(rol);
            if (c.ocupado) {
                cout << c.nombre << " " << c.descripcion << endl;
            } else {
                cout << "NO SE ENCONTRO LA CUENTA" << endl;
            }
        }
        else if (comando == "ESTADISTICAS") {
            registro.estadisticas();
        }
    }
    archivo.close();
    return 0;
}
