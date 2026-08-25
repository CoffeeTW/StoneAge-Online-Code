CC        ?= gcc
RM        ?= rm -f
AR        ?= ar
ARFLAGS   ?= cr
RANLIB    ?= ranlib
SHELL     := /bin/sh

INCFLAGS  = -I.. -I../include
CFLAGS    = -fcommon -march=native -std=gnu99 -O1 -pipe -w -Wextra \
            -ggdb3 -fno-omit-frame-pointer -fPIC $(INCFLAGS)

DEPFLAGS  = -MMD -MP
PROG      = libmap.a
SRC       = readmap.c map_deal.c map_util.c map_warppoint.c
OBJ       = $(SRC:.c=.o)
DEPS      = $(SRC:.c=.d)

.PHONY: all clean

all: $(PROG)

$(PROG): $(OBJ)
	@echo "正在打包 map 模組靜態庫 $@..."
	@$(AR) $(ARFLAGS) $@ $^ > /dev/null
	@$(RANLIB) $@
	@echo "map 模組構建完成: $@ !!"	
	
%.o: %.c
	@echo "正在編譯: $<"
	@$(CC) $(DEPFLAGS) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	@echo "正在清理 map 模組的編譯暫存檔與靜態庫..."
	@$(RM) $(OBJ) $(DEPS) $(PROG)
	@$(RM) *~
	@echo "map模組清理完成！"