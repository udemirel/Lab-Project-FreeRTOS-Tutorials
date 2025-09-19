/*
Concepts
Each FreeRTOS task requires 2 blocks of memory -

Task Control Block (TCB) - FreeRTOS-Kernel uses it to store the control information of a task.
Stack - Each task maintains its own stack.
If a task is created using xTaskCreate API, then the memory needed for TCB and Stack is allocated from the FreeRTOS heap by calling pvPortMalloc. If a task is created using xTaskCreateStatic API, then the memory needed for TCB and Stack is provided by the application writer.
 *
 */

/* Standard includes. */
#include <stdio.h>
#include <unistd.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/**
 * @brief Function that implement FreeRTOS task.
 */
static void prvTaskFunction( void * pvParams );
/*-----------------------------------------------------------*/

/**
 * @brief TCB and stack buffers for the task.
 */
static StaticTask_t xTaskTcbBuffer;
static StackType_t xTaskStackBuffer[ configMINIMAL_STACK_SIZE ];
/*-----------------------------------------------------------*/

/**
 * @brief Tutorial entry point.
 */
int main( void )
{
    TaskHandle_t xCreatedTaskHandle = NULL;

    /* TODO 1 - Create a FreeRTOS task using xTaskCreateStatic API which
     * uses prvTaskFunction as the task function.
     *
     * Use the following values for xTaskCreateStatic parameters:
     * pxTaskCode       prvTaskFunction
     * pcName           "Task1"
     * ulStackDepth     configMINIMAL_STACK_SIZE
     * pvParameters     NULL
     * uxPriority       tskIDLE_PRIORITY
     * puxStackBuffer   &( xTaskStackBuffer[ 0 ] )
     * pxTaskBuffer     &( xTaskTcbBuffer )
     *
     * Assign the return value to xCreatedTaskHandle.
     */
    // FreeRTOS’ta xTaskCreate() heap kullanır, xTaskCreateStatic() stack ve TCB’yi statik olarak yönetir.
    /*
     * NOT:
     * xTaskCreate yerine xTaskCreateStatic kullanmak, Görev Kontrol Bloğu (TCB) ve stack’in
     * statik olarak belirlenmesini sağlar. Bunun avantajları:
     * 1. Deterministik davranış: Heap tahsisi sırasında oluşabilecek gecikmeler yok.
     * 2. Daha iyi performans: Statik tahsis, runtime malloc’a göre daha hızlıdır.
     * 3. Güvenlik ve kararlılık: Heap parçalanması veya tahsis hatası riski yok.
     * 4. Stack yönetimi kolaylığı: Her görevin stack boyutu önceden bilinir ve sabittir.
     * Gerçek zamanlı ve gömülü sistemlerde bu nedenlerle statik tahsis tercih edilir.
     */
    xCreatedTaskHandle = xTaskCreateStatic(
        prvTaskFunction,
        "Task1",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY,
        &(xTaskStackBuffer[0]),
        &(xTaskTcbBuffer));
    configASSERT( xCreatedTaskHandle != NULL );

    /* TODO 2 - Call vTaskStartScheduler to start the scheduler. */
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
    /* Silence warning about unused parameters. */
    ( void ) pvParams;

    for( ;; )
    {
        fprintf( stderr, "Tutorial 3 running...\r\n" );

        /* Pause for a second. */
        vTaskDelay( pdMS_TO_TICKS( 1000 ) );
    }
}
/*-----------------------------------------------------------*/
