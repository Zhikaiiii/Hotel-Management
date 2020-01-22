#ifndef HOTEL_H
#define HOTEL_H
#include "room.h"
#include <QString>
enum Room_Type {Single,Double,Family,Luxurious};//房间类型
enum State {Waiting,Pass,Reject};//酒店状态
class Hotel
{
public:
    Hotel();
    Hotel(QString name, QString location, QString feature, int star,QString id,State state,QString owner);//构造函数
    Room* addRoom(int price, Room_Type type, int roomnumber, int state);//添加房间
    QString returnId() const{return Hotel_Id;}//返回酒店id
    QString returnName() const{return Hotel_Name;}//返回酒店名字
    QString returnLocation() const{return Hotel_Location;}//返回酒店地址
    QString returnFeature() const {return Hotel_Feature;}//返回酒店特色
    QString returnOwner() const{return Hotel_Owner;}//返回酒店拥有者
    int returnStar() const{return Hotel_Star;}//返回酒店星级
    State returnState() const{return Hotel_State;}//返回酒店状态
    int returnTotalRoomNumber()const{return TotalRoomNumber;}
    int returnTotalLeftRoomNumber()const{return TotalLeftRoomNumber;}
    QString returnInfo(int index)const{return HotelInfo[index];}//得到酒店信息
    int returnScore(int index)const{return HotelScore[index];}//得到酒店得分
    int returnRoomnumber(int index)const{return RoomNumber[index];}//得到酒店总房间数
    int returnLeftRoomnumber(int index)const{return LeftRoomNumber[index];}//得到酒店房间余量
    int returnHotelPrice(int index)const{return HotelPrice[index];}//得到酒店房间定价
    void changeState(State h_state);//改变酒店状态
    void changeLeftnumber(Date dayin, Date dayout);//在顾客选定日期之后判断房间余量
    double calScore();//计算酒店评分
    Room* myroom[1000];//酒店的房间
private:
    QString Hotel_Name;
    QString Hotel_Location;
    QString Hotel_Feature;
    int Hotel_Star;
    QString Hotel_Id;
    QString Hotel_Owner;
    State Hotel_State;
    QString HotelInfo[7];//以字符串形式存储酒店信息
    int TotalRoomNumber;//总房间数
    int TotalLeftRoomNumber;//总剩余房间数
    int RoomNumber[4]={0,0,0,0};//存储酒店房间总数
    int LeftRoomNumber[4]={0,0,0,0};//存储酒店剩余的房间数
    int HotelPrice[4]={0,0,0,0};//存储酒店现在四种房间定价
    int HotelScore[5]={0,0,0,0,0};//酒店收到的评价
};


#endif // HOTEL_H
