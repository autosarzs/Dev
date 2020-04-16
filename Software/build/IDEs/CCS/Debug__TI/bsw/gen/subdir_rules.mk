################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
bsw/gen/Can_PBcfg.obj: C:/work_set/AUTOSAR/Dev/Software/bsw/gen/Can_PBcfg.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/work_set/AUTOSAR/Dev/Software/bsw/static/COM/CanIf/src" --include_path="C:/work_set/AUTOSAR/Dev/Software/bsw/gen" --include_path="C:/work_set/AUTOSAR/Dev/Software/bsw/static/Infrastructure/inc" --include_path="C:/work_set/AUTOSAR/Dev/Software/bsw/static/Infrastructure/platform/inc" --include_path="C:/work_set/AUTOSAR/Dev/Software/bsw/static/Infrastructure/platform/src" --include_path="C:/work_set/AUTOSAR/Dev/Software/bsw/static/Mcal/CAN/inc" --include_path="C:/work_set/AUTOSAR/Dev/Software/bsw/static/Mcal/CAN/src" --include_path="C:/work_set/AUTOSAR/Dev/Software/bsw/stub" --include_path="C:/work_set/AUTOSAR/Dev/Software/build/IDEs/CCS" --include_path="C:/work_set/AUTOSAR/Dev/Software/bsw/static/COM/CanIf/inc" --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PZ -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="bsw/gen/$(basename $(<F)).d_raw" --obj_directory="bsw/gen" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


