#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <jni.h>
#include <aes.h>
#include "log.h"
#include "common.h"
#include "native.h"

static const char *gClassPathName = "com/mcxiaoke/ndk/Native";

static JNINativeMethod gMethods[] = {
  {"debugInfo", "()Ljava/lang/String;", (void*)debugInfo },
};

static int registerNativeMethods(JNIEnv* env, const char* className,
                                 JNINativeMethod* methods, int numMethods)
{
  jclass clazz;
  clazz = env->FindClass(className);
  if (clazz == NULL) {
    LOGE("Native registration unable to find class '%s'", className);
    return JNI_FALSE;
  }
  if (env->RegisterNatives(clazz, methods, numMethods) < 0) {
    LOGE("RegisterNatives failed for '%s'", className);
    return JNI_FALSE;
  }
  return JNI_TRUE;
}

static int registerNatives(JNIEnv* env)
{
  if (!registerNativeMethods(
        env, gClassPathName,
        gMethods, sizeof(gMethods) / sizeof(gMethods[0]))) {
    return JNI_FALSE;
  }
  return JNI_TRUE;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
  JNIEnv* env;
  if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
    return -1;
  }
  if (registerNatives(env) != JNI_TRUE) {
    LOGE("ERROR: registerNatives failed");
    return -1;
  }
  return JNI_VERSION_1_6;
}

// crypto test methods
void aesTest()
{
  const char* text = "6BC1BEE22E409F96E93D7E117393172A";
  const uint8_t* data = hex2bin(text);
  const char* password = "2B7E151628AED2A6ABF7158809CF4F3C";
  const uint8_t* key = hex2bin(password);

  unsigned char enc_out[AES_BLOCK_SIZE];
  unsigned char dec_out[AES_BLOCK_SIZE];

  LOGD("AES_encrypt() len:%d,  key: %s", strlen(password), bin2hex(key, strlen(password) / 2));
  LOGD("AES_encrypt() len:%d, data: %s", strlen(text), bin2hex(data, strlen(text) / 2));
  // aes encrypt
  AES_KEY aes_enc_ctx;
  AES_set_encrypt_key(key, 128, &aes_enc_ctx);
  AES_encrypt(data, enc_out, &aes_enc_ctx);
  LOGD("AES_encrypt() enc_out: %s", bin2hex(enc_out, AES_BLOCK_SIZE));

// // aes decrypt
  AES_KEY aes_dec_ctx;
  AES_set_decrypt_key(key, 128, &aes_dec_ctx);
  AES_decrypt(enc_out, dec_out, &aes_dec_ctx);
  LOGD("AES_encrypt() dec_out: %s", bin2hex(dec_out, AES_BLOCK_SIZE));
}


// JNI Methods Implementations

JNIEXPORT jstring JNICALL debugInfo
(JNIEnv *env, jclass clazz)
{
  aesTest();
  return env->NewStringUTF("Native Debug Info");
}
