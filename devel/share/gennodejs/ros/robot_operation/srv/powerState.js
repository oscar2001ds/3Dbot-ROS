// Auto-generated. Do not edit!

// (in-package robot_operation.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class powerStateRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.platform = null;
      this.arm = null;
    }
    else {
      if (initObj.hasOwnProperty('platform')) {
        this.platform = initObj.platform
      }
      else {
        this.platform = false;
      }
      if (initObj.hasOwnProperty('arm')) {
        this.arm = initObj.arm
      }
      else {
        this.arm = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type powerStateRequest
    // Serialize message field [platform]
    bufferOffset = _serializer.bool(obj.platform, buffer, bufferOffset);
    // Serialize message field [arm]
    bufferOffset = _serializer.bool(obj.arm, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type powerStateRequest
    let len;
    let data = new powerStateRequest(null);
    // Deserialize message field [platform]
    data.platform = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [arm]
    data.arm = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 2;
  }

  static datatype() {
    // Returns string type for a service object
    return 'robot_operation/powerStateRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9615bc8520f45afe11363618633070ec';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool platform
    bool arm
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new powerStateRequest(null);
    if (msg.platform !== undefined) {
      resolved.platform = msg.platform;
    }
    else {
      resolved.platform = false
    }

    if (msg.arm !== undefined) {
      resolved.arm = msg.arm;
    }
    else {
      resolved.arm = false
    }

    return resolved;
    }
};

class powerStateResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.finished = null;
    }
    else {
      if (initObj.hasOwnProperty('finished')) {
        this.finished = initObj.finished
      }
      else {
        this.finished = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type powerStateResponse
    // Serialize message field [finished]
    bufferOffset = _serializer.bool(obj.finished, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type powerStateResponse
    let len;
    let data = new powerStateResponse(null);
    // Deserialize message field [finished]
    data.finished = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'robot_operation/powerStateResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e2797c797e620a950ba704492d72873b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool finished
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new powerStateResponse(null);
    if (msg.finished !== undefined) {
      resolved.finished = msg.finished;
    }
    else {
      resolved.finished = false
    }

    return resolved;
    }
};

module.exports = {
  Request: powerStateRequest,
  Response: powerStateResponse,
  md5sum() { return 'e169ea722c6db37813a8d2b875c7d996'; },
  datatype() { return 'robot_operation/powerState'; }
};
