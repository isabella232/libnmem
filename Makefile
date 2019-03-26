#SPDX-License-Identifier: MIT
#MIT License
 
#Copyright (c) 2019 Western Digital Corporation or its affiliates.
 
#Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
#The above copyright notice and this permission notice (including the next paragraph) shall be included in all copies or substantial portions of the Software.
 
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2
LDFLAGS = -lnuma -shared -soname
TARGET_LIB = libnmem.so
OS = $(shell lsb_release -si)
ifeq ($(OS), Ubuntu)
TARGET_PATH = /usr/lib/x86_64-linux-gnu/
else
ifeq ($(OS), RedHatEnterpriseServer)
TARGET_PATH = /usr/lib64/
else
TARGET_PATH = /usr/lib/
endif
endif

ifeq ($(debug), 1)
   CFLAGS += -DNMDEBUG_LOG
endif

TARGET_HDR_PATH = /usr/include
SRCS = nmem.c
LIBHDR = nmem.h
OBJS = $(SRCS:.c=.o)

.PHONY: all

all: clean ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	@echo 'Link $@'
	ld ${LDFLAGS} $@.1 -o $@.1.0 $(OBJS)
	@echo 'Install $(TARGET_LIB)'
	mv ./$@.1.0 $(TARGET_PATH)
	ln -sf $(TARGET_PATH)$@.1.0 $(TARGET_PATH)$@.1
	ln -sf $(TARGET_PATH)$@.1 $(TARGET_PATH)$@
	cp ./$(LIBHDR) $(TARGET_HDR_PATH)/

$(OBJS): $(SRCS)
	@echo 'Compile $^'
	$(CC) $(CFLAGS) -c $^

clean:
	@echo 'Cleanup'
	rm -rf *.o
	rm -rf $(TARGET_PATH)$(TARGET_LIB).*

unittest: all
	make -C test/ run
