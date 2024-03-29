// Generated by gencpp from file robot_operation/temperatureRequest.msg
// DO NOT EDIT!


#ifndef ROBOT_OPERATION_MESSAGE_TEMPERATUREREQUEST_H
#define ROBOT_OPERATION_MESSAGE_TEMPERATUREREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace robot_operation
{
template <class ContainerAllocator>
struct temperatureRequest_
{
  typedef temperatureRequest_<ContainerAllocator> Type;

  temperatureRequest_()
    : temperature(0)  {
    }
  temperatureRequest_(const ContainerAllocator& _alloc)
    : temperature(0)  {
  (void)_alloc;
    }



   typedef int8_t _temperature_type;
  _temperature_type temperature;





  typedef boost::shared_ptr< ::robot_operation::temperatureRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::robot_operation::temperatureRequest_<ContainerAllocator> const> ConstPtr;

}; // struct temperatureRequest_

typedef ::robot_operation::temperatureRequest_<std::allocator<void> > temperatureRequest;

typedef boost::shared_ptr< ::robot_operation::temperatureRequest > temperatureRequestPtr;
typedef boost::shared_ptr< ::robot_operation::temperatureRequest const> temperatureRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::robot_operation::temperatureRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::robot_operation::temperatureRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::robot_operation::temperatureRequest_<ContainerAllocator1> & lhs, const ::robot_operation::temperatureRequest_<ContainerAllocator2> & rhs)
{
  return lhs.temperature == rhs.temperature;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::robot_operation::temperatureRequest_<ContainerAllocator1> & lhs, const ::robot_operation::temperatureRequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace robot_operation

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::robot_operation::temperatureRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robot_operation::temperatureRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::robot_operation::temperatureRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::robot_operation::temperatureRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robot_operation::temperatureRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robot_operation::temperatureRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::robot_operation::temperatureRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "708df609bf4c0f5f446cfd5c1c3b552e";
  }

  static const char* value(const ::robot_operation::temperatureRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x708df609bf4c0f5fULL;
  static const uint64_t static_value2 = 0x446cfd5c1c3b552eULL;
};

template<class ContainerAllocator>
struct DataType< ::robot_operation::temperatureRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "robot_operation/temperatureRequest";
  }

  static const char* value(const ::robot_operation::temperatureRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::robot_operation::temperatureRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int8 temperature\n"
;
  }

  static const char* value(const ::robot_operation::temperatureRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::robot_operation::temperatureRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.temperature);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct temperatureRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::robot_operation::temperatureRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::robot_operation::temperatureRequest_<ContainerAllocator>& v)
  {
    s << indent << "temperature: ";
    Printer<int8_t>::stream(s, indent + "  ", v.temperature);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROBOT_OPERATION_MESSAGE_TEMPERATUREREQUEST_H
