#include "config.h"
/*��������ʼ��
*���ö˿�
*��ʼ���ر�
*/
void power_check_init(void){
	
		POWER_DDR_SET()  ;
		config.is_lowpower = 0;
		return ;
}	

/*�̵�������
*���� �� �¶�
*���� �� ��ǰ�̵���״̬
*
*/
void power_state_refresh(void)
{
 	 //����û��ߵ�ƽ �е�͵�ƽ
    config.is_lowpower = POWER_PIN_READ();
	config.is_lowpower = POWER_PIN_READ();
	if(config.is_lowpower) {
	    LED_ON();
	}
	else {
	    LED_OFF();
	}
	return ;
}