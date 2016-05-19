#include <QApplication>
#include "advice.h"
/*
 * Leoul Yiheyis
 * 905707550
 * leoul16@vt.edu
 * ECE 3574
 * Homework 6
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Advice advisor;
    advisor.resize(500, 500);
    advisor.show();

    return a.exec();
}
