################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
XMLSER_CPP_SRCS += \
../src/modules/jobs/JobScheduler.cpp \
../src/modules/jobs/CronTimer.cpp

XMLSER_OBJS += \
./JobScheduler.o \
./CronTimer.o


XMLSER_CPP_DEPS += \
./JobScheduler.d \
./CronTimer.d


# Each subdirectory must supply rules for building sources it contributes
%.o: ../src/modules/jobs/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ $(PTHREADS) -l ../src/ -I../include -I/usr/local/include -O0 -Wall -g3 -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


