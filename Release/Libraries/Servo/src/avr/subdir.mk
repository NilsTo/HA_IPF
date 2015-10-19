################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Program\ Files\ (x86)/Arduino/libraries/Servo/src/avr/Servo.cpp 

LINK_OBJ += \
./Libraries/Servo/src/avr/Servo.cpp.o 

CPP_DEPS += \
./Libraries/Servo/src/avr/Servo.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Servo/src/avr/Servo.cpp.o: C:/Program\ Files\ (x86)/Arduino/libraries/Servo/src/avr/Servo.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Program Files (x86)/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=165-r5 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\mega" -I"C:\Program Files (x86)\Arduino\libraries\Servo" -I"C:\Program Files (x86)\Arduino\libraries\Servo\src" -I"C:\Program Files (x86)\Arduino\libraries\LiquidCrystal" -I"C:\Program Files (x86)\Arduino\libraries\LiquidCrystal\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


