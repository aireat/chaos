#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = chaos
    
TEST_TARGET = \
    bin/$(COMPONENT_NAME).exe

CPPUTEST_OBJS_DIR = \
    build/objs

CPPUTEST_LIB_DIR = \
    build/lib

#--- Inputs ----#
PROJECT_HOME_DIR = .
CPP_PLATFORM = Gcc

SRC_DIRS = \
    $(PROJECT_HOME_DIR)/source \
    $(PROJECT_HOME_DIR)/source/include \

TEST_SRC_DIRS = \
    tests\
    tests/*\

INCLUDE_DIRS =\
  .\
  $(PROJECT_HOME_DIR)/include \
  $(PROJECT_HOME_DIR)/source/include \
  $(CPPUTEST_HOME)/include\
#  $(PROJECT_HOME_DIR)/include/LedDriver\

  
CPPUTEST_WARNINGFLAGS     += -Werror
CPPUTEST_WARNINGFLAGS     += -Waddress
CPPUTEST_WARNINGFLAGS     += -Warray-bounds 
CPPUTEST_WARNINGFLAGS     += -Wchar-subscripts
CPPUTEST_WARNINGFLAGS     += -Wcomment -Wformat
CPPUTEST_WARNINGFLAGS     += -Wmissing-braces 
CPPUTEST_WARNINGFLAGS     += -Wnonnull
CPPUTEST_WARNINGFLAGS     += -Wparentheses
CPPUTEST_WARNINGFLAGS     += -Wreturn-type
CPPUTEST_WARNINGFLAGS     += -Wsequence-point
#CPPUTEST_WARNINGFLAGS     += -Wstrict-aliasing -Wstrict-aliasing=3
CPPUTEST_WARNINGFLAGS     += -Wstrict-overflow -Wstrict-overflow=1
CPPUTEST_WARNINGFLAGS     += -Wswitch
CPPUTEST_WARNINGFLAGS     += -Wtrigraphs
CPPUTEST_WARNINGFLAGS     += -Wuninitialized
CPPUTEST_WARNINGFLAGS     += -Wunknown-pragmas
CPPUTEST_WARNINGFLAGS     += -Wunused-function
CPPUTEST_WARNINGFLAGS     += -Wunused-label
CPPUTEST_WARNINGFLAGS     += -Wunused-value
CPPUTEST_WARNINGFLAGS     += -Wunused-variable
CPPUTEST_WARNINGFLAGS     += -Wunused-value
CPPUTEST_WARNINGFLAGS     += -Wunused-parameter
CPPUTEST_WARNINGFLAGS     += -Wempty-body

CPPUTEST_WARNINGFLAGS     += -Wmissing-noreturn
CPPUTEST_WARNINGFLAGS     += -Wconversion
CPPUTEST_WARNINGFLAGS     += -Wtype-limits
CPPUTEST_WARNINGFLAGS     += -Wshadow
CPPUTEST_WARNINGFLAGS     += -Wno-endif-labels
CPPUTEST_WARNINGFLAGS     += -Wunreachable-code
CPPUTEST_WARNINGFLAGS     += -Wno-write-strings


CPPUTEST_CXX_WARNINGFLAGS += -Wreorder
CPPUTEST_CXX_WARNINGFLAGS += -Wsign-compare


CPPUTEST_C_WARNINGFLAGS   += -Wmain
CPPUTEST_C_WARNINGFLAGS   += -Wimplicit-int
CPPUTEST_C_WARNINGFLAGS   += -Wimplicit-function-declaration
CPPUTEST_C_WARNINGFLAGS   += -Wpointer-sign
CPPUTEST_C_WARNINGFLAGS   += -Wmissing-declarations
#CPPUTEST_C_WARNINGFLAGS   += -Wmissing-parameter-type
CPPUTEST_C_WARNINGFLAGS   += -Wmissing-prototypes
CPPUTEST_C_WARNINGFLAGS   += -Wnested-externs
CPPUTEST_C_WARNINGFLAGS   += -Wno-pointer-to-int-cast
CPPUTEST_C_WARNINGFLAGS   += -Wno-int-to-pointer-cast


include $(CPPUTEST_HOME)/build/MakefileWorker.mk

