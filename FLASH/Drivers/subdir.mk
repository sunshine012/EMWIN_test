################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Drivers/DrvFlexBus.c" \
"../Drivers/DrvIOPort.c" \
"../Drivers/DrvLcdController_MK70.c" \
"../Drivers/DrvLcd_Color320x240.c" \
"../Drivers/DrvSpi.c" \
"../Drivers/DrvSsp.c" \

C_SRCS += \
../Drivers/DrvFlexBus.c \
../Drivers/DrvIOPort.c \
../Drivers/DrvLcdController_MK70.c \
../Drivers/DrvLcd_Color320x240.c \
../Drivers/DrvSpi.c \
../Drivers/DrvSsp.c \

OBJS += \
./Drivers/DrvFlexBus.o \
./Drivers/DrvIOPort.o \
./Drivers/DrvLcdController_MK70.o \
./Drivers/DrvLcd_Color320x240.o \
./Drivers/DrvSpi.o \
./Drivers/DrvSsp.o \

C_DEPS += \
./Drivers/DrvFlexBus.d \
./Drivers/DrvIOPort.d \
./Drivers/DrvLcdController_MK70.d \
./Drivers/DrvLcd_Color320x240.d \
./Drivers/DrvSpi.d \
./Drivers/DrvSsp.d \

OBJS_QUOTED += \
"./Drivers/DrvFlexBus.o" \
"./Drivers/DrvIOPort.o" \
"./Drivers/DrvLcdController_MK70.o" \
"./Drivers/DrvLcd_Color320x240.o" \
"./Drivers/DrvSpi.o" \
"./Drivers/DrvSsp.o" \

C_DEPS_QUOTED += \
"./Drivers/DrvFlexBus.d" \
"./Drivers/DrvIOPort.d" \
"./Drivers/DrvLcdController_MK70.d" \
"./Drivers/DrvLcd_Color320x240.d" \
"./Drivers/DrvSpi.d" \
"./Drivers/DrvSsp.d" \

OBJS_OS_FORMAT += \
./Drivers/DrvFlexBus.o \
./Drivers/DrvIOPort.o \
./Drivers/DrvLcdController_MK70.o \
./Drivers/DrvLcd_Color320x240.o \
./Drivers/DrvSpi.o \
./Drivers/DrvSsp.o \


# Each subdirectory must supply rules for building sources it contributes
Drivers/DrvFlexBus.o: ../Drivers/DrvFlexBus.c
	@echo 'Building file: $<'
	@echo 'Executing target #37 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Drivers/DrvFlexBus.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Drivers/DrvFlexBus.o"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/DrvIOPort.o: ../Drivers/DrvIOPort.c
	@echo 'Building file: $<'
	@echo 'Executing target #38 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Drivers/DrvIOPort.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Drivers/DrvIOPort.o"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/DrvLcdController_MK70.o: ../Drivers/DrvLcdController_MK70.c
	@echo 'Building file: $<'
	@echo 'Executing target #39 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Drivers/DrvLcdController_MK70.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Drivers/DrvLcdController_MK70.o"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/DrvLcd_Color320x240.o: ../Drivers/DrvLcd_Color320x240.c
	@echo 'Building file: $<'
	@echo 'Executing target #40 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Drivers/DrvLcd_Color320x240.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Drivers/DrvLcd_Color320x240.o"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/DrvSpi.o: ../Drivers/DrvSpi.c
	@echo 'Building file: $<'
	@echo 'Executing target #41 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Drivers/DrvSpi.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Drivers/DrvSpi.o"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/DrvSsp.o: ../Drivers/DrvSsp.c
	@echo 'Building file: $<'
	@echo 'Executing target #42 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Drivers/DrvSsp.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Drivers/DrvSsp.o"
	@echo 'Finished building: $<'
	@echo ' '


