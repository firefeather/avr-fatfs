

/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/

#include "diskio.h"
#include "sd.h"


/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */
/* Note that Tiny-FatFs supports only single drive and always            */
                                      

////////////////////////////
/*
   struct tm {
   	int tm_sec;   // �� seconds after the minute, 0 to 60
   	int tm_min;   // �� minutes after the hour, 0 to 59
	int tm_hour;  // ʱ hours since midnight, 0 to 23*
	int tm_mday;  // �� day of the month, 1 to 31
	int tm_mon;   // �� months since January, 0 to 11
	int tm_year;  // �� years since 1900
	int tm_wday;  // ���� days since Sunday, 0 to 6
	int tm_yday;  // ��Ԫ��������� days since January 1, 0 to 365
 	int tm_isdst; // ����ʱ����Daylight Savings Time flag
 	};
*/
/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */

DSTATUS disk_initialize ( 
BYTE drv				/* Physical drive nmuber (0..) */
)
{
    unsigned char state;

    if(drv)
    {
        return STA_NOINIT;  //��֧�ִ���0�Ĳ���
    }

    state = SD_Init();
    if(state == STA_NODISK)
    {
        return STA_NODISK;
    }
    else if(state != 0)
    {
        return STA_NOINIT;  //�������󣺳�ʼ��ʧ��
    }
    else
    {
        return 0;           //��ʼ���ɹ�
    }
}



/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{
    if(drv)
    {
        return STA_NOINIT;  //��֧�ִ���0����
    }
    return 0;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{
	unsigned char res=0;
    if (drv || !count)
    {    
        return RES_PARERR;  //��֧�ֵ����̲�����count���ܵ���0�����򷵻ز�������
    }

    if(count==1)            //1��sector�Ķ�����      
    {                                                
        res = SD_Read_Sector(sector, buff);      
    }                                                                                                 

    //������ֵ����SD_driver.c�ķ���ֵת��ff.c�ķ���ֵ
    if(res == 0x00)
    {
        return RES_OK;
    }
    else
    {
        return RES_ERROR;
    }
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	BYTE *buff,	        /* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
    if (drv || !count)
    {    
        return RES_PARERR;  //��֧�ֵ����̲�����count���ܵ���0�����򷵻ز�������
    }   
   // ��д����
    SD_Write_Sector(sector,buff);
	  
    return RES_OK;
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
 	drv=drv;
	ctrl=ctrl;
	buff=buff;
	return 0;
}
DWORD get_fattime (void)
{

  return 1950466005;
}
