CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2
LDFLAGS = -lnuma -shared -soname
TARGET_LIB = libnmem.so
TARGET_PATH = /usr/lib/x86_64-linux-gnu/
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
