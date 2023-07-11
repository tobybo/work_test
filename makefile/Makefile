PLAT ?= none
PLATS = linux freebsd macosx

CC ?= gcc

.PHONY : none $(PLATS) clean all cleanall

#ifneq ($(PLAT), none)

.PHONY : default

default :
	@echo $(PLAT)

#endif

none :
	@echo "Please do 'make PLATFORM' where PLATFORM is one of these:"
	@echo "   $(PLATS)"

PLAT1=13

linux : PLAT = 10
linux: PLAT1 = 12
macosx : PLAT1 = macosx
freebsd : PLAT = freebsd
linux all : PLAT = 11

PLAT=14

linux:
	@echo "$(PLAT)"
	@echo "$(PLAT1)"

all: all1

all1:
	@echo all1

