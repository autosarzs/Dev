include Makefile.variable

##############################################################################
# Build                                                                      #
##############################################################################

CMAKE_BUILD_VARIABLES =
CMAKE_BUILD_VARIABLES += -DCMAKE_TOOLCHAIN_FILE=$(CMAKE_PROJECT_DIR)/build_toolchain.cmake
CMAKE_BUILD_VARIABLES += -DTOOLCHAIN_DIR=$(TOOLCHAIN_DIR)
CMAKE_BUILD_VARIABLES += -DCMAKE_PROJECT_DIR=$(CMAKE_PROJECT_DIR)
CMAKE_BUILD_VARIABLES += -DSW_DIR=$(SW_DIR)
CMAKE_BUILD_VARIABLES += -DMODE=COMPILING

build:
ifeq ($(rebuild),1)
	-@rm -rf $(BUILD_DIR)
endif
	@mkdir -p $(BUILD_DIR)
	@echo "BUILD_DIR=$(BUILD_DIR)"
	cd $(BUILD_DIR)/ && \
	cmake -S $(CURDIR) -B $(BUILD_DIR) $(CMAKE_BUILD_VARIABLES) ;\
 	make app_swc install -j$(MAXIMUM_CPU_CORES)

##############################################################################
# Test                                                                       #
##############################################################################

CMAKE_TEST_VARIABLES =
CMAKE_TEST_VARIABLES += -DCMAKE_TOOLCHAIN_FILE=$(CMAKE_PROJECT_DIR)/test_toolchain.cmake
CMAKE_TEST_VARIABLES += -DCMAKE_PROJECT_DIR=$(CMAKE_PROJECT_DIR)
CMAKE_TEST_VARIABLES += -DSW_DIR=$(SW_DIR)
CMAKE_TEST_VARIABLES += -DMODE=TESTING


# Test directories
TEST_DIRS := $(wildcard $(BUILD_TESTS_DIR)/software/*/*/*)

# Find test programs
TEST_PROGRAMS := $(foreach dir,$(TEST_DIRS),$(wildcard $(dir)/*_test))


unit_test:
	@make build_test
	@make test 
	@echo "--------- FINISH -------"

build_test:
ifeq ($(rebuild),1)
	-@rm -rf $(BUILD_TESTS_DIR)
endif
	@mkdir -p $(BUILD_TESTS_DIR)
	@echo "BUILD_DIR=$(BUILD_TESTS_DIR)"
	cd $(BUILD_TESTS_DIR)/ && \
	cmake -S $(CURDIR) -B $(BUILD_TESTS_DIR) $(CMAKE_TEST_VARIABLES)  ;\
	make -j$(MAXIMUM_CPU_CORES) ;\

test: $(TEST_PROGRAMS)
	@echo "Running all test programs"
	@for program in $^; do \
		echo "-----------------------";\
		echo "Running $$program"; \
		$$program -v | sed -E 's#.*\.c:[0-9]+:TEST\(([^)]+)\)#TEST(\1)#g; s#/workspace/software/bsw/mcal/unity_swc/tests/##g'; \
	done

all: build unit_test

.PHONY: build unit_test test all
