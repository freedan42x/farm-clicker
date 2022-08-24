PKGS = sdl2 SDL2_image SDL2_ttf
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude/ $(shell pkg-config --cflags $(PKGS))
LIBS = -lm $(shell pkg-config --libs $(PKGS))
STATIC_LIBS = $(wildcard lib/*.a)

SRCDIR = src
OBJDIR = obj

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

.PHONY: all
all: dir main

.PHONY: dir
dir:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< $(CXXFLAGS) $(LIBS) -o $@

main: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) -o $@ $^ $(STATIC_LIBS)
