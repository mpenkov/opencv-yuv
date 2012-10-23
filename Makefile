#http://www.gnu.org/software/make/manual/make.html

#
# This is here to prevent Make from deleting secondary files.
#
.SECONDARY:
	

SRC=yuv.c
OBJ=$(patsubst %.c,obj/%.o,$(SRC))
EXE=main.out

CC=gcc
CFLAGS=-Wall -ggdb `pkg-config --cflags opencv libavcodec libavformat \
		libavutil libswscale`
LDFLAGS=-lm `pkg-config --libs opencv libavcodec libavformat libavutil \
		libswscale`

all: dirs $(addprefix bin/, $(EXE)) tags

dirs:
	mkdir -p obj
	mkdir -p bin

tags: *.c *.h
	ctags *.c *.h

bin/%.out: obj/%.o $(OBJ)
	$(CC) $< $(OBJ) $(LDFLAGS) -o $@

obj/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f obj/*
	rm -f bin/*
	rm -f tags
