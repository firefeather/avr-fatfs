 ////////////////////////////LCD.H/////////////////////////////////////
//LCDͷ�ļ�
//���ܣ�����lcd���ƺ��� �� ��˵������ʹ�÷���
//�����ˣ�������   
//ʱ�䣺 2010.12.23  v1.0
//�汾�޸ļ�¼��
///////////////////////////////////////////////////////////////////// 
#ifndef _LCD_H_
#define _LCD_H_
//void lcd_test(void);  //pin debug
void lp(unsigned char *p);//��������
void W_1byte(unsigned char RW, unsigned char RS, unsigned char W_data); //дһ�ֽ� ���������
void Write_8bits(unsigned int W_bits);   //дһ�ֽ�����
void LCD_Init(void); //�����λ ��ʼ�� 
unsigned char LCD_INT(void); //��ʼ��  2��  ���50ms
// flash�� ���ַ� ��ʾ ����		  
void LCD_const_disp(unsigned char x,  //	���� 
            		 unsigned char y, //����   
					const unsigned char  *single_data);//�ַ����׵�ַ	 LCD_const_disp(1,5,�������ˡ�);		
//	�����б��� ��ʾ ����		  
void LCD_var_disp(unsigned char x,  //	���� 
	 				 unsigned char y, //����   
					  unsigned char  *single_data);//�ַ����׵�ַ	 unsigned char tab[]={"fugreat"}  LCD_var_disp(2,4,tab);

void LCD_print(unsigned char x,unsigned char y,unsigned char ch);
void LCD_print1(char ch);
void LCD_print4num(unsigned char x,unsigned char y,unsigned int num);
void LCD_print2num(unsigned char x,unsigned char y,unsigned char num);  //LCD_print2num(2,3,wendu);
unsigned char LCD_SW(unsigned char i);
void LCD_char_disp(unsigned char x, unsigned char y, unsigned char data);   //unsigned char wendu=65;  LCD_char_disp(1,2,wendu);   a
void LCD_CLR(void);  //�����ʾ��ַ����
void Set_White(unsigned char x,unsigned char y,unsigned char end_x,unsigned char clear);
void clr_white(void); //�巴��
void set_white_n(unsigned char n,unsigned char clear);
void Set_Draw( void );  //  ����Ϊ��ͼģʽ
//////////////////////����ָ��////////////////////////////////////
//W_1byte(0,0,0x34);			//8BIT���ƽ��棬����ָ�,����ͼ��ʾOFF
//W_1byte(0,0,0x36);	        //8BIT���ƽ��棬����ָ�,����ͼ��ʾON
//W_1byte(0,0,0x30);	        //�������ָ�
void lcm_set_power_high(void);
void lcm_set_power_low(void);

#endif














				   