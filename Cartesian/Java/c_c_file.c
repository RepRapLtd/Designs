
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "c_c_file.h"

#define SL 200

JNIEXPORT jint JNICALL Java_c_1c_1file_c_1open (JNIEnv *env, jobject jo, jstring s)
{
    const char* str = (*env)->GetStringUTFChars(env, s, 0);
    int fd = open(str, O_RDWR | O_NOCTTY | O_NDELAY);
    if(fd == -1)
      printf("Java_cartesian_c_1open: error opening file %s.\n", str);
    fcntl(fd, F_SETFL, 0);
    return fd;
}

JNIEXPORT void JNICALL Java_c_1c_1file_c_1fcntl (JNIEnv *env, jobject jo, jint fd, jint wait)
{
  if(wait)
    fcntl(fd, F_SETFL, 0);
  else
    fcntl(fd, F_SETFL, FNDELAY);
}

JNIEXPORT jint JNICALL Java_c_1c_1file_c_1write (JNIEnv *env, jobject jo, jint fd, jstring s, jint len)
{
   const char* str = (*env)->GetStringUTFChars(env, s, 0);
   int n = write(fd, str, len);
   return n;
}

static int n;

JNIEXPORT jstring JNICALL Java_c_1c_1file_c_1read (JNIEnv *env, jobject jo, jint fd)
{
  char str[SL];
  n = read(fd, str, SL);
  str[n] = 0;
  jstring s = (*env)->NewStringUTF(env, str);
  return s;

}

JNIEXPORT jint JNICALL Java_c_1c_1file_c_1n_1read (JNIEnv *env, jobject jo)
{
  return n;
}
