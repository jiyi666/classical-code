LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
        Main_MyService.cpp \
        MyService.cpp		\
        ../interface/IMyService.cpp

LOCAL_SHARED_LIBRARIES := \
		libui libcutils libutils libbinder

LOCAL_C_INCLUDES := \
    frameworks/base/include \
    frameworks/native/include/binder \
    $(VENDOR_SDK_INCLUDES) \


LOCAL_MODULE:= my_binder_service
LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)