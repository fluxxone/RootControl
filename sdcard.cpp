#include "sdcard.h"
#include "SDCard/SD_Card/sdio_sd.h"
#include "SDCard/FATFS/src/ff.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "string.h"
#include "stdio.h"
void SD_LowLevel_Init();
void NVIC_Configuration();
int SD_TotalSize();
FRESULT scan_files (char* path);
SDCard::SDCard()
{
	_initialized = false;
	//DEBUG.print("SD Card init\r\n");
	SD_LowLevel_Init();
	NVIC_Configuration();
	if( SD_Detect() == SD_PRESENT )
	{
		//DEBUG.print("SD card detected OK!\r\n");
	}
	else
	{
		//DEBUG.print("SD card NOT detected!\r\n");
		return;
	}
	res = f_mount(0,&fs);
	if (res == FR_OK)
		_initialized = true;
	//DEBUG.print("SD Card initialized.!\r\n");
	//res = f_open( &fsrc , "0:/Demo.TXT" , FA_CREATE_NEW | FA_WRITE);

//	if ( res == FR_OK )
//	{
//		/* Write buffer to file */
//		res = f_write(&fsrc, "DEMO TEXT!!!\n123", sizeof("DEMO TEXT!!!\n123"), &br);

//		DEBUG.print("Demo.TXT successfully created\r\n");

//		/*close file */
//		f_close(&fsrc);
//	}
//	else if ( res == FR_EXIST )
//	{
//		DEBUG.print("Demo.TXT created in the disk\r\n");
//	}

//	scan_files("0:");
//	SD_TotalSize();

}

SDCard& SDCard::getInstance()
{
	static SDCard sInstance;
	return sInstance;
}

void SD_LowLevel_Init()
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /*!< GPIOC and GPIOD Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | SD_DETECT_GPIO_CLK, ENABLE);

  /*!< Configure PC.08, PC.09, PC.10, PC.11, PC.12 pin: D0, D1, D2, D3, CLK pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /*!< Configure PD.02 CMD line */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /*!< Configure SD_CD pin: SD Card detect pin */
  GPIO_InitStructure.GPIO_Pin = SD_DETECT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(SD_DETECT_GPIO_PORT, &GPIO_InitStructure);

  /*!< Enable the SDIO AHB Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_SDIO, ENABLE);

  /*!< Enable the DMA2 Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
}

void NVIC_Configuration()
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

int SD_TotalSize()
{
	FATFS *fs;
	DWORD fre_clust;
	FRESULT res;
	res = f_getfree("0:", &fre_clust, &fs);
	if ( res==FR_OK )
	{
		/* Print free space in unit of MB (assuming 512 bytes/sector) */
//		DEBUG.print("\r\n%d MB total drive space.\r\n"
//			    "%d MB available.\r\n",
//			   ( (fs->n_fatent - 2) * fs->csize ) / 2 /1024 , (fre_clust * fs->csize) / 2 /1024 );

		return ENABLE;
	}
	else
		return DISABLE;
}
FRESULT scan_files (char* path)
{
    FILINFO fno;
    DIR dir;
    int i;
    char *fn;
    FRESULT res;
#if _USE_LFN
    static char lfn[_MAX_LFN * (_DF1S ? 2 : 1) + 1];
    fno.lfname = lfn;
    fno.lfsize = sizeof(lfn);
#endif

    res = f_opendir(&dir, path);
    if (res == FR_OK) {
	i = strlen(path);
	for (;;) {
	    res = f_readdir(&dir, &fno);
	    if (res != FR_OK || fno.fname[0] == 0) break;
	    if (fno.fname[0] == '.') continue;
#if _USE_LFN
	    fn = *fno.lfname ? fno.lfname : fno.fname;
#else
	    fn = fno.fname;
#endif
	    if (fno.fattrib & AM_DIR) {
		sprintf(&path[i], "/%s", fn);
		res = scan_files(path);
		if (res != FR_OK) break;
		path[i] = 0;
	    } else {
		//DEBUG.print("%s/%s \r\n", path, fn);
	    }
	}
    }

    return res;
}


extern "C"
{
	void SDIO_IRQHandler(void)
	{
	  /* Process All SDIO Interrupt Sources */
	  SD_ProcessIRQSrc();
	}
}
