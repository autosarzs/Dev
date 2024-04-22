include Makefile.variable

CMAKE_VARIABLES =
CMAKE_VARIABLES += -DCMAKE_TOOLCHAIN_FILE=$(CMAKE_PROJECT_DIR)/toolchain.cmake
CMAKE_VARIABLES += -DTOOLCHAIN=$(TOOLCHAIN)
CMAKE_VARIABLES += -DCMAKE_PROJECT_DIR=$(CMAKE_PROJECT_DIR)
CMAKE_VARIABLES += -DSW_DIR=$(SW_DIR)

build:
ifeq ($(rebuild),1)
	-@rm -rf $(BUILD_DIR)
endif
	@mkdir -p $(BUILD_DIR)
	@echo "BUILD_DIR=$(BUILD_DIR)"
	cd $(BUILD_DIR)/ && \
	cmake -G "Unix Makefiles" -S $(CURDIR) -B $(BUILD_DIR) $(CMAKE_VARIABLES) ;\
	make app_swc install -j$(MAXIMUM_CPU_CORES)

unit_test:
	(cd $(BUILD_DIR) && \
		ctest --verbose --output-on-failure --output-junit test_results.xml . && \
		junit2html test_results.xml test_results.html)
	mkdir -p $(UNIT_TESTS_INSTALL_DIR)
	cp $(BUILD_DIR)/test_results.xml $(UNIT_TESTS_INSTALL_DIR)/
	cp $(BUILD_DIR)/test_results.html $(UNIT_TESTS_INSTALL_DIR)/
