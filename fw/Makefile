BUILD_DIR := build_fw

IDF_OPTIONS := --build-dir "$(BUILD_DIR)"

ifneq (, $(shell which ccache))
IDF_OPTIONS += --ccache
endif


## Targets
all: build

build:
	idf.py $(IDF_OPTIONS) build

size:
	idf.py $(IDF_OPTIONS) size

flash:
	idf.py $(IDF_OPTIONS) flash

monitor:
	idf.py $(IDF_OPTIONS) monitor

monitor2:
	miniterm.py /dev/ttyUSB0 115200

clean:
	idf.py $(IDF_OPTIONS) fullclean
	rm -fdr ./build_docs
	rm -fdr ./build_fw
	rm -fdr ./build_tests

reconfigure:
	idf.py $(IDF_OPTIONS) reconfigure

menuconfig:
	idf.py $(IDF_OPTIONS) menuconfig

docs:
	doxygen doxygen.conf

## Tests
FW_SUBPATH = .
include ./tests/tests.mk


.PHONY: all clean build flash monitor reconfigure menuconfig monitor2 size
