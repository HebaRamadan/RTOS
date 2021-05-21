################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer_prg.c \
../DC_Motor_prg.c \
../Dio_prg.c \
../Keypad_prg.c \
../Lcd_prg.c \
../Led_prg.c \
../PWM_prg.c \
../RTO_prg.c \
../Servo_prg.c \
../Stepper_prg.c \
../Timer0_prg.c \
../Timer1_prg.c \
../Timer2_prg.c \
../main.c 

OBJS += \
./Buzzer_prg.o \
./DC_Motor_prg.o \
./Dio_prg.o \
./Keypad_prg.o \
./Lcd_prg.o \
./Led_prg.o \
./PWM_prg.o \
./RTO_prg.o \
./Servo_prg.o \
./Stepper_prg.o \
./Timer0_prg.o \
./Timer1_prg.o \
./Timer2_prg.o \
./main.o 

C_DEPS += \
./Buzzer_prg.d \
./DC_Motor_prg.d \
./Dio_prg.d \
./Keypad_prg.d \
./Lcd_prg.d \
./Led_prg.d \
./PWM_prg.d \
./RTO_prg.d \
./Servo_prg.d \
./Stepper_prg.d \
./Timer0_prg.d \
./Timer1_prg.d \
./Timer2_prg.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


