MODULE := engines/eldorado
 
MODULE_OBJS := \
	detection.o \
	eldorado.o
 
MODULE_DIRS += \
	engines/eldorado
 
# This module can be built as a plugin
ifeq ($(ENABLE_ELDORADO), DYNAMIC_PLUGIN)
PLUGIN := 1
endif
 
# Include common rules 
include $(srcdir)/rules.mk