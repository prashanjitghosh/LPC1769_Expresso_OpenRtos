
/* Standard includes. */
#include "string.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
/* FreeRTOS+IO includes. */
#include "FreeRTOS_IO.h"

#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "uart.h"



/* Holds the handle of the task that implements the UART command console. */
static xTaskHandle xCommandConsoleTask = NULL;

/* Place holder for calls to ioctl that don't use the value parameter. */
#define cmdPARAMTER_NOT_USED		( ( void * ) 0 )

static void prvUARTCommandConsoleTask( void *pvParameters );

/* The peripheral used by the command interpreter (and the vWriteString()
function). */
static Peripheral_Descriptor_t xConsoleUART = NULL;

void UARTCommandConsole( void )
{
	xTaskCreate( 	prvUARTCommandConsoleTask,				/* The task that implements the command console. */
					( const int8_t * const ) "UARTCmd",		/* Text name assigned to the task.  This is just to assist debugging.  The kernel does not use this name itself. */
					configUART_COMMAND_CONSOLE_STACK_SIZE,	/* The size of the stack allocated to the task. */
					NULL,									/* The parameter is not used, so NULL is passed. */
					configUART_COMMAND_CONSOLE_TASK_PRIORITY,/* The priority allocated to the task. */
					&xCommandConsoleTask );					/* Used to store the handle to the created task. */
}


static void prvUARTCommandConsoleTask( void *pvParameters )
{

	UART_CFG_Type pcfgSerial = {
			                           (uint32_t)115200, //baudRate
			                           UART_PARITY_NONE, //No Parity
			                           UART_DATABIT_8,  // 8 data bits
			                           UART_STOPBIT_1  //1 Stop Bit
	};

	LPC_UART_TypeDef * const pxUART = ( LPC_UART_TypeDef * const )LPC_UART0;

	taskENTER_CRITICAL();
	{
	    UART_Init(pxUART, &pcfgSerial);

	    /* Enable the FIFO. */
	    xUARTFIFOConfig.FIFO_ResetRxBuf = ENABLE;
	    xUARTFIFOConfig.FIFO_ResetTxBuf = ENABLE;
	    xUARTFIFOConfig.FIFO_DMAMode = DISABLE;
	    xUARTFIFOConfig.FIFO_Level = UART_FIFO_TRGLEV2;
	    UART_FIFOConfig( pxUART, &xUARTFIFOConfig );

	    /* Enable Tx. */
	    UART_TxCmd( pxUART, ENABLE );
	}
	taskEXIT_CRITICAL();



}
