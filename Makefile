#CXX=g++
#
#OBJDIR=obj
#OUTDIR=out
#
#CXXFLAGS+=-Wall
#LDFLAGS=-Wl,-O1,-s -lSDL
#
#OUTPUT=out/wonder
#
#SOURCES=src/main.cpp
#SOURCES+=src/pixel.cpp
#SOURCES+=src/display.cpp
#SOURCES+=src/frame.cpp
#SOURCES+=src/rasterizer.cpp
#
#OBJECTS=$(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))
#
#all: $(OUTPUT)
#
#$(OUTPUT): $(OBJECTS)
#	$(CXX) $(LDFLAGS) -o $@ $^
#
#$(OBJDIR):
#	mkdir -p $@
#
#$(OBJDIR)/%.o: %.cpp | $(OBJDIR) 
#	mkdir -p $(dir $@)
#	$(CXX) $(CXXFLAGS) -c -o $@ $<
#
#clean:
#	rm -rf $(OBJDIR)
#
CC=g++

CFLAGS+=-Wall
CFLAGS+=-Weffc++
CFLAGS+=-pedantic
CFLAGS+=-ggdb
CFLAGS+=-O0
#CFLAGS+=-DNDEBUG

LDFLAGS+=-lSDL

SOURCES+=src/main.cpp
SOURCES+=src/pixel.cpp
SOURCES+=src/display.cpp
SOURCES+=src/frame.cpp
SOURCES+=src/rasterizer.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=out/wonder
OBJDIR=obj

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(addprefix $(OBJDIR)/, $(notdir $(OBJECTS))) -o $@

%.o: %.cpp 
	$(CC) $(CFLAGS) $< -c -o $(OBJDIR)/$(@F) 

clean:
	rm -f $(EXECUTABLE)
	rm -f $(addprefix $(OBJDIR)/, $(notdir $(OBJECTS)))

$(OBJDIR)/main.o: src/main.cpp 
$(OBJDIR)/pixel.o: src/pixel.cpp pixel.h 
