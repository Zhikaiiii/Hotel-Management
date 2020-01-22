#ifndef PEOPLE_H
#define PEOPLE_H
#include<QString>
#include "order.h"
#include "hotel.h"
#include <QDebug>
enum People_Type {hotelboss,customer,supeivisor,hotelmanager,};
class People
{
public:
    People();
    People(QString id,QString password,People_Type type);
    QString returnId()const {return Id;}
    QString returnPass() const {return Password;}
    People_Type returnType() const {return Type;}
    int returnState() const{return (!People_State)?0:1;}
    void changeState(int state);//用户的状态改变
    virtual void addHotel(QString name, QString location, QString feature, int star, QString id){}
    virtual int returnManagerNumber() const{}
    virtual void addManager(QString m_manager){}
    virtual void addOrder(Room_Type type,int roomnumber){}
    virtual int* getOrderNumber(){}
    virtual QString* getManager() {}
protected:
    QString Id;
    QString Password;
    People_Type Type;
    bool People_State;
};

//酒店老板类
class HotelBoss:public People
{
public:
    HotelBoss();
    HotelBoss(QString id,QString password,People_Type type);
    void addHotel(QString name, QString location, QString feature, int star, QString id);//添加酒店
    QString* getManager() {return manager;}//得到经理数组的首地址
    void addManager(QString m_manager);//酒店老板的添加经理行为
    int returnManagerNumber() const{return Manager_Number;}
private:
    int Manager_Number;//雇佣的经理个数
    QString manager[100];//对应的经理id
};

//顾客类
class Customer:public People
{
public:
    Customer();
    Customer(QString id,QString password,People_Type type);
    void addOrder(Room_Type type,int roomnumber);//顾客的添加订单行为
    int* getOrderNumber();//顾客的订单数
private:
    int myOrder[2]={0,0};
};

//平台管理者类
class Supervisior:public People
{
public:
    Supervisior();
    Supervisior(QString id,QString password,People_Type type);
};

//经理类
class Manager:public People
{
public:
    Manager();
    Manager(QString id,QString password,People_Type type);
};
#endif // PEOPLE_H
