LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
       Main_MyClient.cpp \
        ../interface/IMyService.cpp \
		../interface/ICallBack.cpp \
		../service/CallBack.cpp \

LOCAL_SHARED_LIBRARIES := \
        libui libcutils libutils libbinder

LOCAL_C_INCLUDES := \
    frameworks/base/include \
    frameworks/native/include \
    $(VENDOR_SDK_INCLUDES)


LOCAL_MODULE:= my_binder_client
LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)
