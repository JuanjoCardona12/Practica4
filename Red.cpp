#include "Red.h"

#include <iostream>
#include <fstream>

#include <queue>
#include <limits>
#include <list>
#include <vector>

const int INF = std::numeric_limits<int>::max();


// Destructor
Red::~Red() {

    for (auto const& [nombre, enrutador] : enrutadores) {
        delete enrutador;
    }
}


// Agregar router
void Red::agregarEnrutador(std::string nombre) {

    if (enrutadores.find(nombre) == enrutadores.end()) {
        enrutadores[nombre] = new Enrutador(nombre);
    }
}


// Eliminar router
void Red::eliminarEnrutador(std::string nombre) {

    if (!enrutadores.count(nombre)) {
        std::cout << "Router no encontrado.\n";
        return;
    }

    // Eliminar referencias
    for (auto const& [n, r] : enrutadores) {
        r->eliminarVecino(nombre);
    }

    delete enrutadores[nombre];
    enrutadores.erase(nombre);

    std::cout << "[SISTEMA] Router eliminado correctamente.\n";
}


// Conectar routers
void Red::conectar(std::string origen,
                   std::string destino,
                   int costo) {

    if (enrutadores.count(origen) &&
        enrutadores.count(destino)) {

        enrutadores[origen]->agregarVecino(destino, costo);
        enrutadores[destino]->agregarVecino(origen, costo);
    }
}


// Eliminar enlace
void Red::desconectar(std::string n1,
                      std::string n2) {

    if (enrutadores.count(n1) &&
        enrutadores.count(n2)) {

        enrutadores[n1]->eliminarVecino(n2);
        enrutadores[n2]->eliminarVecino(n1);

        std::cout << "[SISTEMA] Enlace eliminado.\n";
    }
}


// Cargar desde TXT
void Red::cargarDesdeArchivo(std::string nombreArchivo) {

    std::ifstream archivo(nombreArchivo);

    std::string origen;
    std::string destino;

    int costo;

    if (!archivo.is_open()) {

        std::cout << "Error al abrir archivo.\n";
        return;
    }

    while (archivo >> origen >> destino >> costo) {

        agregarEnrutador(origen);
        agregarEnrutador(destino);

        conectar(origen, destino, costo);
    }

    archivo.close();

    std::cout << "[SISTEMA] Topologia cargada correctamente.\n";
}


// Mostrar conexiones
void Red::mostrarRed() {

    std::cout << "\n===== TOPOLOGIA =====\n";

    for (auto const& [nombre, router] : enrutadores) {

        std::cout << "\nRouter " << nombre << "\n";

        for (auto const& [vecino, costo] :
             router->getVecinos()) {

            std::cout << " -> "
                      << vecino
                      << " (Costo: "
                      << costo
                      << ")\n";
        }
    }
}


// Dijkstra
void Red::calcularMejorRuta(std::string origen,
                            std::string destino) {

    if (!enrutadores.count(origen) ||
        !enrutadores.count(destino)) {

        std::cout << "Nodos invalidos.\n";
        return;
    }

    std::map<std::string, int> distancias;

    std::map<std::string, std::string> predecesor;

    for (auto const& [nom, e] : enrutadores) {
        distancias[nom] = INF;
    }

    distancias[origen] = 0;

    std::priority_queue<
        std::pair<int, std::string>,
        std::vector<std::pair<int, std::string>>,
        std::greater<std::pair<int, std::string>>
    > pq;

    pq.push({0, origen});

    while (!pq.empty()) {

        std::string u = pq.top().second;

        pq.pop();

        for (auto const& [v, costo] :
             enrutadores[u]->getVecinos()) {

            if (distancias[u] != INF &&
                distancias[u] + costo < distancias[v]) {

                distancias[v] =
                    distancias[u] + costo;

                predecesor[v] = u;

                pq.push({distancias[v], v});
            }
        }
    }

    if (distancias[destino] == INF) {

        std::cout << "No existe ruta.\n";
        return;
    }

    std::list<std::string> camino;

    std::string actual = destino;

    while (actual != origen) {

        camino.push_front(actual);

        actual = predecesor[actual];
    }

    camino.push_front(origen);

    std::cout << "\n===== MEJOR RUTA =====\n";

    for (auto it = camino.begin();
         it != camino.end();
         ++it) {

        std::cout << *it;

        auto siguiente = it;
        ++siguiente;

        if (siguiente != camino.end()) {
            std::cout << " -> ";
        }
    }

    std::cout << "\nCosto total: "
              << distancias[destino]
              << "\n";
}


// Mostrar tablas
void Red::mostrarTablaCostos() {

    std::cout << "\n===== TABLAS DE COSTOS =====\n";

    for (auto const& [origen, router] : enrutadores) {

        std::cout << "\nRouter " << origen << "\n";

        for (auto const& [destino, costo] :
             router->getVecinos()) {

            std::cout << origen
                      << " -> "
                      << destino
                      << " = "
                      << costo
                      << "\n";
        }
    }
}

void Red::mostrarMatrizCostos() {
    std::cout << "\n===== MATRIZ DE COSTOS MINIMOS =====\n";

    std::cout << "\t";
    for (auto const& [nombre, e] : enrutadores) {
        std::cout << nombre << "\t";
    }
    std::cout << "\n";

    for (auto const& [origen, router] : enrutadores) {

        std::map<std::string, int> distancias;
        for (auto const& [nom, e] : enrutadores) {
            distancias[nom] = INF;
        }
        distancias[origen] = 0;

        std::priority_queue<std::pair<int,std::string>, std::vector<std::pair<int,std::string>>, std::greater<std::pair<int,std::string>>> pq;
        pq.push({0, origen});

        while (!pq.empty()) {
            std::string u = pq.top().second;
            pq.pop();
            for (auto const& [v, costo] : enrutadores[u]->getVecinos()) {
                if (distancias[u] != INF && distancias[u] + costo < distancias[v]) {
                    distancias[v] = distancias[u] + costo;
                    pq.push({distancias[v], v});
                }
            }
        }

        std::cout << origen << "\t";
        for (auto const& [destino, e] : enrutadores) {
            if (distancias[destino] == INF)
                std::cout << "INF\t";
            else
                std::cout << distancias[destino] << "\t";
        }
        std::cout << "\n";
    }
}


