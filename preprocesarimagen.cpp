#include "preprocesarimagen.h"

PreProcesarImagen::PreProcesarImagen(){}
PreProcesarImagen::PreProcesarImagen(QImage img)
{
    imagen = img;
    width = imagen.width();
    height = imagen.height();
    vectorPixeles = Array2D<double>(1,width*height);
}

//lectura de las imagens y su cabezera
void PreProcesarImagen::setImagen(QImage img)
{
    imagen = img;
    width = imagen.width();
    height = imagen.height();
    vectorPixeles = Array2D<double>(1,width*height);
}


Array2D <double> PreProcesarImagen::getVectorPixeles()
{
    return vectorPixeles;
}

Array2D <double> PreProcesarImagen::getVectorPromedioTotal()
{
    return vectorPromedioTotal;
}

Array2D <double> PreProcesarImagen::getMatrizPromedioPersona()
{
    return matrizPromedioPersona;
}

Array2D <double> PreProcesarImagen::getPhiPersonas()
{
    return phiPersonas;
}

Array2D <double> PreProcesarImagen::getMatrizL()
{
    return matrizL;
}

Array2D <double> PreProcesarImagen::getMatrizU()
{
    return matrizU;
}

QVector <Array2D <double> > PreProcesarImagen::getMatrizPersonas()
{
    return matrizPersonas;
}

//para lectura de la imagen pgm
void PreProcesarImagen::procesarImagen()
{
    int count = 0;

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            vectorPixeles[0][count] = imagen.pixelIndex(i,j);
            count++;
        }
    }
}

//cargar la base de datos de imagenes pgm training set
void PreProcesarImagen::procesarConjuntoImagenes(QDir pathCarpeta)
{
    QString nombre;
    QImage img;
    pathCarpeta.setFilter(QDir::AllDirs);
    QStringList carpetas = pathCarpeta.entryList(), imagenes;
    int cantidadImagenes = 1;
    todasPersonas.clear();

    for(int numCarpeta =2; numCarpeta < carpetas.size(); numCarpeta++)
    {//para tomar todas las carpetas de la BD
        nombre = carpetas.at(numCarpeta);//*********se selecciona la carpeta
        std::cout << nombre.toStdString().c_str()<<" \n";

        if(pathCarpeta.cd(nombre))
        {//*****************************************entrar a la carpeta i
            pathCarpeta.setFilter(QDir::Files);//seleccionar los archivos
            imagenes = pathCarpeta.entryList();
            cantidadImagenes=imagenes.size();//tome todas las imagenes que ahi
            img.load(pathCarpeta.absolutePath()+ "/" +imagenes.at(0));
            setImagen(img);
            int val = 0, tam = height*width;

            if(numCarpeta==2)
            {//inicializar la matriz y vectores
                vectorPromedioTotal = Array2D<double> (1,tam, val);
            }

            Array2D<double> tempPersonas = Array2D<double>(1,tam, val);
            for(int numImagen =0; numImagen < cantidadImagenes; numImagen++)
            {//***************se toman cantidadImagenes imagenes
                img.load(pathCarpeta.absolutePath()+ "/"+imagenes.at(numImagen));
                setImagen(img);
                int count = 0;
                Array2D <double> persona = Array2D<double>(1,height*width);

                for(int p = 0; p < img.width(); p++)
                {
                    for(int q = 0; q < img.height(); q++)
                    {
                        tempPersonas[0][count] += imagen.pixelIndex(p,q);
                        //filtro imagen
                        int valor = imagen.pixelIndex(p,q);
                        if(valor <= 85)
                        {
                            valor = 255;
                        }
                        persona[0][count] = valor;
                        vectorPromedioTotal[0][count] += imagen.pixelIndex(p,q);
                        count++;
                    }
                }
                todasPersonas.push_back(persona);
            }

            for(int m =0; m < tempPersonas.dim2();m++)
            {//se promedia el vector de persona
                tempPersonas[0][m]/=cantidadImagenes;
            }
            matrizPersonas.push_back(tempPersonas);
            pathCarpeta.cdUp();
        }
        else
        {
            QMessageBox::warning(new QWidget,"Error", "Error al abrir base de datos");return;
        }
    }

   for(int m = 0; m < vectorPromedioTotal.dim2(); m++)
    {
        vectorPromedioTotal[0][m]/= (cantidadImagenes* (carpetas.size()-2));//se divide la cantidad de personas

        if(vectorPromedioTotal[0][m] <= 100 || vectorPromedioTotal[0][m] > 255)//filtrar la imagen promedio
            vectorPromedioTotal[0][m] = 255;
    }

   //no se sabe cuantas personas ahi
   phiPersonas=Array2D <double>(todasPersonas.size(),this->width*this->height);

   for(int m = 0; m < todasPersonas.size();m++)
   {
       Array2D <double> tempPersona = todasPersonas.at(m);
       for(int i = 0; i < tempPersona.dim2();i++)
       {
           double valor = tempPersona[0][i] -vectorPromedioTotal[0][i];
           //if(valor<0)
             //  valor =  std::abs(valor);
           phiPersonas[m][i]=valor;
       }
   }
    obtenerMatrizL();
    obtenerValoresPropiosL();
    obtenerMatrizU();
}

//utilizacion de TNT
void PreProcesarImagen::obtenerMatrizL()
{
    matrizL= TNT::matmult(phiPersonas, TNT::transpose(phiPersonas));
}

//Utilizacion de JAMA para hacer la descomposicion SVD
void PreProcesarImagen::obtenerValoresPropiosL()
{
    JAMA::Eigenvalue<double>eig = JAMA::Eigenvalue<double>(matrizL);
    eig.getV(vectoresValoresPropiosL);
    vectoresValoresPropiosL=tomarM(vectoresValoresPropiosL,40);
    normalizar(vectoresValoresPropiosL);
}

//Obtener la matriz U
void PreProcesarImagen::obtenerMatrizU()
{
    matrizU = TNT::matmult(vectoresValoresPropiosL,phiPersonas);
}

//Normalizar el vector columna
void PreProcesarImagen::normalizar(Array2D <double> vector)
{
    for(int j = 0; j < vector.dim1();j++)
    {
        double norma= calcularNorma(vector, j);

        for(int i = 0; i < vector.dim2();i++)
        {
            vector[j][i]/=norma;
        }
    }
}

//Calcular la norma
double PreProcesarImagen::calcularNorma(Array2D <double> vector, int pos)
{
    double norma=0;
    for(int i = 0; i < vector.dim2();i++){
        norma+= vector[pos][i]* vector[pos][i];
    }
    norma=(double) sqrt(norma);

    cout<<norma<<"\n";

    return norma;
}

//almacenar temporal la matriz entrada
Array2D <double> PreProcesarImagen::tomarM(Array2D <double>matrizEntrada, int cantidad )
{
    Array2D <double> mTemp = Array2D <double>(cantidad,matrizEntrada.dim2());
    for(int i = 0; i < cantidad;i++){
        for(int j = 0; j < mTemp.dim2();j++){
            mTemp[i][j] = matrizEntrada[i][j];
        }
    }
    return mTemp;
}


