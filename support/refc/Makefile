TARGET = libidris2_refc

LIBTARGET = $(TARGET).a

SRCS := $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

CFLAGS += -g #-O2

ifeq ($(OLD_WIN), 1)
	CPPFLAGS += -D_OLD_WIN
endif


all: build

.PHONY: build

build: $(LIBTARGET)

$(LIBTARGET): $(OBJS)
	$(AR) rc $@ $^
#	$(RANLIB) $@

-include $(DEPS)

%.d: %.c
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@


.PHONY: clean

clean:
	$(RM) $(OBJS)  $(DEPS) $(LIBTARGET)

cleandep: clean
	$(RM) $(DEPS)
