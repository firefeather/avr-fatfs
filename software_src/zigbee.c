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
#include "config.h"

#ifndef _DEVICE_INFOMATION_
#define _DEVICE_INFOMATION_
//�豸�����Ϣ �ɴ��EEPROM ���Խ׶���ʱ����ȫ�ֳ���

const char CommonId = 0xFF; //���豸����ID
/***************�����豸ID***************/
#define _DEVICE_ID 1
/**************************************/
#if   _DEVICE_ID == 1 
char devicename[8] = {"DEV00001"};//�豸����
const char deviceId = 0xB1;//�豸ID		
#elif  _DEVICE_ID == 2 
char devicename[8] = {"DEV000002"};//�豸����
const char deviceId = 0xB2;//�豸ID		
#elif  _DEVICE_ID == 3  
char devicename[8] = {"DEV000003"};//�豸����
const char deviceId = 0xB3;//�豸ID		
#elif  _DEVICE_ID == 4  
char devicename[8] = {"DEV000004"};//�豸����
const char deviceId = 0xB4;//�豸ID		
#elif  _DEVICE_ID == 5  
char devicename[8] = {"DEV000005"};//�豸����
const char deviceId = 0xB5;//�豸ID		
#elif  _DEVICE_ID == 6  
char devicename[8] = {"DEV000006"};//�豸����
const char deviceId = 0xB6;//�豸ID		
#endif

//char *reslut_a ="Dev000001,0001,20120920,12:00,-40.5,12.3,-55.5,-40.4,-40.3";

//char *p2 = "a123456789b12456789c123456789d123456789e123456789f12456789g123456789h12345789i12456789";
#endif
 

#define FRAME_LEN     13
#define STORAGE_DB_AND_SD  0
#define STORAGE_DB		   1
#define STORAGE_SD		   2
#define Z_CMD0 0xD0   
//����0 ��Ӧ���Ҵӻ�����

#define Z_CMD1_DATE 0xD1
//����1 ���� ��������  Result.Date

#define Z_CMD2_TIME 0xD2
//����2 ���� ����ʱ��  Result.Time

#define Z_CMD3_TEMPERATURE 0xD3
//����3 ���� �¶�

#define Z_CMD4_WS 0xD4
//����4 ���ͷ���

#define Z_CMD5_WCI 0xD5
//����5 ����WCI

#define Z_CMD6_ETC 0xD6
//����6 ����ETC

#define Z_CMD7_TEQ 0xD7
//����7 ����TEQ

#define Z_CMD8_OTHER 0xD8
//����8 ���Ͷ���Σ���Ժ��ᡢ�ء����ĸ��ֽڵ�����

#define Z_CMD9_SINGLE 0xD9
//����09 ���μ��

#define Z_CMD10_CYCLE 0xDA
//����10 ѭ�����

#define Z_CMD11_STOP 0xDB
//����11 ��ֹ���

#define Z_CMD12_SYNC 0xDC
//����12 ͬ��ʱ��

#define Z_CMD13_GET_DATA 0xDD
//����13 ��������

#define Z_CMD14_SET_STORAGE 0xDE
//����9 ���ô洢λ��

struct buffer_struct Rec;
//����� Buf[100] ;
//������ָ��BufReadP;
//д����ָ��BufWriteP;
//��ǰ������� BufCount;

//struct SendStruct Send; 

void zigbee_init( void )
{
  Rec.BufReadP=0;
  Rec.BufWriteP=0;
  Rec.BufCount=0;
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
  {  debug("DEL=",Rec.Buf[Rec.BufReadP]);
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
#define res Result
 //1 ��ͷ 2�ҳ��� 3����β 4��β 5�˶�У���� 6�������� 7ִ�в���
unsigned char RecDeal( void )
{ 
  int i=0 , tmp=0, state=0 ;
  char buf[5];
  //[TASK :��֡ͷ]
  for(i=0;i <= Rec.BufCount ; i++ ){ 
      tmp = RecRead(1);    //������ǰֵ
	  if(tmp != FRAME_HEAD ) {
	      state = 1; //�Ѳ�����֡ͷ
		  RecRemove(1);
	  }		  
	  else{	  //���ҵ�֡ͷ ����ѭ��
      state = 2 ;  //���ҵ�֡ͷ ��־	 
	  break ;
	  }
 }		
 
 if(Rec.BufCount < FRAME_LEN) return 0x01;  //����������̫��  ֱ�ӷ���
 
 if(state == 1 || Rec.BufCount< FRAME_LEN ) return 0x03; //�˳�����  ��֡ͷ
 //debug("#FRAME END =",RecRead(FRAME_LEN));
 //debug("#RECREAD(3) =",RecRead(3));
 if(RecRead(FRAME_LEN) != FRAME_END || ((RecRead(3)!=deviceId)&& (RecRead(3)!=CommonId) )  )  //�ǳ�֡���ݻ�ID����
 {
    RecRemove(1);	//�Ƴ�����
    return 0x05;    //�ǳ�֡���� ��ID����
 }
 else if((CheckCRC(FRAME_LEN)==1))   //У��ͨ��
 {
     switch(RecRead(4)){
         case Z_CMD0 :  //�����豸��Ϣ
		 Send_string((char *)devicename,Z_CMD0,sizeof(devicename));
		 RecRemove(12);
	     return Z_CMD0;  //������� ���سɹ�
		 break ;
  		
		 case Z_CMD1_DATE :  //��������
		 Send_string(res.Date, Z_CMD1_DATE, 9);
		 return Z_CMD1_DATE;  //������� ���سɹ�
		 break ;	
		 
		 case Z_CMD2_TIME :  //����Time
		 Send_string(res.Time, Z_CMD2_TIME, 10);
		 return Z_CMD2_TIME;  //������� ���سɹ�
		 break ;	
		 
		 case Z_CMD3_TEMPERATURE :  //�����¶�
		 Send_string(res.TempChar, Z_CMD3_TEMPERATURE, 6);
		 return Z_CMD3_TEMPERATURE;  //������� ���سɹ�
		 break ;	
		 
		 case Z_CMD4_WS :  //����WSChar
		 Send_string(res.WSChar, Z_CMD4_WS, 5);
		 return Z_CMD4_WS;  //������� ���سɹ�
		 break ;			 
		 
		 case Z_CMD5_WCI :  //����WCIChar
		 Send_string(res.WCIChar, Z_CMD5_WCI ,8);
		 return Z_CMD5_WCI;  //������� ���سɹ�
		 break ;	
		 
		 case Z_CMD6_ETC :  //ECTChar
		 Send_string(res.ECTChar, Z_CMD6_ETC ,6);
		 return Z_CMD6_ETC;  //������� ���سɹ�
		 break ;		
		 
		 case Z_CMD7_TEQ :  //����TeqCharres.TeqChar
		 Send_string(res.TeqChar, Z_CMD7_TEQ ,6);
		 return Z_CMD7_TEQ;  //������� ���سɹ�
		 break ;	 
		 
		 case Z_CMD8_OTHER :  //��������
		 buf[0]= res.WeiHai + 0x30;
		 buf[1]= res.LowLabor + 0x30;
		 buf[2]= res.MidLabor + 0x30;
		 buf[3]= res.HighLabor + 0x30;
		 buf[4]= 0;
		 Send_string(buf, Z_CMD8_OTHER, 4);
		 return Z_CMD8_OTHER;  //������� ���سɹ�
		 break ;
		 
		 case Z_CMD9_SINGLE:
		 	  config.comCmd = 0x01; //sigle����check
		 break;
		 
		 case Z_CMD10_CYCLE:
		 	  config.comCmd = 0x02; //cycle check.
			  
//			  config.checkDeltaTime
		 break;
		 
		 case Z_CMD11_STOP:
		      config.comCmd = 0x03; //stop check 
		 break;
		 
		 case Z_CMD12_SYNC:
		 break;
		 
		 case Z_CMD13_GET_DATA:
		 break;
		 
		 case Z_CMD14_SET_STORAGE:
		 break;
		 
		 default:    
	     return 0xff;			   
     }
 } 
 else { //У�鲻�ɹ� ����֡ͷ Ѱ����һ֡ͷ
  RecRemove(1);  //����֡ͷ
  return 0xff;
 }
return 0xff;
}
void Send_string(char *buf, unsigned char cmd, unsigned char MaxLen){
	 char i = 0;
	 
	 unsigned char sendBuf[64];
	 sendBuf[0] = FRAME_HEAD;
	 sendBuf[1] = 0;
	 sendBuf[2] = 0x00; //������ַ
	 sendBuf[3] = deviceId;//Send.src; //������ַ
	 sendBuf[4] = cmd; //
	 for(i=0;i<MaxLen;i++){
	     if( *(buf+i) != 0 ){
		 	 sendBuf[i+5] = *(buf+i);
		 }
		 else { 
		 break;
		 }
	 }
	 i=i+5;
	 sendBuf[i++] = 0xCC;
	 sendBuf[i++] = 0xCC;
	 sendBuf[i] = FRAME_END;
	 sendBuf[1] = i+1;
	 delayms((deviceId-0xB1)*1);  //��ͬ�豸��ʱ��ͬʱ�䷢�����ݣ�������ײ
	 Send_nByte(sendBuf, i+1); //uart send
}
/* ����hex ��δ�õ�
void Send_bin(char *buf, unsigned char cmd, unsigned char buf_len){
	 char i = 0;
	 
	 unsigned char sendBuf[64];
	 sendBuf[0] = FRAME_HEAD;
	 sendBuf[1] = 0;
	 sendBuf[2] = 0x00; //������ַ
	 sendBuf[3] = deviceId; //������ַ
	 sendBuf[4] = cmd; //
	 for(i=0;i<buf_len;i++){
			 	 sendBuf[i+5] = *(buf+i);
	 }
	 i=i+5;
	 sendBuf[i++] = 0xCC;
	 sendBuf[i++] = 0xCC;
	 sendBuf[i] = FRAME_END;
	 sendBuf[1] = i+1;
	 delayms((deviceId-0xB1)*1);  //��ͬ�豸��ʱ��ͬʱ�䷢�����ݣ�������ײ
	 Send_nByte(sendBuf, i+1); //uart send
}
*/
void zigbee_send_date(void){
	char buf[5];
    Send_string(res.Date, Z_CMD1_DATE, 9);
	Send_string(res.Time, Z_CMD2_TIME, 10);
	Send_string(res.TempChar, Z_CMD3_TEMPERATURE, 6);
	Send_string(res.WSChar, Z_CMD4_WS, 5);
	Send_string(res.WCIChar, Z_CMD5_WCI ,8);
	Send_string(res.ECTChar, Z_CMD6_ETC ,6);
	Send_string(res.TeqChar, Z_CMD7_TEQ ,6);
	
	buf[0]= Result.WeiHai + 0x30;
	buf[1]= Result.LowLabor + 0x30;
	buf[2]= Result.MidLabor + 0x30;
	buf[3]= Result.HighLabor + 0x30;
	buf[4]= 0;
	Send_string(buf, Z_CMD8_OTHER, 5);
	return ;
}

void zigbee_send_id(void){
	 Send_string((char *)devicename,Z_CMD0,sizeof(devicename));
}