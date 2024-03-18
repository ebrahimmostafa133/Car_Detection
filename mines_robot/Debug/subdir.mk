################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Dio.c \
../ExtInt.c \
../Gie.c \
../Gpt.c \
../Gpt_PbCfg.c \
../Pwm.c \
../Pwm_PbCfg.c \
../main.c \
../mines_detector.c 

OBJS += \
./Dio.o \
./ExtInt.o \
./Gie.o \
./Gpt.o \
./Gpt_PbCfg.o \
./Pwm.o \
./Pwm_PbCfg.o \
./main.o \
./mines_detector.o 

C_DEPS += \
./Dio.d \
./ExtInt.d \
./Gie.d \
./Gpt.d \
./Gpt_PbCfg.d \
./Pwm.d \
./Pwm_PbCfg.d \
./main.d \
./mines_detector.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


