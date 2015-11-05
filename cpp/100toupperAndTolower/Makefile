.PHONY:clean all
CXX=g++
CPPFALGS = -Wall -g -O3
BIN=main
all:$(BIN)
%.o:%.c
	$(CXX) $(CPPFLAGS) -o $@ -c $<
clean:
	rm -f *.o $(BIN)
