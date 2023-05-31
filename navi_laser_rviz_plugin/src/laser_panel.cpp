#include <cstdio>

#include <ros/console.h>

#include <fstream>
#include <sstream>

#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/qheaderview.h>

#include "laser_panel.h"

namespace navi_laser_rviz_plugin
{
    LaserPanel::LaserPanel(QWidget *parent)
        : rviz::Panel(parent), nh_()
    {
        laser_ip_pub_ = nh_.advertise<std_msgs::String>("laser_ip_message", 1);

        QVBoxLayout *root_layout = new QVBoxLayout;
        QHBoxLayout *max_layout = new QHBoxLayout;
        output_button_ = new QPushButton("确定");
        max_layout->addWidget(output_button_);
        root_layout->addLayout(max_layout);

        setLayout(root_layout);
        // set a Qtimer to start a spin for subscriptions
        QTimer *output_timer = new QTimer(this);
        output_timer->start(200);

        // 设置信号与槽的连接
        // connect(output_button_, SIGNAL(clicked()), this, SLOT(updateNum()));
        connect(output_button_, &QPushButton::clicked, [=]()
                {
                    IniLaser iniLaser; // 实例化

                    QWidget *widget = new QWidget(); // 创建主窗口
                    widget->setWindowTitle("雷达参数设置");
                    widget->resize(320, 160);

                    QLineEdit *edit = new QLineEdit();                   // 创建输入框
                    QFormLayout *layout = new QFormLayout();             // 创建文本框
                    layout->setRowWrapPolicy(QFormLayout::DontWrapRows); // 标签始终在输入框的左侧
                    // 添加输入框和标签
                    layout->addRow("雷达IP", edit);
                    // 设置行间距和列间距为10
                    layout->setSpacing(10);

                    QSettings *configIniRead = new QSettings("/home/ubuntu/catkin_ws/src/laser_recognition/navi_laser_rviz_plugin/ini/laser.ini", QSettings::IniFormat); // 初始化读取Ini文件对象
                    iniLaser.ip = configIniRead->value("laser/ip").toString();

                    edit->setText(iniLaser.ip); // 赋值
                    // //将layout表单添加到widget窗口中
                    widget->setLayout(layout);

                    QPushButton *button1 = new QPushButton;
                    button1->setParent(widget);
                    button1->setText("读取参数");
                    button1->resize(80, 30);
                    button1->move(20, 100);
                    QObject::connect(button1, &QPushButton::clicked, [=]()
                    {
                        qDebug() << "read laser ip";  // 读取IP

                        IniLaser iniLaser;  // 实例化
                        QSettings *configIniRead = new QSettings("/home/ubuntu/catkin_ws/src/laser_recognition/navi_laser_rviz_plugin/ini/laser.ini", QSettings::IniFormat); // 初始化读取Ini文件对象
                        iniLaser.ip = configIniRead->value("laser/ip").toString();
                        edit->setText(iniLaser.ip); // 赋值
                    });

                    QPushButton *button2 = new QPushButton;
                    button2->setParent(widget);
                    button2->setText("写入参数");
                    button2->resize(80, 30);
                    button2->move(120, 100);
                    QObject::connect(button2, &QPushButton::clicked, [=]()
                    {
                        qDebug() << "write laser ip";//写入IP

                        QSettings *configIniWrite = new QSettings("/home/ubuntu/catkin_ws/src/laser_recognition/navi_laser_rviz_plugin/ini/laser.ini", QSettings::IniFormat);
                        configIniWrite->setValue("laser/ip", edit->text()); 
                    });

                    QPushButton *button3 = new QPushButton;
                    button3->setParent(widget);
                    button3->setText("发送参数");
                    button3->resize(80, 30);
                    button3->move(220, 100);
                    QObject::connect(button3, &QPushButton::clicked, [=]()
                    {
                        qDebug() << "send laser ip";//发送IP

                        IniLaser iniLaser;  // 实例化
                        QSettings *configIniRead = new QSettings("/home/ubuntu/catkin_ws/src/laser_recognition/navi_laser_rviz_plugin/ini/laser.ini", QSettings::IniFormat); // 初始化读取Ini文件对象
                        iniLaser.ip = configIniRead->value("laser/ip").toString();

                        std::string str;
                        str = iniLaser.ip.toStdString();
                        std::cout << str << std::endl;

                        std_msgs::String laser_msg;
                        laser_msg.data = str;
                        laser_ip_pub_.publish(laser_msg);
                    });

                    widget->show(); }); // 设置IP
    }

    // void LaserPanel::updateNum()
    // {
    //     ROS_WARN("updateNum");
    // }

    // spin for subscribing
    void LaserPanel::startSpin()
    {
        if (ros::ok())
        {
            ros::spinOnce();
        }
    }

} // end namespace navi-multi-goals-pub-rviz-plugin

// 声明此类是一个rviz的插件

#include <pluginlib/class_list_macros.h>

PLUGINLIB_EXPORT_CLASS(navi_laser_rviz_plugin::LaserPanel, rviz::Panel)
