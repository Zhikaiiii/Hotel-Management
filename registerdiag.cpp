#include "registerdiag.h"
#include "ui_registerdiag.h"
#include "logindiag.h"
#include <QMessageBox>
#include "data.h"


registerdiag::registerdiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerdiag)
{
    ui->setupUi(this);
    QPixmap pixmap = QPixmap(":/images/1.png").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
}

registerdiag::~registerdiag()
{
    delete ui;
}

//注册及条件要求判断
bool registerdiag::judgeId()
{
    QString Id=ui->lineEdit_name->text();
    if(Id.length()!=11)
    {
        return false;
    }
    else if(Id[0]=='0')
    {
        return false;
    }
    else
    {
        for(int i=0;i<11;i++)
        {
            if(Id[i]<'0'||Id[i]>'9')
            {
                return false;
            }
        }
        return true;
    }
}
void registerdiag::on_pushButton_clicked()
{
    if(!judgeId())
    {
        QMessageBox::QMessageBox::warning(this, tr("警告！"),tr("用户名必须为11位手机号！"), QMessageBox::Yes);
    }
    else
    {
        if(ui->LineEdit_Pass2->text().length()>8)
        {
            if((ui->LineEdit_Pass2->text()==ui->LineEdit_pass->text()))
            {
                QString Id;
                int Type;
                People_Type P_Type;
                QString Password;
                Id=ui->lineEdit_name->text();
                Type=ui->comboBox_Type->currentIndex();
                P_Type=People_Type(Type);
                Password=ui->LineEdit_pass->text();
                if(all_people.contains(Id))
                {
                    QMessageBox::QMessageBox::warning(this, tr("提示！"),tr("该账号已被注册！"), QMessageBox::Yes);
                }
                else
                {
                    QMessageBox::QMessageBox::information(this, tr("提示！"),tr("注册成功！"), QMessageBox::Yes);
                    //People *p=new People(Id,Password,P_Type);
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
                    insert_Data(p);
                }
                this->close();
            }
            else
            {
                 QMessageBox::QMessageBox::warning(this, tr("警告！"),tr("两次密码必须相同！"), QMessageBox::Yes);
            }
        }
        else
        {
             QMessageBox::QMessageBox::warning(this, tr("警告！"),tr("密码长度必须大于8！"), QMessageBox::Yes);
        }
    }

}

void registerdiag::on_pushButton_2_clicked()
{
    close();
}

void registerdiag::on_LineEdit_pass_cursorPositionChanged(int Old, int New)//提示框显示
{
    if(ui->LineEdit_pass->text() == ui->LineEdit_Pass2->text())
    {
            ui->Tips->close();
            Judge=true;
    }
    else
    {
        if(Judge == true)
        {
            ui->Tips->show();
            Judge=false;
        }
    }
}

void registerdiag::on_LineEdit_Pass2_cursorPositionChanged(int arg1, int arg2)//提示框显示
{
    if(arg2>8&&arg1==8)
    {
        ui->Tip->close();
    }
    else if(arg1==9&&arg2<9)
    {
        ui->Tip->show();
    }
}


