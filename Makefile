
IDRIS2CMD=idris2

.PHONY: all idris2 support clean

all: support ${TARGET}

all : support idris2Coronado

support :
	@${MAKE} -C support/refc
	@${MAKE} -C support/c

idris2Coronado :
	${IDRIS2CMD} -p idris2 -p contrib -p network RefCCoronado.idr -o idris2-coronado

clean:
	rm -rf build
	@${MAKE} -C support/refc clean
	@${MAKE} -C support/c clean
