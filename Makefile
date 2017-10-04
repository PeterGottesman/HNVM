CC=clang
OBJS=src/*.c
INC=inc/

EXE=hnvm

FLAGS=-I$(INC) -g

all: $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $(EXE)
	chmod +x $(EXE)

clean:
	rm -f $(EXE)
