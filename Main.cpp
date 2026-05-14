#include <iostream>
#include <string>
#include "Red.h"

void probarTopologia(const std::string& nombre, const std::string& rutaArchivo,
                     const std::string& origen, const std::string& destino) {
    std::cout << "\n===========================================" << std::endl;
    std::cout << " TOPOLOGIA: " << nombre << std::endl;
    std::cout << "===========================================" << std::endl;

    Red red;
    red.cargarDesdeArchivo(rutaArchivo);

   
    red.mostrarRed();
    red.mostrarMatrizCostos();

    std::cout << "\n--- Ruta optima de " << origen << " a " << destino << " ---" << std::endl;
    red.calcularMejorRuta(origen, destino);
}

int main() {
    std::cout << "===========================================" << std::endl;
    std::cout << " SIMULADOR DE ENRUTAMIENTO - UdeA " << std::endl;
    std::cout << "===========================================" << std::endl;


    std::string rutaBase = "C:/Users/PC/Documents/untitled16/build/Desktop_Qt_6_10_2_MinGW_64_bit-Debug/";

 
    probarTopologia("ANILLO",       rutaBase + "ring.txt",           "A", "D");
    probarTopologia("ARBOL",        rutaBase + "tree.txt",           "D", "G");
    probarTopologia("BUS",          rutaBase + "bus.txt",            "A", "E");
    probarTopologia("ESTRELLA",     rutaBase + "star.txt",           "A", "E");
    probarTopologia("HIBRIDO",      rutaBase + "hybrid.txt",         "A", "F");
    probarTopologia("MESH",         rutaBase + "mesh.txt",           "A", "D");
    probarTopologia("PUNTOAPUNTO",  rutaBase + "point_to_point.txt", "A", "B");
    probarTopologia("REDEJEMPLO",   rutaBase + "red_ejemplo.txt",    "A", "E");

    std::cout << "\n===========================================" << std::endl;
    std::cout << " SIMULACION FINALIZADA " << std::endl;
    std::cout << "===========================================" << std::endl;

    return 0;
}
