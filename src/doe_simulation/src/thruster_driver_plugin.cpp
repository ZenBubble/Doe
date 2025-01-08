#include "doe_simulation/thruster_driver_plugin.hpp"

#include <gz/plugin/Register.hh>


namespace doe_simulation {


    ThrusterDriver::ThrusterDriver() {}

    ThrusterDriver::~ThrusterDriver() {}
        
    void ThrusterDriver::Configure(const Entity &_entity, const std::shared_ptr<const sdf::Element> &_sdf, EntityComponentManager &_ecm, EventManager &_eventMgr) {
        (void) _eventMgr;

        if (!rclcpp::ok()) {
            rclcpp::init(0, nullptr);
        }

        node = rclcpp::Node::make_shared("thruster_driver");

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

        auto _model = Model(_entity);

        std::string model_name = _model.Name(_ecm);


        for (unsigned int i = 1; i <= thruster_count; i++)
        {
            std::string thruster_name = model_name + "::thruster" + std::to_string(i);
            this->thrusters.push_back(_model.LinkByName(_ecm, thruster_name));
        }
        
        thrusters = _model.Models(_ecm);

        /// @todo feels like there should be a way to pass rclcpp::spin directly to thread, this works the way it is though 
        this->spinThread = std::thread(std::bind(&ThrusterDriver::SpinNode, this));
    }
        
    void ThrusterDriver::PreUpdate(const UpdateInfo &_info, EntityComponentManager &_ecm) {
        (void) _info;

        for (unsigned int i = 0; i < thruster_count; i++)
        {   
            auto model = Model(thrusters[i]);
            Link thruster = Link(model.LinkByName(_ecm, "thruster"));
            thruster.AddWorldForce(_ecm, math::Vector3d(0, 0, this->thrust_values[i])); // could add a position here for third arg to offset so its pushing from the back 
        }
    }

    void ThrusterDriver::GetRosNamespace(const std::shared_ptr<const sdf::Element> &_sdf) // why does this exist? flexibility for setting topic name sure but just do in code
    {
        std::string _namespace;
        std::string topic;

        if (_sdf->HasElement("namespace"))
        {
            _namespace = _sdf->Get<std::string>("namespace");
        }
        else
        {
            _namespace = "doe/control";
        }

        if (_sdf->HasElement("remapping"))
        {
            topic = _sdf->Get<std::string>("remapping");
        }
        else
        {
            topic = "output_forces";
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


    void ThrusterDriver::SpinNode()
    {
        rclcpp::spin(node);
    }

}

GZ_ADD_PLUGIN(doe_simulation::ThrusterDriver, gz::sim::System, doe_simulation::ThrusterDriver::ISystemPreUpdate, doe_simulation::ThrusterDriver::ISystemConfigure)

GZ_ADD_PLUGIN_ALIAS(doe_simulation::ThrusterDriver, "gz::sim::systems::ThrusterDriver")

