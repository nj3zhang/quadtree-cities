all: qtdriver
qtdriver: qttest.cpp treeOp.cpp data.h tree.h
	g++ -std=c++11 -o qtdriver qttest.cpp
clean:
	rm -f qtdriver
