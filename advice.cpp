#include "advice.h"
/*
 * Leoul Yiheyis
 * 905707550
 * leoul16@vt.edu
 * ECE 3574
 * Homework 6
*/

/*
    Checks to see if given file is invalid.
    If file ends with "\" it is invalid.
*/
bool Advice::invalidFile(QString fName) {
    QFile fin(fName);
    if (!fin.open(QIODevice::ReadOnly)) {
        display -> insertPlainText("ERROR: Invalid File!");
    }
    else {
        QTextStream in(&fin);
        QString file = in.readAll();
        if (file.endsWith('\\')) {
            fin.close();
            return true;
        }
        else {
            fin.close();
            return false;
        }
    }
    //return false;
}

/*
    Reads the file given with "fName" and retrieves one line and returns it.
*/
QString Advice::getLine(QString fName) {
    int counter = 0;
    bool invalid = invalidFile(fName);
    QStringList strings;
    QFile fin(fName);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        display -> insertPlainText("ERROR: Invalid File!");
        //exit(1);
    }
    else {
        QTextStream in(&fin);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.endsWith('\\')) {
                while (line.endsWith('\\')) {
                    line = line.remove(QChar('\\'), Qt::CaseInsensitive) + " " + in.readLine();
                }
            }
            counter++;
            strings.append(line);
        }
        fin.close();
    }
    if (invalid) {
        display -> insertPlainText("ERROR: Cannot end data file with slash.");
        return NULL;
    }
    else {
        int ran = rand() % counter;
        if (counter > 0)
           return strings[ran];
        else
            return NULL;
    }
}

/*
    If the "Advice" button is clicked, this function runs.
    It gets a line from the "advice.dat" file and inserts it in the display.
*/
void Advice::advClicked() {
    QString advice;// = getLine("advice.dat");
    if ((advice = getLine("advice.dat")) != NULL)
        display -> insertPlainText("Advice: " + advice + "\n");
}

/*
    If the "Weather" button is clicked, this function runs.
    It gets a line from the "weather.dat" file and inserts it in the display.
*/
void Advice::weathClicked() {
    QString weather = getLine("weather.dat");
    if (weather != NULL)
        display -> insertPlainText("Weather: " + weather + "\n");
}

/*
    If the "Reminder" button is clicked, this function runs.
    It gets a line from the "reminder.dat" file and inserts it in the display.
*/
void Advice::remClicked() {
    // If check box is checked, then show reminder
    if (shw) {
        //exit(1);
        QCheckBox *chkbx = Advice::makeCheckBox();
        QMessageBox reminder;
        QString rem = getLine("reminder.dat");
        if (rem != NULL) {
            int year   =   rand() % (2018 - 2015) + 2015;
            int month  =   rand() % 12 + 1;
            int day    =   rand() % 30 + 1;
            int hour   =   rand() % 24 + 1;
            int min    =   rand() % 60 + 1;

            reminder.setText(rem + " at " + QTime(hour, min).toString("h:mm ap") + " on " + QString::number(month) + "/" + QString::number(day) + "/" + QString::number(year) + ".");
            reminder.setCheckBox((chkbx));
            connect(chkbx, SIGNAL(stateChanged(int)), this, SLOT(remCheck()));
        }
        else
            display->insertPlainText("No reminders.");
        reminder.exec();
    }
    // If checkbox is not checked, reminders have been disabled.
    else
        display->insertPlainText("Reminders have been disabled.");


}

/*
   If the checkbox is clicked:
                if on  turn off
                if off turn on
*/
void Advice::remCheck() {
    shw = !shw;
}

/*
    If the "Quit" button is clicked, this function runs.
    Properly quits the program and displays message box for confirmation.
*/
void Advice::quitClicked() {
    QMessageBox areyousure;
    areyousure.setText("Are you sure you want to quit?");
    areyousure.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    areyousure.setDefaultButton(QMessageBox::No);
//    if (QMessageBox::Yes == areyousure.exec())
//        Advice::quitAdvisor();
    int check = areyousure.exec();
    switch (check) {
        case QMessageBox::Yes:
            Advice::quitAdvisor();
        break;
    }
}

/*
    The actual function to quit the program.
*/
void Advice::quitAdvisor() {
    this->close();
}

/*
    Function used for making check box for reminder.
*/
QCheckBox* Advice::makeCheckBox() {
    QCheckBox *box = new QCheckBox("Show this message again?", this);
    box->setCheckState(Qt::Checked);
    return box;
}

/*
    Advice class constructor.
    Creates all buttons and layout necesseties.
*/
Advice::Advice(QWidget *parent)
    : QWidget(parent)
{
    display = new QTextEdit();
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignLeft);
    QFont font = display->font();
    font.setPointSize(font.pointSize());
    display->setFont(font);
    shw = true;

    QPushButton *advBut   = new QPushButton("Advice");
    connect(advBut, SIGNAL(clicked()), this, SLOT(advClicked()));
    QPushButton *weathBut =  new QPushButton("Weather");
    connect(weathBut, SIGNAL(clicked()), this, SLOT(weathClicked()));
    QPushButton *remBut   =  new QPushButton("Reminder");
    connect(remBut, SIGNAL(clicked()), this, SLOT(remClicked()));
    QPushButton *quitBut  =  new QPushButton("Quit");
    connect(quitBut, SIGNAL(clicked()), this, SLOT(quitClicked()));

    QGridLayout *window = new QGridLayout;
    window->addWidget(display,  0, 0, 1, 12);
    window->addWidget(advBut,   1, 0, 1, 12);
    window->addWidget(weathBut, 2, 0, 1, 12);
    window->addWidget(remBut,   3, 0, 1, 12);
    window->addWidget(quitBut,  4, 0, 1, 12);
    setLayout(window);
    setWindowTitle(tr("Advisor"));
}
