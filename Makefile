
IDRIS2CMD=idris2

INSTALL_PREFIX=`${IDRIS2CMD} --libdir`


SHLIBSUFFIX = .so
UNAME_S := $(shell uname -s)
ifeq (${UNAME_S},Darwin)
    SHLIBSUFFIX = .dylib
endif

.PHONY: all idris2 support clean

all: support ${TARGET}

all : support idris2Coronado

support :
	@${MAKE} -C support/refc SHLIB_SUFFIX=${SHLIBSUFFIX}
	@${MAKE} -C support/c  SHLIB_SUFFIX=${SHLIBSUFFIX}

idris2Coronado :
	${IDRIS2CMD} -p idris2 -p contrib -p network RefCCoronado.idr -o idris2-coronado

clean:
	rm -rf build
	@${MAKE} -C support/refc clean
	@${MAKE} -C support/c clean



install:
	mkdir -p ${INSTALL_PREFIX}/lib
	mkdir -p ${INSTALL_PREFIX}/support/c
	install -m 755 support/c/lib*${SHLIBSUFFIX}   ${INSTALL_PREFIX}/lib
	install -m 644 support/c/lib*.a                   ${INSTALL_PREFIX}/lib
	install -m 644 support/refc/lib*.a                ${INSTALL_PREFIX}/lib
	install -m 644 support/c/*.h                      ${INSTALL_PREFIX}/support/c
