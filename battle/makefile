CC        ?= gcc
RM        ?= rm -f
AR        ?= ar
ARFLAGS   ?= cr
RANLIB    ?= ranlib
SHELL     := /bin/sh

INCFLAGS  = -I.. -I../include
CFLAGS    = -fcommon -march=x86-64 -std=gnu99 -fgnu89-inline -Wno-error=implicit-function-declaration -Wno-error=implicit-int -Wno-error=return-mismatch -O2 -ggdb3 -pipe \
            -w -fPIC $(INCFLAGS)

DEPFLAGS  = -MMD -MP
PROG      = libbattle.a
SRC       = battle.c battle_event.c battle_command.c battle_ai.c \
            battle_magic.c pet_skill.c battle_item.c profession_skill.c
OBJ       = $(SRC:.c=.o)
DEPS      = $(SRC:.c=.d)

.PHONY: all clean

all: $(PROG)

$(PROG): $(OBJ)
	@echo "正在打包靜態庫 $@"
	@$(AR) $(ARFLAGS) $@ $^ > /dev/null
	@$(RANLIB) $@
	@echo "battle 模組構建完成: $@"	
	
%.o: %.c
	@echo "正在編譯: $<"
	@$(CC) $(DEPFLAGS) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	@echo "正在清理 battle 模組的編譯暫存檔與靜態庫..."
	@$(RM) $(OBJ) $(DEPS) $(PROG)
	@echo "battle 模組清理完成！"