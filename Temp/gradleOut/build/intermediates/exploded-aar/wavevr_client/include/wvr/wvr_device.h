// "WaveVR SDK
// © 2017 HTC Corporation. All Rights Reserved.
//
// Unless otherwise required by copyright law and practice,
// upon the execution of HTC SDK license agreement,
// HTC grants you access to and use of the WaveVR SDK(s).
// You shall fully comply with all of HTC’s SDK license agreement terms and
// conditions signed by you and all SDK and API requirements,
// specifications, and documentation provided by HTC to You."


#ifndef wvr_device_h_
#define wvr_device_h_

#include "wvr_stdinc.h"
#include "wvr_types.h"

#include "begin_code.h"
#ifdef __cplusplus
extern "C" {
#endif

static const uint32_t WVR_DEVICE_COUNT_LEVEL_0 = 1;    /**< Get HMD */
static const uint32_t WVR_DEVICE_COUNT_LEVEL_1 = 3;    /**< Get HMD and 2 controllers */
static const uint32_t WVR_DEVICE_COUNT_LEVEL_2 = 16;   /**< Get HMD, 2 controllers, and other miscellaneous tracking devices */
static const uint32_t WVR_DEVICE_HMD = 0;              /**< Specify device HMD */

/**
 * @brief input type for input id
 */
typedef enum {
    WVR_InputType_Button = 1<<0,    /**< Button input type */
    WVR_InputType_Touch  = 1<<1,    /**< Touch input type */
    WVR_InputType_Analog = 1<<2,    /**< Analog input type */
} WVR_InputType;

/**
 * @brief analog type
 */
typedef enum {
    WVR_AnalogType_None     = 0,
    WVR_AnalogType_TouchPad = 1,    /**< Provide analog data with x and y coordinate*/
    WVR_AnalogType_Trigger  = 2,    /**< Provide analog data with x coordinate*/
} WVR_AnalogType;

/**
 * @brief intensity of vibrator
 */
typedef enum {
    WVR_Intensity_Weak       = 1,   /**< The Intensity of vibrate is Weak. */
    WVR_Intensity_Light      = 2,   /**< The Intensity of vibrate is Light. */
    WVR_Intensity_Normal     = 3,   /**< The Intensity of vibrate is Normal. */
    WVR_Intensity_Strong     = 4,   /**< The Intensity of vibrate is Strong. */
    WVR_Intensity_Severe     = 5,   /**< The Intensity of vibrate is Severe. */
} WVR_Intensity;

/**
 * @brief analog data
 */
typedef struct WVR_Axis {
    float x;  /**< The interval of analog values on coordinates x is -1<x<1. */
    float y;  /**< The interval of analog values on coordinates y is -1<y<1. */
} WVR_Axis_t;

/**
 * @brief analog state structure
 */
typedef struct WVR_AnalogState {
    WVR_InputId     id; /**< indicate the analog state belongs to which WVR_InputId */
    WVR_AnalogType  type; /**< indicate the analog data's type */
    WVR_Axis_t      axis; /**< @ref WVR_Axis, include analog data */
} WVR_AnalogState_t;

/**
 * @brief The status of battery capacity.
 */
typedef enum {
    WVR_BatteryStatus_Unknown  = 0, /**< an error code if device service cannot get the status of the battery. */
    WVR_BatteryStatus_Normal   = 1, /**< battery capacity is normal. */
    WVR_BatteryStatus_Low      = 2, /**< warning, batter capacity is low. */
    WVR_BatteryStatus_UltraLow = 3, /**< battery capacity is too low. */
} WVR_BatteryStatus;

/**
 * @brief The status of battery temperature.
 */
typedef enum {
    WVR_BatteryTemperatureStatus_Unknown       = 0, /**< an error code if device service cannot get the temperature status of the battery. */
    WVR_BatteryTemperatureStatus_Normal        = 1, /**< battery temperature is normal. */
    WVR_BatteryTemperatureStatus_Overheat      = 2, /**< warning, battery temperature is high. */
    WVR_BatteryTemperatureStatus_UltraOverheat = 3, /**< battery temperature is too high. */
} WVR_BatteryTemperatureStatus;

/**
 * @brief The charging status.
 */
typedef enum {
    WVR_ChargeStatus_Unknown     = 0, /**< an error code if device service cannot get the charging status of battery in use. */
    WVR_ChargeStatus_Discharging = 1, /**< device doesn't charge currently. */
    WVR_ChargeStatus_Charging    = 2, /**< device is charging. */
    WVR_ChargeStatus_Full        = 3, /**< battery capacity of device is full. */
} WVR_ChargeStatus;

/**
 * @brief Recenter effect of WVR_InAppRecenter
 */
typedef enum {
    WVR_RecenterType_Disabled   = 0,  /**< Make everything back to system coordinate instantly */
    WVR_RecenterType_YawOnly = 1, /**< Only adjust the Yaw angle */
    WVR_RecenterType_YawAndPosition = 2, /**< Adjust the Yaw angle, and also reset user's position to Virtual World's center */
    WVR_RecenterType_RotationAndPosition = 3, /**< Affect all the XYZ and Pitch Yaw Roll. It is sensitive to user's head gesture at recentering. */
} WVR_RecenterType;

/**
 * @brief Developer can know if WVR_DeviceType is connected
 *
 * @param type which indicate @ref WVR_DeviceType.
 * @return false if is disconnected, true is connected.
 * @version API Level 1
 */
extern WVR_EXPORT bool WVR_IsDeviceConnected(WVR_DeviceType type);

/**
 * @brief Developer can know if WVR_DeviceType is suspend, note only for HMD
 *
 * @param type which indicate @ref WVR_DeviceType.
 * @return true if in suspend status, otherwise return false.
 * @version API Level 1
 */
extern WVR_EXPORT bool WVR_IsDeviceSuspend(WVR_DeviceType type);

/**
 * @brief Function to get Input Device Capability for WVR_InputType
 *
 * @param type which indicate what device to get the capability. (refer to @ref WVR_DeviceType)
 * @param inputType , one of @ref WVR_InputType.
 * @return int32_t, bitmask for WVR_InputType, -1 for error occurs
 * @version API Level 1
*/
extern WVR_EXPORT int32_t WVR_GetInputDeviceCapability(WVR_DeviceType type, WVR_InputType inputType);

/**
 * @brief Function to get InputConfig for WVR_InputType
 *
 * @param type which indicates what device to get the count. (refer to @ref WVR_DeviceType)
 * @param inputType, one of @ref WVR_InputType
 * @return int32_t, count for each WVR_InputType, -1 for error occurs
 * @version API Level 1
*/
extern WVR_EXPORT int32_t WVR_GetInputTypeCount(WVR_DeviceType type, WVR_InputType inputType);

/**
 * @brief Function to get WVR_InputType data, inputType is a bitmask to represent the combination input type for WVR_InputType.
 *
 * @param type which indicates what device to get the InputDeviceState. (refer to @ref WVR_DeviceType)
 * @param inputType , a bitmask to represent the combination input type for @ref WVR_InputType, developer can get singlton or combination input status.
 * @param buttons, a bitmask to represent the button state, each bit is corresponding to HVT_InputId.
 * @param touches, a bitmast to represent the touches state, each bit is corresponding to HVT_InputId.
 * @param analogArray, an array of  WVR_AnalogState_t to represent all analog data. (refer to @ref WVR_AnalogState)
 * @param analoyAarrayCount, Developer should the the array count from the WVR_GetInputTypeCount API.
 * @return false on failure
 * @version API Level 1
*/
extern WVR_EXPORT bool WVR_GetInputDeviceState(WVR_DeviceType type, uint32_t inputType, uint32_t* buttons, uint32_t* touches,
                                                   WVR_AnalogState_t* analogArray, uint32_t analogArrayCount);

/**
 * @brief Function to get button state of specific input id
 *
 * @param type which indicates what device type. (refer to @ref WVR_DeviceType)
 * @param id, one of @ref WVR_InputId, indicate which button
 * @return bool, true for pressed and false is unpressed
 * @version API Level 1
*/
extern WVR_EXPORT bool WVR_GetInputButtonState(WVR_DeviceType type, WVR_InputId id);

/**
 * @brief Function to get touch state of specific input id
 *
 * @param type which indicates what device type. (refer to @ref WVR_DeviceType)
 * @param id, one of @ref WVR_InputId, indicate which touch
 * @return bool, true for touched and false is untouched
 * @version API Level 1
*/
extern WVR_EXPORT bool WVR_GetInputTouchState(WVR_DeviceType type, WVR_InputId id);

/**
 * @brief Function to get analog data of specific input id
 *
 * @param type which indicates what device type. (refer to @ref WVR_DeviceType)
 * @param id, one of @ref WVR_InputId, indicate which touch
 * @return WVR_Axis_t, analog data for @ref WVR_InputType. (refer to @ref WVR_Axis)
 * @version API Level 1
*/
extern WVR_EXPORT WVR_Axis_t WVR_GetInputAnalogAxis(WVR_DeviceType type, WVR_InputId id);

/**
 * @brief Function to get VR device pose w/wo prediction
 *
 * The pose that the tracker thinks that the HMD will be in at the specified number of seconds into the
 * future. Pass 0 to get the state at the instant the method is called. Most of the time the application should
 * calculate the time until the photons will be emitted from the display and pass that time into the method.
 *
 * For devices where isValidPose is true the application can use the pose to position the device
 * in question.
 *
 * Seated experiences should call this method with **WVR_PoseOriginModel_OriginOnHead** and receive poses relative
 * to the seated zero pose. Standing experiences should call this method with **WVR_PoseOriginModel_OriginOnGround**
 * and receive poses relative to the Arena Play Area. **WVR_PoseOriginModel_OriginOnTrackingObserver** should
 * probably not be used unless the application is the Arena calibration tool itself, but will provide
 * poses relative to the hardware-specific coordinate system in the driver.
 *
 * @param type Type of the device to get the InputDeviceState. (refer to @ref WVR_DeviceType)
 * @param originModel Tracking universe that returned poses should be relative to.  (refer to @ref WVR_PoseOriginModel)
 * @param predictedMilliSec Number of milliseconds from now to predict poses for. Positive numbers are in the future.
 * Pass 0 to get the state at the instant the function is called.
 * @param poseState to obtain pose data (refer to @ref WVR_PoseState) of tracked device by @ref WVR_DeviceType.
 * @version API Level 1
*/
extern WVR_EXPORT void WVR_GetPoseState(WVR_DeviceType type, WVR_PoseOriginModel originModel, uint32_t predictedMilliSec, WVR_PoseState_t *poseState);

/**
 * @brief Returns poses to usage for rendering scene.
 *
 * This function gets the poses from runtime for the usage of rendering scene at the specific moment based on the pose origin model.
 * The one-time configuring the tracking universe assumes one kind of origin pose models unless the model setting is not changed.
 * The description of tracking universe can refer to the argument originModel of @ref WVR_GetPoseState.
 *
 * The poses and device type are aggregated together as struct WVR_DevicePosePair_t.
 * The struct pointers of all tracked devices compose a specific size array to keep track of the locomotions of the devices.
 * The specific array size can be substituted with three levels of device count.
 * **WVR_DEVICE_COUNT_LEVEL_0** is only assumed to get HMD device.
 * **WVR_DEVICE_COUNT_LEVEL_1** is assumed that the HMD and two controllers are tracked.
 * **WVR_DEVICE_COUNT_LEVEL_2** should track the number of devices up to 16, including HMD, 2 controllers, and other miscellaneous tracking devices.
 *
 * WVR_GetSyncPose function polls pose once within Vsync cycle time periodically to make scene display more smooth.
 * For this reason, this interface will blocking(non-busy waiting) and return poses based on last Vsync elapsed time.
 *
 * To reduce the judder, the moment of getting poses should approximate the moment update the new scene on display.
 * WVR_GetSyncPose also make short time prediction of poses according to different render methods such as ATW and direct mode.
 *
 * @param originModel enum @ref WVR_PoseOriginModel, specify the tracking universe of origin pose model.
 * @param pairArray struct pointer WVR_DevicePosePair_t (refer to @ref WVR_DevicePosePair), aggregation array to keep pose information and tracked device type.
 * @param pairArrayCount uint32_t, specify the size of WVR_DevicePosePair_t array. The three levels of device count are optional.
 * @version API Level 1
*/
extern WVR_EXPORT void WVR_GetSyncPose(WVR_PoseOriginModel originModel, WVR_DevicePosePair_t * pairArray, uint32_t pairArrayCount);


/**
 * @brief Function to trigger vibrator.
 *
 * @param type which indicate what device type (refer to @ref WVR_DeviceType)
 * @param id indicates the @ref WVR_InputId to trigger a vibrator on.
 * @param durationMicroSec The duration when vibrator works, default value is 65535 microsecond, max value is 65535
 * @param intensity The intensity when vibrator works, default value is WVR_Intensity_Normal
 * @version API Level 1
 * @note Parameter intensity is only effective with Runtime version 2 or higher.
*/
extern WVR_EXPORT void WVR_TriggerVibrator(WVR_DeviceType type, WVR_InputId id = WVR_InputId_Max, unsigned short durationMicroSec = 65535,
                                           WVR_Intensity intensity = WVR_Intensity_Normal);

/**
 * @brief Function to recenter tracker coordinate system to the current rotation and/or position of the App "Virtual World".
 *
 * Sets the zero pose for current tracker coordinate system to the current position and rotation of the Virtual World. After
 * @ref WVR_InAppRecenter all @ref WVR_GetSyncPose and @ref WVR_GetPoseState calls that pass @ref WVR_PoseOriginModel
 * as the origin model will be relative to this new zero pose. Take effects until HMD take-off or App switched.
 * @param recenterType indicates type of recenter in @ref WVR_RecenterType
 * @version API Level 2
*/
extern WVR_EXPORT void WVR_InAppRecenter(WVR_RecenterType recenterType);

/**
 * @brief Function to transform between rotation Matrix and Quaternion
 *
 * Convenience utility to apply the specified transform between rotation Matrix and Quaternion.
 *
 * @param mat input rotation matrix. (refer to @ref WVR_Matrix4f)
 * @param quat input Quaternion. (refer to @ref WVR_Quatf)
 * @param m2q true to convert matrix to Quaternion, false to do opposite.
 * @version API Level 1
*/
extern WVR_EXPORT void WVR_ConvertMatrixQuaternion(WVR_Matrix4f_t *mat, WVR_Quatf_t *quat, bool m2q);

/**
 * @brief Function to set a parameter string to device service.
 *
 * @param type which indicate @ref WVR_DeviceType.
 * @param pchValue set string to let AP communicate to device service.
 * @version API Level 1
*/
extern WVR_EXPORT void WVR_SetParameters(WVR_DeviceType type, const char *pchValue);

/**
 * @brief Function to get a parameter string from device service.
 *
 * @param type which indicate @ref WVR_DeviceType.
 * @param pchValue send string to let AP communicate to device service.
 * @param retValue The buffer to store parameter get from device service. unBufferSize should be the size of this buffer.
 * @param unBufferSize The size of the buffer pointed to by pchValue.
 * @return The number of bytes necessary to hold the string, including the trailing null. Returns 0 (and 0-length string) on failure.
 * @version API Level 1
*/
extern WVR_EXPORT uint32_t WVR_GetParameters(WVR_DeviceType type, const char *pchValue, char *retValue, uint32_t unBufferSize);

/**
 * @brief Function to get the Degree of Freedom (DoF) of device's pose.
 *
 * @param type which indicate @ref WVR_DeviceType.
 * @return WVR_NumDoF_3DoF means the device provides 3 DoF pose (only rotation), WVR_NumDoF_6DoF means the device provides 6 DoF pose (rotation and position). (refer to @ref WVR_NumDoF)
 * @version API Level 1
*/
extern WVR_EXPORT WVR_NumDoF WVR_GetDegreeOfFreedom(WVR_DeviceType type);

/**
 * @brief Function to get the default controller role which will determine the role while the first controller connects.
 * While the controller role is changed, server will send an event of WVR_EventType_DeviceRoleChanged to notify all of applications.
 * At this moment, applications have to check the controller roles again with this API(WVR_GetDefaultControllerRole).
 *
 * @return The type of controller role, it will be WVRDeviceType_Controller_Right or WVRDeviceType_Controller_Left. (refer to @ref WVR_DeviceType)
 * @version API Level 1
*/
extern WVR_EXPORT WVR_DeviceType WVR_GetDefaultControllerRole();

/**
 * @brief Get current battery capacity of specified device with percentage.
 * @param type Type of the device to get the InputDeviceState. (refer to @ref WVR_DeviceType)
 * @return The percentage of battery of specified device.
 * @version API Level 1
 */
extern WVR_EXPORT float WVR_GetDeviceBatteryPercentage( WVR_DeviceType type );

/**
 * @brief Get the current status of battery capacity.
 * @param type Type of the device to get the InputDeviceState. (refer to @ref WVR_DeviceType)
 * @return The status of battery capacity. Return WVR_BatteryStatus_Unknown if device service cannot get the battery status. (refer to @ref WVR_BatteryStatus)
 * @version API Level 1
 */
extern WVR_EXPORT WVR_BatteryStatus WVR_GetBatteryStatus( WVR_DeviceType type );

/**
 * @brief Get the current charging status.
 * @param type Type of the device to get the InputDeviceState. (refer to @ref WVR_DeviceType)
 * @return The charging status. Return WVR_ChargeStatus_Unknown if device service cannot get the charging status. (refer to @ref WVR_ChargeStatus)
 * @version API Level 1
 */
extern WVR_EXPORT WVR_ChargeStatus WVR_GetChargeStatus( WVR_DeviceType type );

/**
 * @brief Get the current status of temperature of battery.
 * @param type : Type of the device to get the InputDeviceState. (refer to @ref WVR_DeviceType)
 * @return The Status of temperature of battery. Return WVR_BatteryTemperatureStatus_Unknown if device service cannot get the temperature status of battery in use. (refer to @ref WVR_BatteryTemperatureStatus)
 * @version API Level 1
 */
extern WVR_EXPORT WVR_BatteryTemperatureStatus WVR_GetBatteryTemperatureStatus( WVR_DeviceType type );

/**
 * @brief Get the current temperature of battery.
 * @param type Type of the device to get the InputDeviceState. (refer to @ref WVR_DeviceType)
 * @return The temperature of battery.
 *          -1 means not support or failure.
 * @version API Level 1
 */
extern WVR_EXPORT float WVR_GetBatteryTemperature( WVR_DeviceType type );

/**
 * @brief Function to set the interaction mode of application.
 *
 * @param mode which indicates @ref WVR_InteractionMode, @ref WVR_InteractionMode_SystemDefault means to reset @ref WVR_InteractionMode and @ref WVR_GazeTriggerType to system default values.
 * @return bool, true for setting successfully.
 * @version API Level 2
 * @note Effective with Runtime version 2 or higher
 */
extern WVR_EXPORT bool WVR_SetInteractionMode(WVR_InteractionMode mode);

/**
 * @brief Function to get the interaction mode of application.
 *
 * @return @ref WVR_InteractionMode, the interaction mode of application.
 * @version API Level 2
 * @note Effective with Runtime version 2 or higher
 */
extern WVR_EXPORT WVR_InteractionMode WVR_GetInteractionMode();

/**
 * @brief Function to set the trigger type of gaze of application.
 *
 * @param type which indicate @ref WVR_GazeTriggerType.
 * @return bool, true for setting successfully.
 * @version API Level 2
 * @note Effective with Runtime version 2 or higher
 */
extern WVR_EXPORT bool WVR_SetGazeTriggerType(WVR_GazeTriggerType type);

/**
 * @brief Function to get the trigger type of gaze of application.
 *
 * @return @ref WVR_GazeTriggerType, the trigger type of gaze of application.
 * @version API Level 2
 * @note Effective with Runtime version 2 or higher
 */
extern WVR_EXPORT WVR_GazeTriggerType WVR_GetGazeTriggerType();

/**
 * @brief Function to get the current states of device errors from the specific device.
 *
 * @param type Type of the device to get the InputDeviceState.
 * @return WVR_DeviceErrorStatus, the bitmask records all of current states of device errors which has occurred on the specific device.
 * @version API Level 2
 * @note Effective with Runtime version 2 or higher
 */
extern WVR_EXPORT WVR_DeviceErrorStatus WVR_GetDeviceErrorStatus( WVR_DeviceType type );

/**
 * @brief Function to enables or disables use of the neck model for 3-DOF head tracking.
 *
 * @param true to enable neck model for 3-DOF head tracking, false to disable.
 * @version API Level 2
 * @note Effective with Runtime version 2 or higher
 */
extern WVR_EXPORT void WVR_SetNeckModelEnabled(bool enabled);

#ifdef __cplusplus
}
#endif
#include "close_code.h"

#endif /* wvr_device_h_ */
