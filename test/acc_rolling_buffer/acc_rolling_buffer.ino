#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#include "Adafruit_LIS3DH.h"
Adafruit_LIS3DH accelerometer;

int global_variable = 0;

// define two tasks for println1 and println2
void TaskPrintLn_1(void *pvParameters);
void TaskPrintLn_2(void *pvParameters);

// setup function runs once when you press reset or power the board.
void setup()
{
	delay(1000);
        Serial.begin(115200);

        // Now set up two tasks to run indepenedently.
	xTaskCreatePinnedToCore(
		TaskPrintLn_1
		,	"TaskPrintLn_1"			// A name for people to understand
		,	2048				// Stack size
		,	NULL
		,	2				// Priority [Highest 3 -> Lowest 0]
		,	NULL
		,	ARDUINO_RUNNING_CORE);

	xTaskCreatePinnedToCore(
		TaskPrintLn_2				// Task function pointer
		,	"TaskPrintLn_2"			// Task name for people
		,	2048				// Stack size
		,	NULL				// Paramaters
		,	1				// Priority
		,	NULL				// TaskHandle_t created Task
		, 	ARDUINO_RUNNING_CORE);

	// Now the task scheduler is automatically started.
}

void loop()
{
	// Empty. Things done in Tasks.
}

void TaskPrintLn_1(void *pvParameters)
{
	(void) pvParameters;

	// Task initialization...
	accelerometer.setDataRate(LIS3DH_DATARATE_LOWPOWER_1K6HZ);
	accelerometer.setRange(LIS3DH_RANGE_16_G);
	accelerometer.begin(LIS3DH_DEFAULT_ADDRESS);
	accelerometer.printSensorDetails();
	float x;
	float y;
	float z;

	for (;;)  // A task *MUST* never return or exit.
	{
		accelerometer.read();
		x = accelerometer.x_g;
		y = accelerometer.y_g;
		z = accelerometer.z_g;
		Serial.printf("x: %0.3f\ty: %0.3f\tz: %0.3f\n", x, y, z);
		delay(1000);
	}
}

void TaskPrintLn_2(void *pvParameters)
{
	(void) pvParameters;

	// Task initialization goes here...

	for (;;)
	{
		Serial.println();
		Serial.println("Task 2 doing nothing.");
		Serial.println();
		delay(5000);
	}
}
