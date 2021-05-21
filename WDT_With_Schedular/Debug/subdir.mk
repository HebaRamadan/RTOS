################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Dio_prg.c \
../Led_prg.c \
../Switch_prg.c \
../Timer0_prg.c \
../main.c 

OBJS += \
./Dio_prg.o \
./Led_prg.o \
./Switch_prg.o \
./Timer0_prg.o \
./main.o 

C_DEPS += \
./Dio_prg.d \
./Led_prg.d \
./Switch_prg.d \
./Timer0_prg.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


