include Makefile.variable

CMAKE_VARIABLES := \
	-DCMAKE_TOOLCHAIN_FILE=$(CMAKE_PROJECT_DIR)/toolchain.cmake \
	-DTOOLCHAIN=$(TOOLCHAIN)

autosar:
ifeq ($(rebuild),1)
	-@rm -rf $(BUILD_DIR)
endif
	@mkdir -p $(BUILD_DIR)
	@echo "BUILD_DIR=$(BUILD_DIR)"
	cd $(BUILD_DIR)/ && \
	cmake -G "Unix Makefiles" -S $(CMAKE_PROJECT_DIR) -B $(BUILD_DIR) $(CMAKE_VARIABLES) && \
	make AutosarApp install -j$(MAXIMUM_CPU_CORES)
