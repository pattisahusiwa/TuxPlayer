VPATH 				= $(BUILDDIR)
vpath %.c	$(CONTROLDIR) $(LIBXOJODIR)
vpath %.cpp $(SDKGLUECODEDIR)


OBJNAME 			= 	PluginMain.o \
						XojoGraphics.o \
						main.o tuxplayer.o \
						definition.o behaviour.o \
						method.o \

INCPLUGIN			= -include $(PREFIXHEADER) -I$(SDKINCLUDEDIR)
INCCONTROL			= -I$(CONTROLDIR) -I$(LIBXOJODIR)
INCLUDES 			= $(INCPLUGIN) $(INCCONTROL)
DEBUGGING_FLAGS		= -g -O0
ifdef PLUGIN_ARCH64
ARCH_FLAGS 			= -m64
else
ARCH_FLAGS 			= -m32 -I/usr/lib32/glib-2.0/include
endif
# Enable Position Independent Code except on Windows where it is the default so the flag produces a warning
ifndef windir
PICFLAGS 			= -fPIC
endif
DEPRECATED			= -DGDK_PIXBUF_DISABLE_DEPRECATED -DGDK_DISABLE_DEPRECATED -DGTK_DISABLE_DEPRECATED -DDISABLE_GDK_FONT
COMPILEFLAGS		= `pkg-config --cflags gtk+-2.0 gstreamer-video-1.0 gstreamer-1.0`
PLUGINFLAGS 		= -DIGNOREQT -D__INTEL__ -DLINUX=1 -D__GCC__

CC 					= codelite-cc gcc
CXX 				= codelite-cc g++
CFLAGS 				= -Wall $(DEBUGGING_FLAGS) $(ARCH_FLAGS) $(PICFLAGS) $(INCLUDES) $(DEPRECATED)
CXXFLAGS 			= --std=c++0x -Wall $(DEBUGGING_FLAGS) $(ARCH_FLAGS) $(PICFLAGS) $(INCLUDES) $(DEPRECATED)
LDLIBS 				= -lstdc++ -lm -lgmodule-2.0 `pkg-config --libs gtk+-2.0 gstreamer-video-1.0 gstreamer-1.0`

$(BUILDDIR)/%.o: %.c
	@echo "----------Compiling $*"
	$(CC) $(CFLAGS) $(PLUGINFLAGS) $(COMPILEFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: %.cpp
	@echo "----------Compiling $*"
	$(CXX) $(CXXFLAGS) $(PLUGINFLAGS) $(COMPILEFLAGS) -c $< -o $@

PLUGIN 				= $(addprefix $(LIBDIR)/, $(APPNAME).so)

all: $(PLUGIN)

$(PLUGIN): $(addprefix $(BUILDDIR)/, $(OBJNAME))
	@echo "----------Building"
	$(CC) $(CFLAGS) $(PLUGINFLAGS) $(COMPILEFLAGS) -shared -Wl,--no-undefined -o $@ $^ $(LDLIBS)
