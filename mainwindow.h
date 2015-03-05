#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//
#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "preprocesarimagen.h"
#include "reconocerimagen.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
Q_OBJECT
public:
    MainWindow( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
        void examinarImagen();
        void examinarBaseDatos();
        void cargarBaseDatos();
        void buscarImagen();
private:
        PreProcesarImagen procesarImagen;
        PreProcesarImagen procesarBD;
        ReconocerImagen reconocimiento;
        QDir dirBaseDatos;
        QImage imagenBuscar;
        QImage imagenEncontrada;

};
#endif
