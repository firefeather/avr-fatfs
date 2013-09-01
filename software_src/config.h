#ifndef _CONFIG_H_
#define _CONFIG_H_
//debugѡ��
#define _DEBUG
//#define _LCDDEBUG
#define _UARTDEBUG
//#define _DBG_RD_
#define _FOR_FAST_TEST
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
//����ͨѶ
#include "zigbee.h"

struct DATA {
   char  ID	;
   char  Name[9]	  ;
   unsigned long Index ;
   char IndexChar[8]  ;
   char  Date[9]	  ;
   char	Time[10] 	  ;
   float    Temperature	   ;  //�¶�
   char  TempChar[6]  ;       //ÿ����ֵ����������char�ͱ�����������ʾ����
   float    WindSpeed ;
   char  WSChar[5]    ;
   float    WCI ;   //����ָ��
   char  WCIChar[8]   ;
   float    ECT ;   //�ȼ������¶�
   char  ECTChar[6]   ;
   float    Teq ;	//�൱�¶�
   char  TeqChar[6] ;
   unsigned char    WeiHai		  ;   //����Σ����(������ʾ)
   char *WeiHaiChar;
   unsigned char    LowLabor	  ;   //���
   unsigned char    MidLabor	  ;   //�ж�
   unsigned char    HighLabor	  ;   //�ض�
   char *strH1;
   char *strH2;
   char *strH3;
   char *strM1;
   char *strM2;
   char *strM3;
   char *strL1;
   char *strL2;
   char *strL3;
   };
 struct CONFIG {
 		char Sd; //SD�洢ʹ�ܣ� =0 ���ã� >=1 ʹ��
		char Relay; //�̵���״̬�� =0 �رգ� =1 ������
		char LcdBackLight; //����״̬ =0 �رգ� =1 ������
		unsigned long THRESHOLD_delta_sec; //һ�μ����ʱ
		unsigned long time1;  //�ϴμ��ʱ��
		unsigned long now;   //��ǰʱ�� 
		char autocheck;   //�Զ���⿪��
		int checkDeltaTime;  //�Զ���ⷭҳ���
		int checkDelta; //�Զ������
		char readMode; //��ȡ���ݼ���� 0=���һ�� 1=��˳��d
		char heatThreshold; //��������
		char lcd_off_temperature;
		char autoSend;  //�Զ����Ϳ���
		char is_lowpower;
		char comCmd; //��λ������  
								// =0x00�� ������
								// =0x01�� ִ��һ�μ��
								// =0x02�� ��checkDelta���ѭ�����
								// =0x03�� ֹͣ���
		unsigned long last5s;
		
  };
 #define READ_MODE_LAST 0
 #define READ_MODE_FIRST 1  
 #define INSIDE_SENSOR 0
 #define OUTSIDE_SENSOR 1
  
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
extern char devicename[8];//�豸����
extern const char deviceId ;	
extern  struct  tm t; //�ļ�ϵͳʱ��洢�ṹ��
extern unsigned char time_buf[8]; //�ⲿ���� �洢��1302��ʱ���ԭʼ��ʽ
extern char buffer[512];
extern unsigned long now;
extern struct DATA Result;

#endif
