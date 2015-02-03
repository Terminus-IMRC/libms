TARGETS:=libms.a
SRCS:=ms.c is_ms.c str_to_ms.c ms_state_print_info.c output_ms.c ms_mem_basics.c
OBJS:=$(SRCS:%.c=%.c.o)
ALLDEPS:=$(MAKEFILE_LIST)
CFLAGS:=-Wall -O2

CC:=gcc
AR:=ar
ARFLAGS:=cr
RANLIB:=ranlib
RM:=rm -f

all: $(TARGETS)

libms.a: $(OBJS) $(ALLDEPS)
	$(AR) $(ARFLAGS) $@ $(OBJS)
	$(RANLIB) $@

%.c.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

.PHONY: clean
clean:
	$(RM) $(TARGETS)
	$(RM) $(OBJS)
