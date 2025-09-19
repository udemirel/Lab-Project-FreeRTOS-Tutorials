/*
Örnek Kullanim
typedef struct {
    int sensorPin;
    int readInterval;
} SensorParams_t;

static void vSensorTask(void *pvParams)
{
    SensorParams_t *params = (SensorParams_t*)pvParams;
    for(;;)
    {
        int value = readSensor(params->sensorPin);
        printf("Sensor %d value: %d\n", params->sensorPin, value);
        vTaskDelay(pdMS_TO_TICKS(params->readInterval));
    }
}

int main(void)
{
    SensorParams_t s1 = { .sensorPin = 3, .readInterval = 1000 };
    SensorParams_t s2 = { .sensorPin = 5, .readInterval = 2000 };

    xTaskCreate(vSensorTask, "Sensor1", 100, &s1, 1, NULL);
    xTaskCreate(vSensorTask, "Sensor2", 100, &s2, 1, NULL);

    vTaskStartScheduler();
}
*/
/* Standard includes. */
#include <stdio.h>
#include <unistd.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/**
 * @brief Function that implement FreeRTOS tasks.
 */
static void prvTaskFunction( void * pvParams );
/*-----------------------------------------------------------*/

/**
 * @brief Tutorial entry point.
 */
int main( void )
{
    BaseType_t xTaskCreationResult = pdFAIL;
    int a = 5;
    int b = 6;
    /* TODO 1 - Create a FreeRTOS task using xTaskCreate API which
     * uses prvTaskFunction as the task function.
     *
     * Use the following values for xTaskCreate parameters:
     * pxTaskCode       prvTaskFunction
     * pcName           "Task1"
     * usStackDepth     configMINIMAL_STACK_SIZE
     * pvParameters     ( void * ) 1
     * uxPriority       tskIDLE_PRIORITY
     * pxCreatedTask    NULL
     *
     * Assign the return value to xTaskCreationResult.
     */
    xTaskCreationResult = xTaskCreate(
        prvTaskFunction,
        "Task1",
        configMINIMAL_STACK_SIZE,
        &a, //(void *)1,
        tskIDLE_PRIORITY,
        NULL
    );
    configASSERT( xTaskCreationResult == pdPASS );

    /* TODO 2 - Create a FreeRTOS task using xTaskCreate API which
     * uses prvTaskFunction as the task function.
     *
     * Use the following values for xTaskCreate parameters:
     * pxTaskCode       prvTaskFunction
     * pcName           "Task2"
     * usStackDepth     configMINIMAL_STACK_SIZE
     * pvParameters     ( void * ) 2
     * uxPriority       tskIDLE_PRIORITY
     * pxCreatedTask    NULL
     *
     * Assign the return value to xTaskCreationResult.
     */
    xTaskCreationResult = xTaskCreate(
        prvTaskFunction,
          "Task2",
          configMINIMAL_STACK_SIZE,
          &b, //( void * ) 2,
          tskIDLE_PRIORITY,
          NULL
    );
    configASSERT( xTaskCreationResult == pdPASS );

    /* Start the scheduler. */
    vTaskStartScheduler();

    /* Should not reach here. */
    for( ;; )
    {

    }

    /* Just to make the compiler happy. */
    return 0;
}
/*-----------------------------------------------------------*/

static void prvTaskFunction( void * pvParams )
{
    int taskID = *(int*)pvParams; // pvParams pointer’dan değeri al    
    for( ;; )
    {
        fprintf( stderr, "Tutorial 5 task %p running...\r\n", pvParams );
        fprintf( stderr, "Tutorial 5 task %d running...\r\n", taskID );

        vTaskDelay( pdMS_TO_TICKS( 1000 ) );
    }
}
/*-----------------------------------------------------------*/
