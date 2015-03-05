#include "mainwindow.h"
#include <iostream>
#include "libs/tnt_array2d_utils.h"
//
MainWindow::MainWindow( QWidget * parent, Qt::WFlags f)
    : QMainWindow(parent, f)
{
    setupUi(this);
    dirBaseDatos = QDir(QDir::currentPath() + "/orl_faces");
    lbBaseDatos->setText(dirBaseDatos.absolutePath());
    this->reconocimiento = ReconocerImagen();

    connect(btExaminarImagen,SIGNAL(clicked()),this,SLOT(examinarImagen()));
    connect(btBaseDatos, SIGNAL(clicked()),this, SLOT(examinarBaseDatos()));
    connect(btBuscar,SIGNAL(clicked()),this,SLOT(buscarImagen()));
    connect(btCargar,SIGNAL(clicked()),this,SLOT(cargarBaseDatos()));
}

//Cargar imagen de test
void MainWindow::examinarImagen()
{
    QString nombreImagen = QFileDialog::getOpenFileName( this,"Seleccionar Imagen para evaluar",dirBaseDatos.absolutePath(),"Imagenes pgm (*.pgm)");
    imagenBuscar.load(nombreImagen);

    if(imagenBuscar.width()<=92 && imagenBuscar.height()<=112)
    {
        lbImagen->setPixmap(QPixmap::fromImage(imagenBuscar));
        procesarImagen = PreProcesarImagen(imagenBuscar);
        procesarImagen.procesarImagen();
        reconocimiento.agregarImagenBuscar(procesarImagen.getVectorPixeles());
    }
    else
    {
        QMessageBox::warning(this,"Error Tamaño de imagen", "El tamaño dde la imagen ebe estar entre 241 de ancho y 191 de alto");
    }
}

//cargar la base de datos de imagener como un conjunto de directorios
void MainWindow::examinarBaseDatos()
{
    dirBaseDatos = QFileDialog::getExistingDirectory(this, "Seleccionar Base Datos",QDir::currentPath());
    lbBaseDatos->setText(dirBaseDatos.absolutePath());
}

//Realizar el test de evaluar una imagen en el conjunto de entrenamiento
void MainWindow::buscarImagen()
{
    reconocimiento.reconocer();
    int pos = reconocimiento.getPosicionClase();

    if(pos==-1)
    {
        QMessageBox::warning(this, "Error Imagen" , "No se encontro la imagen");
        imagenEncontrada=QImage();
        lbImagenBusqueda->setPixmap(QPixmap::fromImage(imagenEncontrada));
        return;
    }

    QDir dir = dirBaseDatos;
    dir.setFilter(QDir::AllDirs);
    QStringList carpetas = dir.entryList(), imag;
    QString nombre = carpetas.at(pos+2);
    dir.cd(nombre);
    dir.setFilter(QDir::Files);
    imag= dir.entryList();
    QString nomImagenEncontrada = dir.absolutePath()+"/"+imag.at(0);
    imagenEncontrada.load(nomImagenEncontrada);
    QMessageBox::information(this,"Resultado", "Se encontro una imagen compatible");
    lbImagenBusqueda->setPixmap(QPixmap::fromImage(imagenEncontrada));
}

//procesamiento de la imagenes pgm en los directorios
void MainWindow::cargarBaseDatos()
{
    procesarBD = PreProcesarImagen();
    procesarBD.procesarConjuntoImagenes(dirBaseDatos);
    QVector <Array2D <double> > tempPersonas = procesarBD.getMatrizPersonas();
    reconocimiento.adicionarBD(procesarBD.getMatrizU(),
                               procesarBD.getVectorPromedioTotal(),
                               tempPersonas);
    QMessageBox::information(this,"Carga de la Base Datos", "La base de datos se cargo correctamente.");
}

