#ifndef ADVICE_H
#define ADVICE_H
#include <QWidget>
#include <QFile>
#include <QtWidgets>
#include <stdlib.h>
#include <QDialog>
#include <QCheckBox>
#include <QStringList>
/*
 * Leoul Yiheyis
 * 905707550
 * leoul16@vt.edu
 * ECE 3574
 * Homework 6
*/
class QPushButton;
class QTextEdit;

class Advice:public QWidget
{
   Q_OBJECT

public:
    Advice(QWidget *parent = 0);
    //virtual ~Advice() {};

private slots:
    void advClicked();
    void weathClicked();
    void remClicked();
    void remCheck();
    void quitClicked();
    void quitAdvisor();

private:
    bool invalidFile(QString fname);
    bool shw;
    QTextEdit *display;
    QString getLine(QString fName);
    QCheckBox* makeCheckBox();

};

#endif // ADVICE_H
