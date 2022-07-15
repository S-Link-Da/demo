################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../si/bootloader.si4project/Backup/main(4740).c 

OBJS += \
./si/bootloader.si4project/Backup/main(4740).o 

C_DEPS += \
./si/bootloader.si4project/Backup/main(4740).d 


# Each subdirectory must supply rules for building sources it contributes
si/bootloader.si4project/Backup/main(4740).o: ../si/bootloader.si4project/Backup/main(4740).c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32emac -mabi=ilp32e -mcmodel=medany -msmall-data-limit=8 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -D_DEBUG -I"E:\work\project\bootloader\FDV32S300\drivers" -I"E:\work\project\bootloader\FDV32S300\include" -I"E:\work\project\bootloader\FDV32S300\env" -std=gnu11 -MMD -MP -MF"si/bootloader.si4project/Backup/main(4740).d" -MT"si/bootloader.si4project/Backup/main(4740).d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


