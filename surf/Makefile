# surf - simple browser
# See LICENSE file for copyright and license details.
.POSIX:

include config.mk

SRC = surf.c
WSRC = webext-surf.c
OBJ = $(SRC:.c=.o)
WOBJ = $(WSRC:.c=.o)
WLIB = $(WSRC:.c=.so)

all: options surf $(WLIB)

options:
	@echo surf build options:
	@echo "CC            = $(CC)"
	@echo "CFLAGS        = $(SURFCFLAGS) $(CFLAGS)"
	@echo "WEBEXTCFLAGS  = $(WEBEXTCFLAGS) $(CFLAGS)"
	@echo "LDFLAGS       = $(LDFLAGS)"

surf: $(OBJ)
	$(CC) $(SURFLDFLAGS) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)

$(OBJ) $(WOBJ): config.h common.h config.mk

config.h:
	cp config.def.h $@

$(OBJ): $(SRC)
	$(CC) $(SURFCFLAGS) $(CFLAGS) -c $(SRC)

$(WLIB): $(WOBJ)
	$(CC) -shared -Wl,-soname,$@ $(LDFLAGS) -o $@ $? $(WEBEXTLIBS)

$(WOBJ): $(WSRC)
	$(CC) $(WEBEXTCFLAGS) $(CFLAGS) -c $(WSRC)

clean:
	rm -f surf $(OBJ)
	rm -f $(WLIB) $(WOBJ)

distclean: clean
	rm -f config.h surf-$(VERSION).tar.gz

dist: distclean
	mkdir -p surf-$(VERSION)
	cp -R LICENSE Makefile config.mk config.def.h README \
	    surf-open.sh surf-session surf-download surf-bookmark surf-reopen surf-go \
	    bookmarks.example UPSTREAM arg.h TODO.md surf.png \
	    surf.1 common.h styles scripts filters vendor $(SRC) $(WSRC) surf-$(VERSION)
	tar -cf surf-$(VERSION).tar surf-$(VERSION)
	gzip surf-$(VERSION).tar
	rm -rf surf-$(VERSION)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f surf $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/surf
	cp -f surf-open.sh $(DESTDIR)$(PREFIX)/bin/surf-open
	cp -f surf-session $(DESTDIR)$(PREFIX)/bin/surf-session
	cp -f surf-download $(DESTDIR)$(PREFIX)/bin/surf-download
	cp -f surf-bookmark $(DESTDIR)$(PREFIX)/bin/surf-bookmark
	cp -f surf-reopen $(DESTDIR)$(PREFIX)/bin/surf-reopen
	cp -f surf-go $(DESTDIR)$(PREFIX)/bin/surf-go
	chmod 755 $(DESTDIR)$(PREFIX)/bin/surf-open
	chmod 755 $(DESTDIR)$(PREFIX)/bin/surf-session
	chmod 755 $(DESTDIR)$(PREFIX)/bin/surf-download
	chmod 755 $(DESTDIR)$(PREFIX)/bin/surf-bookmark
	chmod 755 $(DESTDIR)$(PREFIX)/bin/surf-reopen
	chmod 755 $(DESTDIR)$(PREFIX)/bin/surf-go
	mkdir -p $(DESTDIR)$(DATAPREFIX)/styles
	cp -f styles/cookies.css styles/lichess.css styles/lastfm.css \
	    $(DESTDIR)$(DATAPREFIX)/styles
	chmod 644 $(DESTDIR)$(DATAPREFIX)/styles/cookies.css \
	    $(DESTDIR)$(DATAPREFIX)/styles/lichess.css \
	    $(DESTDIR)$(DATAPREFIX)/styles/lastfm.css
	mkdir -p $(DESTDIR)$(DATAPREFIX)/scripts
	cp -f scripts/cookies.js $(DESTDIR)$(DATAPREFIX)/scripts
	chmod 644 $(DESTDIR)$(DATAPREFIX)/scripts/cookies.js
	mkdir -p $(DESTDIR)$(DATAPREFIX)/filters
	cp -f filters/adblock.json $(DESTDIR)$(DATAPREFIX)/filters
	chmod 644 $(DESTDIR)$(DATAPREFIX)/filters/adblock.json
	mkdir -p $(DESTDIR)$(DATAPREFIX)/licenses/idcac
	cp -f vendor/idcac/LICENSE vendor/idcac/UPSTREAM \
	    $(DESTDIR)$(DATAPREFIX)/licenses/idcac
	chmod 644 $(DESTDIR)$(DATAPREFIX)/licenses/idcac/LICENSE \
	    $(DESTDIR)$(DATAPREFIX)/licenses/idcac/UPSTREAM
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp -f $(WLIB) $(DESTDIR)$(LIBDIR)
	for wlib in $(WLIB); do \
	    chmod 644 $(DESTDIR)$(LIBDIR)/$$wlib; \
	done
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	sed "s/VERSION/$(VERSION)/g" < surf.1 > $(DESTDIR)$(MANPREFIX)/man1/surf.1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/surf.1

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/surf
	rm -f $(DESTDIR)$(PREFIX)/bin/surf-open
	rm -f $(DESTDIR)$(PREFIX)/bin/surf-session
	rm -f $(DESTDIR)$(PREFIX)/bin/surf-download
	rm -f $(DESTDIR)$(PREFIX)/bin/surf-bookmark
	rm -f $(DESTDIR)$(PREFIX)/bin/surf-reopen
	rm -f $(DESTDIR)$(PREFIX)/bin/surf-go
	rm -f $(DESTDIR)$(DATAPREFIX)/styles/cookies.css
	rm -f $(DESTDIR)$(DATAPREFIX)/styles/lichess.css
	rm -f $(DESTDIR)$(DATAPREFIX)/styles/lastfm.css
	rm -f $(DESTDIR)$(DATAPREFIX)/scripts/cookies.js
	rm -f $(DESTDIR)$(DATAPREFIX)/filters/adblock.json
	rm -f $(DESTDIR)$(DATAPREFIX)/licenses/idcac/LICENSE
	rm -f $(DESTDIR)$(DATAPREFIX)/licenses/idcac/UPSTREAM
	rm -f $(DESTDIR)$(MANPREFIX)/man1/surf.1
	for wlib in $(WLIB); do \
	    rm -f $(DESTDIR)$(LIBDIR)/$$wlib; \
	done
	- rmdir $(DESTDIR)$(LIBDIR)
	- rmdir $(DESTDIR)$(DATAPREFIX)/styles
	- rmdir $(DESTDIR)$(DATAPREFIX)/scripts
	- rmdir $(DESTDIR)$(DATAPREFIX)/filters
	- rmdir $(DESTDIR)$(DATAPREFIX)/licenses/idcac
	- rmdir $(DESTDIR)$(DATAPREFIX)/licenses
	- rmdir $(DESTDIR)$(DATAPREFIX)

.PHONY: all options distclean clean dist install uninstall
