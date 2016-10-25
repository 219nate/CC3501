################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/AD1.c \
../Generated_Code/ASerialLdd1.c \
../Generated_Code/AdcLdd1.c \
../Generated_Code/BlueLEDPWM.c \
../Generated_Code/Cpu.c \
../Generated_Code/GreenLEDPWM.c \
../Generated_Code/I2C2.c \
../Generated_Code/Inhr1.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/PwmLdd1.c \
../Generated_Code/PwmLdd2.c \
../Generated_Code/PwmLdd3.c \
../Generated_Code/RedLEDPWM.c \
../Generated_Code/TU1.c \
../Generated_Code/Term1.c \
../Generated_Code/Vectors.c 

OBJS += \
./Generated_Code/AD1.o \
./Generated_Code/ASerialLdd1.o \
./Generated_Code/AdcLdd1.o \
./Generated_Code/BlueLEDPWM.o \
./Generated_Code/Cpu.o \
./Generated_Code/GreenLEDPWM.o \
./Generated_Code/I2C2.o \
./Generated_Code/Inhr1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/PwmLdd1.o \
./Generated_Code/PwmLdd2.o \
./Generated_Code/PwmLdd3.o \
./Generated_Code/RedLEDPWM.o \
./Generated_Code/TU1.o \
./Generated_Code/Term1.o \
./Generated_Code/Vectors.o 

C_DEPS += \
./Generated_Code/AD1.d \
./Generated_Code/ASerialLdd1.d \
./Generated_Code/AdcLdd1.d \
./Generated_Code/BlueLEDPWM.d \
./Generated_Code/Cpu.d \
./Generated_Code/GreenLEDPWM.d \
./Generated_Code/I2C2.d \
./Generated_Code/Inhr1.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/PwmLdd1.d \
./Generated_Code/PwmLdd2.d \
./Generated_Code/PwmLdd3.d \
./Generated_Code/RedLEDPWM.d \
./Generated_Code/TU1.d \
./Generated_Code/Term1.d \
./Generated_Code/Vectors.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/TheBaker/Dropbox/CC3501/Github Repository/CC3501/Lab2/Static_Code/PDD" -I"C:/Users/TheBaker/Dropbox/CC3501/Github Repository/CC3501/Lab2/Static_Code/IO_Map" -I"C:/Users/TheBaker/Dropbox/CC3501/Github Repository/CC3501/Lab2/Sources" -I"C:/Users/TheBaker/Dropbox/CC3501/Github Repository/CC3501/Lab2/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


