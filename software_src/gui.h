#ifndef _GUI_H_
#define _GUI_H_
extern char GUI_date[17];
void GUI_set_time(void);
char *GUI_get_date(void) ;
void GUI_check(void);
unsigned char GUI_mainmeu( void );
void dateRefresh(unsigned char readhardware);
void _GUI_datashow(char page);
void GUI_welcome(void);
void GUI_readback(char *buf);
//�������� ��������
//1 up   �ϼ�/���
//2 down �¼�/�Ҽ�
//3 left  ȷ�� 
//4 right ȡ��/����
//����
//5 lup      
//6 ldown
//7 lleft
//8 ldown
//
#endif