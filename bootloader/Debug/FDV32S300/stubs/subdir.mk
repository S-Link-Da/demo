################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FDV32S300/stubs/_exit.c \
../FDV32S300/stubs/close.c \
../FDV32S300/stubs/fstat.c \
../FDV32S300/stubs/isatty.c \
../FDV32S300/stubs/lseek.c \
../FDV32S300/stubs/printf.c \
../FDV32S300/stubs/read.c \
../FDV32S300/stubs/sbrk.c \
../FDV32S300/stubs/write.c \
../FDV32S300/stubs/write_hex.c 

OBJS += \
./FDV32S300/stubs/_exit.o \
./FDV32S300/stubs/close.o \
./FDV32S300/stubs/fstat.o \
./FDV32S300/stubs/isatty.o \
./FDV32S300/stubs/lseek.o \
./FDV32S300/stubs/printf.o \
./FDV32S300/stubs/read.o \
./FDV32S300/stubs/sbrk.o \
./FDV32S300/stubs/write.o \
./FDV32S300/stubs/write_hex.o 

C_DEPS += \
./FDV32S300/stubs/_exit.d \
./FDV32S300/stubs/close.d \
./FDV32S300/stubs/fstat.d \
./FDV32S300/stubs/isatty.d \
./FDV32S300/stubs/lseek.d \
./FDV32S300/stubs/printf.d \
./FDV32S300/stubs/read.d \
./FDV32S300/stubs/sbrk.d \
./FDV32S300/stubs/write.d \
./FDV32S300/stubs/write_hex.d 


# Each subdirectory must supply rules for building sources it contributes
FDV32S300/stubs/%.o: ../FDV32S300/stubs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32emac -mabi=ilp32e -mcmodel=medany -msmall-data-limit=8 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"E:\work\project\bootloader\FDV32S300\drivers" -I"E:\work\project\bootloader\FDV32S300\include" -I"E:\work\project\bootloader\FDV32S300\env" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


