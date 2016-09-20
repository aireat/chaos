#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = emv_kernel
	
TEST_TARGET = \
	bin/$(COMPONENT_NAME)

CPPUTEST_OBJS_DIR = \
	build/objs

CPPUTEST_LIB_DIR = \
	build/lib

#--- Inputs ----#
PROJECT_HOME_DIR = .
CPP_PLATFORM = Gcc

SRC_DIRS = \
	$(PROJECT_HOME_DIR)/src \
#	$(PROJECT_HOME_DIR)/src/LedDriver \

TEST_SRC_DIRS = \
	tests\
	tests/*\

INCLUDE_DIRS =\
  .\
  $(PROJECT_HOME_DIR)/include \
  $(PROJECT_HOME_DIR)/src/include \
  $(CPPUTEST_HOME)/include\
#  $(PROJECT_HOME_DIR)/include/LedDriver\
  
#CPPUTEST_WARNINGFLAGS += -pedantic-errors -Wconversion -Wshadow  -Wextra
#CPPUTEST_WARNINGFLAGS += -Wall -Werror -Wswitch-default -Wswitch-enum 
CPPUTEST_WARNINGFLAGS += -Wall -Wswitch-default -Wswitch-enum 


include $(CPPUTEST_HOME)/build/MakefileWorker.mk
