#include <iostream>
#include "Red.h"

int main() {
    Red miRed;

    std::cout << "===========================================" << std::endl;
    std::cout << "   SIMULADOR DE ENRUTAMIENTO - UdeA        " << std::endl;
    std::cout << "===========================================\n" << std::endl;

    miRed.cargarDesdeArchivo("red_topologia.txt");

    //  Encontrar camino y costo inicial
    std::cout << "\n--- PRUEBA 1: Ruta Optima Inicial ---" << std::endl;
    miRed.calcularMejorRuta("A", "E");

    //  Modificacioion en tiempo de ejecución
    std::cout << "--- PRUEBA 2: Modificando la Red ---" << std::endl;
    std::cout << "[EVENTO] Agregando nuevo enrutador 'F'..." << std::endl;
    miRed.agregarEnrutador("F");
    miRed.conectar("A", "F", 1);
    miRed.conectar("F", "E", 2);

    std::cout << "[SISTEMA] Recalculando ruta tras expansion..." << std::endl;
    miRed.calcularMejorRuta("A", "E");

    //  eliminación de enlace
    std::cout << "--- PRUEBA 3: Caida de Enlace ---" << std::endl;
    std::cout << "[EVENTO] Se corta la conexion entre F y E..." << std::endl;
    miRed.desconectar("F", "E");

    std::cout << "[SISTEMA] Buscando ruta alternativa..." << std::endl;
    miRed.calcularMejorRuta("A", "E");

    std::cout << "===========================================" << std::endl;
    std::cout << "        SIMULACION FINALIZADA              " << std::endl;
    std::cout << "===========================================" << std::endl;

    return 0;
