/*******************************
 function ����ʱ����
Clock F  :7.3728M 
Software : ICCAVR7.14C
********************************/
/*---------------------------------------------------------------------------------
     ��ʱ������㷽��
     ��������j = ��ʱʱ��/6*����Ƶ�� - 1
---------------------------------------------------------------------------------*/
void delayus(unsigned int tttt)   // 1.2us ��ʱ�Ӻ���   
{ 
   do
   {
       tttt--;
   }
   while(tttt>1);
}
void delayms(unsigned int i)                 //1ms��ʱ
   {
    while(i--)
    {                          
	    unsigned int j;                
        for(j=1;j<=1227;j++)   
			   ;               
    }                       
   }