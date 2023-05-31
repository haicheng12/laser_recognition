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

#include "multi_navi_goal_panel.h"

namespace navi_multi_goals_pub_rviz_plugin
{
    MultiNaviGoalsPanel::MultiNaviGoalsPanel(QWidget *parent)
        : rviz::Panel(parent), nh_()
    {
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
        connect(output_button_, SIGNAL(clicked()), this, SLOT(updateNum()));
    }

    void MultiNaviGoalsPanel::updateNum()
    {
        ROS_WARN("updateNum");
    }

    // spin for subscribing
    void
    MultiNaviGoalsPanel::startSpin()
    {
        if (ros::ok())
        {
            ros::spinOnce();
        }
    }

} // end namespace navi-multi-goals-pub-rviz-plugin

// 声明此类是一个rviz的插件

#include <pluginlib/class_list_macros.h>

PLUGINLIB_EXPORT_CLASS(navi_multi_goals_pub_rviz_plugin::MultiNaviGoalsPanel, rviz::Panel)
