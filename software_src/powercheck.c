#include "config.h"
/*��������ʼ��
*���ö˿�
*��ʼ���ر�
*/
void power_check_init(void){
	
		POWER_DDR_SET();
		config.is_lowpower = 0;
}	

/*�̵�������
*���� �� �¶�
*���� �� ��ǰ�̵���״̬
*
*/
void power_state_refresh(void)
{
 	 //���״̬ˢ�� ˢ�����ݣ�PINE_4û��ߵ�ƽ �е�͵�ƽ
    //
	config.is_lowpower = POWER_PIN_READ();

	if(config.is_lowpower) {
	    LED_ON();
	}
	else {
	    LED_OFF();
	}
	return ;
}