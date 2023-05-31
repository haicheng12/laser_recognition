#ifndef MULTI_NAVI_GOAL_PANEL_H
#define MULTI_NAVI_GOAL_PANEL_H

#include <ros/ros.h>
#include <ros/console.h>

#include <rviz/panel.h>

#include <QPushButton>

namespace navi_multi_goals_pub_rviz_plugin
{
    class MultiNaviGoalsPanel : public rviz::Panel
    {
        Q_OBJECT
    public:
        explicit MultiNaviGoalsPanel(QWidget *parent = 0);

    public Q_SLOTS:

    protected Q_SLOTS:

        void updateNum(); // update max number of goal

        static void startSpin(); // spin for sub
    protected:
        QPushButton *output_button_;

        // The ROS node handle.
        ros::NodeHandle nh_;
    };

} // end namespace navi-multi-goals-pub-rviz-plugin

#endif // MULTI_NAVI_GOAL_PANEL_H
