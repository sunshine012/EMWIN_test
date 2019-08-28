################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../emwin_548/emwin_config/GUIConf.c" \
"../emwin_548/emwin_config/GUI_X.c" \
"../emwin_548/emwin_config/LCDConf.c" \

C_SRCS += \
../emwin_548/emwin_config/GUIConf.c \
../emwin_548/emwin_config/GUI_X.c \
../emwin_548/emwin_config/LCDConf.c \

OBJS += \
./emwin_548/emwin_config/GUIConf.o \
./emwin_548/emwin_config/GUI_X.o \
./emwin_548/emwin_config/LCDConf.o \

C_DEPS += \
./emwin_548/emwin_config/GUIConf.d \
./emwin_548/emwin_config/GUI_X.d \
./emwin_548/emwin_config/LCDConf.d \

OBJS_QUOTED += \
"./emwin_548/emwin_config/GUIConf.o" \
"./emwin_548/emwin_config/GUI_X.o" \
"./emwin_548/emwin_config/LCDConf.o" \

C_DEPS_QUOTED += \
"./emwin_548/emwin_config/GUIConf.d" \
"./emwin_548/emwin_config/GUI_X.d" \
"./emwin_548/emwin_config/LCDConf.d" \

OBJS_OS_FORMAT += \
./emwin_548/emwin_config/GUIConf.o \
./emwin_548/emwin_config/GUI_X.o \
./emwin_548/emwin_config/LCDConf.o \


# Each subdirectory must supply rules for building sources it contributes
emwin_548/emwin_config/GUIConf.o: ../emwin_548/emwin_config/GUIConf.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"emwin_548/emwin_config/GUIConf.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"emwin_548/emwin_config/GUIConf.o"
	@echo 'Finished building: $<'
	@echo ' '

emwin_548/emwin_config/GUI_X.o: ../emwin_548/emwin_config/GUI_X.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"emwin_548/emwin_config/GUI_X.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"emwin_548/emwin_config/GUI_X.o"
	@echo 'Finished building: $<'
	@echo ' '

emwin_548/emwin_config/LCDConf.o: ../emwin_548/emwin_config/LCDConf.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"emwin_548/emwin_config/LCDConf.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"emwin_548/emwin_config/LCDConf.o"
	@echo 'Finished building: $<'
	@echo ' '


