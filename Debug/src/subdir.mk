################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bme280.c \
../src/cr_startup_lpc13uxx.c \
../src/crp.c \
../src/spi.c \
../src/sysinit.c 

OBJS += \
./src/bme280.o \
./src/cr_startup_lpc13uxx.o \
./src/crp.o \
./src/spi.o \
./src/sysinit.o 

C_DEPS += \
./src/bme280.d \
./src/cr_startup_lpc13uxx.d \
./src/crp.d \
./src/spi.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC13UXX__ -D__REDLIB__ -I"/home/sobriodev/Documents/MCUXpresso_10.2.1_795/workspace/lpc_board_nxp_lpcxpresso_1347/inc" -I"/home/sobriodev/Documents/MCUXpresso_10.2.1_795/workspace/lpc_chip_13xx/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


