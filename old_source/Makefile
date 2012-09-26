NAME     = graphics
CC       = g++

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SRC+=src/main.cpp
SRC+=src/pixel.cpp
SRC+=src/display.cpp
SRC+=src/frame.cpp
SRC+=src/rasterizer.cpp

SRCDIRS = $(sort $(dir $(SRC)))
OBJ     = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC))

CFLAGS  = -Wall -Weffc++ -pedantic -ggdb -O0
#CFLAGS+=-DNDEBUG

LDFLAGS = -lSDL

all: $(BINDIR)/$(NAME)

$(BINDIR)/$(NAME): $(OBJDIR)/$(SRCDIRS) $(OBJ) 
	mkdir -p $(dir $@)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: %.cpp
	$(CC) -MM -MF $(subst .o,.d,$@) -MP -MT $@ $(CFLAGS) -c $<
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR)

$(OBJDIR)/$(SRCDIRS):
	mkdir -p $@

distclean: clean
	$(RM) -r $(BINDIR)

run: all
	$(BINDIR)/$(NAME)

.PHONY: all clean distclean run
