#include "reconocerimagen.h"
ReconocerImagen::ReconocerImagen(){}

//Agregar la base de entrenamiento
void ReconocerImagen::adicionarBD(Array2D <double> matrizU, Array2D <double> vectorPromedioTotal, QVector <Array2D <double> > matrizPersonas)
{
    this->matrizU = matrizU;
    this->vectorPromedioTotal = vectorPromedioTotal;
    this->matrizPersonas = matrizPersonas;
}

//obtener su posicion
int ReconocerImagen::getPosicionClase()
{
    return posicionClase;
}

//agregar la iamgen de test
void ReconocerImagen::agregarImagenBuscar(Array2D <double> vectorPixeles)
{
    this->vectorPixeles= vectorPixeles;
}

//Generar el conjunto de imagenes de entrenamiento
void ReconocerImagen::entrenarImagenes()
{//omega sub k
        matrizEntreno.clear();
        Array2D <double> trasMatrizU = TNT::transpose(matrizU);
        normaMax=0;

        for(int i = 0; i < matrizPersonas.size();i++)
        {//se adicionan cada imagen de la BD promediadas a la matriz entreno
            Array2D <double> temp = TNT::matmult(TNT::operator -(matrizPersonas.at(i),vectorPromedioTotal), trasMatrizU);
            normalizar(temp);
            //reconstruccion de esta imagen para saber el error maximo permitido
            Array2D <double> multi = TNT::matmult(temp,matrizU);
            Array2D <double> imagenReconstruida = TNT::operator +(multi,vectorPromedioTotal);
            Array2D <double> temp2 = TNT::operator -(matrizPersonas.at(i),imagenReconstruida);
            double normaTemp2 = this->calcularNorma(temp2);
            if(normaTemp2>normaMax)
                normaMax=normaTemp2;
            matrizEntreno.push_back(temp);
            matrizReconstruida.push_back(temp2);
        }
        calcularUmbral();
}

//Calcular el umbral entre la base de entrenamiento y la imagen test
void ReconocerImagen::calcularUmbral()
{//se calcula el umbral, la distancia max entre clases, sino esta es porque no es un rostro conocido
    double umbralTemporal=0;
    umbral=0;
    Array2D<double> temp;

    for(int i=0; i < matrizEntreno.size();i++)
    {
        for(int j=i+1 ; j < matrizEntreno.size();j++)
        {
            temp = TNT::operator -(matrizEntreno.at(i),matrizEntreno.at(j));
            umbralTemporal=calcularNorma(temp);
            if(umbral<umbralTemporal){//se toma el max
                umbral=umbralTemporal;
            }
        }
    }
    umbral/=2;
    //count<<umbral<<"\n";
}

//Normaliza el vector
void ReconocerImagen::normalizar(Array2D<double> vector)
{//normalizar un vector
    double norma = calcularNorma(vector);
    for(int i = 0; i < vector.dim2();i++)
    {
        vector[0][i] /= norma;
    }
}

//determinar la norma2 de vector de valores singulares
double ReconocerImagen::calcularNorma(Array2D <double> vector)
{
    double norma=0;
    for(int i = 0; i < vector.dim2();i++)
    {
        norma+= vector[0][i]* vector[0][i];
    }
    norma=(double) sqrt(norma);

    cout<<norma<<"\n";
    return norma;
}

//Reconocimiento de la imaagen
void ReconocerImagen::reconocer()
{
    entrenarImagenes(); // se reliaz la parte de entrenamiento de la base de datos; calcular los w sub k, los umbrales de error y distacia
    calcularProyeccionImagen();//se calcula la proyecion de la imagen en el espacio
    calcularDistanciaClase();//se calcula la distancia maxima en cada clase
    calcularDistanciaImagen();// se calcula la distancia a la imagen reconstruida

    //reconocer la imagen
    if(distanciaImagen<=normaMax)
    {//si se cumple es una imagen permitida
        if(minClase<=umbral)
            cout<<"imagen encontrada";//QMessageBox::information(new QWidget,"","");
        else
        {//QMessageBox::information(new QWidget,"",""));
            posicionClase=-1;//determina que no se encontro
        }
    }
    else
    {
        //QMessageBox::information(new QWidget,"No ROSTRO","No ROSTRO");
        posicionClase=-1;//determina que no se encontro
    }
}

//Calcular la proyecion de la imagen eigenfaces
void ReconocerImagen::calcularProyeccionImagen()
{//omega
    //obtenemos la imagen proyectada en el espacio apra poder determinar cual es el valor
    //1 x 40
    Array2D <double> trasMatrizU = TNT::transpose(matrizU);
    vectorPixelesProyectado=TNT::matmult(TNT::operator -(vectorPixeles,vectorPromedioTotal),trasMatrizU);
    normalizar(vectorPixelesProyectado);
}

void ReconocerImagen::calcularDistanciaClase()
{//las distancia a las personas e sub k
    Array2D <double> temp;
    posicionClase =0;
    minClase= 1000000000;
    distanciaClase.clear();

    //calcular las distancias de esta imagen a cada uno e sub k
    for(int i = 0; i<matrizEntreno.size();i++)
    {
        temp = TNT::operator -(vectorPixelesProyectado,matrizEntreno.at(i));
        double valor = calcularNorma(temp);
        if(valor<minClase)
        {
            this->posicionClase = i;//indica cual k es el valor min
            minClase = valor;
        }
        distanciaClase.push_back(valor);
    }
}

void ReconocerImagen::calcularDistanciaImagen()
{//el error diferencia con la reconstruccion de la imagen,
    Array2D <double> multi = TNT::matmult(vectorPixelesProyectado,matrizU);
    Array2D <double> imagenReconstruida = TNT::operator +(multi,vectorPromedioTotal);
    Array2D <double> vectorDiferencia = TNT::operator -(vectorPixeles,imagenReconstruida);
    distanciaImagen=calcularNorma(vectorDiferencia);
    cout<<distanciaImagen<<"\n";
}
