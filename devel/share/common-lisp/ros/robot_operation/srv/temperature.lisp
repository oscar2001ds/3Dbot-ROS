; Auto-generated. Do not edit!


(cl:in-package robot_operation-srv)


;//! \htmlinclude temperature-request.msg.html

(cl:defclass <temperature-request> (roslisp-msg-protocol:ros-message)
  ((temperature
    :reader temperature
    :initarg :temperature
    :type cl:fixnum
    :initform 0))
)

(cl:defclass temperature-request (<temperature-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <temperature-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'temperature-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_operation-srv:<temperature-request> is deprecated: use robot_operation-srv:temperature-request instead.")))

(cl:ensure-generic-function 'temperature-val :lambda-list '(m))
(cl:defmethod temperature-val ((m <temperature-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_operation-srv:temperature-val is deprecated.  Use robot_operation-srv:temperature instead.")
  (temperature m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <temperature-request>) ostream)
  "Serializes a message object of type '<temperature-request>"
  (cl:let* ((signed (cl:slot-value msg 'temperature)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <temperature-request>) istream)
  "Deserializes a message object of type '<temperature-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'temperature) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<temperature-request>)))
  "Returns string type for a service object of type '<temperature-request>"
  "robot_operation/temperatureRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'temperature-request)))
  "Returns string type for a service object of type 'temperature-request"
  "robot_operation/temperatureRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<temperature-request>)))
  "Returns md5sum for a message object of type '<temperature-request>"
  "708df609bf4c0f5f446cfd5c1c3b552e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'temperature-request)))
  "Returns md5sum for a message object of type 'temperature-request"
  "708df609bf4c0f5f446cfd5c1c3b552e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<temperature-request>)))
  "Returns full string definition for message of type '<temperature-request>"
  (cl:format cl:nil "int8 temperature~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'temperature-request)))
  "Returns full string definition for message of type 'temperature-request"
  (cl:format cl:nil "int8 temperature~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <temperature-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <temperature-request>))
  "Converts a ROS message object to a list"
  (cl:list 'temperature-request
    (cl:cons ':temperature (temperature msg))
))
;//! \htmlinclude temperature-response.msg.html

(cl:defclass <temperature-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass temperature-response (<temperature-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <temperature-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'temperature-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_operation-srv:<temperature-response> is deprecated: use robot_operation-srv:temperature-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <temperature-response>) ostream)
  "Serializes a message object of type '<temperature-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <temperature-response>) istream)
  "Deserializes a message object of type '<temperature-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<temperature-response>)))
  "Returns string type for a service object of type '<temperature-response>"
  "robot_operation/temperatureResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'temperature-response)))
  "Returns string type for a service object of type 'temperature-response"
  "robot_operation/temperatureResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<temperature-response>)))
  "Returns md5sum for a message object of type '<temperature-response>"
  "708df609bf4c0f5f446cfd5c1c3b552e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'temperature-response)))
  "Returns md5sum for a message object of type 'temperature-response"
  "708df609bf4c0f5f446cfd5c1c3b552e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<temperature-response>)))
  "Returns full string definition for message of type '<temperature-response>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'temperature-response)))
  "Returns full string definition for message of type 'temperature-response"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <temperature-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <temperature-response>))
  "Converts a ROS message object to a list"
  (cl:list 'temperature-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'temperature)))
  'temperature-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'temperature)))
  'temperature-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'temperature)))
  "Returns string type for a service object of type '<temperature>"
  "robot_operation/temperature")