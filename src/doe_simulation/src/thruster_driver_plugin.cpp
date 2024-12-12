#include "doe_simulation/thruster_driver_plugin.hpp"

#include <gz/plugin/Register.hh>

using namespace doe_simulation;

ThrusterDriver::ThrusterDriver() : node{rclcpp::Node::make_shared("thruster_driver")} {}

ThrusterDriver::~ThrusterDriver() {}

void ThrusterDriver::Configure(const Entity &_entity, const std::shared_ptr<const sdf::Element> &_sdf, EntityComponentManager &_ecm, EventManager &_eventMgr) {
    (void) _entity;
    (void) _ecm;
    (void) _eventMgr;
    if (_sdf->HasElement("thruster_count"))
        {
            this->thruster_count = _sdf->Get<unsigned int>("thruster_count");
        }
        else
        {
            gzerr << "thruster_count value not specified, exiting.\n";
            exit(1);
        }

    this->GetRosNamespace(_sdf);

    this->thrust_values = std::vector<double>(this->thruster_count, 0);
    this->force_cmd = node->create_subscription<std_msgs::msg::Float64MultiArray>(
                        this->topic_name, 
                        10, 
                        std::bind(&ThrusterDriver::GetForceCmd, this, std::placeholders::_1));

    RCLCPP_INFO(node->get_logger(), ("Listening on " + this->topic_name + "\n").c_str());


    // auto _model = Model(_entity);

    // std::string model_name = _model.GetName(); // this is being pissy

    // for (unsigned int i = 1; i <= thruster_count; i++)
    // {
    //     std::string thruster_name = model_name + "::thruster" + std::to_string(i) + "::thruster";
    //     this->thruster.push_back(_model->GetLink(thruster_name));

    //     RCLCPP_INFO(this->node->get_logger(), this->thruster[i-1]->GetName());
    // }




};
    
void ThrusterDriver::Update(const UpdateInfo &_info, EntityComponentManager &_ecm) {
    (void) _ecm;

    (void) _info;
};

void ThrusterDriver::GetRosNamespace(const std::shared_ptr<const sdf::Element> &_sdf)
{
    std::string _namespace;
    std::string topic;

    if (_sdf->HasElement("namespace"))
    {
        _namespace = _sdf->Get<std::string>("namespace");
    }
    else
    {
        _namespace = "doe/doe_simulation";
    }

    if (_sdf->HasElement("remapping"))
    {
        topic = _sdf->Get<std::string>("remapping");
    }
    else
    {
        topic = "thruster_values";
    }

    this->topic_name = _namespace + "/" + topic;
}

void ThrusterDriver::GetForceCmd(const std_msgs::msg::Float64MultiArray::SharedPtr joint_cmd)
{
    if (joint_cmd->data.size() != this->thruster_count)
    {
        RCLCPP_WARN(node->get_logger(), "message size does not match thruster count, ignoring command.\n");
        return;
    }

    for (unsigned int i = 0; i < this->thruster_count; i++)
    {
        this->thrust_values[i] = joint_cmd->data[i];
    }
}

GZ_ADD_PLUGIN(doe_simulation::ThrusterDriver, gz::sim::System, ThrusterDriver::ISystemUpdate, ThrusterDriver::ISystemConfigure)

GZ_ADD_PLUGIN_ALIAS(ThrusterDriver, "gz::sim::systems::ThrusterDriver")