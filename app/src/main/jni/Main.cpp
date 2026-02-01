//
// Created by aantik on 2/1/2026.
//

//Main.cpp

#include <list>
#include <vector>
#include <string>
#include <pthread.h>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"

#include "KittyMemory/MemoryPatch.h"
#include "Menu.h"


#define targetLibName OBFUSCATE("libFileA.so")

#include "Includes/Macros.h"

#include "JavaGPP/Interface/Interface.h"


struct My_Patches {
    MemoryPatch xs;
} hexPatches;



void *hack_thread(void *) {
    LOGI(OBFUSCATE("pthread created"));

    do {
        sleep(1);
    } while (!isLibraryLoaded(targetLibName));


    LOGI(OBFUSCATE("%s has been loaded"), (const char *) targetLibName);

#if defined(__aarch64__)



#else


#endif

    return NULL;
}

jobjectArray  getFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;

    const char *features[] = {
            OBFUSCATE("Category_The Category"), //Not counted
            OBFUSCATE("Toggle_The toggle"),
    };


    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray) env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),env->NewStringUTF(""));
    for (int i = 0; i < Total_Feature; i++) env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));
    pthread_t ptid;

    return (ret);
}

void Changes(JNIEnv *env, jclass clazz, jobject obj, jint featNum, jstring featName, jint value, jboolean boolean, jstring str) {

    switch (featNum) {
        case 1:

            break;
    }
}


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *) {
    antik = vm;
    InterfaceMethods::Icon = (void*) Icon;
    InterfaceMethods::IconWebViewData = (void *) IconWebViewData;
    InterfaceMethods::Changes = (void *) Changes;
    InterfaceMethods::getFeatureList = (void *) getFeatureList;
    InterfaceMethods::settingsList = (void *) settingsList;
    InterfaceMethods::setTitleText = (void *) setTitleText;
    InterfaceMethods::setHeadingText = (void *) setHeadingText;

    binJava();
    return JNI_VERSION_1_6;
}



__attribute__((constructor))
void lib_main() {
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}
