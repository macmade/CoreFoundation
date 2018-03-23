#-------------------------------------------------------------------------------
# The MIT License (MIT)
# 
# Copyright (c) 2016 Jean-David Gadina - www-xs-labs.com
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# makelib configuration
#-------------------------------------------------------------------------------

include Submodules/makelib/Common.mk

PRODUCT             := CoreFoundation
PRODUCT_LIB         := libCoreFoundation
PRODUCT_DYLIB       := libCoreFoundation
PRODUCT_FRAMEWORK   := CoreFoundation
PREFIX_DYLIB        := /usr/local/lib/
PREFIX_FRAMEWORK    := /Library/Frameworks/
DIR_INC             := CoreFoundation/include/
DIR_SRC             := CoreFoundation/source/
DIR_RES             := CoreFoundation/
DIR_TESTS           := Unit-Tests/
EXT_C               := .c
EXT_CPP             := .cpp
EXT_M               := .m
EXT_MM              := .mm
EXT_H               := .h
FILES               := $(call GET_C_FILES, $(DIR_SRC))
FILES_TESTS         := $(call GET_C_FILES, $(DIR_TESTS))
CC                  := clang
FLAGS_OPTIM         := Os
FLAGS_WARN          := -Werror -Wall
FLAGS_STD_C         := c99
FLAGS_STD_CPP       := c++11
FLAGS_OTHER         := -fno-strict-aliasing
XCODE_PROJECT       := CoreFoundation.xcodeproj
XCODE_TEST_SCHEME   := CoreFoundation

ifeq ($(BUILD_TYPE),linux)
LIBS                := -lpthread -luuid
else
LIBS                := -lpthread
endif

FILES_C             := $(call GET_C_FILES, $(DIR_SRC))              \
                       $(call GET_C_FILES, $(DIR_SRC)__private/)
FILES_C_EXCLUDE     := 

FILES               := $(filter-out $(FILES_C_EXCLUDE),$(FILES_C))
FILES_TESTS         := $(call GET_C_FILES, $(DIR_TESTS))

include Submodules/makelib/Targets.mk

#-------------------------------------------------------------------------------
# Custom targets
#-------------------------------------------------------------------------------

example: all
	
	@echo -e $(call PRINT,Demo,universal,Compiling the example program)
	@$(CC) $(FLAGS_WARN) -I$(DIR_INC) -o $(DIR_BUILD_PRODUCTS)$(HOST_ARCH)/test $(call GET_C_FILES, Test/) $(DIR_BUILD_PRODUCTS)$(HOST_ARCH)/$(PRODUCT_LIB).a $(LIBS)
	@echo -e $(call PRINT,Demo,universal,Runing the example program)
	@$(DIR_BUILD_PRODUCTS)$(HOST_ARCH)/test


example-bsd: all
	
	@echo -e $(call PRINT,Demo,universal,Compiling the example program)
	@$(CC) $(FLAGS_WARN) -I$(DIR_INC) -o $(DIR_BUILD_PRODUCTS)$(HOST_ARCH)/test $(call GET_C_FILES, Test/) $(DIR_BUILD_PRODUCTS)$(HOST_ARCH)/$(PRODUCT_LIB).a /usr/local/lib/libuuid.a $(LIBS)
	@echo -e $(call PRINT,Demo,universal,Runing the example program)
	@$(DIR_BUILD_PRODUCTS)$(HOST_ARCH)/test
	
doc:
	
	@echo -e $(call PRINT,Documentation,universal,Generating the documentation)
	@doxygen Documentation/$(PRODUCT).doxygen
