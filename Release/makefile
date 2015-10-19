################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include arduino/core/subdir.mk
-include Libraries/Servo/src/sam/subdir.mk
-include Libraries/Servo/src/avr/subdir.mk
-include Libraries/LiquidCrystal/src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
C:/Arduino/Workspace/Arbeit_zu_Hause/Release/arduino.ar \

ELF += \
Arbeit_zu_Hause.elf \

EEP += \
Arbeit_zu_Hause.eep \

FLASH_IMAGE += \
Arbeit_zu_Hause.hex \


# All Target
all: Arbeit_zu_Hause

# Tool invocations
Arbeit_zu_Hause: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"C:/Program Files (x86)/Arduino/hardware/tools/avr/bin/avr-size" -A "C:/Arduino/Workspace/Arbeit_zu_Hause/Release/Arbeit_zu_Hause.elf"
	@echo 'Finished building target: $@'
	@echo ' '

C:/Arduino/Workspace/Arbeit_zu_Hause/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"C:/Program Files (x86)/Arduino/hardware/tools/avr/bin/avr-ar" rcs  "C:/Arduino/Workspace/Arbeit_zu_Hause/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

Arbeit_zu_Hause.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"C:/Program Files (x86)/Arduino/hardware/tools/avr/bin/avr-gcc" -w -Os -Wl,--gc-sections -mmcu=atmega2560  -o "C:/Arduino/Workspace/Arbeit_zu_Hause/Release/Arbeit_zu_Hause.elf"   $(LINK_OBJ) $(AR)  "C:/Arduino/Workspace/Arbeit_zu_Hause/Release/arduino.ar" "-LC:/Arduino/Workspace/Arbeit_zu_Hause/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

Arbeit_zu_Hause.eep: $(ELF)
	@echo 'Create eeprom image'
	"C:/Program Files (x86)/Arduino/hardware/tools/avr/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "C:/Arduino/Workspace/Arbeit_zu_Hause/Release/Arbeit_zu_Hause.elf" "C:/Arduino/Workspace/Arbeit_zu_Hause/Release/Arbeit_zu_Hause.eep"
	@echo 'Finished building: $@'
	@echo ' '

Arbeit_zu_Hause.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"C:/Program Files (x86)/Arduino/hardware/tools/avr/bin/avr-objcopy" -O ihex -R .eeprom  "C:/Arduino/Workspace/Arbeit_zu_Hause/Release/Arbeit_zu_Hause.elf" "C:/Arduino/Workspace/Arbeit_zu_Hause/Release/Arbeit_zu_Hause.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(C_DEPS)$(AR)$(EEP)$(FLASH_IMAGE)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(SIZEDUMMY)$(ELF)$(CPP_DEPS) Arbeit_zu_Hause
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
