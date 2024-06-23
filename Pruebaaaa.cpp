#include <iostream>
#include <string>
usimg namaspace std;

struct cuenta {
    string rol, nombre, descripcion; // El rol es el identificador de la persona, el nombre y la descripcion son valores asociados al rol
    bool ocupado; // Valor bool si la cuenta está ocupada o no
    cuenta() : ocupado(false) {} // La cuenta no está ocupada en un principio
};

class registro_cuentas {
    private:
        float factor_de_carga = 0.0;
        cuenta tabla*; // Aca se almacenaran los elementos de la tabla
        int ranuras = 15; // Cuantas ranuras tiene la tabla hash (inicialmente)
        int hash(string rol) { // Se obtiene el hash dado el rol
            unsigned int hash_value = 0;
            for (char c : rol) {
                hash_value = (hash_value * 31 + c) % ranuras;
            }
            return hash_value;
        } 
        int p(string rol, int i) { // Se otiene la ranura a revisar en caso de colisión dado el rol y el intento i
            return (hash(rol) + i) % ranuras;
        } 

 public:

     registro_cuentas() {
        tabla = new cuenta[ranuras];
    }
    ~registro_cuentas() {
        delete[] tabla;
    }

 cuenta obtener(string rol) { // Dado el rol, devuelve la cuenta con ese rol
        for (int i = 0; i < ranuras; i++) {
            int idx = p(rol, i);
            if (tabla[idx].ocupado && tabla[idx].rol == rol) {
                return tabla[idx];
            }
        }
        return cuenta(); // Cuenta vacía si no se encuentra
    }

 void agregar(cuenta c); // Se agrega una cuenta a la tabla

 void eliminar(string rol); // Se elimina la cuenta

 void modificar(string rol, string descripcion); // Se modifica la descripcion del rol

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
