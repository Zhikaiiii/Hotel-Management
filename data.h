#ifndef DATA_H
#define DATA_H
#include <QHash>
#include "people.h"
#include "hotel.h"
#include "room.h"
#include "date.h"
#include <QString>
extern QHash<QString,People *>all_people;//存储所有用户的hash表，以id为主键
extern QHash<int,QString>new_people;//存储新增用户的hash表，以数量为主键
extern int new_people_number;//新增用户的数量
extern int all_people_number;//用户数
extern QString people[1000];//存储所有用户的用户名

extern QHash<QString,QString>now_manager;//存储经理及其对应的老板
extern int new_manager_number;//新添加的经理数量
extern QString new_manager[100];//新添加的经理的用户id
extern QString its_boss[100];//对应的酒店老板用户id


extern QHash<QString,Hotel *>all_hotel;//存储所有酒店的hash表，以酒店id为主键
extern QHash<int,QString>new_hotel;//新注册的酒店
extern int hotel_number;//酒店数目
extern int new_hotel_number;//新注册的酒店数目
extern QString hotel[1000];//存储酒店的id
extern Room* new_room[1000];//
extern int new_room_number;//新添加的房间数目
extern int room_number;//总房间数目

extern QHash<int,Order *>all_order;//存储所有订单的hash表，以订单号为主键
extern QHash<int,int>new_order;//新添加的订单
extern int all_order_number;//订单数
extern int new_order_number;//新增加的订单数

extern Date day_in;//顾客预订时选定的入住时间
extern Date day_out;//顾客预订时选定的退房时间

extern People* loginuser;//当前登录的用户
extern Hotel* selecthotel;//当前操作的酒店
extern Order* selectorder;//当前操作的订单

void createConnection();//用户数据的初始化赋值
void hotel_createConnection();//酒店以及房间数据的初始化赋值
void order_createConnection();//订单数据的初始化赋值

void insert_Data(People* p);//增加用户
void insert_Data(Hotel* h);//注册酒店
void insert_Data(Order* o);//新增订单

void savedata();//用户信息存入数据库
void savadataH();//酒店信息存入数据库
void savedataO();//订单信息存入数据库

template<class T>
void Swap(T& a,T& b);//交换函数

void SortScore();//按评分排序
void SortPrice(int type);//按价格排序
void SortLeft(int type);//按房间余量排序

#endif // DATA_H
