/*  �̵�����������
*
*����������  PORTXX
*���������������ڲ��¶ȴ�������ֵ�����Ƿ�򿪼̵����������ڲ����ȹ��ܣ���
 */
#ifndef _RELAY_H_
#define _RELAY_H_
#include "config.h"
//�趨������������ֵ��ѹ



#define RELAY_PORT 		  PORTC
#define RELAY_PORT_NUM	  5
#define RELAY_DDR_SET() DDRC|=(1<<RELAY_PORT_NUM)

#define RELAY_ON()	RELAY_PORT &= ~(1 << RELAY_PORT_NUM)    /*����*/
#define RELAY_OFF() 	RELAY_PORT |=  (1 << RELAY_PORT_NUM)     /*����*/


void relay_init(void);
void relay(signed int temp);

#endif

