CC         ?= gcc
RM         ?= rm -f
AR         ?= ar
RANLIB     ?= ranlib
SED        ?= sed
MV         ?= mv
SHELL      := /bin/sh

INCFLAGS  = -I. -I./include -I/usr/local/include
CFLAGS    = -fcommon -march=x86-64 -std=gnu99 -fgnu89-inline -Wno-error=implicit-function-declaration -Wno-error=implicit-int -Wno-error=return-mismatch -O1 -pipe -w -Wextra \
            -ggdb3 -fno-omit-frame-pointer -fPIC -D_NEW_DECODE $(INCFLAGS)

PROG       = ./gmsv
DEPFLAGS   = -MMD -MP

SUBDIR     = char npc map item battle magic
LIBS       = char/libchar.a npc/libnpc.a map/libmap.a \
             item/libitem.a magic/libmagic.a battle/libbattle.a \
             
SRC        = main.c init.c configfile.c util.c net.c buf.c msignal.c link.c \
             callfromac.c callfromcli.c object.c handletime.c function.c log.c autil.c \
             saacproto_cli.c saacproto_util.c lssproto_serv.c lssproto_util.c

OBJ        = $(SRC:.c=.o)
DEPS       = $(SRC:.c=.d)

SQL        = -lmysqlclient -lz
LDFLAGS    = -L/usr/local/lib $(SQL) -lm -lpthread -ldl

.PHONY: all clean distclean dos2unix chmod depend data

all: $(PROG)

$(PROG): $(LIBS) $(OBJ) 
	@echo "執行連結 $(PROG)..."
	@$(CC) $(CFLAGS) -o $(PROG) $(OBJ) $(LIBS) $(LDFLAGS)
	@echo "編譯完成 : $(PROG) "

%.o: %.c
	@echo "正在編譯: $<"
	@$(CC) $(DEPFLAGS) $(CFLAGS) -c $< -o $@

$(LIBS):
	@echo "--------------------------------------------------"
	@echo "正在構建子模組靜態庫: $(dir $@)"
	@echo "--------------------------------------------------"
	@$(MAKE) --no-print-directory -C $(dir $@)

-include $(DEPS)

dos2unix:
	@for dir in $(SUBDIR) ; do $(MAKE) -C $$dir dos2unix ; done
	@dos2unix ./include/*.h $(SRC) makefile

chmod:
	@for dir in $(SUBDIR) ; do $(MAKE) -C $$dir chmod ; done
	@chmod 777 ./include/*.h $(SRC) makefile

clean:
	@echo "正在清理所有模組的編譯暫存檔..."
	@for dir in $(SUBDIR) ; do $(MAKE) --no-print-directory -C $$dir clean ; done
	@$(RM) $(PROG) $(OBJ) $(DEPS) *~
	@echo "清理完成！"

distclean: clean
	@echo "正在執行深度清理 (distclean)..."
	@$(RM) include/*~ ./gmsv
	@echo "深度清理完成！"