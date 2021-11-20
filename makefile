export MAKEFLAGS 	   += --silent
export APPNAME 			= tuxplayer

export ROOTDIR 			= .
export BUILDROOT 		= $(ROOTDIR)/build
export LIBROOT 			= $(ROOTDIR)/build-output

export LIBXOJODIR		= $(ROOTDIR)/libxojo

export CONTROLDIR		= $(ROOTDIR)/control

##
# plugin directories definition
export PLUGINSDKDIR 	= $(ROOTDIR)/PluginsSDK
export SDKGLUECODEDIR 	= $(PLUGINSDKDIR)/GlueCode
export SDKINCLUDEDIR 	= $(PLUGINSDKDIR)/Includes
export PREFIXHEADER 	= $(SDKINCLUDEDIR)/LinuxHeader.h

all: makedir
	$(MAKE) -f linux32.mk
	@echo "******"
	@echo "******"
#	$(MAKE) -f linux64.mk
	@echo "******"
	@echo "DONE."
makedir:
	mkdir -p $(BUILDROOT)
	mkdir -p $(LIBROOT)

clean:
	$(MAKE) -f linux32.mk clean
	$(MAKE) -f linux64.mk clean
