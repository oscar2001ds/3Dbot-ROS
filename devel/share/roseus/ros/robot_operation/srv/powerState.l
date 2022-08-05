;; Auto-generated. Do not edit!


(when (boundp 'robot_operation::powerState)
  (if (not (find-package "ROBOT_OPERATION"))
    (make-package "ROBOT_OPERATION"))
  (shadow 'powerState (find-package "ROBOT_OPERATION")))
(unless (find-package "ROBOT_OPERATION::POWERSTATE")
  (make-package "ROBOT_OPERATION::POWERSTATE"))
(unless (find-package "ROBOT_OPERATION::POWERSTATEREQUEST")
  (make-package "ROBOT_OPERATION::POWERSTATEREQUEST"))
(unless (find-package "ROBOT_OPERATION::POWERSTATERESPONSE")
  (make-package "ROBOT_OPERATION::POWERSTATERESPONSE"))

(in-package "ROS")





(defclass robot_operation::powerStateRequest
  :super ros::object
  :slots (_platform _arm ))

(defmethod robot_operation::powerStateRequest
  (:init
   (&key
    ((:platform __platform) nil)
    ((:arm __arm) nil)
    )
   (send-super :init)
   (setq _platform __platform)
   (setq _arm __arm)
   self)
  (:platform
   (&optional (__platform :null))
   (if (not (eq __platform :null)) (setq _platform __platform)) _platform)
  (:arm
   (&optional (__arm :null))
   (if (not (eq __arm :null)) (setq _arm __arm)) _arm)
  (:serialization-length
   ()
   (+
    ;; bool _platform
    1
    ;; bool _arm
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _platform
       (if _platform (write-byte -1 s) (write-byte 0 s))
     ;; bool _arm
       (if _arm (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _platform
     (setq _platform (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _arm
     (setq _arm (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass robot_operation::powerStateResponse
  :super ros::object
  :slots (_finished ))

(defmethod robot_operation::powerStateResponse
  (:init
   (&key
    ((:finished __finished) nil)
    )
   (send-super :init)
   (setq _finished __finished)
   self)
  (:finished
   (&optional (__finished :null))
   (if (not (eq __finished :null)) (setq _finished __finished)) _finished)
  (:serialization-length
   ()
   (+
    ;; bool _finished
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _finished
       (if _finished (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _finished
     (setq _finished (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass robot_operation::powerState
  :super ros::object
  :slots ())

(setf (get robot_operation::powerState :md5sum-) "e169ea722c6db37813a8d2b875c7d996")
(setf (get robot_operation::powerState :datatype-) "robot_operation/powerState")
(setf (get robot_operation::powerState :request) robot_operation::powerStateRequest)
(setf (get robot_operation::powerState :response) robot_operation::powerStateResponse)

(defmethod robot_operation::powerStateRequest
  (:response () (instance robot_operation::powerStateResponse :init)))

(setf (get robot_operation::powerStateRequest :md5sum-) "e169ea722c6db37813a8d2b875c7d996")
(setf (get robot_operation::powerStateRequest :datatype-) "robot_operation/powerStateRequest")
(setf (get robot_operation::powerStateRequest :definition-)
      "bool platform
bool arm
---
bool finished
")

(setf (get robot_operation::powerStateResponse :md5sum-) "e169ea722c6db37813a8d2b875c7d996")
(setf (get robot_operation::powerStateResponse :datatype-) "robot_operation/powerStateResponse")
(setf (get robot_operation::powerStateResponse :definition-)
      "bool platform
bool arm
---
bool finished
")



(provide :robot_operation/powerState "e169ea722c6db37813a8d2b875c7d996")


