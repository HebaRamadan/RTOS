################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../croutine.c \
../event_groups.c \
../heap_1.c \
../list.c \
../port.c \
../queue.c \
../stream_buffer.c \
../tasks.c \
../timers.c 

OBJS += \
./croutine.o \
./event_groups.o \
./heap_1.o \
./list.o \
./port.o \
./queue.o \
./stream_buffer.o \
./tasks.o \
./timers.o 

C_DEPS += \
./croutine.d \
./event_groups.d \
./heap_1.d \
./list.d \
./port.d \
./queue.d \
./stream_buffer.d \
./tasks.d \
./timers.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


