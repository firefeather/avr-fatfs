#ifndef _MAIN_H_
#define _MAIN_H_
 
unsigned char ReadSDFile(unsigned int index,char *data); //��ȡһ������
void ftochr(float a,char * dest);                  //������ת�����ַ���
void itochr(int a,char * dest);                    //��������ת�����ַ���
void StructToChar(void);                           //���ṹ���е�����ת���ַ���
void check(void );
float SquareRootFloat(float number);
char *get_name( char fnamep[] );
#endif


