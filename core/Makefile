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

# Build directory
BUILD_DIR ?= build

# Directories containing source code
SRC_DIRS := minus zero

LLIB := $(BUILD_DIR)/libg0core.a
SRCS := $(shell find $(SRC_DIRS) -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
UNITS := $(patsubst %.c,${BUILD_DIR}/%,$(wildcard unit/ctest_*.c))

# list of includes from kernels
KERN_INC_DIRS = $(shell find kernels -type d)
KERN_INCLUDES = $(addprefix -I,$(KERN_INC_DIRS))
INCS := -Iminus -Iminus/STC/include -Izero $(KERN_INCLUDES)

EXEC_LIB_DIRS = 
EXEC_EXT_LIBS = -lm -lpthread -ldl
EXEC_LIBS = -Lbuild ${LLIB} ${EXEC_EXT_LIBS}

unit: $(LLIB) $(UNITS) ## Build unit tests

.PHONY: all
all: unit $(LLIB) ## Build all targets
.DEFAULT_GOAL := all

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) -c $(CFLAGS) $(INCS) $< -o $@

# Unit tests
$(UNITS): ${BUILD_DIR}/unit/%: unit/%.c $(LLIB)
	$(MKDIR_P) ${BUILD_DIR}/unit
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $< -I. $(INCS) ${EXEC_LIB_DIRS} ${EXEC_LIBS}

# build lib
$(LLIB): $(OBJS)
	$(MKDIR_P) $(dir $@)
	ar -crs $@ $(OBJS)

.PHONY: check
# Run all unit tests
check: ${UNITS} ## Build (if needed) and run all unit tests
	$(foreach unit,${UNITS},echo $(unit); $(unit) -E;)

-include $(DEPS)

.PHONY: clean
clean: ## Clean build output
	rm -rf ${BUILD_DIR}

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
