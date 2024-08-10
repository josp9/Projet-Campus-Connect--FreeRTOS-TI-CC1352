################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
cJSON.o: C:/Users/phine/OneDrive/Documents/cJSON-master/cJSON.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/gcc_arm_none_eabi_9_2_1/bin/arm-none-eabi-gcc-9.2.1.exe" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DDeviceFamily_CC13X2 -D_REENT_SMALL -I"C:/Users/phine/workspace_v12/gpiointerrupt_CC1352R1_LAUNCHXL_freertos_gcc" -I"C:/Users/phine/workspace_v12/gpiointerrupt_CC1352R1_LAUNCHXL_freertos_gcc/Debug" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_7_10_02_23/source" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_7_10_02_23/kernel/freertos" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_7_10_02_23/source/ti/posix/gcc" -I"C:/Users/phine/OneDrive/Documents/FreeRTOSv202212.01/FreeRTOS/Source/include" -I"C:/Users/phine/OneDrive/Documents/FreeRTOSv202212.01/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include/newlib-nano" -I"C:/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include" -O3 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/phine/workspace_v12/gpiointerrupt_CC1352R1_LAUNCHXL_freertos_gcc/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/gcc_arm_none_eabi_9_2_1/bin/arm-none-eabi-gcc-9.2.1.exe" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DDeviceFamily_CC13X2 -D_REENT_SMALL -I"C:/Users/phine/workspace_v12/gpiointerrupt_CC1352R1_LAUNCHXL_freertos_gcc" -I"C:/Users/phine/workspace_v12/gpiointerrupt_CC1352R1_LAUNCHXL_freertos_gcc/Debug" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_7_10_02_23/source" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_7_10_02_23/kernel/freertos" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_7_10_02_23/source/ti/posix/gcc" -I"C:/Users/phine/OneDrive/Documents/FreeRTOSv202212.01/FreeRTOS/Source/include" -I"C:/Users/phine/OneDrive/Documents/FreeRTOSv202212.01/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include/newlib-nano" -I"C:/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include" -O3 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/phine/workspace_v12/gpiointerrupt_CC1352R1_LAUNCHXL_freertos_gcc/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1848039839: ../gpiointerrupt.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1_16_2/sysconfig_cli.bat" -s "C:/ti/simplelink_cc13xx_cc26xx_sdk_7_10_02_23/.metadata/product.json" --script "C:/Users/phine/workspace_v12/gpiointerrupt_CC1352R1_LAUNCHXL_freertos_gcc/gpiointerrupt.syscfg" -o "syscfg" --compiler gcc
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_devices_config.c: build-1848039839 ../gpiointerrupt.syscfg
syscfg/ti_drivers_config.c: build-1848039839
syscfg/ti_drivers_config.h: build-1848039839
syscfg/ti_utils_build_linker.cmd.genlibs: build-1848039839
syscfg/syscfg_c.rov.xs: build-1848039839
syscfg/FreeRTOSConfig.h: build-1848039839
syscfg/ti_freertos_config.c: build-1848039839
syscfg/ti_freertos_portable_config.c: build-1848039839
syscfg/: build-1848039839

syscfg/%.o: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/gcc_arm_none_eabi_9_2_1/bin/arm-none-eabi-gcc-9.2.1.exe" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DDeviceFamily_CC13X2 -D_REENT_SMALL -I"C:/Users/phine/workspace_v12/gpiointerrupt_CC1352R1_LAUNCHXL_freertos_gcc" -I"C:/Users/phine/workspace_v12/gpiointerrupt_CC1352R1_LAUNCHXL_freertos_gcc/Debug" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_7_10_02_23/source" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_7_10_02_23/kernel/freertos" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_7_10_02_23/source/ti/posix/gcc" -I"C:/Users/phine/OneDrive/Documents/FreeRTOSv202212.01/FreeRTOS/Source/include" -I"C:/Users/phine/OneDrive/Documents/FreeRTOSv202212.01/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include/newlib-nano" -I"C:/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include" -O3 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"syscfg/$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/phine/workspace_v12/gpiointerrupt_CC1352R1_LAUNCHXL_freertos_gcc/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


