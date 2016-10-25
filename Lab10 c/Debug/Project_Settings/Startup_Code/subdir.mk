################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project_Settings/Startup_Code/startup.c 

OBJS += \
./Project_Settings/Startup_Code/startup.o 

C_DEPS += \
./Project_Settings/Startup_Code/startup.d 


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/Static_Code/PDD" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/Static_Code/IO_Map" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/Sources" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/Generated_Code" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/MQXLITE/include" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/MQXLITE/config" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/MQXLITE/kernel" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/MQXLITE/psp/cortex_m" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/MQXLITE/psp/cortex_m/core/M4" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/MQXLITE/psp/cortex_m/compiler/cwgcc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


