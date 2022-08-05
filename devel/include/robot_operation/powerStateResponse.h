// Generated by gencpp from file robot_operation/powerStateResponse.msg
// DO NOT EDIT!


#ifndef ROBOT_OPERATION_MESSAGE_POWERSTATERESPONSE_H
#define ROBOT_OPERATION_MESSAGE_POWERSTATERESPONSE_H


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
struct powerStateResponse_
{
  typedef powerStateResponse_<ContainerAllocator> Type;

  powerStateResponse_()
    : finished(false)  {
    }
  powerStateResponse_(const ContainerAllocator& _alloc)
    : finished(false)  {
  (void)_alloc;
    }



   typedef uint8_t _finished_type;
  _finished_type finished;





  typedef boost::shared_ptr< ::robot_operation::powerStateResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::robot_operation::powerStateResponse_<ContainerAllocator> const> ConstPtr;

}; // struct powerStateResponse_

typedef ::robot_operation::powerStateResponse_<std::allocator<void> > powerStateResponse;

typedef boost::shared_ptr< ::robot_operation::powerStateResponse > powerStateResponsePtr;
typedef boost::shared_ptr< ::robot_operation::powerStateResponse const> powerStateResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::robot_operation::powerStateResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::robot_operation::powerStateResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::robot_operation::powerStateResponse_<ContainerAllocator1> & lhs, const ::robot_operation::powerStateResponse_<ContainerAllocator2> & rhs)
{
  return lhs.finished == rhs.finished;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::robot_operation::powerStateResponse_<ContainerAllocator1> & lhs, const ::robot_operation::powerStateResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace robot_operation

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::robot_operation::powerStateResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robot_operation::powerStateResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::robot_operation::powerStateResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::robot_operation::powerStateResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robot_operation::powerStateResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robot_operation::powerStateResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::robot_operation::powerStateResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e2797c797e620a950ba704492d72873b";
  }

  static const char* value(const ::robot_operation::powerStateResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe2797c797e620a95ULL;
  static const uint64_t static_value2 = 0x0ba704492d72873bULL;
};

template<class ContainerAllocator>
struct DataType< ::robot_operation::powerStateResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "robot_operation/powerStateResponse";
  }

  static const char* value(const ::robot_operation::powerStateResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::robot_operation::powerStateResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool finished\n"
;
  }

  static const char* value(const ::robot_operation::powerStateResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::robot_operation::powerStateResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.finished);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct powerStateResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::robot_operation::powerStateResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::robot_operation::powerStateResponse_<ContainerAllocator>& v)
  {
    s << indent << "finished: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.finished);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROBOT_OPERATION_MESSAGE_POWERSTATERESPONSE_H
