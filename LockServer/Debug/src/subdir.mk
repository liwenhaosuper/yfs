################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/gettime.cc \
../src/lock_server.cc \
../src/lock_smain.cc \
../src/lock_tester.cc 

OBJS += \
./src/gettime.o \
./src/lock_server.o \
./src/lock_smain.o \
./src/lock_tester.o 

CC_DEPS += \
./src/gettime.d \
./src/lock_server.d \
./src/lock_smain.d \
./src/lock_tester.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


