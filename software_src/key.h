//////////////////////////////////////////////////////////////
//����ɨ�����1.0
/*  ˵����
     ���� Ӳ���ӿ�ͼ
			 
  �˿ڳ�ʼ����ʽ��
  PORTA = 0xff;
  DDRA  = 0x3F;
 
  main ��Ӧ������
 //��ʱ��T0��ʼ��
void timer0_init(void)
{
 TCCR0  = 0x00;//ֹͣ��ʱ��
 TCNT0  = 0xB8;//��ʼֵ
 OCR0   = 0xB7;//ƥ��ֵ
 TIMSK |= 0x01;//�ж�����
 TCCR0  = 0x05;//������ʱ��
}                             

//T0����жϷ������
#pragma interrupt_handler timer0_ovf_isr:10
void timer0_ovf_isr(void)
{
 TCNT0 = 0xB8;
 
 
kbscan_en=1;
}


*/

/////////////////////////////////////////////////////////////////


#include "config.h"
#define up 0B00011110
#define down 0B00011101
#define left 0B00011011
#define right 0B00010111
#define ok 0B00001111
//����
#define lup 0B10011110
#define ldown 0B10011101
#define lleft 0B10011011
#define lright 0B10010111
#define lok 0B10001111
//���̰����ֽ��޳���  80000Լ����1��
#define LONGKEY  80000
 
#define NO_KEY 0x00


#define DDR_SET DDRA &= 0x07
//#define KEY_PORT   PORTA
#define KEY_PIN    PINA&KEY_MASK
#define KEY_MASK   0X1F  
unsigned char kbscan(void);