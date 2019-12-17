SOURCES=graph.hpp main.cpp

graph.out: $(SOURCES)
	g++ main.cpp -o $@ 

graph_debug.out: $(SOURCES)
	g++ -g main.cpp -o $@ 