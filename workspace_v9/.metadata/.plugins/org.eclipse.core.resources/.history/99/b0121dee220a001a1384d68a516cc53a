################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/popi/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/popi/code/workspace_v9/i2ctmp_CC1352R1_LAUNCHXL_tirtos_ccs" --include_path="/home/popi/code/workspace_v9/i2ctmp_CC1352R1_LAUNCHXL_tirtos_ccs/Debug" --include_path="/home/popi/ti/simplelink_cc13x2_26x2_sdk_3_30_00_03/source" --include_path="/home/popi/ti/simplelink_cc13x2_26x2_sdk_3_30_00_03/source/ti/posix/ccs" --include_path="/home/popi/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/include" --define=DeviceFamily_CC13X2 -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="/home/popi/code/workspace_v9/i2ctmp_CC1352R1_LAUNCHXL_tirtos_ccs/Debug/syscfg" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

build-11604369:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-11604369-inproc

build-11604369-inproc: ../i2ctmp.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"/home/popi/ti/ccs920/ccs/utils/sysconfig/sysconfig_cli.sh" -s "/home/popi/ti/simplelink_cc13x2_26x2_sdk_3_30_00_03/.metadata/product.json" -o "syscfg" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_devices_config.c: build-11604369 ../i2ctmp.syscfg
syscfg/ti_drivers_config.c: build-11604369
syscfg/ti_drivers_config.h: build-11604369
syscfg/syscfg_c.rov.xs: build-11604369
syscfg/: build-11604369

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/popi/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/popi/code/workspace_v9/i2ctmp_CC1352R1_LAUNCHXL_tirtos_ccs" --include_path="/home/popi/code/workspace_v9/i2ctmp_CC1352R1_LAUNCHXL_tirtos_ccs/Debug" --include_path="/home/popi/ti/simplelink_cc13x2_26x2_sdk_3_30_00_03/source" --include_path="/home/popi/ti/simplelink_cc13x2_26x2_sdk_3_30_00_03/source/ti/posix/ccs" --include_path="/home/popi/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/include" --define=DeviceFamily_CC13X2 -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="/home/popi/code/workspace_v9/i2ctmp_CC1352R1_LAUNCHXL_tirtos_ccs/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


