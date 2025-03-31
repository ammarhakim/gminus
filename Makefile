# -*- makefile-gmake -*-

# Type "make help" to see help for this Makefile

# determine date of build
BUILD_DATE = $(shell date)
GIT_TIP = $(shell git describe --abbrev=12 --always --dirty=+)

# Build directory
BUILD_DIR ?= ../build

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

# Directory for storing shared data, like ADAS reaction rates and radiation fits
GKYL_SHARE_DIR ?= "${INSTALL_PREFIX}/${PROJ_NAME}/share"
CFLAGS += -DGKYL_SHARE_DIR=$(GKYL_SHARE_DIR)

# Read ADAS paths and flags if needed 
USING_ADAS =
ADAS_INC_DIR = zero # dummy
ADAS_LIB_DIR = .
ifeq (${USE_ADAS}, 1)
	USING_ADAS = yes
	CFLAGS += -DGKYL_HAVE_ADAS
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

all: core moments vlasov gyrokinetic pkpm
	${MKDIR_P} ${INSTALL_PREFIX}/${PROJ_NAME}/share/adas
	cp ./data/adas/radiation_fit_parameters.txt ${INSTALL_PREFIX}/${PROJ_NAME}/share/adas

## Core infrastructure targets
.PHONY: core core-unit core-clean core-install core-check core-valcheck core-regression
core:  ## Build core infrastructure code
	cd core && $(MAKE) -f Makefile-core

core-unit: ## Build core unit tests
	cd core && $(MAKE) -f Makefile-core unit

core-regression: ## Build core regression tests
	cd core && $(MAKE) -f Makefile-core regression

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
.PHONY: moments moments-unit moments-install moments-clean moments-check moments-valcheck moments-regression
moments: core  ## Build moments infrastructure code
	cd moments && $(MAKE) -f Makefile-moments

moments-unit: moments ## Build moments unit tests
	cd moments && $(MAKE) -f Makefile-moments unit

moments-regression: moments ## Build moments regression tests
	cd moments && $(MAKE) -f Makefile-moments regression

moments-amr-regression: moments ## Build moments AMR regression tests
	cd moments && $(MAKE) -f Makefile-moments amr_regression

moments-install: core-install ## Install moments infrastructure code
	cd moments && $(MAKE) -f Makefile-moments install

moments-clean: ## Clean moments infrastructure code
	cd moments && $(MAKE) -f Makefile-moments clean

moments-check: ## Run unit tests in moments
	cd moments && $(MAKE) -f Makefile-moments check

moments-valcheck: ## Run valgrind on unit tests in moments
	cd moments && $(MAKE) -f Makefile-moments valcheck

## Vlasov infrastructure targets
.PHONY: vlasov vlasov-unit vlasov-install vlasov-clean vlasov-check vlasov-valcheck vlasov-regression
vlasov: moments  ## Build Vlasov infrastructure code
	cd vlasov && $(MAKE) -f Makefile-vlasov

vlasov-unit: vlasov ## Build Vlasov unit tests
	cd vlasov && $(MAKE) -f Makefile-vlasov unit

vlasov-regression: vlasov ## Build Vlasov regression tests
	cd vlasov && $(MAKE) -f Makefile-vlasov regression

vlasov-install: moments-install ## Install Vlasov infrastructure code
	cd vlasov && $(MAKE) -f Makefile-vlasov install

vlasov-clean: ## Clean Vlasov infrastructure code
	cd vlasov && $(MAKE) -f Makefile-vlasov clean

vlasov-check: ## Run unit tests in Vlasov
	cd vlasov && $(MAKE) -f Makefile-vlasov check

vlasov-valcheck: ## Run valgrind on unit tests in Vlasov
	cd vlasov && $(MAKE) -f Makefile-vlasov valcheck

## Gyrokinetic infrastructure targets
.PHONY: gyrokinetic gyrokinetic-unit gyrokinetic-install gyrokinetic-clean gyrokinetic-check gyrokinetic-valcheck gyrokinetic-regression
gyrokinetic: vlasov  ## Build Gyrokinetic infrastructure code
	cd gyrokinetic && $(MAKE) -f Makefile-gyrokinetic

gyrokinetic-unit: gyrokinetic ## Build Gyrokinetic unit tests
	cd gyrokinetic && $(MAKE) -f Makefile-gyrokinetic unit

gyrokinetic-regression: gyrokinetic ## Build Gyrokinetic regression tests
	cd gyrokinetic && $(MAKE) -f Makefile-gyrokinetic regression

gyrokinetic-install: vlasov-install ## Install Gyrokinetic infrastructure code
	cd gyrokinetic && $(MAKE) -f Makefile-gyrokinetic install

gyrokinetic-clean: ## Clean Gyrokinetic infrastructure code
	cd gyrokinetic && $(MAKE) -f Makefile-gyrokinetic clean

gyrokinetic-check: ## Run unit tests in Gyrokinetics
	cd gyrokinetic && $(MAKE) -f Makefile-gyrokinetic check

gyrokinetic-valcheck: ## Run valgrind on unit tests in Gyrokinetics
	cd gyrokinetic && $(MAKE) -f Makefile-gyrokinetic valcheck

## PKPM infrastructure targets
.PHONY: pkpm pkpm-unit pkpm-install pkpm-clean pkpm-check pkpm-valcheck pkpm-regression
pkpm: gyrokinetic  ## Build PKPM infrastructure code
	cd pkpm && $(MAKE) -f Makefile-pkpm

pkpm-unit: pkpm ## Build PKPM unit tests
	cd pkpm && $(MAKE) -f Makefile-pkpm unit

pkpm-regression: pkpm ## Build PKM regression tests
	cd pkpm && $(MAKE) -f Makefile-pkpm regression

pkpm-install: gyrokinetic-install ## Install PKPM infrastructure code
	cd pkpm && $(MAKE) -f Makefile-pkpm install

pkpm-clean: ## Clean PKPM infrastructure code
	cd pkpm && $(MAKE) -f Makefile-pkpm clean

pkpm-check: ## Run unit tests in PKPM
	cd pkpm && $(MAKE) -f Makefile-pkpm check

pkpm-valcheck: ## Run valgrind on unit tests in PKPM
	cd pkpm && $(MAKE) -f Makefile-pkpm valcheck

## Targets to build things all parts of the code

# build all unit tests 
.PHONY: unit
unit: core-unit moments-unit vlasov-unit gyrokinetic-unit pkpm-unit ## Build all unit tests

# build all regression tests 
.PHONY: regression
regression: core-regression moments-regression vlasov-regression gyrokinetic-regression pkpm-regression ## Build all regression tests

# Install everything
.PHONY: install 
install: core-install moments-install vlasov-install gyrokinetic-install pkpm-install ## Install all code

# Clean everything
.PHONY: clean 
clean: core-clean moments-clean vlasov-clean gyrokinetic-clean pkpm-clean ## Clean all builds

# Check everything
.PHONY: check
check: core-check moments-check vlasov-check gyrokinetic-check pkpm-check ## Run all unit tests

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
