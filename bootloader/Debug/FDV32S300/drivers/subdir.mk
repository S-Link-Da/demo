################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FDV32S300/drivers/anac.c \
../FDV32S300/drivers/crc.c \
../FDV32S300/drivers/efc.c \
../FDV32S300/drivers/i2c.c \
../FDV32S300/drivers/iom.c \
../FDV32S300/drivers/lptimer.c \
../FDV32S300/drivers/pmu.c \
../FDV32S300/drivers/rtc.c \
../FDV32S300/drivers/spi.c \
../FDV32S300/drivers/sysc.c \
../FDV32S300/drivers/timer.c \
../FDV32S300/drivers/twc.c \
../FDV32S300/drivers/uart.c \
../FDV32S300/drivers/wdt.c 

OBJS += \
./FDV32S300/drivers/anac.o \
./FDV32S300/drivers/crc.o \
./FDV32S300/drivers/efc.o \
./FDV32S300/drivers/i2c.o \
./FDV32S300/drivers/iom.o \
./FDV32S300/drivers/lptimer.o \
./FDV32S300/drivers/pmu.o \
./FDV32S300/drivers/rtc.o \
./FDV32S300/drivers/spi.o \
./FDV32S300/drivers/sysc.o \
./FDV32S300/drivers/timer.o \
./FDV32S300/drivers/twc.o \
./FDV32S300/drivers/uart.o \
./FDV32S300/drivers/wdt.o 

C_DEPS += \
./FDV32S300/drivers/anac.d \
./FDV32S300/drivers/crc.d \
./FDV32S300/drivers/efc.d \
./FDV32S300/drivers/i2c.d \
./FDV32S300/drivers/iom.d \
./FDV32S300/drivers/lptimer.d \
./FDV32S300/drivers/pmu.d \
./FDV32S300/drivers/rtc.d \
./FDV32S300/drivers/spi.d \
./FDV32S300/drivers/sysc.d \
./FDV32S300/drivers/timer.d \
./FDV32S300/drivers/twc.d \
./FDV32S300/drivers/uart.d \
./FDV32S300/drivers/wdt.d 


# Each subdirectory must supply rules for building sources it contributes
FDV32S300/drivers/%.o: ../FDV32S300/drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32emac -mabi=ilp32e -mcmodel=medany -msmall-data-limit=8 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"E:\work\project\bootloader\FDV32S300\drivers" -I"E:\work\project\bootloader\FDV32S300\include" -I"E:\work\project\bootloader\FDV32S300\env" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


