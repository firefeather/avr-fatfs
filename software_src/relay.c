#include "config.h"
/*�̵�����ʼ��
*���ö˿�
*��ʼ���ر�
*/
void relay_init(void){
	
		RELAY_DDR_SET() ;
		RELAY_OFF();
		//state.Relay = 0;
	}	

/*�̵�������
*���� �� �¶�
*���� �� ��ǰ�̵���״̬
*
*/
unsigned char  relay(int temp)
{
	if(temp<HEAT_THRESHOLD)
	{
	 		RELAY_DDR_SET();
			RELAY_ON();
			//state.Relay = 1 ;
	}
	else
	{
	 	RELAY_DDR_SET();
		RELAY_OFF();
		//state.Relay = 0 ;
	}		
	//return state.Relay;
	return 0;
}