#include "config.h"

//��Ӳ�������ʺ���ǿ�ȼ���ǵ�2���·  mega128
#define LCD_PIN_CS   4
#define LCD_PIN_SID  3
#define LCD_PIN_SCLK 2
#define LCD_PIN_RST  1
#define LCD_BACKLIGHT_SW		0
#define LCD_PORT PORTC
#define LCD_PIN_DDR DDRC
#define Set_CS()     LCD_PIN_DDR |= (1<<LCD_PIN_CS)  ;LCD_PORT |= (1<<LCD_PIN_CS) 
#define Set_SID()    LCD_PIN_DDR |= (1<<LCD_PIN_SID) ;LCD_PORT |= (1<<LCD_PIN_SID) 
#define Set_SCLK()   LCD_PIN_DDR |= (1<<LCD_PIN_SCLK);LCD_PORT |= (1<<LCD_PIN_SCLK) 
#define LCD_LIGHT_ON()   LCD_PIN_DDR |= (1<<LCD_BACKLIGHT_SW);LCD_PORT |= (1<<LCD_BACKLIGHT_SW) 
#define Set_RST()   LCD_PIN_DDR |= (1<<LCD_PIN_RST);LCD_PORT |= (1<<LCD_PIN_RST) 

#define Clr_CS()     LCD_PIN_DDR |= (1<<LCD_PIN_CS)  ;LCD_PORT &=~(1<<LCD_PIN_CS) 
#define Clr_SID()    LCD_PIN_DDR |= (1<<LCD_PIN_SID) ;LCD_PORT &=~(1<<LCD_PIN_SID) 
#define Clr_SCLK()   LCD_PIN_DDR |= (1<<LCD_PIN_SCLK);LCD_PORT &=~(1<<LCD_PIN_SCLK) 
#define LCD_LIGHT_OFF()   LCD_PIN_DDR |= (1<<LCD_BACKLIGHT_SW);LCD_PORT &=~(1<<LCD_BACKLIGHT_SW) 
#define Clr_RST()   LCD_PIN_DDR |= (1<<LCD_PIN_RST);LCD_PORT &=~(1<<LCD_PIN_RST) 
 
void W_1byte(unsigned char RW, unsigned char RS, unsigned char W_data); 
void Write_8bits(unsigned int W_bits); 
void LCD_Init(void); 
unsigned char LCD_INT(void); 

unsigned char LCD_SW(unsigned char i)
{
 if(i==0){
 LCD_LIGHT_OFF();
 return 0;
 }
 else{
 LCD_LIGHT_ON();
 return 1;
 }
 
}
 
unsigned char LCD_INT(void) 
{ 
  Clr_CS(); 
  Clr_SID(); 
  Clr_SCLK(); 
  LCD_Init(); 
  return (0);
} 
  
/******************************************************************** 
���� ����address
��ڲ�������ַת��
���ڲ������� 
�������ã� 
˵        ���� 
********************************************************************/ 
unsigned char address(unsigned char x,unsigned char y)
{  
 unsigned char a;

switch(x) 
{ 
case 1: 
{a=0x80;break;} 
case 2: 
{a=0x90;break;} 
  case 3: 
{a=0x88;break;} 
  case 4: 
{a=0x98;break;} 
} 
a=a+y-1;

return a;
}
 
//////////////////////////////////////////////////////////////

/******************************************************************** 
���� ����LCD_const_disp
��ڲ�����x y  *single_data
���ڲ������� 
�������ã����� ��ʾһ������
˵        ���� 
********************************************************************/ 
void LCD_const_disp(unsigned char x, unsigned char y, const unsigned char *single_data) 
{ 
unsigned char  a,i; 
a=address(x,y);
W_1byte(0,0,a);     //��ʾ�ĵ�ַ 
   for(i=0; single_data[i]!='\0';i++) 
   {
    if(i>=16) break; 
    W_1byte(0,1,single_data[i]); 
    
   } 
   W_1byte(0,0,0XFF); // ���ߵ�ַָ�� ��ֹ��һ�������ݵĸ���
 
} 

/******************************************************************** 
���� ����LCD_var_disp
��ڲ�����single_row single_line  *single_data
���ڲ������� 
�������ã����� ��ʾһ������
˵        ���� 
********************************************************************/ 

void LCD_var_disp(unsigned char x, unsigned char y, unsigned char *single_data) 
{ 
unsigned char  a,i; 

#if _debug == 1 
	PrintString_n(single_data);
#endif 

a=address( x,y);
W_1byte(0,0,a);     //��ʾ�ĵ�ַ0x88 

for(i=0; single_data[i]!='\0';i++) 
   { 
    if(i>=16) break;
    W_1byte(0,1,single_data[i]); 
	} 
  W_1byte(0,0,0XFF); // ���ߵ�ַָ�� ��ֹ��һ�������ݵĸ���
} 
/******************************************************************** 
���� ����LCD_char_disp
��ڲ�����single_row single_line  data
���ڲ������� 
�������ã����� ��ʾһ�� ����
˵        ���� 
********************************************************************/ 

void LCD_char_disp(unsigned char x, unsigned char y, unsigned char data) 
{ 
unsigned char a; 
a=address(x,y);
W_1byte(0,0,a);     //��ʾ�ĵ�ַ 
W_1byte(0,1,data);  //��ʾ����
 
  W_1byte(0,0,0XFF); // ���ߵ�ַָ�� ��ֹ��һ�������ݵĸ���
} 

/******************************************************************** 
���� ����LCD_Init
��ڲ�������
���ڲ�����unsigned char  0/1
�������ã����� ���Һ����ʾ
˵        ���� 
********************************************************************/ 
void LCD_Init(void) 
{ 
   unsigned char cmd; 
   cmd=0x30;      //�������� 8 λ���ݣ�����ָ�� 
  W_1byte(0,0,cmd); 
  delayms(2); 
  cmd=0x0C;      //��ʾ״̬ ON���α�OFF������OFF 
  W_1byte(0,0,cmd); //дָ�� 
  delayms(2); 
  cmd=0x01;      //�����ʾ 
  W_1byte(0,0,cmd); //дָ�� 
  delayms(2); 
  cmd=0x02;      //��ַ��λ 
  W_1byte(0,0,cmd); //дָ�� 
  delayms(2); 
  cmd=0x80;      //����DDRAM ��ַ 
  W_1byte(0,0,cmd); //дָ�� 
  delayms(2);     //��ʱ 
} 

void LCD_CLR(void)
{
unsigned char cmd;
  cmd=0x01;      //�����ʾ 
  W_1byte(0,0,cmd); //дָ�� 
  delayms(1); 
  cmd=0x02;      //��ַ��λ 
  W_1byte(0,0,cmd); //дָ�� 
  delayms(1); 
  cmd=0x80;      //����DDRAM ��ַ 
  W_1byte(0,0,cmd); //дָ�� 
  delayms(1);     //��ʱ

}
 
/*******************************************************************
�� �� ����W_1byte
��ڲ�����RW��RS��W_data
���ڲ�������
�������ڣ�2007��3��3��
�޸����ڣ�
�������ã�дһ���ֽڵ����ݵ�12864Һ��������ָ�������
˵    ����RW=1����Һ�������ݵ�MCU��RW=0��дһ�����ݵ�Һ����
		 ��һ��RW����Ϊ0����ֻ��Һ��д���ݣ��������ݣ�
          RS=1��д��������ݣ�RS=0��д�����ָ�
		  һ��ģʽ��RW=0��RS=1;д����
		  			RW=0��RS=0;дָ��
********************************************************************/
void W_1byte(unsigned char RW, unsigned char RS, unsigned char W_data)
{
	unsigned int H_data,L_data,S_ID = 0xf8;	 //11111RWRS0
	if(RW == 0)
	{
	 	S_ID &=~ 0x04;
	}
	else					//if(RW==1)
	{
	 	S_ID |= 0X04;
	}
	if(RS == 0)
	{
	 	S_ID &=~ 0x02;
	}
	else					//if(RS==1)
	{
	 	S_ID |= 0X02;
	}
	H_data = W_data;
	H_data &= 0xf0;			//���ε�4λ������
	L_data = W_data;	   	//xxxx0000��ʽ
	L_data &= 0x0f;			//���θ�4λ������
	L_data <<= 4;			//xxxx0000��ʽ
	Set_CS();
	Write_8bits(S_ID); 		//����S_ID
	Write_8bits(H_data);	//����H_data
	Write_8bits(L_data);	//����L_data
	Clr_CS();	Clr_CS();	Clr_CS();	
	 

}
/********************************************************************
�� �� ����Write_8bits
��ڲ�����W_bits
���ڲ�������
�������ڣ�2007��3��3��
�޸����ڣ�
�������ã����������8��bitλ
˵    ����
********************************************************************/
void Write_8bits(unsigned int W_bits)
{
	unsigned int i,Temp_data;
	for(i=0; i<8; i++)
	{
		Temp_data = W_bits;
		Temp_data <<= i;
		if((Temp_data&0x80)==0) 
		{
		 	Clr_SID();
		}
		else
		{
		 	Set_SID();
		} 
		NOP();
		Set_SCLK();
		NOP();
		NOP();
		Clr_SCLK();
		NOP();
		Clr_SID();
	}
}
 
/********************************************************************
�� �� ����Set_Draw(
��ڲ�������
���ڲ�������
�������ã�����Ϊ��ͼģʽ
˵    ����
********************************************************************/
void Set_Draw(void)
{  	
	//W_1byte(0,0,0x34);			//8BIT���ƽ��棬����ָ�,����ͼ��ʾOFF
	W_1byte(0,0,0x36);
	delayms(1);					//��ʱ
} 
 

/******************************************************************** 
���� ����Set_White 
��ڲ�����  x,   y,  end_x,  clear
���ڲ������� 
�������ã� ���÷���
˵        ���� 
********************************************************************/ 
void Set_White(unsigned char x,unsigned char y,unsigned char end_x,unsigned char clear)
{
 
	unsigned char i, j, white_x, white_y,white_end_x,clr_x,clr_y ;		//
  
	W_1byte(0,0,0x36);	  //8BIT���ƽ��棬����ָ�,����ͼ��ʾON
	delayus(20);					//��ʱ
 
	white_end_x = (end_x-x+1);
	white_end_x <<= 1;
	if(y==1)   //x,1  a=80+x-1                   
	{
	 	white_x = (0x80+x-1); 
		white_y = 0x80;
		clr_x = 0x80;
		clr_y = 0x80;
	}
	else if(y==2)
	{
	 	white_x = (0x80+x-1);
		white_y = 0x90;
		clr_x = 0x80;
		clr_y = 0x90;
	}
	else if(y==3)
	{
	 	white_x = (0x88+x-1);
		white_y = 0x80;
		clr_x = 0x88;
		clr_y = 0x80;
	}
	else if(y==4)
	{
	 	white_x = (0x88+x-1);
		white_y = 0x90;
		clr_x = 0x88;
		clr_y = 0x90;
	}
  if(clear==0)//Ҫ����ʱ���Ƚ����е�Һ��ȫ����ɲ����ף��˴���ָy��
	{
	 	for(i=0;i<16;i++ )			//16��
		{
		 	W_1byte(0,0,clr_y++);	//���û�ͼ����Y��ַ����0
			W_1byte(0,0,clr_x);		//���û�ͼ����X��ַ����0
			for(j=0;j<16;j++)		//
			{
			 	W_1byte(0,1,0x00);	//��ɲ�����
			 	nop();
			}
		}
	}
	nop();
//	
	for(i=0;i<16;i++ )				//16�У���Ϊ��16*16����
	{
		W_1byte(0,0,white_y++);		//���û�ͼ����Y��ַ����0
		W_1byte(0,0,white_x);		//���û�ͼ����X��ַ����0
		for(j=0;j<white_end_x;j++)	//
		{
			 if(clear==1)
			 {
			  	W_1byte(0,1,0x00); //ȡ����һ�е�8����ķ��ף�Һ����ַ�Զ���1
								   //���˴���ָһ��һ��Һ��������ɵ��У�
			 }
			 else
			 {
				W_1byte(0,1,0xff); //������һ�е�8���㣬Һ����ַ�Զ���1
								   //���˴���ָһ��һ��Һ��������ɵ��У�
			 }
			nop();
		}
	}
	W_1byte(0,0,0x30);		//����ָ�,����ͼ��ʾOFF
 }

/******************************************************************** 
���� ����set_white_n
��ڲ����� n ,  clear
���ڲ������� 
�������ã�   �����зֳɰ˸�λ�á�n����λ��1-8�����������ڷ��Ի�ȡ������
          ĳһλ�õ����֡�
˵        ���� ���� set_white_n(1,0); ��ʾ���Ե�һ��ǰ�ĸ���
********************************************************************/ 
void set_white_n(unsigned char n,unsigned char clear)
{
unsigned char tempx,tempy,tempendx;
if(n==1) {tempx=1;tempy=1;tempendx=4;}
else if(n==2) {tempx=5;tempy=1;tempendx=8;}
else if(n==3) {tempx=1;tempy=2;tempendx=4;}
else if(n==4) {tempx=5;tempy=2;tempendx=8;}
else if(n==5) {tempx=1;tempy=3;tempendx=4;}
else if(n==6) {tempx=5;tempy=3;tempendx=8;}
else if(n==7) {tempx=1;tempy=4;tempendx=4;}
else if(n==8) {tempx=5;tempy=4;tempendx=8;}
Set_White(tempx,tempy,tempendx,clear);

}
 
/******************************************************************** 
���� ����clr_white
��ڲ����� ������ ����
���ڲ������� 
�������ã� 
˵        ���� 
********************************************************************/ 
void clr_white(void)
{      unsigned char i,j;

       unsigned char  clr_y=0x80;
	   unsigned char  clr_x=0x80;
	   W_1byte(0,0,0x36);	  //8BIT���ƽ��棬����ָ�,����ͼ��ʾON
	 	for(i=0;i<16;i++ )			//16��
		{
		 	W_1byte(0,0,clr_y++);	//���û�ͼ����Y��ַ����0
			W_1byte(0,0,clr_x);		//���û�ͼ����X��ַ����0
			for(j=0;j<16;j++)		//
			{
			 	W_1byte(0,1,0x00);	//��ɲ�����
			 	nop();
			}
		}
	
	    clr_y=0x80;
	    clr_x=0x90;
		 	for(i=0;i<16;i++ )			//16��
		{
		 	W_1byte(0,0,clr_y++);	//���û�ͼ����Y��ַ����0
			W_1byte(0,0,clr_x);		//���û�ͼ����X��ַ����0
			for(j=0;j<16;j++)		//
			{
			 	W_1byte(0,1,0x00);	//��ɲ�����
			 	nop();
			}
		}   
	   
	     clr_y=0x88;
	     clr_x=0x80;
		 	for(i=0;i<16;i++ )			//16��
		{
		 	W_1byte(0,0,clr_y++);	//���û�ͼ����Y��ַ����0
			W_1byte(0,0,clr_x);		//���û�ͼ����X��ַ����0
			for(j=0;j<16;j++)		//
			{
			 	W_1byte(0,1,0x00);	//��ɲ�����
			 	nop();
			}
		} 
	     clr_y=0x88;
	     clr_x=0x90;
		 	for(i=0;i<16;i++ )			//16��
		{
		 	W_1byte(0,0,clr_y++);	//���û�ͼ����Y��ַ����0
			W_1byte(0,0,clr_x);		//���û�ͼ����X��ַ����0
			for(j=0;j<16;j++)		//
			{
			 	W_1byte(0,1,0x00);	//��ɲ�����
			 	nop();
			}
		} 		
  W_1byte(0,0,0x30);	  //8BIT���ƽ��棬����ָ�,����ͼ��ʾON
	}
/******************************************************************** 
���� ����LCD_print2num
��ڲ����� ��ʾ2����
���ڲ������� 
�������ã� 
˵        ���� 
********************************************************************/ 
void LCD_print2num(unsigned char x,unsigned char y,unsigned char num){
unsigned char tem;
unsigned char a; 

a=address(x,y);
W_1byte(0,0,a);     //��ʾ�ĵ�ַ 
tem=num/10;
W_1byte(0,1,tem+0x30);
tem=num%10;
W_1byte(0,1,tem+0x30); 
W_1byte(0,0,0XFF); // ���ߵ�ַָ�� ��ֹ��һ�������ݵĸ���
}
 
/******************************************************************** 
���� ����LCD_print4num
��ڲ����� ��ʾ4����
���ڲ������� 
�������ã� 
˵        ���� 
********************************************************************/ 
void LCD_print4num(unsigned char x,unsigned char y,unsigned int num){
unsigned char tem;
tem=num/100;
LCD_print2num(x,y,tem);

tem=num%100;   
LCD_print2num(x,y+1,tem);


  W_1byte(0,0,0XFF); // ���ߵ�ַָ�� ��ֹ��һ�������ݵĸ���
}
 
//////////////////////////////////////////////////////////////

/******************************************************************** 
���� ����LCD_print 
��ڲ����� ��ʾ1 ascii
���ڲ������� 
�������ã� 
˵        ���� 
********************************************************************/ 
void LCD_print(unsigned char x,unsigned char y,unsigned char ch)
{  
unsigned char a; 
a=address(x,y);
W_1byte(0,0,a);     //��ʾ�ĵ�ַ 
W_1byte(0,1,ch); 



}
/******************************************************************** 
���� ����LCD_print1 
��ڲ����� ��ʾ1 ascii
���ڲ������� 
�������ã��������ĵ�ַ��ʾ���������ַ 
˵        ���� 
********************************************************************/ 
void LCD_print1(char ch)
{  
W_1byte(0,1,ch); 
}
//////////////////////////////////////////////////////////////



 void lp(unsigned char *p)
 {
 static unsigned char *p1=" ",*p2=" ",*p3=" ",*p4=" ";
 p4=p3;
 p3=p2;
 p2=p1;
 p1=p;
  LCD_const_disp(1,1,"                ");
  LCD_const_disp(2,1,"                ");
  LCD_const_disp(3,1,"                ");
  LCD_const_disp(4,1,"                ");
  LCD_var_disp(1,1,p4);
  LCD_var_disp(2,1,p3);
  LCD_var_disp(3,1,p2);
  LCD_var_disp(4,1,p1);
  delayms(300);
 }

//pin debug
/*
void lcd_test(void)
{

int i;
// Set_CS()Set_SID()Set_SCLK()  Clr_CS() Clr_SID() Clr_SCLK() 
 
 for(i=0;i<5;i++) {Set_CS();delayms(200); Clr_CS();delayms(200); }
  for(i=0;i<5;i++) {Set_SID();delayms(500); Clr_SID();delayms(500); }
   for(i=0;i<5;i++) {Set_SCLK();delayms(1000); Clr_SCLK();delayms(1000); }
 

}

*/
