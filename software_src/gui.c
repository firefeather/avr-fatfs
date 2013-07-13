#include "config.h"
const char labelH[]="��ǿ����ҵ��\0";
const char labelM[]="�е�ǿ����ҵ��\0";
const char labelL[]="��ǿ����ҵ��\0";
const char H01[]="��ǿ�Ͷ��ල��\0";
const char H02[]="������ˮ;\0" ;
const char H03[]="���ָ������¶��\0";
#define M01 H01
#define M02 H03
const char M03[]="�����֡�\0";
const char M04[]="���Ͳʡ�\0";
#define L01 M03
#define L02 M04
const char L03[]="������ҵʱ�䡣";
//-----//
#define H11 M04
#define H12 H03
const char H13[]="��Ϣע�Ᵽů��\0";
#define M11 H01
const char M12[]="���ٷǱ�����ҵ��\0";
const char M13[]="�Ͷ�ʱ��<30min��\0";
const char L11[]="ȡ���Ǳ������ҵ\0";
const char L12[]="�Ͷ�ʱ��<15min��\0";
#define L13 H03
//-----//
#define H21 L11
#define H22 L12
#define H23 H03
const char M21[]="ȡ��������ҵ��"; 
#define L21 M21
const char str_blank[]="----------------"; 
//#define LEDON   PORTC&=~(1<<7)					   
//#define LEDOFF  PINC|=(1<<7)
char GUI_date[17]="09��19��18:00:00\0";
#define SW_ON 1
#define SW_OFF 0
// ���˵�
unsigned char GUI_mainmeu( void ){
 	unsigned char key=0; //init= nokey
	unsigned char select=3;
	LCD_CLR();
	
 	Set_White(1,1,8,1);
	Set_White(1,2,8,1);
	Set_White(1,3,8,1);
	Set_White(1,4,8,1);
	dateRefresh(1); //����ϵͳʱ��
	LCD_const_disp(1,1,GUI_get_date()); //��ʾʱ��
	LCD_const_disp(2,1,"  ���  ʱ�ӵ���");
	LCD_const_disp(3,1,"  ��ѯ  ���ݴ���");
	LCD_const_disp(4,1,"  ��ʼ��");
	
	//LCD_print2num(4,8,config.comCmd);
	Set_White(1,1,8,1);
	Set_White(1,2,8,1);
	Set_White(1,3,8,1);
	Set_White(1,4,8,1);
	set_white_n(select,0);
	//������λ���Զ��������

		
	while(alwaysCheck())
	{
		if(config.comCmd == 0x01 || config.comCmd == 0x02) {
	        
			return 3; //goto check();
		}
		
		if(config.is_lowpower) {
	        LCD_const_disp(4,6,"������"); //devicename[7] = 'F';// DDRC|=(1<<LED_PIN);LED_PORT |=  (1 << LED_PIN) ;
		}
		else{
	   		LCD_const_disp(4,6,"      ");// devicename[7] = 'U'; DDRC|=(1<<LED_PIN);LED_PORT &= ~(1 << LED_PIN);
		}
		
	 	key=kbscan();
		dateRefresh(1); //����ϵͳʱ��
		LCD_const_disp(1,1,GUI_get_date()); //��ʾʱ��
		if((select>3) && ( key==up ) ){
		 Set_White(1,2,8,1);
		 Set_White(1,3,8,1);
		 Set_White(1,4,8,1);
		 select--;
		 set_white_n(select,0);
		}
		if((select<7) && ( key==down ) ){
		 Set_White(1,1,8,1);
		 Set_White(1,2,8,1);
		 Set_White(1,3,8,1);
		 Set_White(1,4,8,1);
		 select++;
		 set_white_n(select,0);
		}
		if(key == left ){
		 Set_White(1,1,8,1);
		 Set_White(1,2,8,1);
		 Set_White(1,3,8,1);
		 Set_White(1,4,8,1);
		 //beep(3,select);
		 return select;
		}
		delayms(5);
    }
	return 0xff; //error
	
}

//����� ���˵�
void GUI_check(void){
    char key;
	char page=0,is_on=0;
	char windcounter=0;
	unsigned long next_step_time=0;
	char selectCheckMode=config.autocheck; //�Զ���⿪��
	
RE_IN:
	key=0;
	page=0;
	is_on=0;
	windcounter=0;
	next_step_time=0;
	dateRefresh(1);
if(config.comCmd == 0x02 && config.checkDelta > 60) {  //ѭ����� �� ���>60s
	 config.autocheck = 0x02;
	 LCD_CLR();
	 LCD_const_disp(1,1,"�յ����");
	 LCD_const_disp(2,1,"  ѭ�����");
	 LCD_const_disp(3,1,"�����(s):");
	 LCD_print4num(4,2,config.checkDelta/10000);
	 LCD_print4num(4,4,config.checkDelta%10000);
	 delayms(1000);
}
else if(config.comCmd == 0x01 || config.comCmd == 0x02){  //���μ�� ��ѭ����⵫������������
	config.autocheck = SW_OFF;
	 LCD_CLR();
	 LCD_const_disp(1,1,"�յ����");
	 LCD_const_disp(2,1,"  ���μ��");
	 config.comCmd = 0x00; //���μ������¼������������������־
	 delayms(1000); 
}
else {	  

	      LCD_CLR();
		  LCD_const_disp(1,1,"�˵�/ ���");
		  LCD_const_disp(2,3,"�Զ�");		 
		  LCD_const_disp(3,3,"�ֶ�");
		  if(selectCheckMode==SW_ON) {
	          Set_White(1,2,8,0);
			  Set_White(1,3,8,1);
		  }
		  else {
		      Set_White(1,2,8,1);
		      Set_White(1,3,8,0);
		  }
	
    //<<�˵�/���/�֣��ԣ���>>
	while(alwaysCheck()){
		if(config.comCmd!=0 ){
			if(config.comCmd == 3) config.comCmd =0;				
		  	return ;
		}
	 	key=kbscan();
		dateRefresh(0); //ֻˢ�º�̨ʱ��
		//�ϼ��̰� ѡ��
		if(key==up || key ==down){
		    if(selectCheckMode >0){
			    selectCheckMode=0;
				Set_White(1,2,8,1);
	 			Set_White(1,3,8,0);
			}
			else {
			    selectCheckMode=1;
				Set_White(1,2,8,0);
	 			Set_White(1,3,8,1);
			}
			
		}
		//����̰�  ����
		if(key == left) {
			config.autocheck=selectCheckMode; 
			Set_White(1,2,8,1);
	 		Set_White(1,3,8,1); 
			break ;		
		}
		//�Ҽ��̰�  ����
		if(key == right) {
			return ;		
		}
		key=0;	
	} //end of while
}//end if	
	
    //�Զ��������
	dateRefresh(0);
	is_on =1 ;
	config.time1=config.now+config.THRESHOLD_delta_sec;
	Result.TempChar[0]=0; //����ϴν��
	Result.WSChar[0]=0;
	while(alwaysCheck()){
		dateRefresh(0); //ֻˢ�º�̨ʱ��
		key=kbscan();
		if(key != 0) beep(0,1);
		if(key==right || config.comCmd == 0x03){	//�Ҽ� �˳�
		    is_on=0;
			LCD_CLR();
		 	LCD_Init();	  
	 	 	LCD_const_disp(4,5,"�˳�    "); 
		 	delayms(200);
		 	LCD_const_disp(4,7,".."); 
		 	delayms(200);
		 	LCD_const_disp(4,8,".."); 	
		 	delayms(500);
		 	LCD_CLR();
			config.comCmd = 0;//����Զ��������
		 	goto RE_IN;
		}
		if(is_on==1){ 
			dateRefresh(1); //����ʱ��
		    _GUI_datashow(page); 
		    if(config.now < config.time1) {
				//ʱ����� �������ټ�� �ȴ���� ��֧�ַ�ҳ
				if(windcounter==0){
				    windcounter=1; //���㿪�����ټ�����
					timer1_init(); //�������ٴ���������
				}
				if(page == 0 ){
				
				    LCD_const_disp(4,1,"���ڼ�⣺");
					LCD_print4num(4,6,config.time1-config.now);
					LCD_const_disp(2,6,"      ");
					LCD_const_disp(3,6,"      ");
				}
			} 
			else {
			   //������ ������� ת������ �洢���� �л����Ǽ��״̬
			    windcounter =0 ; //�رշ��ٴ�����������
				beep(1,1);
				LCD_const_disp(4,1,"--���㲢�洢--       ");
				check();
				StructToChar(); //ת���ַ���
				WriteFileHead();//��д�ļ�ͷ
				WriteSDFile();  //д��sd��
				if(config.autoSend>=1) {
					 zigbee_send_date(); //zigbee����
				}
				Result.Index++; //��������һ
				is_on=0; //�л����Ǽ��״̬
				next_step_time=config.now+config.checkDeltaTime;//�Զ���ҳʱ�����
				page=0;
				if(config.autocheck == 0) config.comCmd = 0;
		   }
		}
		else { //is_on == 0 �Ǽ��״̬ �ֶ���ҳ/�Զ���ҳ
		    dateRefresh(0);//������ʱ��
			_GUI_datashow(page); 
			if(page == 0 ){
				
				    LCD_const_disp(4,1,"��ɼ��        ");
					if(config.autocheck >= 1){
					    LCD_const_disp(4,7,"�Զ�");
					}
					else {
					    LCD_const_disp(4,7,"�ֶ�");
					}
					
				}
						//�ֶ���ҳ 
			
			if(key==up){ //�ϼ� : ҳ��� 
		        if(page>0) page--;
				else{
				page =5;
				next_step_time = config.now + config.checkDeltaTime;
				}
		    	LCD_CLR();
		    	LCD_Init();
			}
			if(key==down){//�¼� �� ҳ���
		        page++;
				next_step_time = config.now + config.checkDeltaTime;
		  		LCD_CLR();
		    	LCD_Init();
				if(page >= 6 ) {
					page=0;
					continue ;
				}
			} 	
			//LCD_print2num(4,1,page);
			//LCD_print4num(4,3,config.now);
			//LCD_print4num(4,6,next_step_time);
			if( config.autocheck == 2  ){ 
			      if(config.now >= next_step_time && page <5 )	{   //�Զ���ҳ
				      next_step_time = config.now + config.checkDeltaTime;
					  page++;
					  LCD_CLR(); 
					  key=0;
				  }
			}
			else if( config.autocheck == 1 ){
				 if(config.now >= next_step_time || page >=6 )	{   //�Զ���ҳ
				      next_step_time = config.now + config.checkDeltaTime;
					  page++;
					  LCD_CLR(); 
					  key=0;
				  }
			}
			if(config.autocheck==2 && page==5 ){
				 LCD_const_disp(4,1,"���´�:");
				 LCD_print4num(4,5,(config.checkDelta+config.time1-config.now)/10000);
				 LCD_print4num(4,7,(config.checkDelta+config.time1-config.now)%10000);
			}
			if(config.autocheck == 0 && config.comCmd !=0) return;
			
			if( page>=6 || key == left ||(config.comCmd == 0x02 && config.now > config.time1+config.checkDelta) ){
			    //�������ҳ���Ҵ����Զ����ģʽ���� ������� �� ���Զ����ģʽ�����´μ��ʱ���ѵ��� 
				// ҳ�����㿪���´μ��
				page = 0;
				dateRefresh(1); //ˢ��ʱ��
				is_on =1 ; //�������
				config.time1=config.now+config.THRESHOLD_delta_sec; //�����´μ����ټ�����ֹͣʱ��
				Result.TempChar[0]=0; //����ϴν��
				Result.WSChar[0]=0;
				LCD_CLR();
				key = 0;  
			}
				         
				

		} 
		  				 
	    delayms(10); 
	}//end while
}//end function
void _GUI_datashow(char page){
	if(page == 0){
 	//��ʾ����ʱ��
	    LCD_var_disp(1,1,GUI_get_date());
	//��ʾ�¶�
	 	LCD_const_disp(2,1,"�¶� (��):      ");
	 	LCD_var_disp(2,6,Result.TempChar);
	//��ʾ����
	    LCD_const_disp(3,1,"����(m/s):      ");
	 	LCD_const_disp(3,6,Result.WSChar);

	 } 
	 if(page == 1){
	     LCD_var_disp(1,1,GUI_get_date());
		 LCD_const_disp(2,1,"����ָ��: ");
		 LCD_var_disp(2,6,Result.WCIChar);						
		 LCD_const_disp(3,1,"�ȼ��¶�: ");
		 LCD_var_disp(3,6,Result.ECTChar);	 
		 LCD_const_disp(4,1,"�൱�¶�: ");
		 LCD_var_disp(4,6,Result.TeqChar);	
	 }
	 if(page == 2){
	     LCD_var_disp(1,1,GUI_get_date());
		 LCD_const_disp(2,1,"����Σ����:");
	 if(Result.WeiHai==0){LCD_const_disp(3,1,"  ����Σ����С");			 }
	 else if(Result.WeiHai==1){	LCD_const_disp(3,1,"  ����Σ���Խϴ�");	 }
	 else if(Result.WeiHai==2){	LCD_const_disp(3,1,"  ����Σ���Ժܴ�");	 }
	 else LCD_const_disp(3,1,"����Σ����С��");
	 }	  
	 if(page==3){
	     LCD_const_disp(1,1,labelH);		
	 	 switch( Result.WeiHai ){
			case 0 :
			LCD_const_disp(2,1,H01);
			LCD_const_disp(3,1,H02);
			LCD_const_disp(4,1,H03);
			break;
			case 1 : 
			LCD_const_disp(2,1,H11);
			LCD_const_disp(3,1,H12);
			LCD_const_disp(4,1,H13);
			break ;	
			case 2 :
			LCD_const_disp(2,1,H21);
			LCD_const_disp(3,1,H22);
			LCD_const_disp(4,1,H23);
			break;
			default : ;
		}
	 } 
	 if(page==4){
	 		LCD_const_disp(1,1,labelM);		
	 		switch( Result.WeiHai ){
	 			case 0 :
				LCD_const_disp(2,1,M01);
				LCD_const_disp(3,1,M02);
				if(Result.Temperature < -17.7){
				    LCD_const_disp(4,1,"�����֣����Ͳʡ�");
				}
				else if(Result.Temperature < -12){
				    LCD_const_disp(4,1,"���Ͳʡ�        \0");
				}
				break;
				case 1 : 
			    LCD_const_disp(2,1,M11);
				LCD_const_disp(3,1,M12);
				LCD_const_disp(4,1,M13);
				break ;
				case 2 :
				LCD_const_disp(2,1,M21);
				break ;
				default :;
	 		}
	 }
	 if(page==5){
	     LCD_const_disp(1,1,labelL);		
	 	 switch( Result.WeiHai ){	
		     case 0 :
			 LCD_const_disp(2,1,L01);
			 if(Result.Temperature < -12) {
			 LCD_const_disp(3,1,L02);
			 LCD_const_disp(4,1,L03);
			 } 
			 else {
			 LCD_const_disp(3,1,L03);
			 }
			 break;
			 case 1: 
			 LCD_const_disp(2,1,L11);
			 LCD_const_disp(3,1,L12);
			 LCD_const_disp(3,1,L13);
			 break ;
			 case 2 :
			 LCD_const_disp(2,1,L21);
			 break;
			 default : ;
		} //end switch
	}  //end if
}
char * GUI_get_date(void) {  
  //��ʽ:12��11��19:00:00
    GUI_date[0]=Result.Date[4]; 
    GUI_date[1]=Result.Date[5];
    GUI_date[4]=Result.Date[6];
    GUI_date[5]=Result.Date[7];
    GUI_date[8]=Result.Time[0];
    GUI_date[9]=Result.Time[1];
    GUI_date[11]=Result.Time[3];
    GUI_date[12]=Result.Time[4];
    GUI_date[14]=Result.Time[6];
    GUI_date[15]=Result.Time[7];
    GUI_date[16]='\0';
    return GUI_date;
}
//����ʱ�� �˵� 
void GUI_set_time(void){
    unsigned char p=2;
	char GUI_up[]= "��";
	char GUI_down[]= "��";
	char *pD=NULL,*pT=NULL;
	char *ary=GUI_up;
	unsigned char i=0,keyc=NO_KEY;
	LCD_CLR(); //����
	pD="2012��12��31��\0";
	pT="12: 30: 59\0";
	LCD_const_disp(1,1,"ʱ������:       ");
	LCD_const_disp(4,7,"����");
	LCD_var_disp(3,p,ary);
	LCD_var_disp(2,1,pD);
	LCD_var_disp(4,1,pT);
	delayms(250);
	while(alwaysCheck()){
	    keyc=kbscan();
		pD[2]=Result.Date[2];
		pD[3]=Result.Date[3];
		pD[6]=Result.Date[4];
		pD[7]=Result.Date[5];
		pD[10]=Result.Date[6];
		pD[11]=Result.Date[7];  
		pT[0] = Result.Time[0];
		pT[1] = Result.Time[1];
		pT[4] = Result.Time[3];
		pT[5] = Result.Time[4];
		pT[8] = Result.Time[6];
		pT[9] = Result.Time[7];
		
		switch(i){
            case 0: p=2;ary=GUI_up;  //��
		 	  	 if(keyc==up){
				     if(time_buf[1]<0x99){ 
					     time_buf[1]++;
						 if((time_buf[1]&0x0f)==0x0a) 
						     time_buf[1]=time_buf[1]+6;
					 }
												     
				}				  
 					        
			    else if(keyc==down){ 
				    if(time_buf[1]>0x00){
				        time_buf[1]--;
						if((time_buf[1]&0x0f)==0x0f) 
						    time_buf[1]=time_buf[1]-6;
		 	  	 		 }
												   
					}			   		
				else if(keyc==left) {i=1;}
				break;
		 case 1:p=4;ary=GUI_up;  //��
		  	  	if(keyc==up){
				    if(time_buf[2]<0x12){  
					    time_buf[2]++;	
						if((time_buf[2]&0x0f)==0x0a) time_buf[2]+=6;
					}
					else 
					    time_buf[2]=0x01;
				}						 
				if(keyc==down){ 
				    if(time_buf[2]>0x01){  
					    time_buf[2]--;	
						if((time_buf[2]&0x0f)==0x0f) 
						    time_buf[2]-=6;
			  		}
				    else 
					    time_buf[2]=0x12;						
				}						 							
 								
				if(keyc==left){
				    i=2;   
				}  
				break;
	 	 case 2: p=6;ary=GUI_up;
		 	  	 if(keyc==up){ 
				     if(time_buf[3]<0x31){ 
				         time_buf[3]++;
						 if ((time_buf[3]&0x0f)==0x0a) time_buf[3]=time_buf[3]+6;
						 if(  //2 4 6 9 11 �����30��
						  ( ((time_buf[2]==0x02) || (time_buf[2]==0x04)|| (time_buf[2]==0x06)||
						  (time_buf[2]==0x09)||(time_buf[2]==0x11))&&(time_buf[3]==0x31))){
						      time_buf[3]=0x30;
						}
				     }
 									  
 				 }
			     else if(keyc==down){ 
				      if(time_buf[3]>0x01){  
					     time_buf[3]--;
				 	  	 if((time_buf[3]&0x0f)==0x0f) time_buf[3]=time_buf[3]-6;
		 	  	 	 }
					 else time_buf[3]=0x31;						
											   
				}
				if(keyc==left) {i=3;  }						 			   		
				break;
		case 3:p=1;ary=GUI_down;
 	  	if(keyc==up){ if(time_buf[4]<0x23){  time_buf[4]++;	
													if((time_buf[4]&0x0f)==0x0a) time_buf[4]+=6;
													 
													
												 }
							else time_buf[4]=0x00;
						  }						 
				if(keyc==down){ if(time_buf[4]>0x00){  time_buf[4]--;	
													if((time_buf[4]&0x0f)==0x0f) time_buf[4]-=6;
													
												 }
							 else time_buf[4]=0x23;						
						  }	
		if(keyc==left) {i=4;    } 
		break;						  					 			
 case 4:p=3;ary=GUI_down;
 	  	if(keyc==up){ if(time_buf[5]<0x59){  time_buf[5]++;	
											 if((time_buf[5]&0x0f)==0x0a) time_buf[5]+=6;
										  }
					  else time_buf[5]=0x00;
					}						 
		if(keyc==down){ if(time_buf[5]>0x00){  time_buf[5]--;	
												if((time_buf[5]&0x0f)==0x0f) time_buf[5]-=6;
											}
						else time_buf[5]=0x59;						
					  }
		if(keyc==left ) {i=5;    } 		  						 								  			
		break;			   
 case 5:p=5;ary=GUI_down;
 	  	if(keyc==up){ if(time_buf[6]<0x59){  time_buf[6]++;	
											 if((time_buf[6]&0x0f)==0x0a) time_buf[6]+=6;
										 }
					  else time_buf[6]=0x00;
					}						 
		if(keyc==down){ if(time_buf[6]>0x00){  time_buf[6]--;	
						if((time_buf[6]&0x0f)==0x0f) time_buf[6]-=6;
					  }
		else time_buf[6]=0x59;		}				
		if(keyc==left) {i=6;p=1;ary=NULL;}  
		break;           
							 
		 }//endcase
 		 dateRefresh(88); //set clock mode
		 
		 LCD_const_disp(3,1,"                "); //��ռ�ͷ 
 		 LCD_var_disp(3,p,ary); //��ʾ��ͷ 
 		 LCD_var_disp(2,1,pD);  //��ʾ����
 		 LCD_var_disp(4,1,pT);  //��ʾʱ��
 if(keyc==right) {		  
 		  LCD_const_disp(3,1,"        �����޸�"); 
		  delayms(500);
		  LCD_CLR(); //����
		  return ;} 
 keyc=NO_KEY;
 if(i==6){    //��ֵ�ı���ɺ� ��ʾ�ѱ��� ���� ����
		  ds1302_write_time(); 
          LCD_const_disp(4,7,"    ");		  
		  LCD_const_disp(3,1,"          �ѱ���"); 
		  delayms(300);
		  LCD_CLR(); //����
		  return ;
		  }
 delayms(2);	  
}//endwhile(1)
}
void GUI_readback(char *buf){
    char key=0;
	char page=0;
	char res=0;
	char file_buf[]="201201.xls\0\0";
	LCD_CLR(); //����
	//1 ���SD״̬
		//��SD�� ��ʾ�޿� �˳�
	if((SD_DET()==0)) {
		LCD_const_disp(2,1,"δ��⵽SD��..");
			#ifdef _DBG_RD_
		   PrintString_n("not find sd");
		   #endif
		delayms(500);
		return ;
	}
	//2 ��ʾ��ǰ�·�
	get_name(file_buf);
	LCD_const_disp(1,1,"��������:");
	LCD_const_disp(2,2,file_buf);
	#ifdef _DBG_RD_
		   PrintString_n(file_buf);
	#endif
	//3 �����ļ��Ƿ����
		//����-> �����ȡ˳���ѡ��
		//������ -> ѯ�ʲ�������
	//4 ѡ�� ��ѯ˳��
		//����������
		//˳�� ����Ϊ1�� ��ѯ��һ�� 
		//���� ����Ϊ-1����ѯ���һ��
	//5 ��ȡ	
	//6 ��ʾ
	//7 ��һ�� ��һ��  �˳�
		//�������� �жϱ߽� ����5
		//�˳� ����������	
	//!!res=checkFile(file_buf);
label_recheck:	
	LCD_Init(); //����
	LCD_CLR();  
	if(res == 0){ //�ҵ����Ѿ�ȷ���ļ�
		   LCD_const_disp(1,1,"�˵�/ ��ѯ");
   		   LCD_const_disp(2,3,"��˳��");
		   LCD_const_disp(3,3,"���һ��");		 
	       if(config.readMode == READ_MODE_LAST){
		       config.readMode=READ_MODE_FIRST;
			   Set_White(1,2,8,0);
 			   Set_White(1,3,8,1);
		  }
		  else {
		       config.readMode=READ_MODE_LAST;
			   Set_White(1,2,8,1);
 			   Set_White(1,3,8,0);
		 }
		   // �˵�/��ѯ   ��˳��/���һ��
		   while(alwaysCheck()){
 		       key=kbscan();
			   dateRefresh(0); //ֻˢ�º�̨ʱ��
			   //�ϼ��̰� ѡ��
			   if(key==up || key ==down){
	    	       if(config.readMode == READ_MODE_LAST){
		    	       config.readMode=READ_MODE_FIRST;
					   Set_White(1,2,8,0);
 					   Set_White(1,3,8,1);
				   }
				   else {
		    	       config.readMode=READ_MODE_LAST;
					   Set_White(1,2,8,1);
 					   Set_White(1,3,8,0);
				   }
				}      
				//����̰�  ����
				if(key == left) {
				    Set_White(1,2,8,1);
 				    Set_White(1,3,8,1);
					delayms(100);
				break ;		
				}
				//�Ҽ��̰�  ����
				if(key == right) {
				    LCD_CLR();
	    			LCD_Init(); //����
					return ;	//����������	
				}
				key=0;
		    } //end of while
			if(config.readMode==READ_MODE_LAST){
			    ReadSDFile(file_buf,65535,buf,0); //���һ��
			}
			else {
			    ReadSDFile(file_buf,1,buf,0); //����һ��
			}
			CharToStruct(buf);      //ת��
			while(alwaysCheck()){
			    key=kbscan();     //����ɨ��
				dateRefresh(0); //ֻˢ�º�̨ʱ��
				if(key != 0){ 
					   beep(0,1);
				}
				//dateRefresh(0);  //ˢ��
				_GUI_datashow(page); //��ʾ
				if( key==left ){ //��left����һ��
					next_item:  //��һ��
				    ReadSDFile(file_buf,1,buf,1); //ƫ�Ƶ���һ��
					CharToStruct(buf);
					LCD_CLR();
		    		LCD_Init();
					page = 0;
					key=0;
				}
				if( key==lleft ){ //����left����һ��
		    	    pre_item: //��һ��
					ReadSDFile(file_buf,-1,buf,1); //ƫ�Ƶ���һ��
					CharToStruct(buf);
					LCD_CLR();
		    		LCD_Init();
					page = 0;
					key=0;
				}
				if(key==up){ //�ϼ� : ҳ��� 
	    		     LCD_CLR();
		    		 LCD_Init();
					 if(page>0) page--;
	    			 else{ 
					    goto pre_item;
					 }
				}
				if(key==lup){ //�����ϼ� : -10 �� 
	    		     LCD_CLR();
		    		 LCD_Init();
					 ReadSDFile(file_buf,-10,buf,1); //ƫ�Ƶ���10��
					 CharToStruct(buf);
					 page = 0;
					 key = 0;
				}
				if(key==down){ //�¼� �� ҳ���
					LCD_CLR();
		    		LCD_Init();
					if(page<5) page++;
	  				else{
						goto next_item;
					}
				}
				if(key==ldown){ //�����¼� �� ҳ���10����
					LCD_CLR();
		    		LCD_Init();
					page = 0;
					key = 0;
	 				ReadSDFile(file_buf,10,buf,1); //ƫ�Ƶ���10��
					CharToStruct(buf);
				}
				//�Ҽ��̰�  ����
				if(key == right) {
				    LCD_CLR();
		    		LCD_Init();
					goto label_recheck;	   
				}
				if(page == 0 ){
					LCD_const_disp(4,1,"ID:             ");
					LCD_const_disp(4,3,Result.IndexChar);
				}

    			delayms(30); 
		 }//end while
		   
	}
	else { //δ�ҵ���δȷ���ļ�
		 //��������ļ���ֱ���·�С�� 200001.xls
		 //�����ֹ�ȷ�ϵķ�ʽ
	}

}
void GUI_welcome(void){
    LCD_CLR(); //����
	LCD_const_disp(2,3,"��ӭʹ��");
	LCD_const_disp(3,1,"������ǿ�ȼ����");
	delayms(800);
	beep(0,1);
	
}

////////////////////////////////////
//  ��������
//   ��ds1302�л����ʱ������ת�����ṹ����
////////////////////////////////////
void dateRefresh(unsigned char readhardware)
{	//readhardware = 0 not refresh, =1 refresh

 if( readhardware!=88 )	ds1302_read_time();
	t.tm_sec=(((time_buf[6]&0x70)>>4)*10)+(time_buf[6]&0x0f);
	t.tm_min=  (((time_buf[5]&0x70)>>4)*10)+(time_buf[5]&0x0f);
	t.tm_hour=  (((time_buf[4]&0x70)>>4)*10)+(time_buf[4]&0x0f);
	t.tm_mday=	(((time_buf[3]&0x70)>>4)*10)+(time_buf[3]&0x0f);
	t.tm_mon= (((time_buf[2]&0x70)>>4)*10)+(time_buf[2]&0x0f);
	t.tm_wday=	(time_buf[7]&0x0f);
    t.tm_year=	(((time_buf[1]&0x70)>>4)*10)+(time_buf[1]&0x0f);
	if(readhardware != 0){
	Result.Date[0]='2';
	Result.Date[1]='0';
	Result.Date[2]=t.tm_year/10+'0';
	Result.Date[3]=t.tm_year%10+'0';
	Result.Date[4]=t.tm_mon/10+'0';
	Result.Date[5]=t.tm_mon%10+'0';
	Result.Date[6]=t.tm_mday/10+'0';
	Result.Date[7]=t.tm_mday%10+'0';
    Result.Date[8]='\0';

	Result.Time[0]=t.tm_hour/10+'0';
	Result.Time[1]=t.tm_hour%10+'0';
	Result.Time[2]=':';
	//Result.Time[3]=' ';
	Result.Time[3]=t.tm_min/10+'0';
	Result.Time[4]=t.tm_min%10+'0';
	Result.Time[5]=':';
	//Result.Time[7]=' ';
	Result.Time[6]=t.tm_sec/10+'0';
	Result.Time[7]=t.tm_sec%10+'0';
	Result.Time[8]='\0'; 
	}
    config.now =t.tm_hour*3600 + t.tm_min*60 + t.tm_sec; //����ϵͳ����
	
}