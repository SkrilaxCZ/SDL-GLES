PREFIX:=$(shell sdl-config --prefix)

CC:=gcc
LIBTOOL:=libtool
MACHINE:=$(shell gcc -dumpmachine)

RELEASE:=1.2
VERSION:=0:1:0

SDL_GLES_TARGET:=libSDL_gles.la

SDL_GLES_LDLIBS:=$(shell sdl-config --libs) -lEGL
SDL_GLES_CFLAGS:=$(shell sdl-config --cflags)
SDL_GLES_LDFLAGS:=-release $(RELEASE) -version-info $(VERSION) -rpath $(PREFIX)/lib/$(MACHINE)

all: $(SDL_GLES_TARGET)

$(SDL_GLES_TARGET): SDL_gles.lo
	$(LIBTOOL) --mode=link $(CC) $(LDFLAGS) $(SDL_GLES_LDFLAGS) $(LDLIBS) $(SDL_GLES_LDLIBS) -o $@ $^
	
SDL_gles.lo: SDL_gles.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(SDL_GLES_CFLAGS) -c $^
	
clean:
	$(LIBTOOL) --mode=clean rm -f *.o *.lo $(SDL_GLES_TARGET)
	
install: $(SDL_GLES_TARGET)
	install -d $(DESTDIR)$(PREFIX)/include/SDL $(DESTDIR)$(PREFIX)/lib/$(MACHINE)
	install SDL_gles.h $(DESTDIR)$(PREFIX)/include/SDL/
	$(LIBTOOL) --mode=install install -c $(SDL_GLES_TARGET) $(DESTDIR)$(PREFIX)/lib/$(MACHINE)
ifeq ($(DESTDIR),)
	$(LIBTOOL) --mode=finish $(PREFIX)/lib/$(MACHINE)
endif

uninstall:
	$(LIBTOOL) --mode=uninstall rm -f $(DESTDIR)$(PREFIX)/lib/$(MACHINE)/$(SDL_GLES_TARGET)
	rm -f $(DESTDIR)$(PREFIX)/include/SDL/SDL_gles.h

