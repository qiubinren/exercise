.PHONY:clean all
CXX=g++
CPPFALGS = -Wall -g -O3
BIN=main
OBJS = main.o Query.o
LIB=/usr/lib64/mysql
$(BIN):$(OBJS)
	$(CXX) -o $@ $^ -L $(LIB) -l mysqlclient
%.o:%.cpp
	$(CXX) $(CPPFLAGS) -o $@ -c $< -L $(LIB) -l mysqlclient
clean:
	rm -f *.o $(BIN)
