#include "Red.h"
#include <iostream>
#include <fstream>

#include <queue>
#include <limits>
#include <list>


const int INF = std::numeric_limits<int>::max();

Red::~Red() {
    for (auto const& [nombre, enrutador] : enrutadores) {
        delete enrutador;
    }
}

void Red::agregarEnrutador(std::string nombre) {
    if (enrutadores.find(nombre) == enrutadores.end()) {
        enrutadores[nombre] = new Enrutador(nombre);
    }
}

void Red::conectar(std::string origen, std::string destino, int costo) {
    if (enrutadores.count(origen) && enrutadores.count(destino)) {
        enrutadores[origen]->agregarVecino(destino, costo);
        enrutadores[destino]->agregarVecino(origen, costo);
    }
}

void Red::desconectar(std::string n1, std::string n2) {
    if (enrutadores.count(n1) && enrutadores.count(n2)) {
        enrutadores[n1]->eliminarVecino(n2);
        enrutadores[n2]->eliminarVecino(n1);
        std::cout << "[SISTEMA] Enlace entre " << n1 << " e " << n2 << " eliminado." << std::endl;
    } else {
        std::cout << "[ERROR] No se pudo eliminar el enlace." << std::endl;
    }
}

void Red::cargarDesdeArchivo(std::string nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    std::string origen, destino;
    int costo;

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }

    while (archivo >> origen >> destino >> costo) {
        agregarEnrutador(origen);
        agregarEnrutador(destino);
        conectar(origen, destino, costo);
    }
    archivo.close();
    std::cout << "[SISTEMA] Red cargada exitosamente." << std::endl;
}

void Red::calcularMejorRuta(std::string origen, std::string destino) {
    if (!enrutadores.count(origen) || !enrutadores.count(destino)) {
        std::cout << "Nodos no validos." << std::endl;
        return;
    }

    std::map<std::string, int> distancias;
    std::map<std::string, std::string> predecesor;
    for (auto const& [nom, e] : enrutadores) distancias[nom] = INF;

    distancias[origen] = 0;


    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<std::pair<int, std::string>>> pq;

    pq.push({0, origen});

    while (!pq.empty()) {
        std::string u = pq.top().second;
        pq.pop();

        for (auto const& [v, costo] : enrutadores[u]->getVecinos()) {
            if (distancias[u] != INF && distancias[u] + costo < distancias[v]) {
                distancias[v] = distancias[u] + costo;
                predecesor[v] = u;
                pq.push({distancias[v], v});
            }
        }
    }

    if (distancias[destino] == INF) {
        std::cout << "No hay camino posible entre " << origen << " y " << destino << "." << std::endl;
    } else {
        std::list<std::string> camino;
        for (std::string en = destino; en != ""; en = predecesor[en]) {
            camino.push_front(en);
            if (en == origen) break;
        }

        std::cout << "Camino mas corto: ";
        for (const auto& nodo : camino) {
            std::cout << nodo << (nodo == destino ? "" : " -> ");
        }
        std::cout << "\nCosto total: " << distancias[destino] << std::endl;
    }
}
