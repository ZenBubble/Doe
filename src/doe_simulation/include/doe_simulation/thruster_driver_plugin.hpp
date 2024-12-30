#ifndef DOE_SIMULATION__THRUSTER_DRIVER_PLUGIN
#define DOE_SIMULATION__THRUSTER_DRIVER_PLUGIN

#include <gz/sim/Model.hh>
#include <gz/sim/Link.hh>
#include <gz/sim/Util.hh>
#include <gz/sim/System.hh>
#include <gz/plugin/Register.hh>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

namespace doe_simulation
{

    using namespace gz;
    using namespace sim;
    using namespace systems;

    class ThrusterDriver: public System, public ISystemConfigure, public ISystemPreUpdate
    {

    public:
        // Constructor
        ThrusterDriver(void);

        // Destructor
        ~ThrusterDriver(void);

        void Configure(const Entity &_entity, const std::shared_ptr<const sdf::Element> &_sdf, EntityComponentManager &_ecm, EventManager &_eventMgr) override;
    
        void PreUpdate(const UpdateInfo &_info, EntityComponentManager &_ecm) override;

    private:
        /** Get information about topic publishing thrust values
         * 
         * @param ros_sdf SDF pointer to ros namespace params
         * 
         */
        void GetRosNamespace(const std::shared_ptr<const sdf::Element> &_sdf);

        /** Receives the force values as a vector from the thrust allocation node
         * 
         * Called continuously and pass each force value to the correct thruster.
         * 
         * @param joint_cmd command from gazebo containing the thruster forces
         */
        void GetForceCmd(const std_msgs::msg::Float64MultiArray::SharedPtr joint_cmd);

        /** Publishes a fixed force value to each thruster in gazebo
         * 
         * Updates in sequence with gazebo's main world update function.
         * 
         */
        void ApplyForce(void);

        /** Spins ROS2 node on a dedicated thread to remain non-blocking
         * 
         */
        void SpinNode(void);

        Entity linkEntity;
        // Number of thrusters attached to model, by convention they must be named thruster<num> in SDF description 
        unsigned int thruster_count;

        rclcpp::Node::SharedPtr node;
        rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr force_cmd;

        std::vector<Entity> thrusters;
        std::vector<double> thrust_values;
        std::thread spinThread;
        std::string topic_name;
        
        
    };


}
#endif // DOE_SIMULATION__THRUSTER_DRIVER_PLUGIN
