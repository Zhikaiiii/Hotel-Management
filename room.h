#ifndef ROOM_H
#define ROOM_H
#include <QString>
#include <QDebug>
#include "date.h"
class Room //房间类
{
public:
    Room():Price(0),RoomNumber(0),State(true),Room_Order_time(0){}
    Room(int price,int roomnumber):Price(price),RoomNumber(roomnumber),State(false),Room_Order_time(0){}
    virtual ~Room(){}//虚析构函数
    int returnRoomNumber() const{return RoomNumber;}
    int returnPrice() const{return Price;}
    QString returnId() const{return Id;}
    bool returnState() const{return State;}
    virtual int returnType() const{}//虚函数返回房间类型，根据派生类指针调用
    virtual void setRoom(int price,int roomnumber,int state,QString id){}//虚函数设定房间参数，根据派生类指针调用
    QString returnInfo(int index)const{return RoomInfo[index];}//得到酒店信息
    bool isEmpty(Date dayin,Date dayout)//判断房间在该段日期内是否空闲
    {
        bool Judge;
        if(Room_Order_time==0)//若没有被预定过则为空
        {
            Judge=true;
        }
        else
        {
            for(int j=0;j<Room_Order_time;j++)
            {
                if(Dayin[j]>dayout||Dayout[j]<dayin)//入住日期在已有订单之后或者离店日期在已有订单之前
                {
                    Judge=true;
                }
                else
                {
                    Judge=false;
                    break;
                }
            }
        }
        return Judge;
    }
    void addOrder(Date dayin,Date dayout)//添加订单，存储该订单的入住与离店时间
    {
        Dayin[Room_Order_time]=dayin;
        Dayout[Room_Order_time]=dayout;
        Room_Order_time++;//该房间订单数加一
    }

    Date Dayin[100];
    Date Dayout[100];
     //存储该房间各个订单的入住和离店时间

protected:
    int Price;//价格
    int RoomNumber;//房间号
    bool State;
    QString Id;//所属酒店
    int Room_Order_time;//房间被预订的次数
    QString RoomInfo[3];//以字符串形式存储房间的房间号、类型、价格
};

class SingleRoom:public Room
{
public:
    SingleRoom(){}
    SingleRoom(int price,int roomnumber):Room(price,roomnumber){}
    virtual void setRoom(int price,int roomnumber,int state,QString id)
    {
        this->Price=price;
        this->RoomNumber=roomnumber;
        this->State=(bool)state;
        this->Id=id;
        RoomInfo[0]=QString::number(roomnumber);
        RoomInfo[1]="单人房";
        RoomInfo[2]=QString::number(price);
    }
    virtual int returnType() const
    {
        int type=0;
        return type;
    }
};

class DoubleRoom:public Room
{
public:
    DoubleRoom(){}
    DoubleRoom(int price,int roomnumber):Room(price,roomnumber){}
    virtual void setRoom(int price,int roomnumber,int state,QString id)
    {
        this->Price=price;
        this->RoomNumber=roomnumber;
        this->State=(bool)state;
        this->Id=id;
        RoomInfo[0]=QString::number(roomnumber);
        RoomInfo[1]="双人房";
        RoomInfo[2]=QString::number(price);
    }
    virtual int returnType() const
    {
        int type=1;
        return type;
    }
};

class FamilyRoom:public Room
{
public:
    FamilyRoom(){}
    FamilyRoom(int price,int roomnumber):Room(price,roomnumber){}
    virtual void setRoom(int price,int roomnumber,int state,QString id)
    {
        this->Price=price;
        this->RoomNumber=roomnumber;
        this->State=(bool)state;
        this->Id=id;
        RoomInfo[0]=QString::number(roomnumber);
        RoomInfo[1]="家庭房";
        RoomInfo[2]=QString::number(price);
    }
    virtual int returnType() const
    {
        int type=2;
        return type;
    }
};

class LuxuryRoom:public Room
{
public:
    LuxuryRoom(){}
    LuxuryRoom(int price,int roomnumber):Room(price,roomnumber){}
    virtual void setRoom(int price,int roomnumber,int state,QString id)
    {
        this->Price=price;
        this->RoomNumber=roomnumber;
        this->State=(bool)state;
        this->Id=id;
        RoomInfo[0]=QString::number(roomnumber);
        RoomInfo[1]="豪华套房";
        RoomInfo[2]=QString::number(price);
    }
    virtual int returnType() const
    {
        int type=3;
        return type;
    }
};

#endif // ROOM_H
