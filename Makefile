# -*- makefile-gmake -*-

# Type make help to see help for this Makefile

# determine date of build
BUILD_DATE = $(shell date)
GIT_TIP = $(shell git describe --abbrev=12 --always --dirty=+)

# Build directory
BUILD_DIR ?= build

ARCH_FLAGS ?= -march=native
CFLAGS ?= -O3 -g -ffast-math -fPIC -MMD -MP -DGIT_COMMIT_ID=\"$(GIT_TIP)\" -DGKYL_BUILD_DATE="${BUILD_DATE}" -DGKYL_GIT_CHANGESET="${GIT_TIP}"
LDFLAGS = 
PREFIX ?= ${HOME}/gkylsoft
INSTALL_PREFIX ?= ${PREFIX}

# determine OS we are running on
UNAME = $(shell uname)

# command to make dir
MKDIR_P ?= mkdir -p

# include config.mak file (if it exists) to overide defaults above
-include config.mak

# at this point, export all top-level variables to sub-makes and
# recurse downwards

.EXPORT_ALL_VARIABLES:

# Core directory targets
.PHONY: core core-clean core-check core-valcheck
core:  ## Build core infrastructure code
	cd core && $(MAKE) -f Makefile-core

core-clean: ## Only clean core infrastructure code
	cd core && $(MAKE) -f Makefile-core clean

core-check: ## Only run unit tests in core
	cd core && $(MAKE) -f Makefile-core check

core-valcheck: ## Only run valgrind on unit tests in core
	cd core && $(MAKE) -f Makefile-core valcheck

# Clean everything
.PHONY: clean
clean: ## Clean all builds
	cd core && $(MAKE) -f Makefile-core clean

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
