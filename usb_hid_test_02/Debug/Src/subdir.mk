################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/acc_data_buffer_obj.c \
../Src/acc_data_read_task.c \
../Src/acc_spi_low_level.c \
../Src/adas1000.c \
../Src/adas1000_get_save_frame.c \
../Src/adc.c \
../Src/configure_adas1000.c \
../Src/diagnost_obj.c \
../Src/diagnostics_task.c \
../Src/ecg_ring_buffer.c \
../Src/ecg_ring_buffer_task.c \
../Src/frame_ring_buffer.c \
../Src/frame_ring_buffer_task.c \
../Src/gpio.c \
../Src/heart_rate_calculation_task.c \
../Src/heart_rate_obj.c \
../Src/histogram_obj.c \
../Src/histogram_task.c \
../Src/isoline.c \
../Src/isoline_calculation_task.c \
../Src/leadoff_detection_task.c \
../Src/leadoff_detector_obj.c \
../Src/main.c \
../Src/movement_detection_task.c \
../Src/movement_detector_obj.c \
../Src/qrs_detection_task.c \
../Src/qrs_obj.c \
../Src/recreation_curve_obj.c \
../Src/rr_window_obj.c \
../Src/rr_window_task.c \
../Src/smb380.c \
../Src/spi.c \
../Src/spi_low_level.c \
../Src/stm32l476g_discovery.c \
../Src/stm32l4xx_it.c \
../Src/temperature_measure_task.c \
../Src/thermometr_obj.c \
../Src/tim.c \
../Src/timer250hz.c \
../Src/timer250hz_irqhandler.c \
../Src/timer_100hz_irqhandler.c \
../Src/timer_100hz_obj.c \
../Src/timer_1hz_irqhandler.c \
../Src/timer_1hz_obj.c \
../Src/usart.c \
../Src/usbd_conf.c \
../Src/usbd_customhid_if.c \
../Src/usbd_desc.c 

OBJS += \
./Src/acc_data_buffer_obj.o \
./Src/acc_data_read_task.o \
./Src/acc_spi_low_level.o \
./Src/adas1000.o \
./Src/adas1000_get_save_frame.o \
./Src/adc.o \
./Src/configure_adas1000.o \
./Src/diagnost_obj.o \
./Src/diagnostics_task.o \
./Src/ecg_ring_buffer.o \
./Src/ecg_ring_buffer_task.o \
./Src/frame_ring_buffer.o \
./Src/frame_ring_buffer_task.o \
./Src/gpio.o \
./Src/heart_rate_calculation_task.o \
./Src/heart_rate_obj.o \
./Src/histogram_obj.o \
./Src/histogram_task.o \
./Src/isoline.o \
./Src/isoline_calculation_task.o \
./Src/leadoff_detection_task.o \
./Src/leadoff_detector_obj.o \
./Src/main.o \
./Src/movement_detection_task.o \
./Src/movement_detector_obj.o \
./Src/qrs_detection_task.o \
./Src/qrs_obj.o \
./Src/recreation_curve_obj.o \
./Src/rr_window_obj.o \
./Src/rr_window_task.o \
./Src/smb380.o \
./Src/spi.o \
./Src/spi_low_level.o \
./Src/stm32l476g_discovery.o \
./Src/stm32l4xx_it.o \
./Src/temperature_measure_task.o \
./Src/thermometr_obj.o \
./Src/tim.o \
./Src/timer250hz.o \
./Src/timer250hz_irqhandler.o \
./Src/timer_100hz_irqhandler.o \
./Src/timer_100hz_obj.o \
./Src/timer_1hz_irqhandler.o \
./Src/timer_1hz_obj.o \
./Src/usart.o \
./Src/usbd_conf.o \
./Src/usbd_customhid_if.o \
./Src/usbd_desc.o 

C_DEPS += \
./Src/acc_data_buffer_obj.d \
./Src/acc_data_read_task.d \
./Src/acc_spi_low_level.d \
./Src/adas1000.d \
./Src/adas1000_get_save_frame.d \
./Src/adc.d \
./Src/configure_adas1000.d \
./Src/diagnost_obj.d \
./Src/diagnostics_task.d \
./Src/ecg_ring_buffer.d \
./Src/ecg_ring_buffer_task.d \
./Src/frame_ring_buffer.d \
./Src/frame_ring_buffer_task.d \
./Src/gpio.d \
./Src/heart_rate_calculation_task.d \
./Src/heart_rate_obj.d \
./Src/histogram_obj.d \
./Src/histogram_task.d \
./Src/isoline.d \
./Src/isoline_calculation_task.d \
./Src/leadoff_detection_task.d \
./Src/leadoff_detector_obj.d \
./Src/main.d \
./Src/movement_detection_task.d \
./Src/movement_detector_obj.d \
./Src/qrs_detection_task.d \
./Src/qrs_obj.d \
./Src/recreation_curve_obj.d \
./Src/rr_window_obj.d \
./Src/rr_window_task.d \
./Src/smb380.d \
./Src/spi.d \
./Src/spi_low_level.d \
./Src/stm32l476g_discovery.d \
./Src/stm32l4xx_it.d \
./Src/temperature_measure_task.d \
./Src/thermometr_obj.d \
./Src/tim.d \
./Src/timer250hz.d \
./Src/timer250hz_irqhandler.d \
./Src/timer_100hz_irqhandler.d \
./Src/timer_100hz_obj.d \
./Src/timer_1hz_irqhandler.d \
./Src/timer_1hz_obj.d \
./Src/usart.d \
./Src/usbd_conf.d \
./Src/usbd_customhid_if.d \
./Src/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L476xx -I"D:/workspace/stm32/rzhdv_usb_github/usb_hid_test_02/Inc" -I"D:/workspace/stm32/rzhdv_usb_github/usb_hid_test_02/Drivers/STM32L4xx_HAL_Driver/Inc" -I"D:/workspace/stm32/rzhdv_usb_github/usb_hid_test_02/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"D:/workspace/stm32/rzhdv_usb_github/usb_hid_test_02/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/workspace/stm32/rzhdv_usb_github/usb_hid_test_02/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc" -I"D:/workspace/stm32/rzhdv_usb_github/usb_hid_test_02/Drivers/CMSIS/Include" -I"D:/workspace/stm32/rzhdv_usb_github/usb_hid_test_02/Drivers/CMSIS/Device/ST/STM32L4xx/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


