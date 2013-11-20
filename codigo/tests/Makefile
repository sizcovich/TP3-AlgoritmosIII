CXX=g++
CXXFLAGS=-Wall -O2 -std=c++0x
IDIR=-I./
LDFLAGS=-lpthread
# EXTRACXXFLAGS=
# SOURCES=experimentacion.cpp ../src/graph.cpp
# OGDF=../include/OGDF/_release/libOGDF.a
#OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLES=graph_generator 

all: $(EXECUTABLES)
generador: graph_generator

graph_generator: graph_generator.cpp random_graphs_generators.cpp
		$(CXX) $(CXXFLAGS) $(LDFLAGS) $(IDIR) -o $@ $^

clean:
		@$(RM) $(EXECUTABLES)
