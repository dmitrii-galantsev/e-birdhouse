################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/popi/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="/home/popi/code/workspace_v9/rfEasyLinkEchoRx_CC2640R2_LAUNCHXL_nortos_ccs" --include_path="/home/popi/ti/simplelink_cc2640r2_sdk_3_30_00_20/source" --include_path="/home/popi/ti/simplelink_cc2640r2_sdk_3_30_00_20/kernel/nortos" --include_path="/home/popi/ti/simplelink_cc2640r2_sdk_3_30_00_20/kernel/nortos/posix" --include_path="/home/popi/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/include" --define=DeviceFamily_CC26X0R2 --define=SUPPORT_PHY_CUSTOM --define=SUPPORT_PHY_2_4_100KBPS2GFSK --define=SUPPORT_PHY_2_4_250KBPS2GFSK -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


