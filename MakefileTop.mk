# set default value for TARGETOS if is it not defined
ifeq ($(TARGETOS), )
$(warning warning: TARGETOS not defined. Choosing linux)
TARGETOS=linux
endif

# set default value for BUILDTOOLS if is it not defined
ifeq ($(BUILDTOOLS), )
$(warning warning: BUILDTOOLS not defined. Choosing x86-gcc-4.6.3)
BUILDTOOLS=x86-gcc-4.6.3
endif

# Location of RTS root.
UMLRTS_ROOT ?= /private/var/folders/18/85qkgmpj1js3p_y38qyj937c0000gn/T/AppTranslocation/D1C036C8-969B-4C23-AA99-429E9BE6BE31/d/Papyrus-RT.app/Contents/Eclipse/plugins/org.eclipse.papyrusrt.rts_1.0.0.201810091347/umlrts/

CONFIG=$(TARGETOS).$(BUILDTOOLS)

# Destination directory for the RTS services library.
LIBDEST=$(UMLRTS_ROOT)/lib/$(CONFIG)

include $(UMLRTS_ROOT)/build/host/host.mk
include $(UMLRTS_ROOT)/build/buildtools/$(BUILDTOOLS)/buildtools.mk

LD_PATHS=$(LIBDEST)
CC_INCLUDES+=$(UMLRTS_ROOT)/include

CC_DEFINES:=$(foreach d, $(CC_DEFINES), $(CC_DEF)$d)
CC_INCLUDES:=$(foreach i, $(CC_INCLUDES), $(CC_INC)$i)
LD_LIBS:=$(foreach i, $(LD_LIBS), $(LD_LIB)$i)
LD_PATHS:=$(foreach i, $(LD_PATHS), $(LD_LIBPATH)$i)

SRCS = TopMain.cc Instruction.cc Comminicator.cc PCPlayer.cc Top.cc TopControllers.cc 
OBJS = $(subst $(CC_EXT),$(OBJ_EXT),$(SRCS))

MAIN = TopMain$(EXE_EXT)

all: $(MAIN)

$(MAIN): $(OBJS) $(UMLRTS_ROOT)/lib/$(CONFIG)/$(LIB_PRFX)rts$(LIB_EXT)
	$(LD) $(LD_FLAGS) $(OBJS) $(LD_PATHS) $(LD_LIBS) $(LD_OUT)$@

%$(OBJ_EXT) : %$(CC_EXT)
	$(CC) $< $(CC_FLAGS) $(CC_DEFINES) $(CC_INCLUDES) $(CC_OUT)$@

clean :
	@echo $(RM) main$(EXE_EXT) *$(OBJ_EXT) *$(DEP_EXT) $(DBG_FILES)
	@$(RM) main$(EXE_EXT) *$(OBJ_EXT) *$(DEP_EXT) $(DBG_FILES)

.PHONY: all clean
