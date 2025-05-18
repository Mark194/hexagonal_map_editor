#include <QApplication>


#include "regulatory.hpp"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Regulatory regulatory;

    regulatory.run();

    return a.exec();
}
