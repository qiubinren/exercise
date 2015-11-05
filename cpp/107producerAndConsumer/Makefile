.PHONY:clean all
CXX=g++
CPPFALGS = -Wall -g -O3 -std=c++11
BIN=main
OBJS = main.o CMutex.o CCondition.o CThread.o 
$(BIN):$(OBJS)
	$(CXX) $(CPPFALGS) -o $@ $^ -l pthread
%.o:%.cpp
	$(CXX) $(CPPFLAGS) -o $@ -c $< 
clean:
	rm -f *.o $(BIN)
