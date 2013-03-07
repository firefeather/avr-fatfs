#ifndef _ZIGBEE_H_
#define _ZIGBEE_H_

#define BufSize 90
#define FRAME_HEAD    	0xFA
#define FRAME_END   	0xFB
#define PACKEG_SIZE		40
struct buffer_struct
{
//����ָ��ȹ̶�10�ֽ� 
//��洢3������������
unsigned char Buf[BufSize] ;
//������ָ��
unsigned char BufReadP;
//д����ָ��
unsigned char BufWriteP;
//��ǰ�������
unsigned char BufCount;
};
struct SendStruct 
{
unsigned char head;
unsigned char lenth;
unsigned char dest;
unsigned char cmd;
unsigned char src ;
unsigned char package_num;
unsigned char * p ;
unsigned char lenthofdate;
unsigned char end;
};
 

void zigbee_init( void );  //zigbee ��ʼ������
unsigned char RecAdd(unsigned char ByteRec);  //�����ڽ��յ�һ���ֽ��͵�������
void RecRemove(char N);    //�Ƴ�Nbyte
char RecRead(unsigned char index) ;//�����ݳ� ������ݳز�Ϊ�յ�index�����ݣ�index= 1��2,3����
char CheckCRC(unsigned char i) ; //crcУ�� ��1 �ɹ�
unsigned char RecDeal( void );
void Send_data(char *p,unsigned char cmd , unsigned int datalen);
#endif