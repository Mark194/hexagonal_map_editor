#include <QApplication>


#include "regulatory.hpp"


int main(int argc, char * argv[ ])
{
    QApplication a( argc, argv );

    a.setWindowIcon( QIcon( ":/icons/app_icon" ) );

    Regulatory regulatory;

    regulatory.run();

    return a.exec();
}
