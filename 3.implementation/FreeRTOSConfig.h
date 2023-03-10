/*
 * FreeRTOS V202212.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <lpc21xx.h>
#include <stdlib.h>
#include <stdio.h>
#include "gpio.h"
/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/
 /* Tasks variables */
extern int TasksInTime[6],TasksOutTime[6],TasksTotalTime[6],Task_Loads[6];
extern int System_Time    ;
extern int CPU_Load        ;

/* configure dynamic allocation   1 */
#define configSUPPORT_DYNAMIC_ALLOCATION 1

/* configure size queue  0 */
#define configQUEUE_REGISTRY_SIZE 	     0

#define configUSE_EDF_SCHEDULER 1
#define configUSE_PREEMPTION		1
#define configUSE_IDLE_HOOK			1
#define configUSE_TICK_HOOK			1
#define configCPU_CLOCK_HZ			( ( unsigned long ) 60000000 )	/* =12.0MHz xtal multiplied by 5 using the PLL. */
#define configTICK_RATE_HZ			( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES		( 4 )
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 90 )
#define configTOTAL_HEAP_SIZE		( ( size_t ) 13 * 1024 )
#define configMAX_TASK_NAME_LEN		( 8 )
#define configUSE_TRACE_FACILITY	0
#define configUSE_16_BIT_TICKS		0
#define configIDLE_SHOULD_YIELD		1

#define configQUEUE_REGISTRY_SIZE 	0
#define configUSE_APPLICATION_TASK_TAG 1
/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Run time configuration */
#define configUSE_APPLICATION_TASK_TAG            1
#define configUSE_STATS_FORMATTING_FUNCTIONS      1
#define configGENERATE_RUN_TIME_STATS             1
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()  /* Empty because you configured the timer */
#define portGET_RUN_TIME_COUNTER_VALUE()          (T1TC)

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	0
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1


														
#define traceTASK_SWITCHED_IN() do\
																{\
																	if(pxCurrentTCB!=xIdleTaskHandle)\
																{\
																	switch((int)pxCurrentTCB->pxTaskTag)\
																	 {\
																		case 20:\
																		TasksInTime[0]=T1TC;\
																		break;\
																		case 21:\
																		TasksInTime[1]=T1TC;\
																		break;\
																		case 22:\
																		TasksInTime[2]=T1TC;\
																		break;\
																		case 23:\
																		TasksInTime[3]=T1TC;\
																		break;\
																		case 24:\
																		TasksInTime[4]=T1TC;\
																		break;\
																		case 25:\
																		TasksInTime[5]=T1TC;\
																		break;\
																	}\
																  GPIO_write(PORT_0, (pinX_t)pxCurrentTCB->pxTaskTag , PIN_IS_HIGH);\
																}\
																}while(0)
//
#define traceTASK_SWITCHED_OUT() do\
																 {\
																 if(pxCurrentTCB!=xIdleTaskHandle)\
																 {\
																	 switch((int)pxCurrentTCB->pxTaskTag)\
																	 {\
																		case 20:\
																			TasksOutTime[0]=T1TC;\
																			TasksTotalTime[0]+=(T1TC - TasksInTime[0]);\
																			Task_Loads[0]=((TasksTotalTime[0]*100)/(float)System_Time);\
																		break;\
																		case 21:\
																			TasksOutTime[1]=T1TC;\
																			TasksTotalTime[1]+=(T1TC - TasksInTime[1]);\
																			Task_Loads[1]=((TasksTotalTime[1]*100)/(float)System_Time);\
																		break;\
																		case 22:\
																			TasksOutTime[2]=T1TC;\
																			TasksTotalTime[2]+=(T1TC - TasksInTime[2]);\
																			Task_Loads[2]=((TasksTotalTime[2]*100)/(float)System_Time);\
																		break;\
																		case 23:\
																			TasksOutTime[3]=T1TC;\
																			TasksTotalTime[3]+=(T1TC - TasksInTime[3]);\
																			Task_Loads[3]=((TasksTotalTime[3]*100)/(float)System_Time);\
																		break;\
																		case 24:\
																			TasksOutTime[4]=T1TC;\
																			TasksTotalTime[4]+=(T1TC - TasksInTime[4]);\
																			Task_Loads[4]=((TasksTotalTime[4]*100)/(float)System_Time);\
																		break;\
																		case 25:\
																			TasksOutTime[5]=T1TC;\
																			TasksTotalTime[5]+=(T1TC - TasksInTime[5]);\
																			Task_Loads[5]=((TasksTotalTime[5]*100)/(float)System_Time);\
																		break;\
																		}\
																		System_Time=T1TC;\
																		CPU_Load=(((TasksTotalTime[0]+TasksTotalTime[1]+TasksTotalTime[2]+TasksTotalTime[3]+TasksTotalTime[4]+TasksTotalTime[5])*100)/ (float)System_Time);\
																		GPIO_write(PORT_0, (pinX_t)pxCurrentTCB->pxTaskTag , PIN_IS_LOW);\
																 }\
																 }while(0)\
																 
#endif /* FREERTOS_CONFIG_H */
