// by Marius Versteegen, 2024

#include <crt_CleanRTOS.h>        // This file includes crt_Config.h  You'll need to change defines there for a release build.

// All Tasks should be created in this main file.
#include "crt_TestInputfield.h"
namespace crt
{
	MainInits mainInits;            // Initialize CleanRTOS.
	TestInputfield testInputfield("TestInputfield", 2 /*priority*/, ARDUINO_RUNNING_CORE);
}

void setup()
{
	ESP_LOGI("checkpoint", "start of main");
}

void loop()
{
	vTaskDelay(1);// Nothing to do in loop - all example code runs in the 4 threads above.
}
