NAME     = 0d
CC       = g++

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SRC+=src/main.cpp
SRC+=src/Display.cpp
SRC+=src/Rasterizer.cpp
SRC+=src/Vector3d.cpp
SRC+=src/Vector4d.cpp
SRC+=src/Point.cpp
SRC+=src/Matrix4x4.cpp
SRC+=src/ApplicationBase.cpp
SRC+=src/GraphicsApp.cpp

SRCDIRS = $(sort $(dir $(SRC)))
OBJ     = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC))

ifeq ($(OS),Windows_NT)
	CFLAGS  = -ggdb -O0 -Isrc -I/usr/local/include -I/usr/include -Wall -pedantic -Weffc++
	LDFLAGS = -L/usr/local/lib -lmingw32 -lSDLmain -lSDL -lpthread
else
	CFLAGS  = -ggdb -O0 -pedantic -Weffc++
	LDFLAGS = -lSDL -lpthread
endif

all: $(BINDIR)/$(NAME)

$(BINDIR)/$(NAME): $(OBJDIR)/$(SRCDIRS) $(OBJ)
	mkdir -p $(dir $@)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

DEPS := $(OBJ:.o=.d)
-include $(DEPS)

$(OBJDIR)/%.o: %.cpp
	$(CC) -MM -MF $(subst .o,.d,$@) -MP -MT $@ $(CFLAGS) -c $<
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR)

$(OBJDIR)/$(SRCDIRS):
	mkdir -p $@

distclean: clean
	$(RM) -r $(BINDIR)
	$(RM) tags

run: all
	$(BINDIR)/$(NAME)

.PHONY: all clean distclean run
