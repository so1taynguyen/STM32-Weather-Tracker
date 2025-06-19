################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ADXL.c \
../Core/Src/MAX30102.c \
../Core/Src/SHT31.c \
../Core/Src/algorithm.c \
../Core/Src/fonts.c \
../Core/Src/freertos.c \
../Core/Src/main.c \
../Core/Src/st7789.c \
../Core/Src/stm32h7xx_hal_msp.c \
../Core/Src/stm32h7xx_hal_timebase_tim.c \
../Core/Src/stm32h7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32h7xx.c 

C_DEPS += \
./Core/Src/ADXL.d \
./Core/Src/MAX30102.d \
./Core/Src/SHT31.d \
./Core/Src/algorithm.d \
./Core/Src/fonts.d \
./Core/Src/freertos.d \
./Core/Src/main.d \
./Core/Src/st7789.d \
./Core/Src/stm32h7xx_hal_msp.d \
./Core/Src/stm32h7xx_hal_timebase_tim.d \
./Core/Src/stm32h7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32h7xx.d 

OBJS += \
./Core/Src/ADXL.o \
./Core/Src/MAX30102.o \
./Core/Src/SHT31.o \
./Core/Src/algorithm.o \
./Core/Src/fonts.o \
./Core/Src/freertos.o \
./Core/Src/main.o \
./Core/Src/st7789.o \
./Core/Src/stm32h7xx_hal_msp.o \
./Core/Src/stm32h7xx_hal_timebase_tim.o \
./Core/Src/stm32h7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32h7xx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I"C:/Users/Nguyen Van Linh/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.2/Drivers/STM32H7xx_HAL_Driver/Inc" -I"C:/Users/Nguyen Van Linh/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.2/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Nguyen Van Linh/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.2/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/Nguyen Van Linh/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.2/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"C:/Users/Nguyen Van Linh/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.2/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/Nguyen Van Linh/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.2/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"C:/Users/Nguyen Van Linh/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.2/Drivers/CMSIS/Include" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/ADXL.cyclo ./Core/Src/ADXL.d ./Core/Src/ADXL.o ./Core/Src/ADXL.su ./Core/Src/MAX30102.cyclo ./Core/Src/MAX30102.d ./Core/Src/MAX30102.o ./Core/Src/MAX30102.su ./Core/Src/SHT31.cyclo ./Core/Src/SHT31.d ./Core/Src/SHT31.o ./Core/Src/SHT31.su ./Core/Src/algorithm.cyclo ./Core/Src/algorithm.d ./Core/Src/algorithm.o ./Core/Src/algorithm.su ./Core/Src/fonts.cyclo ./Core/Src/fonts.d ./Core/Src/fonts.o ./Core/Src/fonts.su ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/st7789.cyclo ./Core/Src/st7789.d ./Core/Src/st7789.o ./Core/Src/st7789.su ./Core/Src/stm32h7xx_hal_msp.cyclo ./Core/Src/stm32h7xx_hal_msp.d ./Core/Src/stm32h7xx_hal_msp.o ./Core/Src/stm32h7xx_hal_msp.su ./Core/Src/stm32h7xx_hal_timebase_tim.cyclo ./Core/Src/stm32h7xx_hal_timebase_tim.d ./Core/Src/stm32h7xx_hal_timebase_tim.o ./Core/Src/stm32h7xx_hal_timebase_tim.su ./Core/Src/stm32h7xx_it.cyclo ./Core/Src/stm32h7xx_it.d ./Core/Src/stm32h7xx_it.o ./Core/Src/stm32h7xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32h7xx.cyclo ./Core/Src/system_stm32h7xx.d ./Core/Src/system_stm32h7xx.o ./Core/Src/system_stm32h7xx.su

.PHONY: clean-Core-2f-Src

