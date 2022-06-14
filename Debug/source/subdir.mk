################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/LPC55S69_Robot_Biere.c \
../source/device_interrupt.c \
../source/device_motor.c \
../source/device_system.c \
../source/device_vl53l0x.c \
../source/device_xl320.c \
../source/driver_ultrason.c \
../source/driver_vl53l0x.c \
../source/middleware_ic2.c \
../source/middleware_uart.c \
../source/robot_shell.c \
../source/semihost_hardfault.c \
../source/usb_device_descriptor.c \
../source/virtual_com.c 

OBJS += \
./source/LPC55S69_Robot_Biere.o \
./source/device_interrupt.o \
./source/device_motor.o \
./source/device_system.o \
./source/device_vl53l0x.o \
./source/device_xl320.o \
./source/driver_ultrason.o \
./source/driver_vl53l0x.o \
./source/middleware_ic2.o \
./source/middleware_uart.o \
./source/robot_shell.o \
./source/semihost_hardfault.o \
./source/usb_device_descriptor.o \
./source/virtual_com.o 

C_DEPS += \
./source/LPC55S69_Robot_Biere.d \
./source/device_interrupt.d \
./source/device_motor.d \
./source/device_system.d \
./source/device_vl53l0x.d \
./source/device_xl320.d \
./source/driver_ultrason.d \
./source/driver_vl53l0x.d \
./source/middleware_ic2.d \
./source/middleware_uart.d \
./source/robot_shell.d \
./source/semihost_hardfault.d \
./source/usb_device_descriptor.d \
./source/virtual_com.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DCPU_LPC55S69JBD100_cm33_core0 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_OS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=1 -DDEBUG_CONSOLE_RX_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\freertos\freertos_kernel\include" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\drivers" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\utilities" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\component\uart" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\component\serial_manager" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\component\lists" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\usb\phy" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\usb\include" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\usb\device\class\cdc" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\usb\output\source\device\class" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\usb\device\include" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\usb\device\source" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\usb\device\source\lpcip3511" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\usb\device\class" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\usb\output\source\device" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\component\osa" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\CMSIS" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\source" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\freertos\freertos_kernel\portable\GCC\ARM_CM33_NTZ\non_secure" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\device" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\freertos\freertos_kernel\include" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\drivers" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\utilities" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\component\uart" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\component\serial_manager" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\component\lists" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\CMSIS" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\source" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\freertos\freertos_kernel\portable\GCC\ARM_CM33_NTZ\non_secure" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\device" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\board" -I"C:\Users\Baptiste\Documents\ENSEA\3D\S10_011_Projet\IDE\LPC55S69_Robot_Biere\startup" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


