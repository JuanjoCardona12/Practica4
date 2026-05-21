#include <iostream>
#include "Red.h"

int main() {
    Red red;
    int opcion;


    std::cout << "   SIMULADOR DE ENRUTAMIENTO - UdeA\n";


    do {
        std::cout << "\nMENU\n";
        std::cout << "1. Cargar topologia desde archivo\n";
        std::cout << "2. Mostrar red\n";
        std::cout << "3. Mostrar tabla de costos\n";
        std::cout << "4. Mostrar matriz de costos minimos\n";
        std::cout << "5. Calcular mejor ruta\n";
        std::cout << "6. Agregar enrutador\n";
        std::cout << "7. Eliminar enrutador\n";
        std::cout << "8. Conectar enrutadores\n";
        std::cout << "9. Desconectar enrutadores\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1: {
            int topologia;
            std::cout << "\nTOPOLOGIAS DISPONIBLES\n";
            std::cout << "1. ANILLO\n";
            std::cout << "2. ARBOL\n";
            std::cout << "3. BUS\n";
            std::cout << "4. ESTRELLA\n";
            std::cout << "5. HIBRIDO\n";
            std::cout << "6. MESH\n";
            std::cout << "7. PUNTOAPUNTO\n";
            std::cout << "8. REDEJEMPLO\n";
            std::cout << "Seleccione una topologia: ";
            std::cin >> topologia;

            std::string archivo;
            switch (topologia) {
            case 1: archivo = "ANILLO";      break;
            case 2: archivo = "ARBOL";       break;
            case 3: archivo = "BUS";         break;
            case 4: archivo = "ESTRELLA";    break;
            case 5: archivo = "HIBRIDO";     break;
            case 6: archivo = "MESH";        break;
            case 7: archivo = "PUNTOAPUNTO"; break;
            case 8: archivo = "REDEJEMPLO";  break;
            default:
                std::cout << "Topologia invalida.\n";
                break;
            }

            if (!archivo.empty()) {
                red.cargarDesdeArchivo(archivo);
            }
            break;
        }
        case 2:
            red.mostrarRed();
            break;
        case 3:
            red.mostrarTablaCostos();
            break;
        case 4:
            red.mostrarMatrizCostos();
            break;
        case 5: {
            std::string origen, destino;
            std::cout << "Origen: ";
            std::cin >> origen;
            std::cout << "Destino: ";
            std::cin >> destino;
            red.calcularMejorRuta(origen, destino);
            break;
        }
        case 6: {
            std::string nombre;
            std::cout << "Nombre del enrutador: ";
            std::cin >> nombre;
            red.agregarEnrutador(nombre);
            std::cout << "[SISTEMA] Enrutador " << nombre << " agregado.\n";
            break;
        }
        case 7: {
            std::string nombre;
            std::cout << "Nombre del enrutador a eliminar: ";
            std::cin >> nombre;
            red.eliminarEnrutador(nombre);
            break;
        }
        case 8: {
            std::string origen, destino;
            int costo;
            std::cout << "Origen: ";
            std::cin >> origen;
            std::cout << "Destino: ";
            std::cin >> destino;
            std::cout << "Costo: ";
            std::cin >> costo;
            red.conectar(origen, destino, costo);
            std::cout << "[SISTEMA] Enlace creado.\n";
            break;
        }
        case 9: {
            std::string n1, n2;
            std::cout << "Enrutador 1: ";
            std::cin >> n1;
            std::cout << "Enrutador 2: ";
            std::cin >> n2;
            red.desconectar(n1, n2);
            break;
        }
        case 0:
            std::cout << "Saliendo...\n";
            break;
        default:
            std::cout << "Opcion invalida.\n";
            break;
        }

    } while (opcion != 0);

    return 0;
}
