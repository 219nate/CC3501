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
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/TheBaker/Dropbox/CC3501/Github Repository/CC3501/Lab2/Static_Code/PDD" -I"C:/Users/TheBaker/Dropbox/CC3501/Github Repository/CC3501/Lab2/Static_Code/IO_Map" -I"C:/Users/TheBaker/Dropbox/CC3501/Github Repository/CC3501/Lab2/Sources" -I"C:/Users/TheBaker/Dropbox/CC3501/Github Repository/CC3501/Lab2/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

