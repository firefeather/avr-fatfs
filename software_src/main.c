#include "config.h"
#define  N_per_Second  (168.64)
//=2.72*N_Seconds, now N=62��N_per_Second=62*2.72=168.64
//#define _FOR_FAST_TEST

const char tab[]="\t\0";
const char enter[]="\n\0";
char buffer[512];
char TempChar[80]; //�����ʱ�ִ�
struct DATA Result;
struct tm t;
unsigned long now =0; //ʱ��Ĵ��� ��λS
void debug(UINT8 *str,UINT8 val);//debug�������
void WriteSDFile(void);//дSD��
float Round(float x); //�������뺯��
struct CONFIG config; //ϵͳ���ñ����ṹ��

void initDevices(void){
     CLI();
	 DDRA=0XFF;
	 PORTA=0XFF;
	 DDRB=0XFF;
	 PORTB=0XFF; 	 
	 DDRC=0XFF;
	 PORTC=0XFF;
	 DDRE=0XFF;
	 PORTE=0XFF;
	 DDRG=0XFF;
	 PORTG=0XFF;
	 power_check_init(); 
	 SPI_IO_Init(); //spi�ӿ�Ӳ����ʼ��
	 SD_Init();//sd����ʼ��
	 uart1_init();//ͨ���õ�UARTΪUART1
	 LCD_INT();delayms(50);LCD_INT();//LCD��ʼ��
	 LCD_SW(1);
	 config.comCmd = 0; //����λ������
	 config.last5s=0; //5s��ʱ��
	 config.THRESHOLD_delta_sec=60; //һ�μ����ʱ
	 config.heatThreshold = 5; //�̵��������¶� 
	 config.checkDeltaTime=20;  //�Զ����ģʽ ʱ����	 
	 config.checkDelta = 0;     //
	 config.autocheck=1;        //�Զ���⿪��
	 config.readMode = 0;      //������ģʽ
	 config.autoSend = 1; //zigbee���Ϳ��أ���Ϊ0ʱ��ʹ�ܷ���
	 config.Sd = 1;      //Sd�洢���أ� ��Ϊ0ʱ��ʹ�ܴ洢
	 config.is_lowpower = 0; //��ص���ָʾ�Ĵ��� is_lowpower !=0�����͡�
	 #ifdef _FOR_FAST_TEST
	 config.THRESHOLD_delta_sec=5; //һ�μ����ʱ
	 config.heatThreshold = 20; //�̵��������¶� 
	 config.checkDeltaTime=5;  //�Զ����ģʽ ʱ����	 
	 #endif
	 
	 SEI();
}
void timer1_init(void)
{
 TCCR1B = 0x00; //stop
 TCNT1H = 0x00 /*INVALID SETTING*/; //setup
 TCNT1L = 0x00 /*INVALID SETTING*/;
 TCCR1A = 0x00;
 TCCR1B = 0x46; //start Timer
}
////////////////////////////////////////////////////////////////
void main(void){
	 UINT8 tmp,keycode;
	 UINT8 buf512[513];
	 char filename[]="201301.xls\0\0\0";
	 int i=0;
	 initDevices();
	 dateRefresh(1);
	 WriteFileHead();
     Result.Index=findIndex(get_name(filename),buf512);
	 #ifdef _DBG_RD_  
	 	 while(1){
		     GUI_readback(buf512);
	     }
	 #endif
	 //selfTest();
	 GUI_welcome();
	/*   //FOR DEBUG
	 while(alwaysCheck())
	 {
	   delayms(100);dateRefresh(1);StructToChar();
	   check();
	   zigbee_send_date();
	 }
	 */
	 while(alwaysCheck()){
	    tmp=GUI_mainmeu();
		switch(tmp){
		    case 3 : GUI_check(); break; 
			case 4 : GUI_set_time(); break ;
			case 5 : GUI_readback(buf512); break;
			//case 6 : GUI_send_date();
			case 7 : selfTest(); break ;
			default : break;
	   }
	   delayms(100);
	 }
}
char alwaysCheck(void)
{
 float temp;
 RecDeal(); //zigbee data deal
  	 
 power_state_refresh();
 //���5s ���¼��,���ͱ���ID
 if(config.now>config.last5s)
 {   
 	 config.last5s=config.now+5;
	 zigbee_send_id(); //���ͱ���ID
     temp= readWithoutDelay(INSIDE_SENSOR);
     if (temp>config.heatThreshold) {
 	     RELAY_OFF(); //debug("off=",(int)temp);
		 return 1;
 	 }
     else  {
   	     RELAY_ON();//debug("on=",(int)temp);
	 } 
 }
 
 
 return 1;
}
void selfTest(void){
	float tmp=0;                                                                
	char str1[6],str2[6];
	lp("����������������");
	lp("��  �Լ����  ��");
	lp("��            ��");
	lp("����������������");
	 //�Լ����
	delayms(500);
	lp("�ⲿ�¶� ");
	tmp=read_T_NUM(OUTSIDE_SENSOR);
	sprintf(str1,"%#0.1f",tmp);
	str1[6]=0;
	lp(str1);
	delayms(500);
	lp("�ڲ��¶�");
	tmp=read_T_NUM(INSIDE_SENSOR);
	sprintf(str2,"%#0.1f",tmp);
	str2[6]=0;
	lp(str2);
	delayms(500);
	lp("�������壺");delayms(500);
	lp("������"); beep(2,2);delayms(500);
	lp("power ָʾ��");
	LED_OFF();delayms(100);LED_ON();delayms(100);
	LED_OFF();delayms(100);LED_ON();delayms(100);
	LED_OFF();delayms(100);LED_ON();delayms(100);
	delayms(500);
	lp("���ȿ���");
	RELAY_ON();delayms(100);  
	RELAY_OFF();delayms(100);
	RELAY_ON();delayms(100);
	RELAY_OFF();delayms(100);
	lp("  ");delayms(500);
	lp("                ");
	lp("                ");
	lp("                ");
	lp("                ");
	delayms(100);
	  
}

void WriteFileHead(void)   
{
 	 unsigned int bw;
	 FRESULT res;
	 FATFS fs;
	 FIL file;
	 char fnamep[]="201201.xls\0\0\0"; 
	 UINT8 itam[]="DEV000001\t\t\t\t\t\t\t\t\t\t\r\n���\t����\tʱ��\t�¶�\t����\t����ָ��\t�ȼ������¶�\t�൱�¶�\t����Σ����\t������ҵ\t�е�ǿ����ҵ\t��ǿ����ҵ\n\0";
	 res=disk_initialize(0);
	 res = f_mount(0, &fs);
	 //get_name(fnamep)
	 res = f_open(&file, get_name(fnamep) , FA_OPEN_ALWAYS | FA_WRITE );  //����һ���µ��ļ�
	 res = f_write(&file,itam,128,&bw);   //bw ��д���ֽ���
	 f_close(&file);
	 f_mount(0, NULL);
} /////////////////////////////////////////////////
//       д���ļ����� 
//(����)���ļ� 
// data ָ����д��ĵ��ַ��� 64byt 
//////////////////////////////////////////////// 
void WriteSDFile(void)   
{
    unsigned int bw;
	FRESULT res;
	FATFS fs;
    FIL file;
	char fnamep[13];
	long lenth=0;
	disk_initialize(0);
	res = f_mount(0, &fs);
	res = f_open(&file,get_name(fnamep), FA_OPEN_ALWAYS | FA_WRITE );  //����һ���µ��ļ�
	lenth=file.fsize;   
	res = f_lseek (&file,lenth);	 
	res = f_write(&file,TempChar,SINGLE_ITEM_SIZE,&bw);   //bw ��д���ֽ���
	f_close(&file);
	f_mount(0, NULL);
}
/////////////////////////////////////////////////
//       ��ȡ�ļ�����
//��64byteΪһ�� ��ȡ
//index����ƫ����   data�������ŵ�
//////////////////////////////////////////////// 
char ReadSDFile(char *fnamep,int index, char *data, char mode)
{
 	unsigned int bw;
	char res;
	FATFS fs;
    FIL file;
	static int indexoffset;
	unsigned int max;
	disk_initialize(0);
    res = f_mount(0, &fs);
    res = f_open(&file,fnamep,FA_READ);  
    if(res==FR_NO_FILE) {
	data=NULL;
    #if _debug >= 1 
    debug_out("now file",255);
	debug_out(filename,res);
	debug_out("file is no exist....",255);
    #endif 
    return res;
    }   
    max = (file.fsize-128)/SINGLE_ITEM_SIZE;
	if(mode == 0){ //����λ��ģʽ
		indexoffset = index;
	}
	else if(mode == 1){ //λ��ƫ��ģʽ
		indexoffset+=index;
	}
	if(indexoffset >max){
	    indexoffset = max;
	}
	else if(indexoffset <=0){
		indexoffset = 1;
	}
	res = f_lseek (&file,(indexoffset-1)*SINGLE_ITEM_SIZE+128);	 //ǰ�����ֽ�����Ϊ�ļ�ͷ�ռ� ���Դӵ������/д��
    res = f_read(&file,data,SINGLE_ITEM_SIZE,&bw);
    f_close(&file);
	f_mount(0, NULL);
	return res;
} 
//////////////////////////////////
//   find index
// ��鵱ǰ�ļ��ߴ磬���ݵ����ڶ���
//'\n'��������indexȷ����ǰindexֵ
//////////////////////////////////
unsigned int findIndex(char *filename,char *buf){
    unsigned int bw,tmp;
	long index =0;
	unsigned char is_first_end=0;
	char *fnamep=filename;
	FRESULT res;
	FATFS fs;
	FIL file;
	long lenth=0;
	int readsize=0;
	//PrintString_n(fnamep);
	res = f_mount(0, &fs);
	res = f_open(&file,fnamep, FA_OPEN_ALWAYS | FA_READ );  //����һ���µ��ļ�
	if(res !=  FR_OK){ //openerror
	    return res;}
	lenth=file.fsize;   //�ļ�β��Ϊ file.size 
	//debug("size=",0xff);
	//PrintLong(lenth);
	if(lenth > 512) {
	    readsize=512;
		lenth=file.fsize;
	}
	else {
	    readsize =file.fsize;
		lenth=0;
	}
	res = f_lseek (&file,file.fsize-readsize);
	//debug("readSIZE=",0x00);
	//PrintLong((file.fsize-readsize));
	res = f_read(&file,buf,readsize,&bw);
	f_close(&file);
	//debug("readRES=",res);
	//debug("readbw=",0X00);
	//PrintLong(bw);
	//PrintString_n(buf);
	for(tmp=readsize;tmp>0;tmp--){
		//debug("buf index",buf[tmp]);
		//PrintLong(tmp);
		//if(buf[tmp] == '\n') Usart_Transmit('@');						  
		if(buf[tmp] == '\n' && is_first_end== 0){
		    is_first_end=1; 	
			//debug("first=",0xf0);					      
		}
		else if(buf[tmp] == '\n' && is_first_end== 1){
		    lenth -= (512-tmp);
			break;
		} 						
	}
	//debug("start=",0X00); PrintLong(lenth);
	if(lenth < 118 ){ 
 		return 1;
	}
	else {
		 //debug(">128 ",0X00);
		 while(buf[tmp] <= '0' || buf[tmp] >= '9') tmp++;
		 //debug("nozero ",bw); PrintLong(tmp);
		 while(buf[tmp] != 't' && buf[tmp] >= '0' && buf[tmp] <= '9'){
		     index=index*10+(buf[tmp]-'0');
		 	 //Usart_Transmit(buf[tmp]);	
		 	 tmp++;
		 }
	}
	//debug("index=",0X00);
	//PrintLong(index+1);
	return index+1;
}
float Round(float x){
    x=x*10;
	if(x >=0) x+=0.5;
	else x-=0.5;
	x=(int)x;
	x=x/10.0;
	return x;
}

void check( void )
{
 unsigned char tmp;
 unsigned int WScounter;
 //������
 //��������1 �˲����ϸ��ֲ���С�
 tmp=SREG;
 CLI();
 WScounter=TCNT1;
 SREG=tmp;
 SEI();
 TCCR1B = 0x00; //�رռ�����
 //�������
 Result.WindSpeed=WScounter/N_per_Second;
 //��������
 //�����ټ���ֵ��ʹ����һ��������ʱ�����µ���
 //       ����V<3m/sʱ��V=V-0.1
 //       3<V<13M/Sʱ��V=V
 //       13<=V<=16ʱ��V=V+0.3
 //       V>16ʱ��V=V+0.6
 //       �ô˽��������ʾ���洢�����빫ʽ���㡣
 if(Result.WindSpeed < 3) {
     Result.WindSpeed = Result.WindSpeed - 0.1;
 }
 else if( Result.WindSpeed <13.0 && Result.WindSpeed >3 ) {
 	 ;//nothing to do
 }
 else if ( Result.WindSpeed >=13.0 && Result.WindSpeed<=16 )
 {
  	 Result.WindSpeed = Result.WindSpeed + 0.3; 
 }else if(Result.WindSpeed > 16){
 	   Result.WindSpeed = Result.WindSpeed + 0.6;
 }
  
 //��������
 Result.WindSpeed=Round(Result.WindSpeed);
  //�¶�
 Result.Temperature=read_T_NUM(OUTSIDE_SENSOR); //������ �������
 Result.Temperature=read_T_NUM(OUTSIDE_SENSOR);
 //��������
 Result.Temperature=Round(Result.Temperature);
 //WCI����ָ��
 Result.WCI = 4.18 *(10*SquareRootFloat(Result.WindSpeed) + 10.45 -  Result.WindSpeed  ) *( 33 - Result.Temperature );
 //ECT�ȼ������¶�
 Result.ECT=33.0f - 0.01085f*Result.WCI;
 //TEQ �൱�¶�
 Result.Teq = Result.Temperature +( (Result.Temperature -36)/10 ) * Result.WindSpeed ;
//������ת�����ַ���
sprintf(Result.WSChar, "%#.1lf", (float)Result.WindSpeed);
sprintf(Result.TempChar, "%#.1lf", (float)Result.Temperature); //PrintString_n(Result.TempChar);
sprintf(Result.WCIChar, "%#.1lf",  (float)Result.WCI); //PrintString_n(Result.WCIChar);
sprintf(Result.ECTChar, "%#.1lf", (float)Result.ECT);  //PrintString_n(Result.ECTChar);
sprintf(Result.TeqChar, "%#.1lf", (float)Result.Teq);
sprintf(Result.IndexChar, "%d", Result.Index);
Result.TempChar[6]='\0';
Result.WSChar[5]='\0';
Result.WCIChar[7]='\0';
Result.ECTChar[6]='\0';
Result.TeqChar[6]='\0';
 return ;
}
/*
////////////////////////////////////////////
//				�ַ���ת������
//   ���� ��  �ַ���
////////////////////////////////////////////
void ftochr(float a,char * dest){//float
char i=0,j=0,lenth;
int status;
char *res;
 res=ftoa(a,&status);  //float to ascii
lenth=strlen(res);

for(i=0;i <lenth;i++) 
       {
	   	dest[i]=res[i];

		if( res[i]=='.'  ) 
			{
				dest[i+1]=res[i+1];
					dest[i+2]='\0';
						return ;    
		    }
 
 		}
}
//////////////////////////////////////////////////////
//              �������ݱ��ַ���
//    a  ��  dest
///////////////////////////////////////////////////////
void itochr(int a,char * dest){ //int to ascii
	 itoa(dest,a,10); 
}
*/
//////////////////////////////////////////////////////
//                  �ṹ�� ���ַ���
// ��Ŀǰ���ڽṹ�������ת����Temp_Char�С�
///////////////////////////////////////////////////////
void  StructToChar(void)
{ 
  unsigned char i;
  char otherbyte[]="0\t0\t0\t0";
  char *(ary[])={Result.IndexChar,Result.Date,Result.Time,
 	  			Result.TempChar,Result.WSChar,Result.WCIChar,Result.ECTChar,
				Result.TeqChar
			   };  //ָ�������׵�ַ��ָ��
  //strcat(Temp_Char,Result.Name);
  for(i=0;i<=80;i++) TempChar[i]='\0';  //�������
    for(i=0;i<=7;i++){
		strcat(TempChar,ary[i]);  // ��˳�����ַ���
		strcat(TempChar,tab);     // �ִ���β�����Ʊ��
    }
				 
				 otherbyte[0]=otherbyte[0]+Result.WeiHai;
				 otherbyte[2]=otherbyte[0]+Result.LowLabor;
				 otherbyte[4]=otherbyte[0]+Result.MidLabor;
				 otherbyte[6]=otherbyte[0]+Result.HighLabor;
 
  strcat(TempChar,otherbyte);  
  strcat(TempChar,enter);  
  strcat(TempChar,"\0");
}

//////////////////////////////////////////////////////
//               �ַ���  ��  �ṹ��
// 
///////////////////////////////////////////////////////
void CharToStruct(char *buf)
{
  unsigned char j=0;
  unsigned char *p,*q;
  char *(ary[])={Result.IndexChar,Result.Date,Result.Time,
 	  			Result.TempChar,Result.WSChar,Result.WCIChar,Result.ECTChar,
				Result.TeqChar
			   };  //ָ�������׵�ַ��ָ��
    p=ary[j];
	q=buf;
	
	while(1){
    if(*q =='\n') {*p='\0'; return;} ;
	if(*q =='\t') {
		*p='\0';
		q++;
	    if(j>7) break ;
		j++;
		p=ary[j];
		continue ;
	}
    *p++=*q++;
	}
	return ;
}
 
 ////////////////////////////////////////////
//				���ݵ�ǰ���ڻ�ȡ�ļ���
//   
////////////////////////////////////////////
char *get_name( char filenamep[] ){     
	  unsigned char i=0;
 	  for(i=0;i<6;i++) {
	  				    *(filenamep+i)=Result.Date[i];
	  				   } 
	 	*(filenamep+(i++))='.';
		*(filenamep+(i++))='x';
		*(filenamep+(i++))='l';
		*(filenamep+(i++))='s';
		*(filenamep+(i))='\0';
					   
      return filenamep;
} 
float SquareRootFloat(float number)
{
    long i;
    float x, y;
    const float f = 1.5F;
    x = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;
    i  = 0x5f3759df - ( i >> 1 );  //�����
  //i  = 0x5f375a86 - ( i >> 1 );  //Lomont
    y  = * ( float * ) &i;
    y  = y * ( f - ( x * y * y ) );
    y  = y * ( f - ( x * y * y ) );
    return number * y;
} 
//
//###############################################################//
//debug
void debug(UINT8 *str,UINT8 val)
{
 UINT8 str2[4]={0,0,0,0};
 str=str;
 val=val;
 #ifdef _UARTDEBUG
 PrintString("\r\n");
 PrintString(str);
 PrintChar(val);
 #endif
 #ifdef _LCDDEBUG
 lp(str);
 str2[2]=val%10+0x30;
 val=val/10;
 str2[1]=val%10+0x30;
 val=val/10;
 str2[0]=val%10+0x30;
 lp(str2);
 #endif
}
