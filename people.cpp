#include "people.h"
#include "data.h"
People::People(){}

People::People(QString id,QString password,People_Type type):Id(id),Password(password),Type(type)
{
    People_State=false;
}

void People::changeState(int state)
{
    if(state!=0)
    {
        People_State=true;
    }
    else
    {
        People_State=false;
    }
}

HotelBoss::HotelBoss()
{
    Manager_Number=0;
}

HotelBoss::HotelBoss(QString id, QString password, People_Type type):People(id,password,type)
{
    Manager_Number=0;
}

void HotelBoss::addManager(QString m_manager)//添加新经理
{
    if(Type==hotelboss)
    {
        manager[Manager_Number]=m_manager;
        Manager_Number++;//酒店老板拥有的经理数目+1
    }
}

void HotelBoss::addHotel(QString name, QString location, QString feature, int star, QString id)//创建酒店
{
    QString Owner=Id;
    State H_State=Waiting;
    Hotel *h=new Hotel(name,location,feature,star,id,H_State,Owner);
    insert_Data(h);
}
Customer::Customer(){}

Customer::Customer(QString id, QString password, People_Type type):People(id,password,type){}

void Customer::addOrder(Room_Type type, int roomnumber)//添加订单
{
    qDebug()<<"dy";
    if(Type==customer)
    {
        int num=all_order_number;
        QString hotel=selecthotel->returnId();
        QString ccustomer=this->returnId();
        Order *o=new Order(num,hotel,ccustomer,day_in,day_out,type,roomnumber);//动态创建订单对象
        int k=0;//当前已经分配的房间数
        while(k<roomnumber)
        {
            for(int i=0;i<all_hotel.value(hotel)->returnTotalRoomNumber();i++)
            {
                if(all_hotel.value(hotel)->myroom[i]->isEmpty(day_in,day_out)//房间空闲且类型相符
                        &&all_hotel.value(hotel)->myroom[i]->returnType()==(int)type)
                {
                    all_hotel.value(hotel)->myroom[i]->addOrder(day_in,day_out);//给该房间创建新订单
                    o->setRoomnumber(k,all_hotel.value(hotel)->myroom[i]->returnRoomNumber());//将该房间号存入订单中
                    k++;
                    break;
                }
            }
        }
        insert_Data(o);//将订单插入Hash表中
    }
}

int* Customer::getOrderNumber()
{
    myOrder[0]=0;//总订单数
    myOrder[1]=0;//收到的投诉数
    for(int i=0;i<all_order_number;i++)
    {
        if(all_order.value(i)->returnCustomer()==Id)
        {
            myOrder[0]++;
            if(all_order.value(i)->returnState()==4
                    &&all_order.value(i)->returnCscore()!=0)//已退房且被投诉
            {
                myOrder[1]++;
            }
        }
    }
    return myOrder;//返回数组首地址
}

Supervisior::Supervisior(){}

Supervisior::Supervisior(QString id, QString password, People_Type type):People(id,password,type){}

Manager::Manager(){}

Manager::Manager(QString id, QString password, People_Type type):People(id,password,type){}
