.PHONY:clean all
CXX = g++
CPPFLAGS =-std=c++11 -lpthread -g -O2
BIN = main
OBJS = CThreadPool.o main.o
$(BIN):$(OBJS)
	$(CXX) -o $(BIN) $(OBJS) -lpthread
%.o:%.cpp
	$(CXX) $(CPPFLAGS) -o $@ -c $<

clean:
	rm -rf *.o main
