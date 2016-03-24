#ifndef KEYBOX_H
#define KEYBOX_H
#include <QString>

class KeyBox
{
private:
    quint64 number;
public:
    KeyBox();
    QString GetKey(void);
    quint64 GetNumber(void);
};

#endif // KEYBOX_H
