
(cl:in-package :asdf)

(defsystem "robot_operation-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "powerState" :depends-on ("_package_powerState"))
    (:file "_package_powerState" :depends-on ("_package"))
    (:file "temperature" :depends-on ("_package_temperature"))
    (:file "_package_temperature" :depends-on ("_package"))
  ))