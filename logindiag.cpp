#include "logindiag.h"
#include "ui_logindiag.h"
#include "registerdiag.h"
#include <QMessageBox>
#include <QString>
#include "data.h"

LoginDiag::LoginDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDiag)
{
    //界面美化
    ui->setupUi(this);
    QPixmap pixmap = QPixmap(":/images/1.png").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
}

LoginDiag::~LoginDiag()
{
    delete ui;
}

void LoginDiag::on_ExitBtn_clicked()
{
    close();
}

void LoginDiag::on_LoginBtn_clicked()//登录界面
{
    QString Id=ui->usrLineEdit->text();
    int Type=ui->comboBox->currentIndex();
    People_Type P_Type=People_Type(Type);
    QString Password=ui->pwdLineEdit->text();
    if(all_people.contains(Id)
         && Password==all_people.value(Id)->returnPass()
           &&all_people.value(Id)->returnType()==P_Type)
    {
        QMessageBox::QMessageBox::information(this, tr("提示！"),tr("登录成功！"), QMessageBox::Yes);
        int user_type=ui->comboBox->currentIndex();
        loginuser=all_people.value(Id);
        switch(user_type)//根据用户类型显示界面
        {
            case 0:
            {
                hhotel=new MainWindow(this);
                this->hide();
                hhotel->show();
                break;
            }
            case 1:
            {
                ccustomer=new customerDialog(this);
                this->hide();
                ccustomer->show();
                break;
            }
            case 2:
            {
                ssupervisor=new MainWindow_supervisor(this);
                this->hide();
                ssupervisor->show();
                break;
            }
            case 3:
            {
                mmanager=new MainWindow_manager(this);
                this->hide();
                mmanager->show();
                break;
            }
            default:
            {
                break;
            }
        }
    }
    else
    {
        QMessageBox::QMessageBox::warning(this, tr("警告！"),tr("用户名或密码错误！"), QMessageBox::Yes);
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->usrLineEdit->setFocus();
    }
}

void LoginDiag::on_pwdLineEdit_cursorPositionChanged(int Old, int New)//提示条的显示与否
{
    if(ui->pwdLineEdit->text().length()!=0)
    {
        ui->Tip->close();
    }
    else
    {
        ui->Tip->show();
    }
}

void LoginDiag::on_RegBtn_clicked()//注册界面
{
    registerdiag *dig=new registerdiag(this);
    dig->show();
}

void LoginDiag::closeEvent(QCloseEvent *event)//数据保存
{
    int temp =QMessageBox::question(this,tr("关闭"),tr("是否要关闭程序？"),QMessageBox::Yes,QMessageBox::No);
    if(temp == QMessageBox::Yes)
    {
        savedata();
        savadataH();
        savedataO();
        this->close();
    }
    else
    {
        event->ignore();
    }
}
