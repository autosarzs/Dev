include Makefile.variable

CMAKE_VARIABLES =
CMAKE_VARIABLES += -DCMAKE_TOOLCHAIN_FILE=$(CMAKE_PROJECT_DIR)/toolchain.cmake
CMAKE_VARIABLES += -DTOOLCHAIN=$(TOOLCHAIN)
CMAKE_VARIABLES += -DCMAKE_PROJECT_DIR=$(CMAKE_PROJECT_DIR)
CMAKE_VARIABLES += -DSW_DIR=$(SW_DIR)

autosar:
ifeq ($(rebuild),1)
	-@rm -rf $(BUILD_DIR)
endif
	@mkdir -p $(BUILD_DIR)
	@echo "BUILD_DIR=$(BUILD_DIR)"
	cd $(BUILD_DIR)/ && \
	cmake -G "Unix Makefiles" -S $(CURDIR) -B $(BUILD_DIR) $(CMAKE_VARIABLES) ;\
	make app_swc install -j$(MAXIMUM_CPU_CORES)
