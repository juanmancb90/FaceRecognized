#ifndef RECONOCERIMAGEN_H
#define RECONOCERIMAGEN_H
#include <iostream>
#include <QVector>
#include <QMessageBox>
#include "libs/tnt.h"
#include <QImageReader>

using namespace TNT;
using namespace std;

class ReconocerImagen
{
private:
    Array2D <double> vectorPixeles; // [1][pixeles]
    Array2D <double> vectorPixelesProyectado;//[1][personas]omega
    Array2D <double> matrizU;//[personas][pixeles]
    QVector <Array2D <double> > matrizPersonas;//contiene las imagenes de la base de datos[personas][pixeles]
    Array2D <double> vectorPromedioTotal;//el promedio total constante[1][pixeles]
    QVector <Array2D <double> > matrizEntreno;//esta es la q contiene las imagenes entrenadas[personas][personas] omega sub k
    QVector <Array2D <double> > matrizReconstruida;
    double umbral;// teta sub k
    double minClase; //ek min
    int posicionClase;
    QVector <double> distanciaClase;//los distancia euclidea
    double distanciaImagen;//calcular las distancia euclidea
    double normaMax;

public:
    ReconocerImagen();
    void adicionarBD(Array2D <double> matrizU, Array2D <double> vectorPromedioTotal, QVector <Array2D <double> > matrizPersonas);
    int getPosicionClase();
    void agregarImagenBuscar(Array2D <double> vectorPixeles);
    void entrenarImagenes();
    void calcularUmbral();
    void normalizar(Array2D <double> vector);
    double calcularNorma(Array2D <double> vector);
    void reconocer();
    void calcularProyeccionImagen();
    void calcularDistanciaClase();
    void calcularDistanciaImagen();
};

#endif // RECONOCERIMAGEN_H
