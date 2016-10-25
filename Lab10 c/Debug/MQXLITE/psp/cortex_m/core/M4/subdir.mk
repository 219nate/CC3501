################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../MQXLITE/psp/cortex_m/core/M4/boot.S \
../MQXLITE/psp/cortex_m/core/M4/dispatch.S 

OBJS += \
./MQXLITE/psp/cortex_m/core/M4/boot.o \
./MQXLITE/psp/cortex_m/core/M4/dispatch.o 

S_UPPER_DEPS += \
./MQXLITE/psp/cortex_m/core/M4/boot.d \
./MQXLITE/psp/cortex_m/core/M4/dispatch.d 


# Each subdirectory must supply rules for building sources it contributes
MQXLITE/psp/cortex_m/core/M4/%.o: ../MQXLITE/psp/cortex_m/core/M4/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/MQXLITE/include" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/MQXLITE/config" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/MQXLITE/kernel" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/MQXLITE/psp/cortex_m" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/MQXLITE/psp/cortex_m/core/M4" -I"C:/Users/jc299170/Desktop/dik/Lab8CC3501/MQXLITE/psp/cortex_m/compiler/cwgcc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


