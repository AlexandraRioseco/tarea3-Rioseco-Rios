#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <tarea3-Rioseco-Rios.cpp>

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
        if (comando == "AGREGAR"){

        }
        else if (comando == "MODIFICAR){

        }
        else if (comando == "QUITAR"){

        }
        else if (comando == "OBTENER"){

        }
        else if (comando == "ESTADISTICAS"){

        }
      archivo.close();
    return 0;
    }
