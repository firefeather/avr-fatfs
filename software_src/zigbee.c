/*  ���ļ������˴ӻ�zigbee��ģ���Լ� �� ����λ��ͨ�ŵ���غ���
*   �汾 V1.0
*   ���� 2012 08 10
*   �汾��ʷ��
* ���ݸ�ʽ
* ֡ͷ    ����    Ŀ�ĵ�ַ   ����  ����     У��    ֡β
* FA       AA      B1        D1    01 03    00 00    fb  
*
*
*
************/
#include "include.h"

#ifndef _DEVICE_INFOMATION_
#define _DEVICE_INFOMATION_
//�豸�����Ϣ �ɴ��EEPROM ���Խ׶���ʱ����ȫ�ֳ���

const char CommonId = 0xFF; //���豸����ID
/***************�����豸ID***************/
#define _DEVICE_ID 1
/**************************************/
#if   _DEVICE_ID == 1 
const char devicename[8] = {"De000001"};//�豸����
const char deviceId = 0xB1;//�豸ID		
unsigned char deviceDescrieString[]={0xFA,0x10,0x00,0xD0,0xB1,'D','E','V','0','0','0','0','1',0xCC,0xCC,0xFB};	
#elif  _DEVICE_ID == 2 
const char devicename[8] = {"De000002"};//�豸����
const char deviceId = 0xB2;//�豸ID		
unsigned char deviceDescrieString[]={0xFA,0x10,0x00,0xD0,0xB2,'D','E','V','0','0','0','0','2',0xCC,0xCC,0xFB};	
#elif  _DEVICE_ID == 3  
const char devicename[8] = {"De000003"};//�豸����
const char deviceId = 0xB3;//�豸ID		
unsigned char deviceDescrieString[]={0xFA,0x10,0x00,0xD0,0xB3,'D','E','V','0','0','0','0','3',0xCC,0xCC,0xFB};	
#elif  _DEVICE_ID == 4  
const char devicename[8] = {"De000004"};//�豸����
const char deviceId = 0xB4;//�豸ID		
unsigned char deviceDescrieString[]={0xFA,0x10,0x00,0xD0,0xB4,'D','E','V','0','0','0','0','4',0xCC,0xCC,0xFB};	
#elif  _DEVICE_ID == 5  
const char devicename[8] = {"De000005"};//�豸����
const char deviceId = 0xB5;//�豸ID		
unsigned char deviceDescrieString[]={0xFA,0x10,0x00,0xD0,0xB5,'D','E','V','0','f','j','x','5',0xCC,0xCC,0xFB};	
#elif  _DEVICE_ID == 6  
const char devicename[8] = {"De000006"};//�豸����
const char deviceId = 0xB6;//�豸ID		
unsigned char deviceDescrieString[]={0xFA,0x10,0x00,0xD0,0xB6,'D','E','V','0','0','0','0','6',0xCC,0xCC,0xFB};	
#endif

//char *reslut_a ="Dev000001,0001,20120920,12:00,-40.5,12.3,-55.5,-40.4,-40.3";

//char *p2 = "a123456789b12456789c123456789d123456789e123456789f12456789g123456789h12345789i12456789";
#endif
 

#define FRAME_LEN     13
#define STORAGE_DB_AND_SD  0
#define STORAGE_DB		   1
#define STORAGE_SD		   2
#define Z_CMD0 0xD0   
//����0 ���Ҵӻ�
#define Z_CMD1 0xD1
//����1 ���β���
#define Z_CMD2 0xD2
//����2
#define Z_CMD3 0xD3
//����3
#define Z_CMD4 0xD4
//����4
#define Z_CMD5 0xD5
//����5
#define Z_CMD6 0xD6
//����6
#define Z_CMD7 0xD7
//����7
#define Z_CMD8 0xD8
//����8

struct buffer_struct Rec;
//����� Buf[100] ;
//������ָ��BufReadP;
//д����ָ��BufWriteP;
//��ǰ������� BufCount;
struct SendStruct Send; 

void zigbee_init( void )
{
  Rec.BufReadP=0;
  Rec.BufWriteP=0;
  Rec.BufCount=0;
  
  Send.head = FRAME_HEAD;
  Send.dest = 0x00;
  Send.src  = deviceId;
  Send.end  = FRAME_END;
  
  deviceDescrieString[4] = deviceId;
}
unsigned char RecAdd(unsigned char ByteRec)
{
  if (Rec.BufWriteP >= BufSize)  
  	 Rec.BufWriteP=0;
  Rec.Buf[Rec.BufWriteP++] = ByteRec ;
  Rec.BufCount++;
  return Rec.BufWriteP;
} 

void RecRemove(char N)
{ 
  if(Rec.BufCount >= N ) 
  {  debug_out("DEL=",Rec.Buf[Rec.BufReadP]);
     Rec.Buf[Rec.BufReadP]=0x00; 
   	 Rec.BufReadP=Rec.BufReadP+N;
	 if(Rec.BufReadP >= BufSize) {
	 				 		 Rec.BufReadP =Rec.BufReadP-BufSize;
							 }
	 Rec.BufCount=Rec.BufCount-N;
	 if(Rec.BufCount==0) {
	 Rec.BufReadP=0;
     Rec.BufWriteP=0;
	 
	 }
	 
  }
  else 
  {  //�Ƴ������������� �Ƴ����� ��������
    Rec.BufReadP=0;
    Rec.BufWriteP=0;
    Rec.BufCount=0;
  
  }
 }
char  RecRead(unsigned char index)
{ 
  int tmp;
  if(Rec.BufCount < index) 
  	return 0;
	
  tmp=Rec.BufReadP+index;
  if(tmp>=BufSize)  {tmp=tmp-BufSize;}
  return Rec.Buf[tmp-1];
} 


char CheckCRC(unsigned char i)
{
 i=i;
 return 1;  //У��ɹ�

}

 //1 ��ͷ 2�ҳ��� 3����β 4��β 5�˶�У���� 6�������� 7ִ�в���
unsigned char RecDeal( void )
{ 
  int i=0 , tmp=0, state=0 ;
  //[TASK :��֡ͷ]
  for(i=0;i <= Rec.BufCount ; i++ )
  	{ 
	  		tmp = RecRead(1);    //������ǰֵ
	 		if(tmp != FRAME_HEAD ) 
	   		{	   	  state = 1; //�Ѳ�����֡ͷ
					  RecRemove(1);
			}		  
	 		else 
	 		{
	  		 	 	  //���ҵ�֡ͷ ����ѭ��
      		 		 state = 2 ;  //���ҵ�֡ͷ ��־	 
	  			 	 break ;
	 		}
	}		
 if(Rec.BufCount < FRAME_LEN) return 0x01;  //����������̫��  ֱ�ӷ���
 
 if(state == 1 || Rec.BufCount< FRAME_LEN ) return 0x03; //�˳�����  ��֡ͷ
 debug_out("#FRAME END =",RecRead(FRAME_LEN));
 debug_out("#RECREAD(3) =",RecRead(3));
 if(RecRead(FRAME_LEN) != FRAME_END || ((RecRead(3)!=deviceId)&& (RecRead(3)!=CommonId) )  )  //�ǳ�֡���ݻ�ID����
 {
  		RecRemove(1);	//�Ƴ�����
		return 0x05;    //�ǳ�֡���� ��ID����
 }
 else if((CheckCRC(FRAME_LEN)==1))   //У��ͨ��
 {
   switch(RecRead(4))
  					{
  					 case Z_CMD0 : 
					 	  		    
								   Send.cmd = 0xD0 ;
					 	  		   Send_data(deviceDescrieString,Send.cmd,deviceDescrieString[1]);
								   RecRemove(12);
								   
								   return 0xD0;  //������� ���سɹ�
					 	  		   break ;
  					 case Z_CMD1 :  //���μ�� ���ִ洢ģʽ
					 	  		   //check();
								   //deal();
								   //storage(RecRead(5));
								   Send.cmd = 0xD1 ; 
								   //Send_data(p2,Send.cmd,10);
								   RecRemove(FRAME_LEN);
					 	  		   break ;	
	  				 case Z_CMD2 : debug_out("zcmd=",Z_CMD2);
					 	  		   Send.cmd = 0xD1 ; 
								   //Send_data(p2,Send.cmd,20);
								   RecRemove(FRAME_LEN);
					 	  		   break ;							   
  					 case Z_CMD3 : debug_out("zcmd=",Z_CMD3);
					 	  		   Send.cmd = 0xD1 ; 
								   //Send_data(p2,Send.cmd,30);
								   RecRemove(FRAME_LEN);
					 	  		   break ;
  					 case Z_CMD4 : debug_out("zcmd=",Z_CMD4);
					 	  		   Send.cmd = 0xD1 ; 
								   //Send_data(p2,Send.cmd,40);
								   RecRemove(FRAME_LEN);
					 	  		   break ;
  					 case Z_CMD5 : debug_out("zcmd=",Z_CMD5);
					 	  		   Send.cmd = 0xD1 ; 
								  // Send_data(p2,Send.cmd,50);
								   RecRemove(FRAME_LEN);
					 	  		   break ;
  
					 default:    
					          return 7;			   
  
  					}
 } 
 else //У�鲻�ɹ� ����֡ͷ Ѱ����һ֡ͷ
 {
  
  RecRemove(1);  //����֡ͷ
  return 0x07;
 }
  	 return 0x00;		 
 
}

void Send_data(char *p,unsigned char cmd,unsigned int datalen)
{   
	delayms((deviceId-0xB1)*30);
  	Send.package_num=0;
	CLI();
 	while(datalen>=PACKEG_SIZE-9)
 	{
	Usart_Transmit(Send.head);
	Usart_Transmit(PACKEG_SIZE);
	Usart_Transmit(0x00);
	Usart_Transmit(cmd);
	Usart_Transmit(Send.src);
	Send_nByte(p,PACKEG_SIZE-9);
	Usart_Transmit(Send.package_num++);
	Usart_Transmit(0xCC);
	Usart_Transmit(0xCC);
	Usart_Transmit(Send.end);
	p=p+(PACKEG_SIZE-9);
	datalen=datalen-(PACKEG_SIZE-9);
	delayms(1);
	}
	Usart_Transmit(Send.head);
	Usart_Transmit(datalen+9);
	Usart_Transmit(0x00);
	Usart_Transmit(cmd);
	Usart_Transmit(Send.src);
	Send_nByte(p,datalen);
	Usart_Transmit(0xF0+Send.package_num);
	Usart_Transmit(0xCC);
	Usart_Transmit(0xCC);
	Usart_Transmit(Send.end);
	SEI();
	return ; 
	}