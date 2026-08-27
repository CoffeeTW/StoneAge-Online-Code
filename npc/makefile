CC        ?= gcc
RM        ?= rm -f
AR        ?= ar
ARFLAGS   ?= cr
RANLIB    ?= ranlib
SHELL     := /bin/sh

INCFLAGS  = -I. -I../include
CFLAGS    = -fcommon -march=native -std=gnu99 -fgnu89-inline -Wno-error=implicit-function-declaration -Wno-error=implicit-int -Wno-error=return-mismatch -O1 -pipe -w -Wextra \
            -ggdb3 -fno-omit-frame-pointer -fPIC $(INCFLAGS)

DEPFLAGS  = -MMD -MP
PROG      = libnpc.a
SRC       = readnpc.c npcgen.c npctemplate.c npccreate.c npcutil.c \
            npc_warp.c npc_townpeople.c npc_msg.c npc_healer.c npc_oldman.c \
            npc_storyteller.c npc_dengon.c npc_doorman.c npc_npcenemy.c npc_itemchange.c \
            npc_action.c npc_windowman.c npc_savepoint.c npc_windowhealer.c npc_itemshop.c \
            npc_sysinfo.c npc_duelranking.c npc_petskillshop.c npc_petshop.c npc_signboard.c \
            npc_warpman.c npc_exchangeman.c npc_timeman.c npc_bodylan.c npc_mic.c \
            npc_luckyman.c npc_bus.c npc_charm.c npc_quiz.c npc_poolitemshop.c \
            npc_checkman.c npc_janken.c npc_transmigration.c npc_makepair.c npc_familyman.c \
            npc_fmdengon.c npc_fmwarpman.c npc_fmhealer.c npc_bankman.c npc_fmpkman.c \
            npc_airplane.c npc_scheduleman.c npc_fmpkcallman.c npc_manorsman.c npc_riderman.c \
            npc_fmletter.c npc_petmaker.c npc_gamblemaster.c npc_gambleroulette.c npc_petfusion.c \
            npc_stoneserviceman.c npc_newnpcman.c npc_gamblebank.c npc_petracemaster.c npc_petracepet.c \
            npc_bigsmallmaster.c npc_bigsmallpet.c npc_auctioneer.c npc_freepetskillshop.c npc_eventaction.c \
            npc_vipshop.c npc_autopk.c npc_vippoint.c npc_mtradenpcman.c npc_blackmarket.c \
            npc_transerman.c npc_pauctionman.c npc_alldoman.c npc_sellsthman.c npc_welfare.c \
            npc_verywelfare.c
OBJ       = $(SRC:.c=.o)
DEPS      = $(SRC:.c=.d)

.PHONY: all clean

all: $(PROG)

$(PROG): $(OBJ)
	@echo "正在打包 NPC 模組靜態庫 $@..."
	@$(AR) $(ARFLAGS) $@ $^ > /dev/null
	@$(RANLIB) $@
	@echo "NPC 模組構建完成: $@ !!"	
	
%.o: %.c
	@echo "正在編譯: $<"
	@$(CC) $(DEPFLAGS) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	@echo "正在清理 NPC 模組的編譯暫存檔與靜態庫..."
	@$(RM) $(OBJ) $(DEPS) $(PROG)
	@$(RM) *~
	@echo "NPC 模組清理完成！"