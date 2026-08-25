CC        ?= gcc
RM        ?= rm -f
AR        ?= ar
ARFLAGS   ?= cr
RANLIB    ?= ranlib
SHELL     := /bin/sh

INCFLAGS  = -I.. -I../include
CFLAGS    = -fno-common -march=native -std=gnu99 -O1 -pipe -w -Wextra \
            -g3 -fno-omit-frame-pointer -fPIC $(INCFLAGS)

DEPFLAGS  = -MMD -MP
PROG      = libmagic.a
SRC       = magic.c magic_base.c magic_field.c
OBJ       = $(SRC:.c=.o)
DEPS      = $(SRC:.c=.d)

.PHONY: all clean

all: $(PROG)

$(PROG): $(OBJ)
	@echo "正在打包 magic 模組靜態庫 $@..."
	@$(AR) $(ARFLAGS) $@ $^ > /dev/null
	@$(RANLIB) $@
	@echo "magic 模組構建完成: $@ !!"	
	
%.o: %.c
	@echo "正在編譯: $<"
	@$(CC) $(DEPFLAGS) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	@echo "正在清理 magic 模組的編譯暫存檔與靜態庫..."
	@$(RM) $(OBJ) $(DEPS) $(PROG)
	@$(RM) *~
	@echo "magic 模組清理完成！"