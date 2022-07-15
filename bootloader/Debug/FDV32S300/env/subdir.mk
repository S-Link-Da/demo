################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FDV32S300/env/init.c \
../FDV32S300/env/system_phnx02.c 

S_UPPER_SRCS += \
../FDV32S300/env/entry.S \
../FDV32S300/env/start.S 

OBJS += \
./FDV32S300/env/entry.o \
./FDV32S300/env/init.o \
./FDV32S300/env/start.o \
./FDV32S300/env/system_phnx02.o 

S_UPPER_DEPS += \
./FDV32S300/env/entry.d \
./FDV32S300/env/start.d 

C_DEPS += \
./FDV32S300/env/init.d \
./FDV32S300/env/system_phnx02.d 


# Each subdirectory must supply rules for building sources it contributes
FDV32S300/env/%.o: ../FDV32S300/env/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross Assembler'
	riscv-none-embed-gcc -march=rv32emac -mabi=ilp32e -mcmodel=medany -msmall-data-limit=8 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -x assembler-with-cpp -I"E:\work\project\bootloader\FDV32S300\drivers" -I"E:\work\project\bootloader\FDV32S300\include" -I"E:\work\project\bootloader\FDV32S300\env" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FDV32S300/env/%.o: ../FDV32S300/env/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32emac -mabi=ilp32e -mcmodel=medany -msmall-data-limit=8 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"E:\work\project\bootloader\FDV32S300\drivers" -I"E:\work\project\bootloader\FDV32S300\include" -I"E:\work\project\bootloader\FDV32S300\env" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


