################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /home/popi/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./CC2640R2_LAUNCHXL.obj" \
"./CC2640R2_LAUNCHXL_fxns.obj" \
"./ccfg.obj" \
"./main_nortos.obj" \
"./rfEasyLinkEchoRx_nortos.obj" \
"./easylink/EasyLink_nortos.obj" \
"./easylink/easylink_config.obj" \
"./smartrf_settings/smartrf_settings.obj" \
"./smartrf_settings/smartrf_settings_predefined.obj" \
"../CC2640R2_LAUNCHXL_NoRTOS.cmd" \
$(GEN_CMDS__FLAG) \
-l"ti/display/lib/display.aem3" \
-l"ti/grlib/lib/ccs/m3/grlib.a" \
-l"third_party/spiffs/lib/ccs/m3/spiffs_cc26xx.a" \
-l"ti/drivers/rf/lib/rf_multiMode_cc26x0r2.aem3" \
-l"ti/drivers/lib/drivers_cc26x0r2.aem3" \
-l"lib/nortos_cc26x0r2.aem3" \
-l"ti/devices/cc26x0r2/driverlib/bin/ccs/driverlib.lib" \
-llibc.a \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include easylink/subdir_vars.mk
-include smartrf_settings/subdir_vars.mk
-include subdir_rules.mk
-include easylink/subdir_rules.mk
-include smartrf_settings/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
rfEasyLinkEchoRx_CC2640R2_LAUNCHXL_nortos_ccs.out \

EXE_OUTPUTS__QUOTED += \
"rfEasyLinkEchoRx_CC2640R2_LAUNCHXL_nortos_ccs.out" \

BIN_OUTPUTS += \
rfEasyLinkEchoRx_CC2640R2_LAUNCHXL_nortos_ccs.hex \

BIN_OUTPUTS__QUOTED += \
"rfEasyLinkEchoRx_CC2640R2_LAUNCHXL_nortos_ccs.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "rfEasyLinkEchoRx_CC2640R2_LAUNCHXL_nortos_ccs.out"

# Tool invocations
rfEasyLinkEchoRx_CC2640R2_LAUNCHXL_nortos_ccs.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"/home/popi/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --define=DeviceFamily_CC26X0R2 --define=SUPPORT_PHY_CUSTOM --define=SUPPORT_PHY_2_4_100KBPS2GFSK --define=SUPPORT_PHY_2_4_250KBPS2GFSK -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on -z -m"rfEasyLinkEchoRx_CC2640R2_LAUNCHXL_nortos_ccs.map" -i"/home/popi/ti/simplelink_cc2640r2_sdk_3_30_00_20/source" -i"/home/popi/ti/simplelink_cc2640r2_sdk_3_30_00_20/kernel/nortos" -i"/home/popi/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/lib" --diag_wrap=off --display_error_number --warn_sections --xml_link_info="rfEasyLinkEchoRx_CC2640R2_LAUNCHXL_nortos_ccs_linkInfo.xml" --rom_model -o "rfEasyLinkEchoRx_CC2640R2_LAUNCHXL_nortos_ccs.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

rfEasyLinkEchoRx_CC2640R2_LAUNCHXL_nortos_ccs.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"/home/popi/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armhex"  -o "rfEasyLinkEchoRx_CC2640R2_LAUNCHXL_nortos_ccs.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "CC2640R2_LAUNCHXL.obj" "CC2640R2_LAUNCHXL_fxns.obj" "ccfg.obj" "main_nortos.obj" "rfEasyLinkEchoRx_nortos.obj" "easylink/EasyLink_nortos.obj" "easylink/easylink_config.obj" "smartrf_settings/smartrf_settings.obj" "smartrf_settings/smartrf_settings_predefined.obj" 
	-$(RM) "CC2640R2_LAUNCHXL.d" "CC2640R2_LAUNCHXL_fxns.d" "ccfg.d" "main_nortos.d" "rfEasyLinkEchoRx_nortos.d" "easylink/EasyLink_nortos.d" "easylink/easylink_config.d" "smartrf_settings/smartrf_settings.d" "smartrf_settings/smartrf_settings_predefined.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

