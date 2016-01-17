LOCAL_PATH := $(call my-dir)

#prebuilt scrypto module
include $(CLEAR_VARS)
LOCAL_MODULE := scrypto_static
LOCAL_SRC_FILES := libs/$(TARGET_ARCH_ABI)/libscrypto_static.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_STATIC_LIBRARY)

# include $(CLEAR_VARS)
# LOCAL_MODULE := scrypto_shared
# LOCAL_SRC_FILES := libs/$(TARGET_ARCH_ABI)/libscrypto_shared.so
# LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
# include $(PREBUILT_SHARED_LIBRARY)

# app native module
include $(CLEAR_VARS)
LOCAL_MODULE    := native
LOCAL_SRC_FILES := common.cpp native.cpp
# LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_LDFLAGS := -llog
LOCAL_STATIC_LIBRARIES := scrypto_static
include $(BUILD_SHARED_LIBRARY)

#LOCAL_MODULE_FILENAME = jni-hello
#LOCAL_CPP_EXTENSION := .cpp .cxx .cc
#LOCAL_CPP_FEATURES := rtti
#LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
#LOCAL_CFLAGS := -DPORT=9999 -DNDEBUG
#LOCAL_CPPFLAGS := -DMAX=100
#LOCAL_LDFLAGS := -llog
#LOCAL_ARM_NENO := true
#LOCAL_DISABLE_NO_EXECUTE := true
#LOCAL_EXPORT_CFLAGS := − DENABLE_AUDIO
#LOCAL_EXPORT_CPPFLAGS
#LOCAL_EXPORT_LDFLAGS
#LOCAL_EXPORT_C_INCLUDES

# build system defined
#TARGET_ARCH: Name of the target CPU architecture, such as arm.
#TARGET_PLATFORM: Name of the target Android platform, such as android-3
#TARGET_ARCH_ABI: Name of the target CPU architecture and the ABI, such as
#armeabi-v7a.
#TARGET_ABI: Concatenation of target platform and ABI, such as android-3-
#armeabi-v7a

#build system marcros
#include $(call all-subdir-makefiles)
#all-subdir-makefiles - makefiles in sub-directories
#this-makefile - current makefile
#parent-makefile - path of parent makefile

# custom variables
#MY_SRC_FILES := avilib.c platform_posix.c
#LOCAL_SRC_FILES := $(addprefix avilib/, $(MY_SRC_FILES))

# conditional operations
# ifeq ($(TARGET_ARCH),arm)
# LOCAL_SRC_FILES + = armonly.c
# else
# LOCAL_SRC_FILES + = generic.c
# endif
