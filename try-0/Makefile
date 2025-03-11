# -*- makefile-gmake -*-

# Type make help to see help for this Makefile

# determine date of build
BUILD_DATE = $(shell date)
GIT_TIP = $(shell git describe --abbrev=12 --always --dirty=+)

ARCH_FLAGS ?= -march=native
CFLAGS ?= -O3 -g -ffast-math -fPIC -MMD -MP -DGIT_COMMIT_ID=\"$(GIT_TIP)\" -DGKYL_BUILD_DATE="${BUILD_DATE}" -DGKYL_GIT_CHANGESET="${GIT_TIP}"
LDFLAGS = 
PREFIX ?= ${HOME}/gkylsoft
INSTALL_PREFIX ?= ${PREFIX}

# determine OS we are running on
UNAME = $(shell uname)

# Include config.mak file (if it exists) to overide defaults above
-include config.mak

.PHONY: all
all: core
.DEFAULT_GOAL := all

# Core library and code
core: ## Build core infrastructure library 
	$(MAKE) -C core

# command to make dir
MKDIR_P ?= mkdir -p

# From: https://www.client9.com/self-documenting-makefiles/
.PHONY: help
help: ## Show help
	@echo "GkylZero Makefile help. You can set parameters on the command line:"
	@echo ""
	@echo "make CC=nvcc -j"
	@echo ""
	@echo "Or run the configure script to set various parameters. Usually"
	@echo "defaults are all you need, specially if the dependencies are in"
	@echo "${HOME}/gkylsoft and you are using standard compilers (not building on GPUs)"
	@echo ""
	@echo "See ./configure --help for usage of configure script"
	@echo ""
	@awk -F ':|##' '/^[^\t].+?:.*?##/ {\
        printf "\033[36m%-30s\033[0m %s\n", $$1, $$NF \
        }' $(MAKEFILE_LIST)
