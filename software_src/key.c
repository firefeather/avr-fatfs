#include "config.h"
//����ɨ�躯��
unsigned char kbscan(void)
  {
   unsigned char key;
   unsigned long temp=0;
   DDR_SET;
   
   if((KEY_PIN) != KEY_MASK)         //���A�ڰ������ŵ�ƽ�����ȫ�Ǹߵ�ƽ���˳�
    {
     delayms(20);           //����
     if((KEY_PIN) != KEY_MASK )      //�ٴμ��A�ڵ�ƽ�������ȫ�Ǹߵ�ƽ�����ִ�г���
      {
       key = KEY_PIN ;          //��ȡPINA����������key��
        while((KEY_PIN) != KEY_MASK)
		{
		 temp++ ;
		 if(temp>LONGKEY) {  
		     delayms(30);
			 return key+0x80;  
		 };
		}
		; //��ǰ�а������ڰ���״̬���ٰ���������ʱ����ά�ֵ�ǰ״̬ 
      	
		return key;
	  
	  }
    }
	else return NO_KEY;
	
	return NO_KEY;
	}	



/*
unsigned char kbscan(void)
{
   unsigned  int i=0;
   unsigned char tmp;
   unsigned char ReadData=KEY_PIN ^ 0XFF; //0  1 0   1
  Try = ReadData & ( ReadData ^ Cont );   //0 1 0   0
  Cont = ReadData; 	 		  		 	  //0 1	0   1
 return Cont;

 
     
      char key_in; 
      char key_return = NO_KEY,key_temp= NO_KEY;
      unsigned int holdtime=0;
	  unsigned char i;
	DDR_SET;
	key_in=KEY_PIN & KEY_MASK;
	key_in=KEY_PIN & KEY_MASK;
	//
	if(key_in!=KEY_MASK)
		 {	
		 	delayms(30); 
			key_in=KEY_PIN & KEY_MASK;
			if(key_in!=KEY_MASK) 
				{   RELAY_ON();delayms(5); RELAY_OFF();delayms(5);
				  	do { 
					    key_return = key_temp>>3;
					    delayms(1);
						key_temp=KEY_PIN & KEY_MASK	;					 				 
						holdtime++;
					}while( key_temp !=KEY_MASK )	;
					
					if ( holdtime>LOMGKEY ) holdtime=10;
					else holdtime=0;
					 
					for(i=0;i<5;i++)
					{
					key_return=key_return>>i;
					if( !(key_return & 0x01) ){
						return i+holdtime;
					 }
					
					}
					return NO_KEY;
								 			
			}
		 }
	
	 			   
            
 
}
*/