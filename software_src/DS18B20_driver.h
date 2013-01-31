//------------------------------------------------------------------------------
// �ļ�����DS18B20_driver.h
// ˵����  DS18B20����ͷ�ļ�
// ���ܣ�  ʵ��1-wire�����Ķ�д
// ʹ�÷�����  
// ����ƽ̨��   AVR 8bit (M16����֤)
// �����ϵ��   DS18B20_driver.c    DS18B20�����������ļ���������дλ���ֽڷ�����
// ��ֲ�ˣ�     
// ����޸ģ�   
//------------------------------------------------------------------------------


#ifndef _DS18B20_DRIVER_H_

 #define _DS18B20_DRIVER_H_


#ifndef TRUE
		#define TRUE 1
#endif

#ifndef FALSE
		#define FALSE 0
#endif
#define TemIn 1
#define TemOut 2
//------------------------------------------------------------------------------
// ������������
//------------------------------------------------------------------------------
void          Delay_nus(unsigned int n);             //��ʱn΢�뺯��
unsigned char reset_18B20(void);                     //18B20��λ
void          write_bit_18B20(char bitval);          //дһλ��18B20
unsigned char read_bit_18B20(void);         									//��һλ��18B20
void          write_byte_18B20(unsigned char data);  //дһ�ֽڵ�18B20
unsigned char read_18B20(void);             									//��һ�ֽڵ�18B20
float read_T(void);
float read_T_NUM(unsigned char NUM);
float readWithoutDelay(unsigned char NUM);
//------------------------------------------------------------------------------
// ���ܺ������� (��Ե�������)
//------------------------------------------------------------------------------
unsigned char reset_18B20(void);  
void convert_T(void);

//void last_temp(unsigned int data);


#endif
