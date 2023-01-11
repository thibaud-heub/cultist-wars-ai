CFLAGS = -Wall -g

SUBDIRS := ia tad
SOURCES := $(foreach d,$(SUBDIRS),$(wildcard $(d)/*.c) $(wildcard $(d)/*.h)) engine/game.c engine/game.h engine/game_types.h

ia/testia: $(SOURCES)