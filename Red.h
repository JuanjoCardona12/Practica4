#ifndef RED_H
#define RED_H

#include "Enrutador.h"
#include <map>
#include <string>

class Red {

private:

    std::map<std::string, Enrutador*> enrutadores;  //guarda todos los enrutadores de la red ----

public:

    ~Red();  //destructor

    // Gestion de routers
    void agregarEnrutador(std::string nombre);
    void eliminarEnrutador(std::string nombre);

    // Gestion de enlaces
    void conectar(std::string origen, std::string destino, int costo);
    void desconectar(std::string n1, std::string n2);

    // Archivo
    void cargarDesdeArchivo(std::string nombreArchivo); //lee y contruye la red

    // Algoritmo de rutas
    void calcularMejorRuta(std::string origen, std::string destino);

    // Mostrar informacion
    void mostrarRed();  //enr y vec
    void mostrarTablaCostos(); //directo
    void mostrarMatrizCostos(); //minimo
};

#endif
