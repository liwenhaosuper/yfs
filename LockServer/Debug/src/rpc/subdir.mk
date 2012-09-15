################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/rpc/connection.cc \
../src/rpc/jsl_log.cc \
../src/rpc/pollmgr.cc \
../src/rpc/rpc.cc \
../src/rpc/rpctest.cc \
../src/rpc/thr_pool.cc 

OBJS += \
./src/rpc/connection.o \
./src/rpc/jsl_log.o \
./src/rpc/pollmgr.o \
./src/rpc/rpc.o \
./src/rpc/rpctest.o \
./src/rpc/thr_pool.o 

CC_DEPS += \
./src/rpc/connection.d \
./src/rpc/jsl_log.d \
./src/rpc/pollmgr.d \
./src/rpc/rpc.d \
./src/rpc/rpctest.d \
./src/rpc/thr_pool.d 


# Each subdirectory must supply rules for building sources it contributes
src/rpc/%.o: ../src/rpc/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


