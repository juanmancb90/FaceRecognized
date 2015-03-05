/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue May 27 10:47:31 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QLabel *label;
    QLabel *lbImagen;
    QPushButton *btExaminarImagen;
    QWidget *widget_2;
    QLabel *label_3;
    QLabel *lbEncontrada;
    QLabel *lbImagenBusqueda;
    QWidget *widget_3;
    QLabel *lbBaseDatos;
    QLabel *label_2;
    QWidget *widget_4;
    QPushButton *btBaseDatos;
    QPushButton *btCargar;
    QPushButton *btBuscar;
    QFrame *line;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(703, 474);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 10, 241, 271));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(1, 1, 110, 17));
        lbImagen = new QLabel(widget);
        lbImagen->setObjectName(QString::fromUtf8("lbImagen"));
        lbImagen->setEnabled(true);
        lbImagen->setGeometry(QRect(0, 20, 241, 191));
        btExaminarImagen = new QPushButton(widget);
        btExaminarImagen->setObjectName(QString::fromUtf8("btExaminarImagen"));
        btExaminarImagen->setGeometry(QRect(10, 240, 141, 27));
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(350, 10, 331, 271));
        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 0, 161, 16));
        lbEncontrada = new QLabel(widget_2);
        lbEncontrada->setObjectName(QString::fromUtf8("lbEncontrada"));
        lbEncontrada->setGeometry(QRect(10, 30, 281, 241));
        lbImagenBusqueda = new QLabel(widget_2);
        lbImagenBusqueda->setObjectName(QString::fromUtf8("lbImagenBusqueda"));
        lbImagenBusqueda->setEnabled(true);
        lbImagenBusqueda->setGeometry(QRect(50, 60, 211, 161));
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(20, 380, 661, 71));
        lbBaseDatos = new QLabel(widget_3);
        lbBaseDatos->setObjectName(QString::fromUtf8("lbBaseDatos"));
        lbBaseDatos->setGeometry(QRect(10, 20, 631, 31));
        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 10, 151, 16));
        widget_4 = new QWidget(centralwidget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(120, 310, 441, 61));
        btBaseDatos = new QPushButton(widget_4);
        btBaseDatos->setObjectName(QString::fromUtf8("btBaseDatos"));
        btBaseDatos->setGeometry(QRect(10, 20, 170, 27));
        btCargar = new QPushButton(widget_4);
        btCargar->setObjectName(QString::fromUtf8("btCargar"));
        btCargar->setGeometry(QRect(200, 20, 91, 27));
        btBuscar = new QPushButton(widget_4);
        btBuscar->setObjectName(QString::fromUtf8("btBuscar"));
        btBuscar->setGeometry(QRect(310, 20, 91, 27));
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(290, 10, 20, 271));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Proyecto AMN", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Imagen Test", 0, QApplication::UnicodeUTF8));
        lbImagen->setText(QString());
        btExaminarImagen->setText(QApplication::translate("MainWindow", "Cargar Imagen Test", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Imagen Encontrada", 0, QApplication::UnicodeUTF8));
        lbEncontrada->setText(QString());
        lbImagenBusqueda->setText(QString());
        lbBaseDatos->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Ruta de los Archivos", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btBaseDatos->setToolTip(QApplication::translate("MainWindow", "Ingrese la base de Imagenes pgm", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btBaseDatos->setText(QApplication::translate("MainWindow", "Cargar Base Datos", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btCargar->setToolTip(QApplication::translate("MainWindow", "Entrenar el software", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btCargar->setText(QApplication::translate("MainWindow", "Entrenar", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btBuscar->setToolTip(QApplication::translate("MainWindow", "Hacer el Test", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btBuscar->setText(QApplication::translate("MainWindow", "Test", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
