; Auto-generated. Do not edit!


(cl:in-package robot_operation-srv)


;//! \htmlinclude powerState-request.msg.html

(cl:defclass <powerState-request> (roslisp-msg-protocol:ros-message)
  ((platform
    :reader platform
    :initarg :platform
    :type cl:boolean
    :initform cl:nil)
   (arm
    :reader arm
    :initarg :arm
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass powerState-request (<powerState-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <powerState-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'powerState-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_operation-srv:<powerState-request> is deprecated: use robot_operation-srv:powerState-request instead.")))

(cl:ensure-generic-function 'platform-val :lambda-list '(m))
(cl:defmethod platform-val ((m <powerState-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_operation-srv:platform-val is deprecated.  Use robot_operation-srv:platform instead.")
  (platform m))

(cl:ensure-generic-function 'arm-val :lambda-list '(m))
(cl:defmethod arm-val ((m <powerState-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_operation-srv:arm-val is deprecated.  Use robot_operation-srv:arm instead.")
  (arm m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <powerState-request>) ostream)
  "Serializes a message object of type '<powerState-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'platform) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'arm) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <powerState-request>) istream)
  "Deserializes a message object of type '<powerState-request>"
    (cl:setf (cl:slot-value msg 'platform) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'arm) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<powerState-request>)))
  "Returns string type for a service object of type '<powerState-request>"
  "robot_operation/powerStateRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'powerState-request)))
  "Returns string type for a service object of type 'powerState-request"
  "robot_operation/powerStateRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<powerState-request>)))
  "Returns md5sum for a message object of type '<powerState-request>"
  "e169ea722c6db37813a8d2b875c7d996")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'powerState-request)))
  "Returns md5sum for a message object of type 'powerState-request"
  "e169ea722c6db37813a8d2b875c7d996")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<powerState-request>)))
  "Returns full string definition for message of type '<powerState-request>"
  (cl:format cl:nil "bool platform~%bool arm~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'powerState-request)))
  "Returns full string definition for message of type 'powerState-request"
  (cl:format cl:nil "bool platform~%bool arm~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <powerState-request>))
  (cl:+ 0
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <powerState-request>))
  "Converts a ROS message object to a list"
  (cl:list 'powerState-request
    (cl:cons ':platform (platform msg))
    (cl:cons ':arm (arm msg))
))
;//! \htmlinclude powerState-response.msg.html

(cl:defclass <powerState-response> (roslisp-msg-protocol:ros-message)
  ((finished
    :reader finished
    :initarg :finished
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass powerState-response (<powerState-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <powerState-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'powerState-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_operation-srv:<powerState-response> is deprecated: use robot_operation-srv:powerState-response instead.")))

(cl:ensure-generic-function 'finished-val :lambda-list '(m))
(cl:defmethod finished-val ((m <powerState-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_operation-srv:finished-val is deprecated.  Use robot_operation-srv:finished instead.")
  (finished m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <powerState-response>) ostream)
  "Serializes a message object of type '<powerState-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'finished) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <powerState-response>) istream)
  "Deserializes a message object of type '<powerState-response>"
    (cl:setf (cl:slot-value msg 'finished) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<powerState-response>)))
  "Returns string type for a service object of type '<powerState-response>"
  "robot_operation/powerStateResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'powerState-response)))
  "Returns string type for a service object of type 'powerState-response"
  "robot_operation/powerStateResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<powerState-response>)))
  "Returns md5sum for a message object of type '<powerState-response>"
  "e169ea722c6db37813a8d2b875c7d996")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'powerState-response)))
  "Returns md5sum for a message object of type 'powerState-response"
  "e169ea722c6db37813a8d2b875c7d996")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<powerState-response>)))
  "Returns full string definition for message of type '<powerState-response>"
  (cl:format cl:nil "bool finished~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'powerState-response)))
  "Returns full string definition for message of type 'powerState-response"
  (cl:format cl:nil "bool finished~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <powerState-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <powerState-response>))
  "Converts a ROS message object to a list"
  (cl:list 'powerState-response
    (cl:cons ':finished (finished msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'powerState)))
  'powerState-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'powerState)))
  'powerState-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'powerState)))
  "Returns string type for a service object of type '<powerState>"
  "robot_operation/powerState")