#include <iostream>
#include "Red.h"

void probarTopologia(const std::string& nombre, const std::string& archivo,
                     const std::string& origen, const std::string& destino) {
    std::cout << "\n===========================================" << std::endl;
    std::cout << " TOPOLOGIA: " << nombre << std::endl;
    std::cout << "===========================================" << std::endl;

    Red red;
    red.cargarDesdeArchivo(archivo);
    red.mostrarRed();
    red.mostrarMatrizCostos();

    std::cout << "\n--- Ruta optima de " << origen << " a " << destino << " ---" << std::endl;
    red.calcularMejorRuta(origen, destino);
}

int main() {
    std::cout << "===========================================" << std::endl;
    std::cout << " SIMULADOR DE ENRUTAMIENTO - UdeA " << std::endl;
    std::cout << "===========================================" << std::endl;

    probarTopologia("ANILLO",       "ANILLO",       "A", "D");
    probarTopologia("ARBOL",        "ARBOL",        "D", "G");
    probarTopologia("BUS",          "BUS",          "A", "E");
    probarTopologia("ESTRELLA",     "ESTRELLA",     "A", "E");
    probarTopologia("HIBRIDO",      "HIBRIDO",      "A", "F");
    probarTopologia("MESH",         "MESH",         "A", "D");
    probarTopologia("PUNTOAPUNTO",  "PUNTOAPUNTO",  "A", "B");
    probarTopologia("REDEJEMPLO",   "REDEJEMPLO",   "A", "E");

    std::cout << "\n===========================================" << std::endl;
    std::cout << " SIMULACION FINALIZADA " << std::endl;
    std::cout << "===========================================" << std::endl;

    return 0;
}
