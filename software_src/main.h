#ifndef _MAIN_H_
#define _MAIN_H_
#define SINGLE_ITEM_SIZE 64 
char ReadSDFile(char *fnamep,int index, char *data, char mode);//��ȡһ������
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
void CharToStruct(char *buf);
void timer1_init(void);
char scan_files (char* path); //�ļ����Һ��� ����ָ��Ŀ¼�µ������ļ�
#endif


