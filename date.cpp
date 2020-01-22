#include "date.h"

Date::Date(){}

Date::Date(QString &d){date=d;}

bool Date::operator <(Date &d)//判断格式为yyyy-mm-dd格式的日期哪个在前
{
    int Length=date.length();
    bool Judge;
    for(int i=0;i<Length;i++)
    {
        if(date[i]<(d.returnDate()[i]))
        {
            Judge= true;
            break;
        }
        else if(date[i]>(d.returnDate()[i]))
        {
            Judge= false;
            break;
        }
        else
        {
            continue;
        }
    }
    return Judge;
}

bool Date::operator >(Date &d)
{
    int Length=date.length();
    bool Judge;
    for(int i=0;i<Length;i++)
    {
        if(date[i]>(d.returnDate()[i]))
        {
            Judge= true;
            break;
        }
        else if(date[i]<(d.returnDate()[i]))
        {
            Judge= false;
            break;
        }
        else
        {
            continue;
        }
    }
    return Judge;
}
