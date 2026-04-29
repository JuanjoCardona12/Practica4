#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <map>

class Enrutador {
private:
    std::string nombre;
    //  Costo del enlace
    std::map<std::string, int> vecinos;

public:
    Enrutador(std::string n) : nombre(n) {}

    // Almacena vecinos y costos
    void agregarVecino(std::string v, int costo) { vecinos[v] = costo; }

    //  eliminación de enlaces
    void eliminarVecino(std::string v) { vecinos.erase(v); }

    std::string getNombre() const { return nombre; }
    std::map<std::string, int>& getVecinos() { return vecinos; }
};

#endif
