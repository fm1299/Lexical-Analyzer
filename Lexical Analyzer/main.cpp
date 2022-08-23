#include "LexicalAnalyzer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LexicalAnalyzer w;
    w.show();
    return a.exec();
}
