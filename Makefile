CC=clang
OBJS=src/*.c
INC=inc/

EXE=hnvm

FLAGS=-I$(INC) -g -Wall

all: $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $(EXE)
	chmod +x $(EXE)

clean:
	rm -f $(EXE)
