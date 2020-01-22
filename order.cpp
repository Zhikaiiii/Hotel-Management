#include "order.h"
#include <QString>
Order::Order(){}

Order::Order(int num, QString hotel, QString customer, Date day_in, Date day_out, Room_Type type, int number)
    :Ordernumber(num),its_Hotel(hotel),its_Customer(customer),Day_in(day_in),Day_out(day_out),Type(type),Number(number),State(Paying)
{
    //设定存储订单信息的字符串数组
    OrderInfo[0]=QString::number(Ordernumber);
    OrderInfo[1]=its_Hotel;
    OrderInfo[2]=its_Customer;
    OrderInfo[3]=Day_in.returnDate();
    OrderInfo[4]=Day_out.returnDate();
    switch(Type)
    {
    case 0:
    {
        OrderInfo[5]="单人房";
        break;
    }
    case 1:
    {
        OrderInfo[5]="双人房";
        break;
    }
    case 2:
    {
        OrderInfo[5]="家庭房";
        break;
    }
    case 3:
    {
        OrderInfo[5]="豪华套房";
    }
    default:
    {
        break;
    }
    }
    OrderInfo[6]=QString::number(Number);
    OrderInfo[7]="已付款";
    OrderInfo[8]="未评价";
    OrderInfo[9]="好评";
    Customer_score=false;
    Hotel_score=0;
}

void Order::changeState(Order_State new_state)//改变订单状态
{
    State=new_state;
    switch(State)
    {
    case 0:
    {
        OrderInfo[7]="已付款";
        break;
    }
    case 1:
    {
        OrderInfo[7]="退款中";
        break;
    }
    case 2:
    {
        OrderInfo[7]="已退款";
        break;
    }
    case 3:
    {
        OrderInfo[7]="已入住";
        break;
    }
    case 4:
    {
        OrderInfo[7]="已退房";
        break;
    }
    default:
    {
        break;
    }
    }
}

void Order::setRoomnumber(int k,int roomnumber)//添加订单房间号
{
    Rooms_Number[k]=roomnumber;
}

void Order::scoreHotel(int score)
{
    if(State==Checkingout)//只有退房后才可评价
    {
        Hotel_score=score;
    }
    else
    {
        Hotel_score=0;
    }
    OrderInfo[8]=QString::number(Hotel_score);
}

void Order::scoreCustomer(int score)
{
    if(State==Checkingout)//只有退房后才可投诉顾客
    {
        if(score!=0)
        Customer_score=true;
    }
    else
    {
        Customer_score=false;
    }
    if(Customer_score)
    {
        OrderInfo[9]="投诉";
    }
    else
    {
        OrderInfo[9]="好评";
    }
}
