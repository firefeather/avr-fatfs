#ifndef _ZIGBEE_H_
#define _ZIGBEE_H_

#define BufSize 90
#define FRAME_HEAD    	0xFA
#define FRAME_END   	0xFB
#define PACKEG_SIZE		40
struct buffer_struct
{
//主机指令长度固定10字节 
//最长存储3条待处理命令
unsigned char Buf[BufSize] ;
//读缓存指针
unsigned char BufReadP;
//写缓存指针
unsigned char BufWriteP;
//当前缓存个数
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
 

void zigbee_init( void );  //zigbee 初始化函数
unsigned char RecAdd(unsigned char ByteRec);  //将串口接收的一个字节送到缓冲区
void RecRemove(char N);    //移除Nbyte
char RecRead(unsigned char index) ;//读数据池 如果数据池不为空第index个数据，index= 1，2,3。。
char CheckCRC(unsigned char i) ; //crc校验 回1 成功
unsigned char RecDeal( void );
void Send_data(char *p,unsigned char cmd , unsigned int datalen);
#endif