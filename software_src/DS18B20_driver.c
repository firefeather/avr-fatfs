//------------------------------------------------------------------------------
// �ļ�����DS18B20_driver.c
// ˵����  DS18B20����ͷ�ļ�
// ���ܣ�  ʵ��1-wire�����Ķ�д
// ʹ�÷�����   void Delay_nus(unsigned int n);             //��ʱn΢�뺯��
//              unsigned char reset_18B20(void);            //18B20��λ
//              void write_bit_18B20(char bitval);          //дһλ��18B20
//              unsigned char read_bit_18B20(void);         //��һλ��18B20
//              void write_byte_18B20(unsigned char data);  //дһ�ֽڵ�18B20
//              unsigned char read_18B20(void);             //��һ�ֽڵ�18B20
//
// ����ƽ̨��   AVR 8bit (M16����֤)
// �����ϵ��   DS18B20_driver.h    DS18B20��������ͷ�ļ�������������
// ��ֲ�ˣ�     
// ����޸ģ�   
//------------------------------------------------------------------------------

#include "config.h"
#define DS18B20_PORT PORTG
#define DS18B20_PIN  PING
#define DS18B20_DDR  DDRG
#define CL_DQ   DS18B20_PORT&=~(1<<T_NUM)					   
#define SET_DQ  DS18B20_PORT|=(1<<T_NUM)			   
#define SET_OUT DS18B20_DDR|=(1<<T_NUM)				   
#define SET_IN  DS18B20_DDR&=~(1<<T_NUM)			   
#define IN_DQ   DS18B20_PIN&(1<<T_NUM)				  
unsigned char T_NUM=0;


//------------------------------------------------------------------------------
// ��ʱN΢����� �����ƶ�дDS18B20ʱ��ʹ��
//------------------------------------------------------------------------------
void Delay_nus(unsigned int n)   
{  unsigned int i;
	  for (i=0;i<n;i++) 
	  		{NOP();
						NOP();
						NOP();				        //20--300//�ȽϽӽ�
					}
}


//------------------------------------------------------------------------------
// 1-wire���߸�λ
//------------------------------------------------------------------------------
unsigned char reset_18B20(void)
{
	char bus_flag;
	CLI();
	SET_DQ;
	SET_OUT;
 	
  	Delay_nus(1);
  	CL_DQ;
  	Delay_nus(550);		//��������480usʱ��
  	SET_DQ;				//�ͷ�
					NOP();
					NOP();
  	SET_IN;				//����
  	Delay_nus(60);
  	
						//�ȴ��ظ�
  	bus_flag = IN_DQ;
  	
  	Delay_nus(240);		//�ظ��ĵ͵�ƽ��60��240US
  	SET_OUT;
					NOP();
					NOP();
  	SET_DQ;				//�ص���ʼDQ=1��

  	SEI();
	if(bus_flag){
		return FALSE;
	}else{
		return TRUE;
	}

}

//------------------------------------------------------------------------------
// дһλ������
//------------------------------------------------------------------------------
void write_bit_18B20(char bitval)
{
    SET_OUT;
					NOP();
					NOP();
			 CL_DQ;
	   Delay_nus(1);
	   if(bitval){    //д���ݣ��ӵ�λ��ʼ
		     SET_DQ;
	  }else{
		     CL_DQ;
	  }
	Delay_nus(40);		//15~60us
	SET_DQ;
	Delay_nus(10);
}

//------------------------------------------------------------------------------
// ��һλ������
//------------------------------------------------------------------------------
unsigned char read_bit_18B20(void)
{
	unsigned char k;
	SET_OUT;
	CL_DQ;			//��ʱ��Ƭ��ʼ��������������1us
	Delay_nus(1);
	
					//SET_DQ;	
	SET_IN;
	Delay_nus(4);
	k=IN_DQ;    	//������,�ӵ�λ��ʼ
	Delay_nus(10);
	SET_DQ;	
				NOP();
				NOP();
	SET_OUT;
	    NOP();
					NOP();
	if(k){
	    return 1;
	}else{
	    return 0;
	}
	
}

//------------------------------------------------------------------------------
// дһ���ֽڵ�����
//------------------------------------------------------------------------------
void write_byte_18B20(unsigned char data)
{
	unsigned char i;
   CLI();
    for(i=0;i<8;i++)
    {
        write_bit_18B20(data&(1<<i));
        
    }
    SET_DQ;
				  NOP();
					 NOP();
    SEI();
    
    //return;
}

//------------------------------------------------------------------------------
// ��һ���ֽ�
//------------------------------------------------------------------------------
unsigned char read_byte_18B20(void)
{
	unsigned char temp,n;
    CLI();
  	temp=0;
    for(n=0;n<8;n++)
    {
      	if(read_bit_18B20()){
      		temp|=(1<<n);
      	}else{
      		temp&=~(1<<n);
      	}
      	Delay_nus(70); //60~120us
      	
   }
   SEI();

   return temp;
}



//------------------------------------------------------------------------------
// Ӧ�ú������֣� ���ⲿ����
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// ������/����������ʼת��
//------------------------------------------------------------------------------
void convert_T(void)
{
					if(reset_18B20()){
					write_byte_18B20(0xcc);
					write_byte_18B20(0x44);
					}
}

//------------------------------------------------------------------------------
// �����������¶ȣ�����INIT8U���¶����ݣ�ԭʼ���ݣ�
//------------------------------------------------------------------------------
float read_T(void)
{
    unsigned char th=0,tl=0;
	float tmp;
    if(reset_18B20()){
    	write_byte_18B20(0xcc);
    	write_byte_18B20(0xbe);
    }
    
    tl = read_byte_18B20();
    th = read_byte_18B20();
 	tmp= ((float)(th<<8|tl))*0.0625;
    return( tmp);
}

float read_T_NUM(unsigned char NUM){
float ttemp;
if ( NUM >1) return 123.45;
T_NUM=NUM;//���÷�������
convert_T();//�¶�ת��
delayms(800);
ttemp=read_T();
return ttemp;
}


//-----------------------------------------------------------------------------
//��������ת��
//-----------------------------------------------------------------------------
/*
void last_temp(unsigned int data)
{ 
  unsigned char zhengshu;
  unsigned char xiaoshu1;   //ֻȡһλС��
		unsigned int data;
		unsigned char sign;
		
		data=read_T();
	 if((data&0x8000)==0x8000) //���¶�
					{
					 sign='-';
					 data=(~data)+1;       //������ʽ��ȡ����һ
					}
		elae 
					{
					 sign=' ';
					}
		xiaoshu1=(unsigned char) ((data&0x0f)*10/16);
		zhengshu=(unsigned char) (data>>4);
				
		real_temp[4]={sign,zhengshu,'.',xiaoshu1,'��'};
		//��char�ʹ洢
}


*/
