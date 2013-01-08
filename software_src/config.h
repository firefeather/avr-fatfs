#ifndef _CONFIG_H_
#define _CONFIG_H_
//debugѡ��
#define _DEBUG
//#define _LCDDEBUG
#define _UARTDEBUG

//���Ͷ���
#define INT8   char
#define UINT8  unsigned char
#define INT16  int 
#define UINT16 unsigned int 
#define INT32  long 
#define UINT32 unsigned long 
#define nop()    NOP()
//����ͷ�ļ�
#include "iom128v.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <macros.h>
#include "main.h"
//�ļ�ϵͳ
#include "sd.h"
#include "SPI.h"
#include "diskio.h"
#include "ff.h"
//����
#include "usart.h"
//��ʱ����
#include "delay.h"
//LCD��ʾ
#include "lcd.h"
//������
#include "beep.h"
//�̵���
#include "relay.h"
//�¶ȴ�����
#include "DS18B20_driver.h"
//ʱ��
#include "ds1302.h"
//���ٴ�����
//�������
#include "key.h"
//�������
#include "gui.h"
//��ص������
#include "powercheck.h"

struct DATA {
   char  ID;
   char  Name[9]	  ;
   unsigned int Index ;
   char IndexChar[6]  ;
   char  Date[9]	  ;
   char	Time[10] 	  ;
   float    Temperature	   ;  //�¶�
   char  TempChar[6]  ;       //ÿ����ֵ����������char�ͱ�����������ʾ����
   float    WindSpeed ;
   char  WSChar[5]    ;
   float    WCI ;   //����ָ��
   char  WCIChar[6]   ;
   float    ECT ;   //�ȼ������¶�
   char  ECTChar[6]   ;
   float    Teq ;	//�൱�¶�
   char  TeqChar[6] ;
   unsigned char    WeiHai		  ;   //����Σ����(������ʾ)
   unsigned char    LowLabor	  ;   //���
   unsigned char    MidLabor	  ;   //�ж�
   unsigned char    HighLabor	  ;   //�ض�
   };
 struct CONFIG {
 		char Sd;
		char Relay;
		char LcdBackLight;
		char BackTemp;
		long THRESHOLD_delta_sec;
		long time1;
		long now;
		char autocheck;
		
  };  
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
extern struct CONFIG config; 
extern const char devicename[8];//�豸����
extern const char deviceId ;	
extern  struct  tm t; //�ļ�ϵͳʱ��洢�ṹ��
extern unsigned char time_buf[8]; //�ⲿ���� �洢��1302��ʱ���ԭʼ��ʽ
extern char buffer[512];
extern unsigned long now;
extern struct DATA Result;

#endif
