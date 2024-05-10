#include "mainwindow.h"
#include "loginform.h"

#include<QtSql>

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFile>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("GidraProject");
    QCoreApplication::setOrganizationDomain("nowdomainyet.com");
    QCoreApplication::setApplicationName("GidraPK");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = ":/langs/gidra_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    // Worikng with langs
    translator.load(":/langs/gidra_" + QLocale::system().name());
    qApp->installTranslator(&translator);
    if(!qApp->installTranslator(&translator)) qDebug("Translation!!!");


// To install style forever
//    QFile file(":/style_deafult.css");
//    file.open(QFile::ReadOnly);

//    a.setStyleSheet(file.readAll());

//    MainWindow w;
//    w.show();

    loginform l;
    l.show();

    return a.exec();
}

