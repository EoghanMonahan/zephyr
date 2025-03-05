/*
 * Copyright (c) 2023, Meta
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <iostream>

#include "pthread.h"
#include "mqueue.h"
#include "signal.h"

#include "appconnector.h"
#include "nativeapp.h"
#include "tppdu.h"
#include "datatypes.h"
#include "shared.h"

#include "hssems.h"
#include "hsudp.h"
#include "hsthreads.h"
#include "hsqueues.h"
#include "toolthreads.h"
#include "serverstate.h"
#include "ad74416h.h"

template<> bool AppConnector<AppPdu>::time2stop = false;
// FILE *p_toolLogPtr = NULL;
static uint16_t portNum = 5094;
enum AppState eAppState = APP_STOP;

pthread_t popRxThrID;  // used by Server to read msg from APP
pthread_t popTxThrID;  // used by APP to read msg from Server
pthread_t socketThrID; // used by Server to read socket
pthread_t appThrID = 0; // used by Server to launch the APP program

// template <AppPdu>
// uint16_t AppConnector<AppPdu>::getStats(uint16_t &stxs, uint16_t &acks, uint16_t &baks)
// {
// 	return 0;
// }

int signal(int signum, void (*_sig_func_ptr)(int))
{
	return 0;
}

int raise(int sig)
{
	return 0;
}

AppConnector<AppPdu> *pAppConnector = NULL;
//App *pGlobalApp = NULL;
NativeApp *pGlobalApp = NULL;

errVal_t NativeApp::getLowMAC(uint8_t *pArr, bool getFullAddress)
{
	return 0;
}



errVal_t serializationFile::putData(void)
{
	return 0;
}

errVal_t serializationFile::getData(void)
{
	return 0;
}

void serializationFile::Close_File(void)
{
	return 0;
}

bool serializationFile::CheckFile(char* filespec)
{
	return true;
}


int serializationFile::Open_File(char* filespec, int filespecLen)
{
	return 0;
}

serializationFile::serializationFile()
{
	pFD = NULL;
}

serializationFile::~serializationFile()
{
	if ( pFD )
	{
		// fclose(pFD);
		pFD = NULL;
	}
}


errVal_t NativeApp::initHostNameDns()
{
	return 0;
}

void bcm2835_delay(unsigned int millis)
{

}

errVal_t create_hs_semaphores(uint8_t createFlag)
{
	errVal_t errVal = SEM_ERROR;

	const char *funcName = "create_hs_semaphores";

	/* Create/open all synchronization semaphores */
	uint8_t initVal = (createFlag ? SEMTAKEN : SEMIGN);

	do
	{
		if (create_semaphores(createFlag) != NO_ERROR)
		{
			break;
		}
		// #191
		char semStop[SEM_NAME_SIZE] = "semStopMainThr";
		char semServ[SEM_NAME_SIZE] = "semServerTables";
		createUniqueName(semStop);

		p_semStopMainThr = open_a_semaphore(semStop, createFlag,
				initVal);
		if (p_semStopMainThr == NULL)
		{
			printf("Null p_semStopMainThr\n");
			break;
		}

		createUniqueName(semServ);
		p_semServerTables = open_a_semaphore(semServ, createFlag,
				initVal);
		if (p_semServerTables == NULL)
		{
			printf("Null p_semServerTables\n");
			break;
		}

		errVal = NO_ERROR;
	} while (0);

	if ((createFlag) && (errVal == NO_ERROR))
	{
		// dbgp_init("  %d %s Semaphores Created\n", get_sem_count(), TOOL_NAME);
		sem_post(p_semServerTables);	// access to Server Tables is enabled
	}
	else
	{
		printf("Failed to create p_semServerTables");
	}
	dbgp_init("----------------------------------\n");

	return errVal;
}

static errVal_t create_hs_threads(void)
{
	const char *popRxThrName = "popRxMsg Thread";
	const char *popTxThrName = "popTxMsg Thread";
	const char *socketThrName = "Socket Thread";
	errVal_t errval = NO_ERROR;

	/* Thread to process HServer socket communication */
	errval = start_a_thread(&socketThrID, socketThrFunc, socketThrName);

	/* Thread for Server to receive msg from APP */
	//errval = start_a_thread(&popRxThrID, popRxThrFunc, popRxThrName);

	return (errval);
}

void shutdown_server(void)
{
	// Send the signal for Ctrl+C to the thread.
	// #6004
	// sighandler_hs_endall(SIGINT);
}

void *run_io(void *data)
{
	sharedArgs_s *pshared = (sharedArgs_s *)data;

	// memset(pshared->padc, 0xEF, 4 * sizeof(pshared->padc));

	for (int idx = 0;; idx++){
		sem_wait(pshared->pSemaPhore);
		for (int i = 0; i < 3; i++){
			pshared->padc[i] = 0x7845 + (idx << 8);
		}
		(*pshared->upCnt)++;
		sem_post(pshared->pSemaPhore);

		// printf("run_io running\n");
		k_sleep(K_MSEC(10));
	}

	return NULL;
}

struct ad74416h_desc *ad74416h;


int main(void)
{
	int ret;
	uint16_t reg_read;
	errVal_t errval = NO_ERROR;
	char *app_name = "ADI HART-IP Zephyr Server";
	struct ad74416h_init_param ad74416h_ip = {
		.id = 	ID_AD74416H,
	};

	ret = ad74416h_init(&ad74416h,
			    &ad74416h_ip);
	if (ret) {
		printf("%s:%d: error\n", __func__, __LINE__);
	} else {
		//printf("%s:%d: success\n", __func__, __LINE__);
	}

	ret = ad74416h_gpio_set(ad74416h, AD74416H_CH_B, NO_OS_GPIO_HIGH);
	if (ret)
		printf("ad74416h_gpio_set() failed\n");

	ret = ad74416h_gpio_set(ad74416h, AD74416H_CH_D, NO_OS_GPIO_HIGH);
	if (ret)
		printf("ad74416h_gpio_set() failed\n");


	/* Configure the channel in the appropriate function (current input loop powered with HART) */
	ret = ad74416h_reg_update(ad74416h, AD74416H_CH_FUNC_SETUP(0),
				  AD74416H_CH_FUNC_SETUP_MSK,
				  AD74416H_CURRENT_IN_LOOP_HART);
	if (ret)
		printf("%s:%d: error\n", __func__, __LINE__);

	/* Wait 200 μs before proceeding with another step */
	no_os_udelay(200);

	/* Wait until HART Compliant Slew is Settled */
	while (1) {
		ret = ad74416h_reg_read(ad74416h,
					AD74416H_OUTPUT_CONFIG(0), &reg_read);
		if (ret)
			printf("%s:%d: error\n", __func__, __LINE__);
		reg_read = no_os_field_get(AD74416H_HART_COMPL_SETTLED_MSK, reg_read);
		if (reg_read == 1)
			break;
	}

	/* Enable the HART slew option SLEW_EN to binary 10 (SLEW_HART_COMPL) */
	ret = ad74416h_reg_update(ad74416h, AD74416H_OUTPUT_CONFIG(0),
				  AD74416H_SLEW_EN_MSK, 2);
	if (ret)
		printf("%s:%d: error\n", __func__, __LINE__);

	/* Power up the HART modem */
	ret = ad74416h_reg_update(ad74416h, AD74416H_HART_CONFIG(0), AD74416H_MODEM_PWRUP_MSK, 1);
	if (ret)
		printf("%s:%d: error\n", __func__, __LINE__);

	ret = create_hs_semaphores(1);

	ret = create_hs_threads();

	while(1){
		k_sleep(K_MSEC(10));
	}

	return 0;
}