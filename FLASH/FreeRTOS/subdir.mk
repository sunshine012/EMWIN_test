################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../FreeRTOS/croutine.c" \
"../FreeRTOS/event_groups.c" \
"../FreeRTOS/list.c" \
"../FreeRTOS/queue.c" \
"../FreeRTOS/stream_buffer.c" \
"../FreeRTOS/tasks.c" \
"../FreeRTOS/timers.c" \

C_SRCS += \
../FreeRTOS/croutine.c \
../FreeRTOS/event_groups.c \
../FreeRTOS/list.c \
../FreeRTOS/queue.c \
../FreeRTOS/stream_buffer.c \
../FreeRTOS/tasks.c \
../FreeRTOS/timers.c \

OBJS += \
./FreeRTOS/croutine.o \
./FreeRTOS/event_groups.o \
./FreeRTOS/list.o \
./FreeRTOS/queue.o \
./FreeRTOS/stream_buffer.o \
./FreeRTOS/tasks.o \
./FreeRTOS/timers.o \

C_DEPS += \
./FreeRTOS/croutine.d \
./FreeRTOS/event_groups.d \
./FreeRTOS/list.d \
./FreeRTOS/queue.d \
./FreeRTOS/stream_buffer.d \
./FreeRTOS/tasks.d \
./FreeRTOS/timers.d \

OBJS_QUOTED += \
"./FreeRTOS/croutine.o" \
"./FreeRTOS/event_groups.o" \
"./FreeRTOS/list.o" \
"./FreeRTOS/queue.o" \
"./FreeRTOS/stream_buffer.o" \
"./FreeRTOS/tasks.o" \
"./FreeRTOS/timers.o" \

C_DEPS_QUOTED += \
"./FreeRTOS/croutine.d" \
"./FreeRTOS/event_groups.d" \
"./FreeRTOS/list.d" \
"./FreeRTOS/queue.d" \
"./FreeRTOS/stream_buffer.d" \
"./FreeRTOS/tasks.d" \
"./FreeRTOS/timers.d" \

OBJS_OS_FORMAT += \
./FreeRTOS/croutine.o \
./FreeRTOS/event_groups.o \
./FreeRTOS/list.o \
./FreeRTOS/queue.o \
./FreeRTOS/stream_buffer.o \
./FreeRTOS/tasks.o \
./FreeRTOS/timers.o \


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/croutine.o: ../FreeRTOS/croutine.c
	@echo 'Building file: $<'
	@echo 'Executing target #28 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"FreeRTOS/croutine.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"FreeRTOS/croutine.o"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/event_groups.o: ../FreeRTOS/event_groups.c
	@echo 'Building file: $<'
	@echo 'Executing target #29 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"FreeRTOS/event_groups.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"FreeRTOS/event_groups.o"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/list.o: ../FreeRTOS/list.c
	@echo 'Building file: $<'
	@echo 'Executing target #30 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"FreeRTOS/list.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"FreeRTOS/list.o"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/queue.o: ../FreeRTOS/queue.c
	@echo 'Building file: $<'
	@echo 'Executing target #31 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"FreeRTOS/queue.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"FreeRTOS/queue.o"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/stream_buffer.o: ../FreeRTOS/stream_buffer.c
	@echo 'Building file: $<'
	@echo 'Executing target #32 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"FreeRTOS/stream_buffer.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"FreeRTOS/stream_buffer.o"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/tasks.o: ../FreeRTOS/tasks.c
	@echo 'Building file: $<'
	@echo 'Executing target #33 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"FreeRTOS/tasks.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"FreeRTOS/tasks.o"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/timers.o: ../FreeRTOS/timers.c
	@echo 'Building file: $<'
	@echo 'Executing target #34 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"FreeRTOS/timers.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"FreeRTOS/timers.o"
	@echo 'Finished building: $<'
	@echo ' '


