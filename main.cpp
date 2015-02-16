#include "MainWindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    // Show main window
    QApplication a(argc, argv);

    MainWindow w;
    QIcon icon("icon.ico");

    //stylesheet
    /*QFile style_file("./style/dark.qss");
    style_file.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(style_file.readAll());
    a.setStyleSheet(StyleSheet);*/

    w.setWindowIcon(icon);
    w.show();
    // Start event loop
    return a.exec();
}
