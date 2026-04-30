
#ifndef RED_H
#define RED_H

#include "Enrutador.h"
#include <map>
#include <string>
#include <list> // NECESARIO PARA std::list

class Red {
private:
    std::map<std::string, Enrutador*> enrutadores;

public:
    ~Red();
    void agregarEnrutador(std::string nombre);
    void conectar(std::string origen, std::string destino, int costo);
    void desconectar(std::string n1, std::string n2);
    void cargarDesdeArchivo(std::string nombreArchivo);
    void calcularMejorRuta(std::string origen, std::string destino);
};

#endif
