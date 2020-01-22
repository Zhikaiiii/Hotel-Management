#include "data.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QString>

QHash<QString,People *>all_people;
QHash<int,QString>new_people;
int new_people_number=0;
int all_people_number=0;
QString people[1000];

int new_manager_number=0;
QString new_manager[100];
QHash<QString,QString>now_manager;
QString its_boss[100];

QHash<QString,Hotel *>all_hotel;
QHash<int,QString>new_hotel;
int hotel_number=0;
int new_hotel_number=0;
QString hotel[1000];

Room* new_room[1000];
int room_number=0;
int new_room_number=0;

QHash<int,Order *>all_order;
QHash<int,int>new_order;
int all_order_number=0;
int new_order_number=0;

Date day_in;
Date day_out;

People* loginuser;
Hotel* selecthotel;
Order* selectorder;

void createConnection()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE","connection1");//数据库操作
    db.setDatabaseName("data.db");
    if(!db.open())
    {
        qDebug()<<"数据库打开异常";
    }
    else
    {
        qDebug()<<"数据库成功打开！！";
    }
    QSqlQuery query1(db);
    if(db.tables().contains("user"))
    {
        query1.exec("select * from user");
        while(query1.next())
        {
            QString Id=query1.value(0).toString();
            QString Password=query1.value(2).toString();
            int Type=query1.value(1).toInt();
            int State=query1.value(3).toInt();
            People_Type P_Type=People_Type(Type);
            People *p;
            switch(Type)
            {
            case 0:
            {
                p=new HotelBoss(Id,Password,P_Type);
                break;
            }
            case 1:
            {
                p=new Customer(Id,Password,P_Type);
                break;
            }
            case 2:
            {
                p=new Supervisior(Id,Password,P_Type);
                break;
            }
            case 3:
            {
                p=new Manager(Id,Password,P_Type);
                break;
            }
            default:
            {
                break;
            }
            }
            p->changeState(State);
            all_people.insert(Id,p);//创建people类指针并将其与id绑定插入hash表中
            people[all_people_number]=Id;
            all_people_number++;
        }
    }
    else
    {
        query1.exec("create table user(id varchar(20) primary key,type int,password varchar(20),state int)");
    }
    QSqlQuery query2(db);
    if(db.tables().contains("mantohotel"))
    {
        query2.exec("select * from mantohotel");
        while(query2.next())
        {
            QString boss=query2.value(1).toString();
            QString manager=query2.value(0).toString();
            all_people.value(boss)->addManager(manager);//调用people类的addManager添加函数
            now_manager.insert(manager,boss);
        }
    }
    else
    {
        query2.exec("create table mantohotel(manager varchar(20) primary key,hotelboss varchar(20))");
    }
}

void hotel_createConnection()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE","connection1");//连接数据库
    db.setDatabaseName("data.db");
    if(!db.open())
    {
        qDebug()<<"数据库打开异常";
    }
    else
    {
        qDebug()<<"数据库成功打开123！！";
    }
    QSqlQuery query1(db);
    if(db.tables().contains("hotel"))
    {
        query1.exec("select * from hotel");
        while(query1.next())
        {
             QString Id=query1.value(0).toString();
             QString Name=query1.value(1).toString();
             QString Location=query1.value(2).toString();
             QString Feature=query1.value(3).toString();
             int Star=query1.value(4).toInt();
             QString Owner=query1.value(5).toString();
             int h_State=query1.value(6).toInt();
             hotel[hotel_number]=Id;
             hotel_number++;
             State H_State=State(h_State);
             Hotel *h=new Hotel(Name,Location,Feature,Star,Id,H_State,Owner);
             all_hotel.insert(Id,h);//创建hotel类指针并将其与id绑定插入hash表中
        }
    }
    else
    {
        query1.exec("create table hotel(id varchar(20) primary key,name varchar(20),location varchar(20),feature varchar(20),star int,owner varchar(20),state int)");
    }
    QSqlQuery query2(db);
    if(db.tables().contains("room"))
    {
        query2.exec("select * from room");
        while(query2.next())
        {
            int Roomnumber=query2.value(1).toInt();
            int Price=query2.value(2).toInt();
            int Type=query2.value(3).toInt();
            QString Id=query2.value(4).toString();
            int State=query2.value(5).toInt();
            Room_Type R_Type=Room_Type(Type);
            all_hotel.value(Id)->addRoom(Price,R_Type,Roomnumber,State);//调用hotel类的addRoom函数对应添加酒店房间
            room_number++;
        }
    }
    else
    {
        query2.exec("create table room(num int primary key,roomnumber int,price int,type int,id varchar(20),state int)");
    }
}

void order_createConnection()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE","connection1");//数据库连接操作
    db.setDatabaseName("data.db");
    if(!db.open())
    {
        qDebug()<<"数据库打开异常";
    }
    else
    {
        qDebug()<<"数据库成功打开123456！！";
    }
    QSqlQuery query1(db);
    if(db.tables().contains("bill"))
    {
        query1.exec("select* from bill");
        while (query1.next())
        {
            int num=query1.value(0).toInt();
            QString hotelid=query1.value(1).toString();
            QString customerid=query1.value(2).toString();
            QString ddayin=query1.value(3).toString();
            QString ddayout=query1.value(4).toString();
            Date dayin(ddayin);
            Date dayout(ddayout);
            Room_Type type=Room_Type(query1.value(5).toInt());//订单的房间类型
            int roomnumber=query1.value(6).toInt();//订单的房间数
            Order_State state=Order_State(query1.value(7).toInt());//订单的状态
            int hotelscore=query1.value(8).toInt();//酒店评分
            int customerscore=query1.value(9).toInt();//顾客是否收到投诉
            Order *o=new Order(num,hotelid,customerid,dayin,dayout,type,roomnumber);
            o->changeState(state);
            o->scoreHotel(hotelscore);
            o->scoreCustomer(customerscore);//创建order类的指针
            int k=0;
            while(k<roomnumber)
            {
                for(int i=0;i<all_hotel.value(hotelid)->returnTotalRoomNumber();i++)
                {
                    if(all_hotel.value(hotelid)->myroom[i]->isEmpty(dayin,dayout)
                            &&all_hotel.value(hotelid)->myroom[i]->returnType()==((int)type))//循环判断该酒店的房间是否空闲
                    {
                        all_hotel.value(hotelid)->myroom[i]->addOrder(dayin,dayout);
                        o->setRoomnumber(k,all_hotel.value(hotelid)->myroom[i]->returnRoomNumber());//返回空余的房间号并传递给订单，同时改变房间状态
                        k++;
                        break;
                    }
                }
            }
            all_order.insert(num,o);//插入数据
            all_order_number++;
        }
    }
    else
    {
        query1.exec("create table bill(num int primary key,hotelid varchar(20),customer varchar (20),dayin varchar(10),dayout varchar(10),type int,roomnumber int,state int,hscore int,cscore int)");
    }
}

void insert_Data(People *p)
{
    QString Id=p->returnId();
    new_people.insert(new_people_number,Id);//新成员插入
    new_people_number++;
    all_people.insert(Id,p);//在hash表中添加该成员
    people[all_people_number]=Id;//对应的id存储
    all_people_number++;
}

void insert_Data(Hotel *h)
{

    QString Id=h->returnId();
    new_hotel.insert(new_hotel_number,Id);//新成员插入
    new_hotel_number++;
    all_hotel.insert(Id,h);//在hash表中添加该成员
    hotel[hotel_number]=Id;//对应的id存储
    hotel_number++;
}

void insert_Data(Order* o)
{
    int num=o->returnOrdenumber();
    new_order.insert(new_order_number,num);
    new_order_number++;
    all_order.insert(num,o);//在hash表中添加成员
    all_order_number++;
}
void savedata()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE","connection1");
    db.setDatabaseName("data.db");
    if(!db.open())
    {
        qDebug()<<"数据库打开异常";
    }
    else
    {
        qDebug()<<"数据库成功打开！！";
    }
    QSqlQuery query1(db);
    query1.first();
    for(int i=0;i<all_people_number;i++)//将已有用户的状态改变存入数据库
    {
        QString state=QString::number(all_people.value(people[i])->returnState());
        QString Id=people[i];
        query1.exec(QString("update user set state= %1 where id='%2'").arg(state,Id));
        query1.next();
    }
    query1.last();
    for(int i=0;i<new_people_number;i++)//将新增用户存入数据库
    {
        People *p=all_people.value(new_people.value(i));
        QString Id=p->returnId();
        QString Password=p->returnPass();
        People_Type Type=p->returnType();
        int State=p->returnState();
        query1.prepare("insert into user(id,type,password,state) values(:id,:type,:password,:state)");
        query1.bindValue(":id",Id);
        query1.bindValue(":password",Password);
        query1.bindValue(":type",Type);
        query1.bindValue(":state",State);
        query1.exec();
    }
    QSqlQuery query2(db);
    query2.last();
    for(int i=0;i<new_manager_number;i++)//将新的经理与老板对应关系存入数据库
    {

        query2.prepare("insert into mantohotel(manager,hotelboss) values(:manager,:hotelboss)");
        query2.bindValue(":manager",new_manager[i]);
        query2.bindValue(":hotelboss",its_boss[i]);
        query2.exec();
    }
    all_people.clear();
    new_people.clear();
    for(int i=0;i<1000;i++)
    {
        people[i]="0";
    }
    all_people_number=0;
    new_people_number=0;
    now_manager.clear();
    for(int i=0;i<100;i++)
    {
        new_manager[i]="0";
        its_boss[i]="0";
    }
    new_manager_number=0;
}
void savadataH()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE","connection1");
    db.setDatabaseName("data.db");
    if(!db.open())
    {
        qDebug()<<"数据库打开异常";
    }
    else
    {
        qDebug()<<"数据库成功打开！！";
    }
    QSqlQuery query1(db);
    query1.first();
    for(int i=0;i<hotel_number;i++)//将已有酒店的通过状态改变存入数据库
    {
        QString H_State=QString::number(all_hotel.value(hotel[i])->returnState());
        QString Id=hotel[i];
        query1.exec(QString("update hotel set state= %1 where id='%2'").arg(H_State,Id));
        query1.next();
    }
    query1.last();
    for(int i=0;i<new_hotel_number;i++)//将新增酒店存入数据库
    {
        Hotel *h=all_hotel.value(new_hotel.value(i));
        QString Id=h->returnId();
        QString Name=h->returnName();
        QString Location=h->returnLocation();
        QString Feature=h->returnFeature();
        QString Owner=h->returnOwner();
        int Star=h->returnStar();
        int H_State=(int)h->returnState();
        query1.prepare("insert into hotel(id,name,location,feature,star,owner,state) values(:id,:name,:location,:feature,:star,:owner,:state)");
        query1.bindValue(":id",Id);
        query1.bindValue(":name",Name);
        query1.bindValue(":location",Location);
        query1.bindValue(":feature",Feature);
        query1.bindValue(":star",Star);
        query1.bindValue(":owner",Owner);
        query1.bindValue(":state",H_State);
        query1.exec();
    }
    all_hotel.clear();
    new_hotel.clear();
    new_hotel_number=0;
    hotel_number=0;
    QSqlQuery query2(db);
    query2.last();
    for(int j=0;j<new_room_number;j++)//将新增房间存入数据库
    {
        int Num=room_number+j+1;
        int Roomnumber=new_room[j]->returnRoomNumber();
        int Price=new_room[j]->returnPrice();
        int Type=new_room[j]->returnType();
        int State=(int)new_room[j]->returnState();
        QString Id=new_room[j]->returnId();
        query2.prepare("insert into room(num,roomnumber,price,type,id,state) values(:num,:roomnumber,:price,:type,:id,:state)");
        query2.bindValue(":num",Num);
        query2.bindValue(":roomnumber",Roomnumber);
        query2.bindValue(":type",Type);
        query2.bindValue(":price",Price);
        query2.bindValue(":state",State);
        query2.bindValue(":id",Id);
        query2.exec();
    }
    all_hotel.clear();
    new_hotel.clear();
    hotel_number=0;
    new_hotel_number=0;
    for(int i=0;i<1000;i++)
    {
        hotel[i]="0";
        new_room[i]=NULL;
    }
    new_room_number=0;
    room_number=0;
    //hotel_createConnection();
}

void savedataO()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE","connection1");
    db.setDatabaseName("data.db");
    if(!db.open())
    {
        qDebug()<<"数据库打开异常";
    }
    else
    {
        qDebug()<<"数据库成功打开wzk！！";
    }
    QSqlQuery query1(db);
    query1.first();
    for(int i=0;i<all_order_number;i++)//订单状态的改变、顾客评分、酒店投诉等变化存入数据库
    {
        QString state=QString::number(all_order.value(i)->returnState());
        QString hscore=QString::number(all_order.value(i)->returnHscore());
        QString cscore=QString::number(all_order.value(i)->returnCscore());
        QString Id=QString::number(i);
        query1.exec(QString("update bill set state= %1 where num='%2'").arg(state,Id));
        query1.exec(QString("update bill set hscore= %1 where num='%2'").arg(hscore,Id));
        query1.exec(QString("update bill set cscore= %1 where num='%2'").arg(cscore,Id));
        query1.next();
    }
    query1.last();
    for(int j=0;j<new_order_number;j++)//新增订单存入数据库
    {
        int num=all_order.value(new_order.value(j))->returnOrdenumber();
        QString hotelid=all_order.value(new_order.value(j))->returnHotel();
        QString customerid=all_order.value(new_order.value(j))->returnCustomer();
        QString dayin=all_order.value(new_order.value(j))->returnDayin();
        QString dayout=all_order.value(new_order.value(j))->returnDayout();
        int type=all_order.value(new_order.value(j))->returnType();
        int roomnumber=all_order.value(new_order.value(j))->returnNumber();
        int state=all_order.value(new_order.value(j))->returnState();
        int hotelscore=all_order.value(new_order.value(j))->returnHscore();
        int customerscore=all_order.value(new_order.value(j))->returnCscore();
        query1.prepare("insert into bill(num,hotelid,customer,dayin,dayout,type,roomnumber,state,hscore,cscore) values(:num,:hotelid,:customer,:dayin,:dayout,:type,:roomnumber,:state,:hscore,:cscore)");
        query1.bindValue(":num",num);
        query1.bindValue(":hotelid",hotelid);
        query1.bindValue(":customer",customerid);
        query1.bindValue(":dayin",dayin);
        query1.bindValue(":dayout",dayout);
        query1.bindValue(":type",type);
        query1.bindValue(":roomnumber",roomnumber);
        query1.bindValue(":state",state);
        query1.bindValue(":hscore",hotelscore);
        query1.bindValue(":cscore",customerscore);
        query1.exec();
    }
    all_order.clear();
    new_order.clear();
    all_order_number=0;
    new_order_number=0;
    all_hotel.clear();
    new_hotel.clear();
    hotel_number=0;
    new_hotel_number=0;
    for(int i=0;i<1000;i++)
    {
        hotel[i]="0";
        new_room[i]=NULL;
    }
    new_room_number=0;
    room_number=0;
    selectorder=NULL;
    selecthotel=NULL;
   // hotel_createConnection();
    //order_createConnection();
}

template <class T>
void Swap(T& a,T& b)
{
    T temp=a;
    a=b;
    b=temp;
}

void SortScore()//冒泡排序对酒店分数降序排序
{
    int i=hotel_number-1;
    while(i>0)
    {
        int lastExchangeIndex=0;
        for(int j=0;j<i;j++)
        {
            if(all_hotel.value(hotel[j+1])->calScore()>all_hotel.value(hotel[j])->calScore())
            {
                Swap(hotel[j],hotel[j+1]);
                lastExchangeIndex=j;
            }
        }
        i=lastExchangeIndex;
    }
}

void SortPrice(int type)//冒泡排序对酒店价格升序排序，type表示房间类型
{
    int i=hotel_number-1;
    while(i>0)
    {
        int lastExchangeIndex=0;
        for(int j=0;j<i;j++)
        {
            if(type!=0)
            {
                if(all_hotel.value(hotel[j+1])->returnHotelPrice(type-1)<all_hotel.value(hotel[j])->returnHotelPrice(type-1))
                {
                    Swap(hotel[j],hotel[j+1]);
                    lastExchangeIndex=j;
                }
            }
            else
            {
                if(all_hotel.value(hotel[j+1])->returnHotelPrice(0)<all_hotel.value(hotel[j])->returnHotelPrice(0))
                {
                    Swap(hotel[j],hotel[j+1]);
                    lastExchangeIndex=j;
                }
            }
        }
        i=lastExchangeIndex;
    }
}

void SortLeft(int type)//冒泡排序对房间余量进行排序，type表示房间类型
{
    int i=hotel_number-1;
    while(i>0)
    {
        int lastExchangeIndex=0;
        for(int j=0;j<i;j++)
        {
            if(type!=0)
            {
                if(all_hotel.value(hotel[j+1])->returnLeftRoomnumber(type-1)>all_hotel.value(hotel[j])->returnLeftRoomnumber(type-1))
                {
                    Swap(hotel[j],hotel[j+1]);
                    lastExchangeIndex=j;
                }
            }
            else
            {
                if(all_hotel.value(hotel[j+1])->returnTotalLeftRoomNumber()>all_hotel.value(hotel[j])->returnTotalLeftRoomNumber())
                {
                    Swap(hotel[j],hotel[j+1]);
                    lastExchangeIndex=j;
                }
            }
        }
        i=lastExchangeIndex;
    }
}
