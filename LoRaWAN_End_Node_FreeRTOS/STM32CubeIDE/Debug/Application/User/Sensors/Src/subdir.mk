################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Sensors/Src/app_bme280.c \
../Application/User/Sensors/Src/logger.c 

OBJS += \
./Application/User/Sensors/Src/app_bme280.o \
./Application/User/Sensors/Src/logger.o 

C_DEPS += \
./Application/User/Sensors/Src/app_bme280.d \
./Application/User/Sensors/Src/logger.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Sensors/Src/%.o Application/User/Sensors/Src/%.su Application/User/Sensors/Src/%.cyclo: ../Application/User/Sensors/Src/%.c Application/User/Sensors/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WL55xx -c -I../../Core/Inc -I../../LoRaWAN/App -I../../LoRaWAN/Target -I../../Drivers/STM32WLxx_HAL_Driver/Inc -I../../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../../Utilities/trace/adv_trace -I../../Utilities/misc -I../../Utilities/timer -I../../Utilities/lpm/tiny_lpm -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../../Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -I../../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../../Middlewares/Third_Party/LoRaWAN/Crypto -I../../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../../Middlewares/Third_Party/LoRaWAN/Mac -I../../Middlewares/Third_Party/LoRaWAN/LmHandler -I../../Middlewares/Third_Party/LoRaWAN/Utilities -I../../Middlewares/Third_Party/SubGHz_Phy -I../../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/STM32WLxx_Nucleo -I"F:/01-Especializacion en sistemas embebidos/IoT_workspace/LoRaWAN_End_Node_FreeRTOS/STM32CubeIDE/Application/User/Sensors/Inc" -I"F:/01-Especializacion en sistemas embebidos/IoT_workspace/LoRaWAN_End_Node_FreeRTOS/STM32CubeIDE/Application/User/Sensors/BME280/Inc" -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-2f-User-2f-Sensors-2f-Src

clean-Application-2f-User-2f-Sensors-2f-Src:
	-$(RM) ./Application/User/Sensors/Src/app_bme280.cyclo ./Application/User/Sensors/Src/app_bme280.d ./Application/User/Sensors/Src/app_bme280.o ./Application/User/Sensors/Src/app_bme280.su ./Application/User/Sensors/Src/logger.cyclo ./Application/User/Sensors/Src/logger.d ./Application/User/Sensors/Src/logger.o ./Application/User/Sensors/Src/logger.su

.PHONY: clean-Application-2f-User-2f-Sensors-2f-Src

