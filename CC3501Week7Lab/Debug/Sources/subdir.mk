################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Events.c \
../Sources/main.c 

OBJS += \
./Sources/Events.o \
./Sources/main.o 

C_DEPS += \
./Sources/Events.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/jc299529/Desktop/git/Lab 9/CC3501Week7Lab/Static_Code/PDD" -I"C:/Users/jc299529/Desktop/git/Lab 9/CC3501Week7Lab/Static_Code/IO_Map" -I"C:/Users/jc299529/Desktop/git/Lab 9/CC3501Week7Lab/Sources" -I"C:/Users/jc299529/Desktop/git/Lab 9/CC3501Week7Lab/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


