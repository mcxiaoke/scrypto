LOCAL_PATH := $(call my-dir)

CRYPTO_SRC_FILES := crypto/aes.c crypto/mode_wrappers.c crypto/des.c crypto/base64.c \
	crypto/modes/cbc.c crypto/modes/cfb.c crypto/modes/ctr.c crypto/modes/ofb.c \
	crypto/modes/gcm.c crypto/mem.c crypto/sha1.c crypto/sha256.c crypto/sha512.c \
	crypto/md5.c
CRYPTO_INCLUDES := $(LOCAL_PATH)/include

include $(CLEAR_VARS)
LOCAL_MODULE    := scrypto_static
LOCAL_SRC_FILES := $(CRYPTO_SRC_FILES)
LOCAL_C_INCLUDES := $(CRYPTO_INCLUDES)
LOCAL_EXPORT_C_INCLUDES := $(CRYPTO_INCLUDES)
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := scrypto_shared
LOCAL_SRC_FILES := $(CRYPTO_SRC_FILES)
LOCAL_C_INCLUDES := $(CRYPTO_INCLUDES)
LOCAL_EXPORT_C_INCLUDES := $(CRYPTO_INCLUDES)
include $(BUILD_SHARED_LIBRARY)

# include $(CLEAR_VARS)
# LOCAL_MODULE    := sample
# LOCAL_SRC_FILES := sample/aes_sample.cpp
# #LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
# LOCAL_CPPFLAGS += -std=c++11
# LOCAL_STATIC_LIBRARIES := scrypto_static
# include $(BUILD_SHARED_LIBRARY)
