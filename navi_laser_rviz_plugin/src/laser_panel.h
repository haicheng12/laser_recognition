#ifndef MULTI_NAVI_GOAL_PANEL_H
#define MULTI_NAVI_GOAL_PANEL_H

#include <ros/ros.h>
#include <std_msgs/String.h>

#include <rviz/panel.h>

#include <QPushButton>
#include <QSettings>
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>

#include <string.h>
#include <iostream>

typedef struct IniLaser
{
    QString ip; // ip
} IniLaser;

namespace navi_laser_rviz_plugin
{
    class LaserPanel : public rviz::Panel
    {
        Q_OBJECT
    public:
        explicit LaserPanel(QWidget *parent = 0);

    public Q_SLOTS:

    protected Q_SLOTS:

        void updateNum();        // update max number
        static void startSpin(); // spin for sub

    protected:
        QPushButton *output_button_;

        // The ROS node handle.
        ros::NodeHandle nh_;

        ros::Publisher laser_ip_pub_;
    };

} // end namespace navi-multi-goals-pub-rviz-plugin

#endif // MULTI_NAVI_GOAL_PANEL_H
