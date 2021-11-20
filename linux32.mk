export PLUGIN_ARCH32 	= 32
export BUILDDIR 		= $(BUILDROOT)/Linux-X86
export LIBDIR 			= $(LIBROOT)/Linux-X86

all: makedir
	@echo "***Building plugin:[ tuxplayer - linux-x86 release ]***"
	$(MAKE) -f makeplugin-linux.mk

makedir:
	mkdir -p $(BUILDDIR)
	mkdir -p $(LIBDIR)

clean:
	rm -rvf $(BUILDDIR)/*.o
	rm -rvf $(LIBDIR)/*.so
