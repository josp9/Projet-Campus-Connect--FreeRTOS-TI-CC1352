################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
SYSCFG_SRCS += \
../gpiointerrupt.syscfg 

LDS_SRCS += \
../cc13x2_cc26x2_freertos.lds 

C_SRCS += \
C:/Users/phine/OneDrive/Documents/cJSON-master/cJSON.c \
../gpiointerrupt.c \
./syscfg/ti_devices_config.c \
./syscfg/ti_drivers_config.c \
./syscfg/ti_freertos_config.c \
./syscfg/ti_freertos_portable_config.c \
../main_freertos.c 

GEN_FILES += \
./syscfg/ti_devices_config.c \
./syscfg/ti_drivers_config.c \
./syscfg/ti_freertos_config.c \
./syscfg/ti_freertos_portable_config.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./cJSON.d \
./gpiointerrupt.d \
./syscfg/ti_devices_config.d \
./syscfg/ti_drivers_config.d \
./syscfg/ti_freertos_config.d \
./syscfg/ti_freertos_portable_config.d \
./main_freertos.d 

OBJS += \
./cJSON.o \
./gpiointerrupt.o \
./syscfg/ti_devices_config.o \
./syscfg/ti_drivers_config.o \
./syscfg/ti_freertos_config.o \
./syscfg/ti_freertos_portable_config.o \
./main_freertos.o 

GEN_MISC_FILES += \
./syscfg/ti_drivers_config.h \
./syscfg/ti_utils_build_linker.cmd.genlibs \
./syscfg/syscfg_c.rov.xs \
./syscfg/FreeRTOSConfig.h 

GEN_MISC_DIRS__QUOTED += \
"syscfg\" 

OBJS__QUOTED += \
"cJSON.o" \
"gpiointerrupt.o" \
"syscfg\ti_devices_config.o" \
"syscfg\ti_drivers_config.o" \
"syscfg\ti_freertos_config.o" \
"syscfg\ti_freertos_portable_config.o" \
"main_freertos.o" 

GEN_MISC_FILES__QUOTED += \
"syscfg\ti_drivers_config.h" \
"syscfg\ti_utils_build_linker.cmd.genlibs" \
"syscfg\syscfg_c.rov.xs" \
"syscfg\FreeRTOSConfig.h" 

C_DEPS__QUOTED += \
"cJSON.d" \
"gpiointerrupt.d" \
"syscfg\ti_devices_config.d" \
"syscfg\ti_drivers_config.d" \
"syscfg\ti_freertos_config.d" \
"syscfg\ti_freertos_portable_config.d" \
"main_freertos.d" 

GEN_FILES__QUOTED += \
"syscfg\ti_devices_config.c" \
"syscfg\ti_drivers_config.c" \
"syscfg\ti_freertos_config.c" \
"syscfg\ti_freertos_portable_config.c" 

C_SRCS__QUOTED += \
"C:/Users/phine/OneDrive/Documents/cJSON-master/cJSON.c" \
"../gpiointerrupt.c" \
"./syscfg/ti_devices_config.c" \
"./syscfg/ti_drivers_config.c" \
"./syscfg/ti_freertos_config.c" \
"./syscfg/ti_freertos_portable_config.c" \
"../main_freertos.c" 

SYSCFG_SRCS__QUOTED += \
"../gpiointerrupt.syscfg" 


