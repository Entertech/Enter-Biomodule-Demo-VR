// "WaveVR SDK
// © 2017 HTC Corporation. All Rights Reserved.
//
// Unless otherwise required by copyright law and practice,
// upon the execution of HTC SDK license agreement,
// HTC grants you access to and use of the WaveVR SDK(s).
// You shall fully comply with all of HTC’s SDK license agreement terms and
// conditions signed by you and all SDK and API requirements,
// specifications, and documentation provided by HTC to You."


#ifndef wvr_render_h_
#define wvr_render_h_

#include "wvr_stdinc.h"
#include "wvr_types.h"
#include "begin_code.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef void* WVR_Texture_t;                                /**< **WVR_Texture_t**: type define the name of texture. */
typedef void* WVR_TextureQueueHandle_t;                     /**< **WVR_TextureQueueHandle_t**: type define the name of texture queue handler instance in runtime. */

/**
 * @brief Graphics API for render support.
 *
 * Texture type is only supported OpenGL currently.
 * There will be other types of graphics API in future release.
 */
typedef enum {
    WVR_GraphicsApiType_OpenGL                  = 1,        /**< **WVR_GraphicsApiType_OpenGL**: Specify OpenGL as graphics API during render runtime initializing. */
} WVR_GraphicsApiType;

/**
 * @brief Render runtime initialization configuration.
 *
 * Developer can determine whether render runtime use the additional method to improve the user experience after runtime initializing.
 * The render configuration is a 4 bytes bit mask which is able to combine with these methods.
 * This bit mask should be set to the member renderConfig of WVR_RenderInitParams_t.
 * As a necessary part of input parameter of interface WVR_RenderInit, the render configurations are passed to render runtime initializing stage.
 */
typedef enum {
    WVR_RenderConfig_Default                    = 0x0000,   /**< **WVR_RenderConfig_Default**: Set the render runtime without direct mode, MSAA, vertical sync, timewarp, and asynchronous time warp*/
    WVR_RenderConfig_Direct_Mode                = 0x0001,   /**< **WVR_RenderConfig_Direct_Mode**: Runtime uses direct mode when this config is asserted. The direct mode determine whether runtime controls over frame queue based on specific timing of vertical retrace occurring on display. This method helps to reduce latency and improve the visual experience. */
    WVR_RenderConfig_MSAA                       = 0x0002,   /**< **WVR_RenderConfig_MSAA**: Set config to enable MSAA effect to runtime. */
    WVR_RenderConfig_sRGB                       = 0x0004,   /**< **WVR_RenderConfig_sRGB**: Determine whether the color space is set as sRGB domain. */
    WVR_RenderConfig_Vertical_Sync              = 0x0010,   /**< **WVR_RenderConfig_Vertical_Sync**: Determine the runtime front/back buffer behavior whether buffers swap upon vertical retrace occurring on display. */
    WVR_RenderConfig_Timewarp                   = 0x0100,   /**< **WVR_RenderConfig_Timewarp**: The timewarp is also known as reprojection. This config determine that runtime choose to correct the rendered scene based on the head movement before updateing the result to display. This method help to reduce the judder. */
    WVR_RenderConfig_Timewarp_Asynchronous      = 0x0300    /**< **WVR_RenderConfig_Timewarp_Asynchronous**: This config determine whether runtime uses the Asynchronous time warp method. Asynchrounous timewarp is held parallelly with scene rendering. Runtime determines to use the generated timewarped frame when the frame rate drops. This method helps to reduce latency. */
} WVR_RenderConfig;

/**
 * @brief Error for render runtime initialization.
 *
 * The return value for the initializing interface WVR_RenderInit.
 */
typedef enum {
    WVR_RenderError_None                        = 0,        /**< **WVR_RenderError_None**: No error. */
    WVR_RenderError_RuntimeInitFailed           = 410,      /**< **WVR_RenderError_RuntimeInitFailed**: The dependent component is failed to block render runtime initializing go on.*/
    WVR_RenderError_ContextSetupFailed          = 411,      /**< **WVR_RenderError_ContextSetupFailed**: The necessary context for runtime is failed to accomplish.*/
    WVR_RenderError_DisplaySetupFailed          = 412,      /**< **WVR_RenderError_DisplaySetupFailed**: The display configuration for display is failed to set up. */
    WVR_RenderError_LibNotSupported             = 413,      /**< **WVR_RenderError_LibNotSupported**: The provided graphics api type is not supported by runtime. */
    WVR_RenderError_NullPtr                     = 414,      /**< **WVR_RenderError_NullPtr**: Not passing Null check. */
    WVR_RenderError_Max                         = 65535,    /**< **WVR_RenderError_Max**: Maxium value to reserve bit word among compilers . */
} WVR_RenderError;

/**
 * @brief Extend the add-on functionality for WVR_SubmitFrame.
 *
 * WVR_SubmitFrame need this flag to specify invoking path.
 * Currently, the default funcationality is available for the runtime submit texture target process.
 */
typedef enum {
    WVR_SubmitExtend_Default = 0x00,                        /**< **WVR_SubmitExtend_Default**: The default process to submit texture to display. */
} WVR_SubmitExtend;

/**
 * @brief The return type of API WVR_SubmitFrame
 *
 * Enumerate the error type of submitting frame.
 */
typedef enum {
    WVR_SubmitError_None                        = 0,        /**< **WVR_SubmitError_None**: No error */
    WVR_SubmitError_InvalidTexture              = 400,      /**< **WVR_SubmitError_InvalidTexture**: The submitted texture is invalid. Make sure texture is correct and not in use.*/
    WVR_SubmitError_ThreadStop                  = 401,      /**< **WVR_SubmitError_ThreadStop**: The submitted thread stops in the runtime. */
    WVR_SubmitError_BufferSubmitFailed          = 402,      /**< **WVR_SubmitError_BufferSubmitFailed**: The submitted buffer encounters error  in the runtime. */
    WVR_SubmitError_Max                         = 65535,    /**< **WVR_SubmitError_Max**: Maxium value to reserve bit word among compilers . */
} WVR_SubmitError;

/**
 * @brief Target texture
 *
 * Enumerate the specific target texture to generate texture.
 */
typedef enum {
    WVR_TextureTarget_2D,                                    /**< **WVR_TextureTarget_2D**: Correspond to OpenGL target texture GL_TEXTURE_2D*/
    WVR_TextureTarget_2D_ARRAY,                             /**< **WVR_TextureTarget_2D_ARRAY**: Correspond to OpenGL target texture GL_TEXTURE_2D_ARRAY*/
} WVR_TextureTarget;

/**
 * @brief Texture format
 *
 * Enumerate the specific texture format to generate texture.
 */
typedef enum {
    WVR_TextureFormat_RGBA                                  /**< **WVR_TextureFormat_RGBA**: Correspond to OpenGL format of the pixel data GL_RGBA*/
} WVR_TextureFormat;

/**
 * @brief Texture type
 *
 * Enumerate the specific texture type to generate texture.
 */
typedef enum {
    WVR_TextureType_UnsignedByte                            /**< **WVR_TextureType_UnsignedByte**: Correspond to OpenGL data type of the pixel data GL_UNSIGNED_BYTE*/
} WVR_TextureType;

/**
 * @brief Screenshot mode
 *
 * Enumerate screenshot mode to select stereo scene or single eye image.
 */
typedef enum {
    WVR_ScreenshotMode_Default,                             /**< **WVR_ScreenshotMode_Default**: Screenshot image is stereo. Just as what is shown on screen*/
    WVR_ScreenshotMode_Raw,                                 /**< **WVR_ScreenshotMode_Raw**: Screenshot image has only single eye, and without distortion correction*/
    WVR_ScreenshotMode_Distorted,                           /**< **WVR_ScreenshotMode_Distorted**: Screenshot image has only single eye, and with distortion correction*/
} WVR_ScreenshotMode;

/**
 * @brief Render initialization parameters
 *
 * Aggregate necessary information to initialize the render runtime.
 */
typedef struct WVR_RenderInitParams {
    WVR_GraphicsApiType graphicsApi;                        /**< Select the supported graphics api library, currently, only support OpenGL.*/
    uint64_t renderConfig;                             /**< 4 bytes bit mask to choose combination of render initializing configuration. The corresponding enumeration is defined in WVR_RenderConfig*/
} WVR_RenderInitParams_t;

/**
 * @brief Render properties
 *
 * Aggregate the propertie values from runtime via API WVR_GetRenderProps.
 */
typedef struct WVR_RenderProps {
    float refreshRate;                                      /**< The refresh rate is the number of frame shown in a second.*/
    bool hasExternal;                                       /**< To probe whether the present display is an external device.*/
    float ipdMeter;                                         /**< The presumed interpupillary distance of HMD user, measured in meters.*/
} WVR_RenderProps_t;

/**
 * @brief Texture parameters
 *
 * Aggregate the texture related information which needs to be updated to runtime.
 * The texture parameters can be obtained via WVR_GetTexture or assigned a valid texture directly.
 * The WVR_SubmitFrame need this struct as an argument to pass current texture identiy to runtime.
 */
typedef struct WVR_TextureParams {
    WVR_Texture_t id;                                       /**< Correspond to the name of texture to identify texture entity in graphics library such as OpenGL. */
} WVR_TextureParams_t;

/**
 * @brief Aggregate the function pointers to support the callbacks of runtime.
 *
 * Runtime maintains a stereo renderer mode to handle the customized callback at the specific moment.
 * Native application developer implements all the callbacks and delegates the invoking timing to runtime.
 * The optimized algorithm improves the stereoscopic experience in render runtime with single buffer method.
 *
 */
typedef struct WVR_StereoRenderer {
    /**
     * @brief To initialize graphics library.
     *
     * Developer can enable server-side capabilities such as doing depth comparisons and update the depth buffer,
     * specifying the value used for depth buffer comparisons, or specifying whether depth buffer is enabled for writing.
     * Based on developer's requirement, to set up the scene objects, frame buffer for stereo render targets, or render models.
     *
     * @retval true succeed to initialize graphics library.
     * @retval false fail to initialize graphics library.
     */
    bool (*graphics_init)();
    /**
     * @brief Called when a new frame is about to be drawn.
     *
     * Any per-frame operations not specific to a single view should happen here.
     *
     * @retval true succeed to invoke this function.
     * @retval false fail to invoke this function.
     */
    bool (*pre_draw_frame)();
    /**
     * @brief Requests to draw the contents from the point of view of an eye.
     *
     * Implementor should draw the frame buffer corresponding to the different eye.
     * In order to submit the content of view as texture to runtime, binding the framebuffer, rendering the scene,
     * packing the texture id as the argument of @ref WVR_SubmitFrame.
     *
     * @param eye WVR_Eye, eye id.
     */
    void (*draw_eye)(WVR_Eye eye);
    /**
     * @brief Called before a frame is finished.
     *
     * By the time of this call, the frame contents have been already drawn.
     * Any rendering in this step is relative to the full surface, not to any single eye view,
     * such as polling the pose of devices.
     *
     */
    void (*post_draw_frame)();
} WVR_StereoRenderer_t;

/**
* @brief The interface to initiate the render runtime.
*
* Render runtime is in charge of pre-processing the rendered scene before updating to display.
* To initiate render runtime, this interface is recommended to be invoked before the following interfaces in some platforms,
* such as @ref WVR_RenderMask, @ref WVR_SubmitFrame, @ref WVR_ObtainTextureQueue, @ref WVR_GetTextureQueueLength, @ref WVR_GetAvailableTextureIndex,
* @ref WVR_GetAvailableTextureIndex, @ref WVR_GetAvailableTextureIndex, @ref WVR_GetTexture, @ref WVR_ReleaseTextureQueue,
* @ref WVR_RequestScreenshot, @ref WVR_StartRenderer, @ref WVR_IsRendererRendering, and @ref WVR_GetSyncPose.
*
* Instead of default configuration and selecting OpenGL graphics API, the first shot of WVR_RenderInit invocation can provide
* the customized initiating configuration and selecting supported graphics library via the argument @ref WVR_RenderInitParams_t.
* Based on the return type WVR_RenderError, the status of render runtime initialization can be determined.
*
* @param param pointer of struct `WVR_RenderInitParams_t`, to aggregate necessary information to initialize the render runtime.
* @return WVR_RenderError, this return type enumerates all the possible error status for this interface.
* @version API Level 1
*/
extern WVR_EXPORT WVR_RenderError WVR_RenderInit(const WVR_RenderInitParams_t* param);

/**
* @brief Requests the properties from render runtime.
*
* The interface fetch necessary properties from render runtime.
* The output argument WVR_RenderProps_t* carries the frame rate and the existing status of the external display.
* The corresponding member value can be access via dereferencing the interface parameter referring to @ref WVR_RenderProps_t.
* Return value is the validness of properties. If it is not true, it means the fetched value is not available.
* Please note that some platforms return false rather than fetching render properties.
*
* @param props pointer of struct WVR_RenderProps_t, to aggregate the properties fetched from render runtime.
* @retval true Success to get the render properties.
* @retval false Fail to get the render properties, the fetched properties value is invalid.
* @version API Level 1
*/
extern WVR_EXPORT bool WVR_GetRenderProps(WVR_RenderProps_t* props);

/**
* @brief Renders a mask to cover the pixels that will be hidden after distortion.
*
* The mask will be drawn into the depth buffer setting near clipping distance in the z-direction.
* This will improve performance by letting the GPU early-reject pixels the user
* will never see.
* Called before rendering the scene texture of each eye.
*
* @param eye WVR_Eye, eye id to specify the side of scene.
* @version API Level 1
*/
extern WVR_EXPORT void WVR_RenderMask(WVR_Eye eye);

/**
* @brief Updated scene texture to display.
*
* The scene is rendered by developer with both sides of eye.
* The scene content is in form of index or pointer corresponding to supported graphics API, such as texture name in OpenGL.
* Developer must respectively submit right and left scene at least one time to signal the runtime to process.
* The WVR_TextureParams_t contains the texture which specifies the current scene. This scene is already rendered beforehand.
* This texture is verified its validness in advance of updating it to display.
*
* The third parameter is optional. This is the referenced pose of HMD.
* A much more accurate polling pose approximating the moment that scene is rendered, provides much more stabilized performance of rendering.
* The fourth is a flag to specify the internal invoking path.
* The default process of handing scene fulfills all the basic requirement of updating scene to display.
* Add-on functionalities will be appended in the future.
*
* @param eye WVR_Eye, eye id to specify the side of scene.
* @param param pointer to struct WVR_TextureParams_t, to aggregate the name of scene texture.
* @param pose pointer to struct WVR_PoseState_t, an optional referenced pose to reduce judder of rendering.
* @param extendMethod enum WVR_SubmitExtend, flag to specify invoking path.
* @return WVR_SubmitError, the error status of interface WVR_SubmitFrame, the possible status can refer to @ref WVR_RenderError.
* @version API Level 1
*/
extern WVR_EXPORT WVR_SubmitError WVR_SubmitFrame(WVR_Eye eye, const WVR_TextureParams_t *param, const WVR_PoseState_t* pose = NULL, WVR_SubmitExtend extendMethod = WVR_SubmitExtend_Default);

/**
* @brief Obtain a new texture queue.
*
* Several texture queue related methods are provided for maintaining textures.
* Call @ref WVR_ReleaseTextureQueue to release the queue when the queue is no longer used.
*
* @param target Specifies the target texture. Must be WVR_TextureTarget_2D or WVR_TextureTarget_2D_ARRAY.
* @param format Specifies the number of color components in the texture. Must be WVR_TextureFormat_RGBA.
* @param type Specifies the data type of the pixel data. The following symbolic values are accepted: WVR_TextureType_UnsignedByte.
* @param width Specifies the width of the texture image.
* @param height Specifies the height of the texture image.
* @param level Specifies the level-of-detail number.
* @return The handle of the queue @ref WVR_TextureQueueHandle_t.
* @version API Level 1
*/
extern WVR_EXPORT WVR_TextureQueueHandle_t WVR_ObtainTextureQueue(WVR_TextureTarget target, WVR_TextureFormat format, WVR_TextureType type, uint32_t width, uint32_t height, int32_t level);

/**
* @brief Get the length of a texture queue.
* @param handle The texture queue handle returned by @ref WVR_ObtainTextureQueue
* @return The length of the queue.
* @version API Level 1
*/
extern WVR_EXPORT uint32_t WVR_GetTextureQueueLength(WVR_TextureQueueHandle_t handle);

/**
* @brief Get the index of an available texture.
*
* Before drawing, applications should call this function to get the index of an available
* texture and call @ref WVR_GetTexture to get the real texture ID.
*
* @param handle The texture queue handle returned by @ref WVR_ObtainTextureQueue
* @return The ID of the texture. -1 means no available texture currently or invalid handle.
* @version API Level 1
*/
extern WVR_EXPORT int32_t WVR_GetAvailableTextureIndex(WVR_TextureQueueHandle_t handle);

/**
* @brief Get texture of given index in the given texture queue.
*
* Use the index returned from @ref WVR_GetAvailableTextureIndex.
* The available index can specify the available texture in texture queue maintained in runtime.
*
* @param handle The texture queue handle returned by @ref WVR_ObtainTextureQueue
* @param index The index of the texture in the queue.
* @return The struct WVR_TextureParams_t. aggregate the name of texture as a member inside the struct.
* @version API Level 1
*/
extern WVR_EXPORT WVR_TextureParams_t WVR_GetTexture(WVR_TextureQueueHandle_t handle, int32_t index);

/**
* @brief Release a texture queue.
* @param handle The handle of the texture queue to be released.
* @version API Level 1
*/
extern WVR_EXPORT void WVR_ReleaseTextureQueue(WVR_TextureQueueHandle_t handle);

/**
* @brief Request a screenshot of requested mode.
* @param width Specifies the width of the texture image.
* @param height Specifies the height of the texture image.
* @param mode Specifies requested screenshot mode. The values should be one of @ref WVR_ScreenshotMode.
* @param filename Specifies preferred saving filename. (optional)
* @retval true Succeed to request screenshot.
* @retval false Fail to request screenshot.
* @version API Level 1
*/
extern WVR_EXPORT bool WVR_RequestScreenshot(uint32_t width, uint32_t height, WVR_ScreenshotMode mode = WVR_ScreenshotMode_Default, const char* filename = NULL);

/**
* @brief Send the callback function set to runtime.
*
* Runtime needs the callback function implemented by developer.
* Runtime hooks the member functions pointer of @ref WVR_StereoRenderer_t with function set from external.
* This functions also trigger runtime to achieve the algorithm of direct mode method.
*
* @param renderer pointer to struct WVR_StereoRenderer, aggregate the function pointers to support the callback of runtime.
* @version API Level 1
*/
extern WVR_EXPORT void WVR_StartRenderer(WVR_StereoRenderer_t* renderer);

/**
* @brief Check whether the direct mode is still working.
*
* Runtime will clear the callback set when it is going to terminate the invoking delegation.
* Check existence of callback function set in runtime. If the renderer is null then return false. If on the contrary then returning true.
* This function is used to handle the life cycle of the native activity in the main loop. The render thread is held in runtime.
* Activity can proceed to terminating state when the render thread is going to put an end to the process.
*
* @retval true callback set is still presence in runtime.
* @retval false callback set is no longer existing in runtime.
* @version API Level 1
*/
extern WVR_EXPORT bool WVR_IsRendererRendering();


#ifdef __cplusplus
} /* extern "C" */
#endif
#include "close_code.h"

#endif /* wvr_render_h_ */

