#ifndef PREPROCESARIMAGEN_H
#define PREPROCESARIMAGEN_H

#include <QImage>
#include "libs/tnt.h"
#include "libs/jama_eig.h"
#include <QDir>
#include <QVector>
#include <QImageReader>
#include <QMessageBox>
using namespace TNT;
class PreProcesarImagen{

private:
    QImage imagen;
    Array2D <double> vectorPixeles;//contiene el vector de imagen a buscar
    Array2D <double> vectorPromedioTotal;//promedio de todas las imagenes
    QVector <Array2D <double> > matrizPersonas;//cada columna representa el promedio de cada imagend de una misma persona
    Array2D <double> matrizPromedioPersona;//primera dimension numero de personas, segunda dimension pixeles(columnas por filas)
    Array2D <double> vectoresValoresPropiosL;
    Array2D <double> phiPersonas;//la diferencia entre cada imagen y el promedio
    Array2D <double> matrizL;//descomposicion SVD
    Array2D <double> matrizU;//descomposicion SVD
    QVector <Array2D <double> > todasPersonas;//todas las imagenes de la base de datos
    int width;
    int height;

public:
    PreProcesarImagen();
    PreProcesarImagen(QImage);
    void setImagen(QImage);
    Array2D <double> getVectorPixeles();
    Array2D <double> getVectorPromedioTotal();
    QVector <Array2D <double> > getMatrizPersonas();
    Array2D <double> getMatrizPromedioPersona();
    Array2D <double> getPhiPersonas();
    Array2D <double> getMatrizL();
    Array2D <double> getMatrizU();
    void procesarImagen();//funcion que procesa la imagen almacenada y la convierte en el vectorPixeles
    void procesarConjuntoImagenes(QDir);//procesa la base de datos y crea los vectores y matrices correspondientes
    void obtenerMatrizL();//se obtiene de  traspuesta(phiPersonas) * phiPersonas
    void obtenerValoresPropiosL();//se obtiene y se selecciona los valores propios (los 40 con mayor valor)
    void obtenerMatrizU();// se obtiene la matriz U que representa los eigen face
    void normalizar(Array2D <double> vector);
    double calcularNorma(Array2D <double> vector, int pos);
    Array2D <double> tomarM(Array2D <double>matrizEntrada, int cantidad );//funcion para seleccionar los M' vectores propios (PCA)
};

#endif // PREPROCESARIMAGEN_H
