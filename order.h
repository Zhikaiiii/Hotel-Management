#ifndef ORDER_H
#define ORDER_H
#include <QString>
#include "hotel.h"
#include "date.h"
enum Order_State{Paying,Refunding,Refuned,Checkingin,Checkingout};
//订单状态（已付款，正在退款，已退款，已入住，已退房）

class Order
{
public:
    Order();
    Order(int num,QString hotel,QString customer,Date day_in,Date day_out,Room_Type type,int number);
    void changeState(Order_State new_state);//改变订单状态
    void setRoomnumber(int k,int roomnumber);//设定房间号
    void scoreHotel(int score);//酒店评分
    void scoreCustomer(int score);//顾客评分
    int returnOrdenumber()const{return Ordernumber;}//得到订单号
    int returnState()const{return (int)State;}//返回订单状态
    int returnType()const{return (int)Type;}//得到订单的房间类型
    int returnNumber()const{return Number;}//得到订单的房间数
    int returnHscore()const{return Hotel_score;}//得到订单的酒店评价
    int returnCscore()const{return (Customer_score)?1:0;}//得到顾客是否被投诉的信息
    int returnRoomsNumber(int index)const{return Rooms_Number[index];}
    QString returnHotel()const{return its_Hotel;}//得到订单对应的酒店
    QString returnCustomer()const{return its_Customer;}//得到订单对应的客户
    QString returnDayin()const{return Day_in.returnDate();}//得到订单对应的入住日期
    QString returnDayout()const{return Day_out.returnDate();}//得到订单对应的离店日期
    QString returnInfo(int index)const{return OrderInfo[index];}//得到订单的字符串信息

private:
    int Ordernumber;//订单号
    Order_State State;
    QString its_Hotel;
    QString its_Customer;
    Date Day_in;
    Date Day_out;
    Room_Type Type;
    int Number;//订单对应的房间数
    int Hotel_score;//酒店评价
    bool Customer_score;//顾客评价
    QString OrderInfo[10];
    int Rooms_Number[100];//房间号
};

#endif // ORDER_H
