include Makefile.variable


##############################################################################
# Shell Colors                                                               #
##############################################################################
UND=\e[4m
CUR=\e[3m
NC=\033[0m

ERROR=\033[0;31m
INFO=\033[32m
WARNING=\033[92m
HEADRS=$(UND)$(CUR)

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
CMAKE_TEST_VARIABLES += -DBUILD_TESTS_DIR=$(BUILD_TESTS_DIR)


# Test directories
TEST_DIRS := $(wildcard $(BUILD_TESTS_DIR)/software/*/*/*)

# Find test programs
TEST_PROGRAMS := $(foreach dir,$(TEST_DIRS),$(wildcard $(dir)/*_test))


unit_test:
ifeq ($(rebuild),1)
	-@rm -rf $(BUILD_TESTS_DIR)
	-@rm -rf $(UNIT_TESTS_INSTALL_DIR)
endif
	@rm -f $(UNIT_TESTS_INSTALL_DIR)/test_results.txt 
	@make check_dependencies
	@make build_test
	@make test
	@make coverage
	@echo ""
	@echo "${HEADRS}--------- TEST SUMMERY -------${NC}"
	@ruby $(UNITY_ROOT)/auto/parse_output.rb -xml $(UNIT_TESTS_INSTALL_DIR)/test_results.txt
	@mv $(WORKSPACE_DIR)/report.xml $(UNIT_TESTS_INSTALL_DIR)/test_results.xml


##############################################################################
# Build Test files                                                           #
##############################################################################
build_test:
	@mkdir -p $(BUILD_TESTS_DIR)
	@echo "BUILD_DIR=$(BUILD_TESTS_DIR)"
	cd $(BUILD_TESTS_DIR)/ && \
	cmake -S $(CURDIR) -B $(BUILD_TESTS_DIR) $(CMAKE_TEST_VARIABLES)  ;\
	make -j$(MAXIMUM_CPU_CORES) ;


test: $(TEST_PROGRAMS)
	@echo ""
	@echo "${HEADRS}Running all test programs${NC}"
	@echo ""
	@mkdir -p $(UNIT_TESTS_INSTALL_DIR)
	@for program in $^; do \
		echo "-----------------------";\
		echo "Running $$program"; \
		$$program -v | sed -E 's#.*\.c:[0-9]+:TEST\(([^)]+)\)#TEST(\1)#g; s#/workspace/software/bsw/mcal/unity_swc/tests/##g' | tee -a $(UNIT_TESTS_INSTALL_DIR)/test_results.txt; \
	done;

##############################################################################
# Check Dependencies                                                        #
##############################################################################
check_dependencies:
	@ruby --version ;\
	if [ $$? -ne 0 ]; \
    then \
		make error_msg ;\
        false; \
    fi
	
	@gcovr --version ;\
	if [ $$? -ne 0 ]; \
	then \
		make error_msg ;\
		false ; \
	fi

error_msg:
	@echo "--------------------------------------------------------------------------------------------------------------------------------"
	@echo "${ERROR}Your dev container run out of data.${NC}"
	@echo "--------------------------------------"
	@echo "    1. Remove the Docker container using the command: ${INFO}docker rm -f mycontainer $(shell cat /etc/hostname)${NC}"
	@echo "If any of the above steps fail, please check your setup and try again."
	@echo "--------------------------------------------------------------------------------------------------------------------------------"

##############################################################################
# Coverage                                                                   #
##############################################################################
# Search Path
GCOVR_INCLUDE_PATHS := '.*/core/.*'
# Options: {green,blue,github.blue,github.green,github.dark-green,github.dark-blue}
HTML_THEME ?= github.green

coverage:
	@echo ""
	@echo "${HEADRS}Generate Coverage Reports${NC}"
	@echo ""
	@mkdir -p $(UNIT_TESTS_INSTALL_DIR)/html
	@cd $(WORKSPACE_DIR) ;\
	gcovr -r . --filter ${GCOVR_INCLUDE_PATHS} \
	--html-self-contained \
	--html-theme ${HTML_THEME} \
	--html-nested \
	--cobertura \
	--html=$(UNIT_TESTS_INSTALL_DIR)/html/test_report.html \
	--xml=$(UNIT_TESTS_INSTALL_DIR)/test_report.xml \
	-j$(MAXIMUM_CPU_CORES);

##############################################################################
# help                                                                       #
##############################################################################
help:
	@echo ""
	@echo "${HEADRS}Available targets:${NC}"
	@echo "  build        - Generate executable files for the target MCU."
	@echo "  unit_test    - Run unit tests of project components."
	@echo "  build_test   - Sub-process from ${HEADRS}unit_test${NC} to build test files only."
	@echo "  test         - Sub-process from ${HEADRS}unit_test${NC} to execute pre-built test files."
	@echo "  coverage     - Sub-process from ${HEADRS}unit_test${NC} to generate coverage files only."
	@echo ""
	@echo "${HEADRS}Available Options:${NC}"
	@echo "  rebuild=1           - It will rebuild whole project (valid for build and unit_test only)."
	@echo "                      - ${HEADRS}Options${NC}: {0,1}"
	@echo "                      - ${HEADRS}Defailt Value${NC}: 0"
	@echo ""
	@echo "  HTML_THEME=green    - It will generate html with selected theme (valid for coverage and unit_test only)."
	@echo "                      - ${HEADRS}Options${NC}: {green,blue,github.blue,github.green,github.dark-green,github.dark-blue}"
	@echo "                      - ${HEADRS}Defailt Value${NC}: github.green"
	@echo ""
	@echo "${HEADRS}Use${NC}: make ${INFO}<target> <Option1> <Option2> ...${NC} "
	@echo ""


all: build unit_test

.PHONY: build unit_test test all check_dependencies coverage
