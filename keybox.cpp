#include "keybox.h"

KeyBox::KeyBox()
{
    this->number = 9653600000L;
}

QString KeyBox::GetKey()
{
    QString str = QString::number(number);
    number++;
    return str;
}

quint64 KeyBox::GetNumber()
{
   return number;
}
