#ifndef DATE_H
#define DATE_H
#include <QString>

class Date
{
public:
    Date();
    Date(QString &d);
    bool operator<(Date &d);//<号重载
    bool operator>(Date &d);//>号重载
    QString returnDate()const{return date;}
private:
    QString date;
};

#endif // DATE_H
