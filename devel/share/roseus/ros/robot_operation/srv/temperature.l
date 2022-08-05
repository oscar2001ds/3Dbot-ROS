;; Auto-generated. Do not edit!


(when (boundp 'robot_operation::temperature)
  (if (not (find-package "ROBOT_OPERATION"))
    (make-package "ROBOT_OPERATION"))
  (shadow 'temperature (find-package "ROBOT_OPERATION")))
(unless (find-package "ROBOT_OPERATION::TEMPERATURE")
  (make-package "ROBOT_OPERATION::TEMPERATURE"))
(unless (find-package "ROBOT_OPERATION::TEMPERATUREREQUEST")
  (make-package "ROBOT_OPERATION::TEMPERATUREREQUEST"))
(unless (find-package "ROBOT_OPERATION::TEMPERATURERESPONSE")
  (make-package "ROBOT_OPERATION::TEMPERATURERESPONSE"))

(in-package "ROS")





(defclass robot_operation::temperatureRequest
  :super ros::object
  :slots (_temperature ))

(defmethod robot_operation::temperatureRequest
  (:init
   (&key
    ((:temperature __temperature) 0)
    )
   (send-super :init)
   (setq _temperature (round __temperature))
   self)
  (:temperature
   (&optional __temperature)
   (if __temperature (setq _temperature __temperature)) _temperature)
  (:serialization-length
   ()
   (+
    ;; int8 _temperature
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _temperature
       (write-byte _temperature s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _temperature
     (setq _temperature (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _temperature 127) (setq _temperature (- _temperature 256)))
   ;;
   self)
  )

(defclass robot_operation::temperatureResponse
  :super ros::object
  :slots ())

(defmethod robot_operation::temperatureResponse
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass robot_operation::temperature
  :super ros::object
  :slots ())

(setf (get robot_operation::temperature :md5sum-) "708df609bf4c0f5f446cfd5c1c3b552e")
(setf (get robot_operation::temperature :datatype-) "robot_operation/temperature")
(setf (get robot_operation::temperature :request) robot_operation::temperatureRequest)
(setf (get robot_operation::temperature :response) robot_operation::temperatureResponse)

(defmethod robot_operation::temperatureRequest
  (:response () (instance robot_operation::temperatureResponse :init)))

(setf (get robot_operation::temperatureRequest :md5sum-) "708df609bf4c0f5f446cfd5c1c3b552e")
(setf (get robot_operation::temperatureRequest :datatype-) "robot_operation/temperatureRequest")
(setf (get robot_operation::temperatureRequest :definition-)
      "int8 temperature
---
")

(setf (get robot_operation::temperatureResponse :md5sum-) "708df609bf4c0f5f446cfd5c1c3b552e")
(setf (get robot_operation::temperatureResponse :datatype-) "robot_operation/temperatureResponse")
(setf (get robot_operation::temperatureResponse :definition-)
      "int8 temperature
---
")



(provide :robot_operation/temperature "708df609bf4c0f5f446cfd5c1c3b552e")


