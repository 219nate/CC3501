################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/AD1.c \
../Generated_Code/ASerialLdd1.c \
../Generated_Code/AdcLdd1.c \
../Generated_Code/Cpu.c \
../Generated_Code/Inhr1.c \
../Generated_Code/IntI2cLdd1.c \
../Generated_Code/MMA8451Q.c \
../Generated_Code/MQX1.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/SystemTimer1.c \
../Generated_Code/Term1.c \
../Generated_Code/Vectors.c 

OBJS += \
./Generated_Code/AD1.o \
./Generated_Code/ASerialLdd1.o \
./Generated_Code/AdcLdd1.o \
./Generated_Code/Cpu.o \
./Generated_Code/Inhr1.o \
./Generated_Code/IntI2cLdd1.o \
./Generated_Code/MMA8451Q.o \
./Generated_Code/MQX1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/SystemTimer1.o \
./Generated_Code/Term1.o \
./Generated_Code/Vectors.o 

C_DEPS += \
./Generated_Code/AD1.d \
./Generated_Code/ASerialLdd1.d \
./Generated_Code/AdcLdd1.d \
./Generated_Code/Cpu.d \
./Generated_Code/Inhr1.d \
./Generated_Code/IntI2cLdd1.d \
./Generated_Code/MMA8451Q.d \
./Generated_Code/MQX1.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/SystemTimer1.d \
./Generated_Code/Term1.d \
./Generated_Code/Vectors.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/Static_Code/PDD" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/Static_Code/IO_Map" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/Sources" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/Generated_Code" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/MQXLITE/include" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/MQXLITE/config" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/MQXLITE/kernel" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/MQXLITE/psp/cortex_m" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/MQXLITE/psp/cortex_m/core/M4" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/MQXLITE/psp/cortex_m/compiler/cwgcc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


