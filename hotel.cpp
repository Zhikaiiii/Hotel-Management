#include "hotel.h"
#include <QString>
#include "data.h"
#include "date.h"
Hotel::Hotel(){}

Hotel::Hotel(QString name, QString location, QString feature, int star, QString id, State state, QString owner)//hotel类的构造函数
    :Hotel_Name(name),Hotel_Location(location),Hotel_Feature(feature),Hotel_Star(star),Hotel_Id(id),Hotel_State(state),Hotel_Owner(owner)
{
    //包含酒店信息的字符串赋值
    HotelInfo[0]=this->Hotel_Id;
    HotelInfo[1]=this->Hotel_Name;
    HotelInfo[2]=this->Hotel_Location;
    HotelInfo[3]=this->Hotel_Feature;
    HotelInfo[4]=QString::number(this->Hotel_Star);
    HotelInfo[5]=this->Hotel_Owner;
    switch(state)
    {
    case 0:
    {
        HotelInfo[6]="待审核";
        break;
    }
    case 1:
    {
        HotelInfo[6]="通过";
        break;
    }
    case 2:
    {
        HotelInfo[6]="未通过";
        break;
    }
    default:
    {
        break;
    }
    }
    TotalRoomNumber=0;
    TotalLeftRoomNumber=0;
}
Room* Hotel::addRoom(int price, Room_Type type, int roomnumber, int state)//添加房间
{
    Room *myroom1;//定义基类指针
    QString Type;
    int pprice;
    if(RoomNumber[(int)type]==0)//判断此前是否有该类型房间，若有以此前价格赋值
    {
        HotelPrice[(int)type]=price;
    }
    pprice=HotelPrice[(int)type];
    switch (type) {
    case 0:
    {
        myroom1=new SingleRoom();
        myroom1->setRoom(pprice,roomnumber,state,Hotel_Id);
        Type="单人房";
        RoomNumber[0]++;//房间数加一
        LeftRoomNumber[0]++;
        break;
    }
    case 1:
    {
        myroom1=new DoubleRoom();//隐含转换为派生类指针并进行房间类型设定
        myroom1->setRoom(pprice,roomnumber,state,Hotel_Id);
        Type="双人房";
        RoomNumber[1]++;
        LeftRoomNumber[1]++;
        break;
    }
    case 2:
    {
        myroom1=new FamilyRoom();
        myroom1->setRoom(pprice,roomnumber,state,Hotel_Id);
        Type="家庭房";
        RoomNumber[2]++;
        LeftRoomNumber[2]++;
        break;
    }
    case 3:
    {
        myroom1=new LuxuryRoom();
        myroom1->setRoom(pprice,roomnumber,state,Hotel_Id);
        Type="豪华套房";
        RoomNumber[3]++;
        LeftRoomNumber[3]++;
        break;
    }
    default:
    {
        break;
    }
    }
    myroom[TotalRoomNumber]=myroom1;
    TotalRoomNumber++;//该酒店对应的房间数目加一
    TotalLeftRoomNumber++;//该酒店对应的剩余房间数目加一
    return myroom1;
}

void Hotel::changeState(State h_state)//改变酒店的状态
{
    Hotel_State=h_state;
    switch(h_state)
    {
    case 0:
    {
        HotelInfo[6]="待审核";
        break;
    }
    case 1:
    {
        HotelInfo[6]="通过";
        break;
    }
    case 2:
    {
        HotelInfo[6]="未通过";
        break;
    }
    default:
    {
        break;
    }
    }
}

void Hotel::changeLeftnumber(Date dayin,Date dayout)//在顾客选定日期之后改变酒店空余房间数
{
    TotalLeftRoomNumber=0;
    for(int i=0;i<4;i++)
    {
        LeftRoomNumber[i]=0;
    }
    for(int i=0;i<TotalRoomNumber;i++)
    {
        if(myroom[i]->isEmpty(dayin,dayout))//该房间在此时段内为空
        {
            LeftRoomNumber[myroom[i]->returnType()]++;
            TotalLeftRoomNumber++;//房间余量加一
        }
    }
}


double Hotel::calScore()//计算酒店的评分并返回平均值
{
    double hotelscore=0;
    for(int i=0;i<5;i++)
    {
        HotelScore[i]=0;
    }
    int r=0;//有效订单数
    for(int k=0;k<all_order_number;k++)
    {
        if(all_order.value(k)->returnState()==4
                &&all_order.value(k)->returnHotel()==Hotel_Id
                &&all_order.value(k)->returnHscore()!=0)//判断条件：订单已退房且顾客已评价
        {
              hotelscore+=all_order.value(k)->returnHscore();
              HotelScore[all_order.value(k)->returnHscore()-1]++;
              r++;
        }
    }
    if(r!=0)
    {
        return hotelscore*1.0/r;
    }
    else
    {
        return hotelscore;
    }
}
