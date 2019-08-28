################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../FreeRTOS/portable/heap_4.c" \
"../FreeRTOS/portable/port.c" \

C_SRCS += \
../FreeRTOS/portable/heap_4.c \
../FreeRTOS/portable/port.c \

OBJS += \
./FreeRTOS/portable/heap_4.o \
./FreeRTOS/portable/port.o \

C_DEPS += \
./FreeRTOS/portable/heap_4.d \
./FreeRTOS/portable/port.d \

OBJS_QUOTED += \
"./FreeRTOS/portable/heap_4.o" \
"./FreeRTOS/portable/port.o" \

C_DEPS_QUOTED += \
"./FreeRTOS/portable/heap_4.d" \
"./FreeRTOS/portable/port.d" \

OBJS_OS_FORMAT += \
./FreeRTOS/portable/heap_4.o \
./FreeRTOS/portable/port.o \


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/heap_4.o: ../FreeRTOS/portable/heap_4.c
	@echo 'Building file: $<'
	@echo 'Executing target #35 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"FreeRTOS/portable/heap_4.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"FreeRTOS/portable/heap_4.o"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/portable/port.o: ../FreeRTOS/portable/port.c
	@echo 'Building file: $<'
	@echo 'Executing target #36 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"FreeRTOS/portable/port.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"FreeRTOS/portable/port.o"
	@echo 'Finished building: $<'
	@echo ' '


