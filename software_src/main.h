#ifndef _MAIN_H_
#define _MAIN_H_
 
char ReadSDFile(unsigned int index,char *data); //��ȡһ������
void ftochr(float a,char * dest);                  //������ת�����ַ���
void itochr(int a,char * dest);                    //��������ת�����ַ���
void StructToChar(void);                           //���ṹ���е�����ת���ַ���
void check(void );
float SquareRootFloat(float number);
char *get_name( char fnamep[] );
unsigned int findIndex(char *filename,char *buf);
void WriteFileHead(void) ;
void selfTest(void);
void WriteSDFile(void);
void CharToStruct(void);
void timer1_init(void);
#endif


