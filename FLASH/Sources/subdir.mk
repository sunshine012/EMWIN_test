################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/AppDisplay.c" \
"../Sources/AppTask.c" \
"../Sources/Appserial.c" \
"../Sources/Events.c" \
"../Sources/Global_data.c" \
"../Sources/SysDisplay.c" \
"../Sources/SysFont.c" \
"../Sources/key.c" \
"../Sources/main.c" \

C_SRCS += \
../Sources/AppDisplay.c \
../Sources/AppTask.c \
../Sources/Appserial.c \
../Sources/Events.c \
../Sources/Global_data.c \
../Sources/SysDisplay.c \
../Sources/SysFont.c \
../Sources/key.c \
../Sources/main.c \

OBJS += \
./Sources/AppDisplay.o \
./Sources/AppTask.o \
./Sources/Appserial.o \
./Sources/Events.o \
./Sources/Global_data.o \
./Sources/SysDisplay.o \
./Sources/SysFont.o \
./Sources/key.o \
./Sources/main.o \

C_DEPS += \
./Sources/AppDisplay.d \
./Sources/AppTask.d \
./Sources/Appserial.d \
./Sources/Events.d \
./Sources/Global_data.d \
./Sources/SysDisplay.d \
./Sources/SysFont.d \
./Sources/key.d \
./Sources/main.d \

OBJS_QUOTED += \
"./Sources/AppDisplay.o" \
"./Sources/AppTask.o" \
"./Sources/Appserial.o" \
"./Sources/Events.o" \
"./Sources/Global_data.o" \
"./Sources/SysDisplay.o" \
"./Sources/SysFont.o" \
"./Sources/key.o" \
"./Sources/main.o" \

C_DEPS_QUOTED += \
"./Sources/AppDisplay.d" \
"./Sources/AppTask.d" \
"./Sources/Appserial.d" \
"./Sources/Events.d" \
"./Sources/Global_data.d" \
"./Sources/SysDisplay.d" \
"./Sources/SysFont.d" \
"./Sources/key.d" \
"./Sources/main.d" \

OBJS_OS_FORMAT += \
./Sources/AppDisplay.o \
./Sources/AppTask.o \
./Sources/Appserial.o \
./Sources/Events.o \
./Sources/Global_data.o \
./Sources/SysDisplay.o \
./Sources/SysFont.o \
./Sources/key.o \
./Sources/main.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/AppDisplay.o: ../Sources/AppDisplay.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/AppDisplay.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/AppDisplay.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/AppTask.o: ../Sources/AppTask.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/AppTask.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/AppTask.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Appserial.o: ../Sources/Appserial.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Appserial.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Appserial.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Events.o: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Events.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Events.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Global_data.o: ../Sources/Global_data.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Global_data.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Global_data.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/SysDisplay.o: ../Sources/SysDisplay.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/SysDisplay.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/SysDisplay.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/SysFont.o: ../Sources/SysFont.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/SysFont.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/SysFont.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/key.o: ../Sources/key.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/key.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/key.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '


