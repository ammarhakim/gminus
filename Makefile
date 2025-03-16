# -*- makefile-gmake -*-

# Type "make help" to see help for this Makefile

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
PROJ_NAME ?= greorg

# Determine OS we are running on
UNAME = $(shell uname)

# Default lapack include and libraries: we prefer linking to static library
LAPACK_INC = $(PREFIX)/OpenBLAS/include
LAPACK_LIB_DIR = $(PREFIX)/OpenBLAS/lib
LAPACK_LIB = -lopenblas

# On OSX we should use Accelerate framework
ifeq ($(UNAME), Darwin)
	LAPACK_LIB_DIR = .
	LAPACK_INC = core # dummy
	LAPACK_LIB = -framework Accelerate
	CFLAGS += -DGKYL_USING_FRAMEWORK_ACCELERATE
endif

# Include config.mak file (if it exists) to overide defaults above
-include config.mak

# MPI paths and flags
USING_MPI =
MPI_RPATH = 
MPI_INC_DIR = core # dummy
MPI_LIB_DIR = .
ifeq (${USE_MPI}, 1)
	USING_MPI = yes
	MPI_INC_DIR = ${CONF_MPI_INC_DIR}
	MPI_LIB_DIR = ${CONF_MPI_LIB_DIR}

ifdef USING_NVCC
	MPI_RPATH = -Xlinker "-rpath,${CONF_MPI_LIB_DIR}"
else
	MPI_RPATH = -Wl,-rpath,${CONF_MPI_LIB_DIR}
endif

	MPI_LIBS = -lmpi
	CFLAGS += -DGKYL_HAVE_MPI
endif

# LUA paths and flags
USING_LUA =
LUA_RPATH = 
LUA_INC_DIR = core # dummy
LUA_LIB_DIR = .
ifeq (${USE_LUA}, 1)
	USING_LUA = yes
	LUA_INC_DIR = ${CONF_LUA_INC_DIR}
	LUA_LIB_DIR = ${CONF_LUA_LIB_DIR}

ifdef USING_NVCC
	LUA_RPATH = -Xlinker "-rpath,${CONF_LUA_LIB_DIR}"
else
	LUA_RPATH = -Wl,-rpath,${CONF_LUA_LIB_DIR}
endif

	LUA_LIBS = -l${CONF_LUA_LIB}
	CFLAGS += -DGKYL_HAVE_LUA
endif

# Command to make dir
MKDIR_P ?= mkdir -p

# At this point, export all top-level variables to sub-makes and
# recurse downwards

.EXPORT_ALL_VARIABLES:

all: core

## Core infrastructure targets
.PHONY: core core-unit core-clean core-install core-check core-valcheck
core:  ## Build core infrastructure code
	cd core && $(MAKE) -f Makefile-core

core-unit: ## Build core unit tests
	cd core && $(MAKE) -f Makefile-core unit

core-install: ## Install core infrastructure code
	cd core && $(MAKE) -f Makefile-core install
	test -e config.mak && cp -f config.mak ${INSTALL_PREFIX}/${PROJ_NAME}/share/config.mak || echo "No config.mak"

core-clean: ## Clean core infrastructure code
	cd core && $(MAKE) -f Makefile-core clean

core-check: ## Run unit tests in core
	cd core && $(MAKE) -f Makefile-core check

core-valcheck: ## Run valgrind on unit tests in core
	cd core && $(MAKE) -f Makefile-core valcheck

## Moments infrastructure targets
.PHONY: moments moments-unit moments-install moments-clean moments-check moments-valcheck
moments: core  ## Build moments infrastructure code
	cd moments && $(MAKE) -f Makefile-moments

moments-unit: moments ## Build moments unit tests
	cd moments && $(MAKE) -f Makefile-moments unit

moments-regression: moments ## Build moments regression tests
	cd moments && $(MAKE) -f Makefile-moments regression

moments-install: core-install ## Install moments infrastructure code
	cd moments && $(MAKE) -f Makefile-moments install

moments-clean: ## Clean moments infrastructure code
	cd moments && $(MAKE) -f Makefile-moments clean

moments-check: ## Run unit tests in moments
	cd moments && $(MAKE) -f Makefile-moments check

moments-valcheck: ## Run valgrind on unit tests in moments
	cd moments && $(MAKE) -f Makefile-moments valcheck


## Targets to build things all parts of the code

# build all unit tests 
.PHONY: unit 
unit: core-unit ## Build all unit tests

# build all regression tests 
.PHONY: regression
regression: moments-regression ## Build all regression tests

# Install everything
.PHONY: install 
install: core-install moments-install ## Install all code

# Clean everything
.PHONY: clean 
clean: core-clean moments-clean  ## Clean all builds

# Check everything
.PHONY: check
check: core-check moments-check ## Run all unit tests

# From: https://www.client9.com/self-documenting-makefiles/
.PHONY: help
help: ## Show help
	@echo "Gkeyll Makefile help. You can set parameters on the command line:"
	@echo ""
	@echo "make CC=cc -j"
	@echo ""
	@echo "Or run the configure script to set various parameters. Usually"
	@echo "defaults are all you need, specially if the dependencies are in"
	@echo "${HOME}/gkylsoft and you are using standard compilers (not building on GPUs)."
	@echo ""
	@echo "See ./configure --help for usage of configure script."
	@echo ""
	@echo "You can build only portions of the code using the specific targers below."
	@echo "Typing \"make all\" will build the complete code"
	@echo ""
	@awk -F ':|##' '/^[^\t].+?:.*?##/ {\
        printf "\033[36m%-30s\033[0m %s\n", $$1, $$NF \
        }' $(MAKEFILE_LIST)
