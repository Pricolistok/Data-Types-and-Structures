CC := gcc

CFLAGS := -Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-conversion -Wfloat-equal -Iinc

EXEFLAGS := -lm

create := $(shell mkdir -p out)

ifeq ($(mode), release)
	CFLAGS += -g0
endif

ifeq ($(mode), debug)
	CFLAGS += -g3 -gdwarf-2
	CC = clang
endif

ifeq ($(mode), memory)
	CFLAGS += -fsanitize=memory -fPIE -fno-omit-frame-pointer -g 
	EXEFLAGS += -fsanitize=memory
	CC = clang
endif

ifeq ($(mode), adress)
	CFLAGS += -fsanitize=address -fno-omit-frame-pointer -g
	EXEFLAGS += -fsanitize=address
	CC = clang
endif

ifeq ($(mode), ubsan)
	CFLAGS += -fsanitize=undefined -fno-omit-frame-pointer -g
	EXEFLAGS += -fsanitize=undefined
	CC = clang
endif



app.exe: out/main.o out/input_output.o out/process.o
	$(CC) -o app.exe out/main.o out/input_output.o out/process.o $(EXEFLAGS)

out/main.o: src/main.c inc/input_output.h inc/errors.h inc/consts.h inc/process.h
	$(CC) -std=c99 $(CFLAGS) -o ./out/main.o -c src/main.c

out/input_output.o: src/input_output.c inc/errors.h inc/input_output.h inc/consts.h
	$(CC) -std=c99 $(CFLAGS) -o ./out/input_output.o -c src/input_output.c

out/process.o: src/process.c inc/errors.h inc/process.h
	$(CC) -std=c99 $(CFLAGS) -o ./out/process.o -c src/process.c



.PHONY : clean
clean:
	rm -rf out/*.o 
	rm -rf *.exe 
# rm -rf *.txt  