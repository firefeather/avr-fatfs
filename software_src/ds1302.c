#include "config.h"

#define TPORT PORTB
#define TDDR DDRB
#define TPIN PINB
#define PIN_RST	 4
#define PIN_IO	 5
#define PIN_SCK	 6
/******************��λ��*********************/
#define RST_CLR	TPORT &= ~(1 << PIN_RST)   /*��ƽ�õ�*/
#define RST_SET	TPORT |= (1 << PIN_RST)    /*��ƽ�ø�*/
#define RST_IN	TDDR &= ~(1 << PIN_RST)    /*��������*/
#define RST_OUT	TDDR |= (1 << PIN_RST)     /*�������*/

/*****************˫������********************/
#define IO_CLR	TPORT &= ~(1 << PIN_IO)  /*��ƽ�õ�*/
#define IO_SET	TPORT |= (1 << PIN_IO)   /*��ƽ�ø�*/
#define IO_R	TPIN & (1 << PIN_IO)     /*��ƽ��ȡ*/
#define IO_IN	TDDR &= ~(1 << PIN_IO)   /*��������*/
#define IO_OUT	TDDR |= (1 << PIN_IO)    /*�������*/

/*****************ʱ���ź�*******************/
#define SCK_CLR	TPORT &= ~(1 << PIN_SCK)  /*ʱ���ź�*/
#define SCK_SET	TPORT |= (1 << PIN_SCK)   /*��ƽ�ø�*/
#define SCK_IN	TDDR &= ~(1 << PIN_SCK)   /*��������*/
#define SCK_OUT	TDDR |= (1 << PIN_SCK)    /*�������*/

#define ds1302_sec_add			0x80		//�����ݵ�ַ
#define ds1302_min_add			0x82		//�����ݵ�ַ
#define ds1302_hr_add			0x84		//ʱ���ݵ�ַ
#define ds1302_date_add			0x86		//�����ݵ�ַ
#define ds1302_month_add		0x88		//�����ݵ�ַ
#define ds1302_day_add			0x8a		//�������ݵ�ַ
#define ds1302_year_add			0x8c		//�����ݵ�ַ
#define ds1302_control_add		0x8e		//�������ݵ�ַ
#define ds1302_charger_add		0x90 					 
#define ds1302_clkburst_add		0xbe

unsigned char time_buf[8] = {0x20,0x0c,0x0A,0x1c,0x22,0x46,0x00,0x06};
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

//DS1302��ʼ������
void ds1302_init(void) 
{
	RST_CLR;			/*RST���õ�*/
	SCK_CLR;			/*SCK���õ�*/
	RST_OUT;			/*RST������Ϊ���*/
	SCK_OUT;			/*SCK������Ϊ���*/
}

//��DS1302д��һ�ֽ�����
void ds1302_write_byte(unsigned char addr, unsigned char d) {

	unsigned char i;
	RST_SET;					/*����DS1302����*/
	
	/*д��Ŀ���ַ��addr*/
	IO_OUT;
	addr = addr & 0xFE;   //���λ���㣬�Ĵ���0λΪ0ʱд��Ϊ1ʱ��
	for (i = 0; i < 8; i ++) {
		if (addr & 0x01) {
			IO_SET;
			}
		else {
			IO_CLR;
			}
		SCK_SET;      //����ʱ��
		SCK_CLR;
		addr = addr >> 1;
		}
	
	/*д�����ݣ�d*/
	IO_OUT;
	for (i = 0; i < 8; i ++) {
		if (d & 0x01) {
			IO_SET;
			}
		else {
			IO_CLR;
			}
		SCK_SET;    //����ʱ��
		SCK_CLR;
		d = d >> 1;
		}
	RST_CLR;		//ֹͣDS1302����
	
}

//��DS1302����һ�ֽ�����
unsigned char ds1302_read_byte(unsigned char addr) {

	unsigned char i;
	unsigned char temp;
	RST_SET;					/*����DS1302����*/

	/*д��Ŀ���ַ��addr*/
	IO_OUT;
	addr = addr | 0x01;    //���λ�øߣ��Ĵ���0λΪ0ʱд��Ϊ1ʱ��
	for (i = 0; i < 8; i ++) {
		if (addr & 0x01) {
			IO_SET;
			}
		else {
			IO_CLR;
			}
		SCK_SET;
		SCK_CLR;
		addr = addr >> 1;
		}
	
	/*������ݣ�temp*/
	IO_IN;
	for (i = 0; i < 8; i ++) {
		temp = temp >> 1;
		if (IO_R) {
			temp |= 0x80;
			}
		else {
			temp &= 0x7F;
			}
		SCK_SET;
		SCK_CLR;
		}
	
	RST_CLR;					/*ֹͣDS1302����*/
	return temp;
}

//��DS302д��ʱ������
void ds1302_write_time(void) {

	ds1302_write_byte(ds1302_control_add,0x00);			//�ر�д���� 
	ds1302_write_byte(ds1302_sec_add,0x80);				//��ͣʱ�� 
	//ds1302_write_byte(ds1302_charger_add,0xa9);	    //������ 
	ds1302_write_byte(ds1302_year_add,time_buf[1]);		//�� 
	ds1302_write_byte(ds1302_month_add,time_buf[2]);	//�� 
	ds1302_write_byte(ds1302_date_add,time_buf[3]);		//�� 
	ds1302_write_byte(ds1302_hr_add,time_buf[4]);		//ʱ 
	ds1302_write_byte(ds1302_min_add,time_buf[5]);		//��
	ds1302_write_byte(ds1302_sec_add,time_buf[6]);		//��
	ds1302_write_byte(ds1302_day_add,time_buf[7]);		//�� 
	ds1302_write_byte(ds1302_control_add,0x80);			//��д���� 
}

//��DS302����ʱ������
void ds1302_read_time(void)  { 
	time_buf[1]=ds1302_read_byte(ds1302_year_add);		//�� 
	time_buf[2]=ds1302_read_byte(ds1302_month_add);		//�� 
	time_buf[3]=ds1302_read_byte(ds1302_date_add);		//�� 
	time_buf[4]=ds1302_read_byte(ds1302_hr_add);		//ʱ 
	time_buf[5]=ds1302_read_byte(ds1302_min_add);		//�� 
	time_buf[6]=(ds1302_read_byte(ds1302_sec_add))&0x7F;//�룬������ĵ�7λ�����ⳬ��59
	time_buf[7]=ds1302_read_byte(ds1302_day_add);		//�� 
}


