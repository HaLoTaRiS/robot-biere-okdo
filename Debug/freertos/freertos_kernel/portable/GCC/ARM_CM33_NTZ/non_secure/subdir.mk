################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/freertos_kernel/portable/GCC/ARM_CM33_NTZ/non_secure/port.c \
../freertos/freertos_kernel/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.c 

OBJS += \
./freertos/freertos_kernel/portable/GCC/ARM_CM33_NTZ/non_secure/port.o \
./freertos/freertos_kernel/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.o 

C_DEPS += \
./freertos/freertos_kernel/portable/GCC/ARM_CM33_NTZ/non_secure/port.d \
./freertos/freertos_kernel/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/freertos_kernel/portable/GCC/ARM_CM33_NTZ/non_secure/%.o: ../freertos/freertos_kernel/portable/GCC/ARM_CM33_NTZ/non_secure/%.c freertos/freertos_kernel/portable/GCC/ARM_CM33_NTZ/non_secure/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DCPU_LPC55S69JBD100_cm33_core0 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_OS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=1 -DDEBUG_CONSOLE_RX_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\freertos\freertos_kernel\include" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\drivers" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\utilities" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\component\uart" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\component\serial_manager" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\component\lists" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\CMSIS" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\source" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\freertos\freertos_kernel\portable\GCC\ARM_CM33_NTZ\non_secure" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\device" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\board" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\source" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\freertos\freertos_kernel\portable\GCC\ARM_CM33_NTZ\non_secure" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\freertos\freertos_kernel\include" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\drivers" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\utilities" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\component\uart" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\component\serial_manager" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\component\lists" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\startup" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\CMSIS" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


