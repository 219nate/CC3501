################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/ASerialLdd1.c \
../Generated_Code/ASerialLdd2.c \
../Generated_Code/Cpu.c \
../Generated_Code/Inhr1.c \
../Generated_Code/Inhr2.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/Term1.c \
../Generated_Code/Term2.c \
../Generated_Code/Vectors.c 

OBJS += \
./Generated_Code/ASerialLdd1.o \
./Generated_Code/ASerialLdd2.o \
./Generated_Code/Cpu.o \
./Generated_Code/Inhr1.o \
./Generated_Code/Inhr2.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/Term1.o \
./Generated_Code/Term2.o \
./Generated_Code/Vectors.o 

C_DEPS += \
./Generated_Code/ASerialLdd1.d \
./Generated_Code/ASerialLdd2.d \
./Generated_Code/Cpu.d \
./Generated_Code/Inhr1.d \
./Generated_Code/Inhr2.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/Term1.d \
./Generated_Code/Term2.d \
./Generated_Code/Vectors.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/jc299529/Desktop/New folder/prac 3 thingo/Static_Code/PDD" -I"C:/Users/jc299529/Desktop/New folder/prac 3 thingo/Static_Code/IO_Map" -I"C:/Users/jc299529/Desktop/New folder/prac 3 thingo/Sources" -I"C:/Users/jc299529/Desktop/New folder/prac 3 thingo/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


