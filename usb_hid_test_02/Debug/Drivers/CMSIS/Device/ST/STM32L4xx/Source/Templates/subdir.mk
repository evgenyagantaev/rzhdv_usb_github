################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/Device/ST/STM32L4xx/Source/Templates/system_stm32l4xx.c 

OBJS += \
./Drivers/CMSIS/Device/ST/STM32L4xx/Source/Templates/system_stm32l4xx.o 

C_DEPS += \
./Drivers/CMSIS/Device/ST/STM32L4xx/Source/Templates/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/Device/ST/STM32L4xx/Source/Templates/%.o: ../Drivers/CMSIS/Device/ST/STM32L4xx/Source/Templates/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L476xx -I"D:/workspace/stm32/rzhdv_usb_github/usb_hid_test_02/Inc" -I"D:/workspace/stm32/rzhdv_usb_github/usb_hid_test_02/Drivers/STM32L4xx_HAL_Driver/Inc" -I"D:/workspace/stm32/rzhdv_usb_github/usb_hid_test_02/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"D:/workspace/stm32/rzhdv_usb_github/usb_hid_test_02/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/workspace/stm32/rzhdv_usb_github/usb_hid_test_02/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc" -I"D:/workspace/stm32/rzhdv_usb_github/usb_hid_test_02/Drivers/CMSIS/Include" -I"D:/workspace/stm32/rzhdv_usb_github/usb_hid_test_02/Drivers/CMSIS/Device/ST/STM32L4xx/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


