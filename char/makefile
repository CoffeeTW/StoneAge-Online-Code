CC        ?= gcc
RM        ?= rm -f
AR        ?= ar
ARFLAGS   ?= cr
RANLIB    ?= ranlib
SHELL     := /bin/sh

INCFLAGS  = -I.. -I../include
CFLAGS    = -fcommon -march=native -std=gnu99 -fgnu89-inline -Wno-error=implicit-function-declaration -Wno-error=implicit-int -Wno-error=return-mismatch -O1 -pipe -w -Wextra \
            -g3 -fno-omit-frame-pointer -fPIC $(INCFLAGS)

DEPFLAGS  = -MMD -MP
PROG      = libchar.a
SRC       = char_base.c char.c char_event.c char_data.c skill.c title.c \
            addressbook.c chatmagic.c event.c char_walk.c encount.c pet.c \
            enemy.c pet_event.c char_talk.c char_party.c char_item.c deathcontend.c \
            chatroom.c petmail.c trade.c family.c defend.c char_angel.c
OBJ       = $(SRC:.c=.o)
DEPS      = $(SRC:.c=.d)

.PHONY: all clean

all: $(PROG)

$(PROG): $(OBJ)
	@echo "正在打包靜態庫 $@..."
	@$(AR) $(ARFLAGS) $@ $^ > /dev/null
	@$(RANLIB) $@
	@echo "char 模組構建完成: $@ !!"	
	
%.o: %.c
	@echo "正在編譯: $<"
	@$(CC) $(DEPFLAGS) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	@echo "正在清理 char 模組的編譯暫存檔與靜態庫..."
	@$(RM) $(OBJ) $(DEPS) $(PROG)
	@$(RM) *~
	@echo "char 模組清理完成！"