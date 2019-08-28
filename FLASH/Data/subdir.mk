################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Data/DatFont8x16.c" \
"../Data/Doraemon.c" \
"../Data/bird.c" \
"../Data/pictures.c" \
"../Data/road.c" \
"../Data/tree.c" \

C_SRCS += \
../Data/DatFont8x16.c \
../Data/Doraemon.c \
../Data/bird.c \
../Data/pictures.c \
../Data/road.c \
../Data/tree.c \

OBJS += \
./Data/DatFont8x16.o \
./Data/Doraemon.o \
./Data/bird.o \
./Data/pictures.o \
./Data/road.o \
./Data/tree.o \

C_DEPS += \
./Data/DatFont8x16.d \
./Data/Doraemon.d \
./Data/bird.d \
./Data/pictures.d \
./Data/road.d \
./Data/tree.d \

OBJS_QUOTED += \
"./Data/DatFont8x16.o" \
"./Data/Doraemon.o" \
"./Data/bird.o" \
"./Data/pictures.o" \
"./Data/road.o" \
"./Data/tree.o" \

C_DEPS_QUOTED += \
"./Data/DatFont8x16.d" \
"./Data/Doraemon.d" \
"./Data/bird.d" \
"./Data/pictures.d" \
"./Data/road.d" \
"./Data/tree.d" \

OBJS_OS_FORMAT += \
./Data/DatFont8x16.o \
./Data/Doraemon.o \
./Data/bird.o \
./Data/pictures.o \
./Data/road.o \
./Data/tree.o \


# Each subdirectory must supply rules for building sources it contributes
Data/DatFont8x16.o: ../Data/DatFont8x16.c
	@echo 'Building file: $<'
	@echo 'Executing target #43 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Data/DatFont8x16.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Data/DatFont8x16.o"
	@echo 'Finished building: $<'
	@echo ' '

Data/Doraemon.o: ../Data/Doraemon.c
	@echo 'Building file: $<'
	@echo 'Executing target #44 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Data/Doraemon.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Data/Doraemon.o"
	@echo 'Finished building: $<'
	@echo ' '

Data/bird.o: ../Data/bird.c
	@echo 'Building file: $<'
	@echo 'Executing target #45 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Data/bird.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Data/bird.o"
	@echo 'Finished building: $<'
	@echo ' '

Data/pictures.o: ../Data/pictures.c
	@echo 'Building file: $<'
	@echo 'Executing target #46 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Data/pictures.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Data/pictures.o"
	@echo 'Finished building: $<'
	@echo ' '

Data/road.o: ../Data/road.c
	@echo 'Building file: $<'
	@echo 'Executing target #47 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Data/road.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Data/road.o"
	@echo 'Finished building: $<'
	@echo ' '

Data/tree.o: ../Data/tree.c
	@echo 'Building file: $<'
	@echo 'Executing target #48 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Data/tree.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Data/tree.o"
	@echo 'Finished building: $<'
	@echo ' '


