#ifndef CALCTHREAD_H
#define CALCTHREAD_H
#include <QThread>

class CalcThread : public QThread
{
public:
    CalcThread(); 
    void run ()
    {
        //Код, исполняемый в потоке
    }
};

#endif // CALCTHREAD_H
