INNER_SAVED_LOCAL_PATH := $(LOCAL_PATH)

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := rapidvg

LOCAL_CFLAGS := -std=gnu99

LOCAL_C_INCLUDES  := \
	${SHADERLAB_SRC_PATH} \
	${EJOY2D_SRC_PATH} \
	${SHADERLAB_SRC_PATH}/include \
	${UNIRENDER_SRC_PATH}/include \

LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,,$(shell find $(LOCAL_PATH) -name "*.c" -print)) \

LOCAL_STATIC_LIBRARIES := \
	unirender \

include $(BUILD_STATIC_LIBRARY)	

LOCAL_PATH := $(INNER_SAVED_LOCAL_PATH)