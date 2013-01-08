//*****************************************************************************//
//*								�������
//*����оƬ��ATmgea128
//*����������AVR Studio+GCC
//*����ģ�飺SD������
//*�޸��ߣ�  ����
//*****************************************************************************//
#include "sd.h"

//****************************************************************
//*����ģ�飺SD������
//*�������ܣ�д6�ֽ�����
//****************************************************************
UINT8 SD_Write_cmd(UINT8 *p)
{	
	UINT16 temp,k=0;
	SD_CS_DIS();//��ֹSPI
	SPI_Read();//�ն�һ�ֽ�
	SD_CS_EN();//ʹ��SPI

	SPI_Write(p[0]);
	SPI_Write(p[1]);
	SPI_Write(p[2]);
	SPI_Write(p[3]);
	SPI_Write(p[4]);
	SPI_Write(p[5]);

	do 
 	{  
  		temp = SPI_Read();//һֱ����ֱ�������Ĳ���0xff��ʱ
 		k++;
 	}while((temp==0xff)&&(k<TRY_TIME)); 

	return temp;
}
//****************************************************************
//*����ģ�飺SD������
//*�������ܣ���ʼ��
//****************************************************************
UINT8 SD_Init(void)	
{  
	UINT8 time=0,temp=0;
	UINT8 pcmd[] = {0x40,0x00,0x00,0x00,0x00,0x95}; //����0���ֽ�����
	if(SD_DET()==0) return 0x02; //no disk
	SD_PORT |= (1<<SD_CS);
	SD_DDR |= (1<<SD_CS);

	SPI_IO_Init();
	SPI_Low();

	SD_CS_DIS();  //�ر�Ƭѡ 
	for(time=0;time<10;time++) //��ʼʱ������Ҫ��������74��ʱ���źţ����Ǳ���ģ�����
	{
  		SPI_Read(); 
	}
	SD_CS_EN(); //��Ƭѡ
	time = 0;
	do
	{ 
		temp=SD_Write_cmd(pcmd);//д��CMD0
	 	time++;
	 	if(time==TRY_TIME) 
	 	{ 
	  		SD_CS_DIS(); //�ر�Ƭѡ
	  		return(INIT_CMD0_ERROR);//CMD0д��ʧ��
	 	}
	 }while(temp!=0x01);

	SD_CS_DIS(); //�ر�Ƭѡ
	SPI_Read(); //����SD���Ĳ���ʱ�������ﲹ8��ʱ�� 
	SD_CS_EN(); //��Ƭѡ

	pcmd[0]=0x41,pcmd[5]=0xff;
	time = 0;
	do
	{ 
		temp=SD_Write_cmd(pcmd);
		time++;
		if(time==TRY_TIME) 
		{ 
		 	SD_CS_DIS(); //�ر�Ƭѡ
			 return(INIT_CMD1_ERROR);//CMD1д��ʧ��
		 }
	 }while(temp!=0);
  
	 SPI_High();  
	 SD_CS_DIS();  //�ر�Ƭѡ 
	 SPI_Read(); //����SD���Ĳ���ʱ�������ﲹ8��ʱ��
	 return SD_TURE; //����0,˵����ʼ�������ɹ�
} 
//****************************************************************
//*����ģ�飺SD������
//*�������ܣ�д512�ֽ����ݣ�һ�����ֽڣ�
//****************************************************************
UINT16 SD_Write_Sector(UINT32 addr,UINT8 *buffer)
{  
	UINT8 temp=0,time=0;
	UINT16 i=0;
	UINT8 pcmd[] = {0x58,0x00,0x00,0x00,0x00,0xff}; //��SD���е����飨512�ֽڣ�һ��������д�����ݣ���CMD24

	 addr<<=9; //�����ַ��������ַ��תΪ�ֽڵ�ַ �������������SD�����������Ϊ4G��

	 pcmd[1]=(addr>>24); //���ֽڵ�ַд�뵽CMD24�ֽ�������
	 pcmd[2]=(addr>>16);
	 pcmd[3]=(addr>>8);
	// pcmd[4]=offset;	
	 SD_CS_EN();//��SD��Ƭѡ

	 do
	 {  
		temp=SD_Write_cmd(pcmd);
  		time++;
  		if(time==TRY_TIME) 
  		{ 
   			SD_CS_DIS(); //�ر�Ƭѡ
   			return(temp); //����д��ʧ��
  		}
	}while(temp!=0); 

	for(i=0;i<100;i++) //����Ҫ��������ʱ���ź�
  		SPI_Read();
	
	SPI_Write(0xfe);//д�뿪ʼ�ֽ� 0xfe���������Ҫд���512���ֽڵ�����	
	
	for(i=0;i<512;i++) //����������Ҫд���512���ֽ�д��SD��
		SPI_Write(*buffer++);
  
	SPI_Read(); 
	SPI_Read(); //�����ֽڵ�CRCУ���룬���ù���
   
    
	temp=SPI_Read();   //��ȡ����ֵ
	if((temp&0x1F)!=0x05) //�������ֵ�� XXX00101˵�������Ѿ���SD��������
	{
 		SD_CS_DIS();
 		return(WRITE_BLOCK_ERROR); //д������ʧ��
	}
 
	while(SPI_Read()!=0xff);//�ȵ�SD����æ�����ݱ������Ժ�SD��Ҫ����Щ����д�뵽�����FLASH�У���Ҫһ��ʱ�䣩
						    //æʱ����������ֵΪ0x00,��æʱ��Ϊ0xff

	SD_CS_DIS(); //�ر�Ƭѡ

	SPI_Read();//����SD���Ĳ���ʱ�������ﲹ8��ʱ��
	return SD_TURE;		 //����0,˵��д���������ɹ�
} 
//****************************************************************
//*����ģ�飺SD������
//*�������ܣ���512�ֽ����ݣ�һ�����ֽڣ�
//****************************************************************
UINT16 SD_Read_Sector(UINT32 addr,UINT8 *buffer)//��SD����ָ�������ж���512���ֽڣ�ʹ��CMD17��17�����
{

	 UINT16 j=0;
	 UINT8 time=0,temp=0;
	 UINT8 pcmd[]={0x51,0x00,0x00,0x00,0x00,0xff}; //CMD17���ֽ�����

	 addr <<= 9; //�����ַ��������ַ��תΪ�ֽڵ�ַ

	 pcmd[1] = (addr>>24);//���ֽڵ�ַд�뵽CMD17�ֽ�������
	 pcmd[2] = (addr>>16);
	 pcmd[3] =(addr>>8);
	// pcmd[4] = offset;

	 SD_CS_EN();//��Ƭѡ 

	 do
	 {  
		  temp=SD_Write_cmd(pcmd); //д��CMD17
		  time++;
		  if(time==TRY_TIME) 
		  {
		   SD_CS_DIS();
		   return(READ_BLOCK_ERROR); //����ʧ��
		  }
	 }while(temp!=0); 
   			
	 while(SPI_Read()!= 0xfe); //һֱ����������0xfeʱ��˵���������512�ֽڵ�������
 		   	   	
	 for(j=0;j<512;j++)	 //������д�뵽���ݻ�������
	 {	
	    buffer[j]=SPI_Read();
	 }

	 SPI_Read();//��ȡ�����ֽڵ�CRCУ���룬���ù�������
	 SPI_Read();

	 SD_CS_DIS();  //SD���ر�Ƭѡ 

	 SPI_Read();//����SD���Ĳ���ʱ�������ﲹ8��ʱ��

	 return SD_TURE;
}
//****************************************************************
//*����ģ�飺SD������
//*�������ܣ�д���������ݣ��������ֽڣ�
//****************************************************************
UINT16 SD_Read_Sector_ndata(UINT32 addr,UINT8 *buffer,UINT16 offset,UINT16 len)//��SD����ָ�������ж���512���ֽڣ�ʹ��CMD17��17�����
{

	 UINT16 j=0;
	 UINT8 time=0,temp=0;
	 UINT8 pcmd[]={0x51,0x00,0x00,0x00,0x00,0xff}; //CMD17���ֽ�����

	 addr <<= 9; //�����ַ��������ַ��תΪ�ֽڵ�ַ

	 pcmd[1] = (addr>>24);//���ֽڵ�ַд�뵽CMD17�ֽ�������
	 pcmd[2] = (addr>>16);
	 pcmd[3] =(addr>>8);
	// pcmd[4] = offset;

	 SD_CS_EN();//��Ƭѡ 

	 do
	 {  
		  temp=SD_Write_cmd(pcmd); //д��CMD17
		  time++;
		  if(time==TRY_TIME) 
		  {
		   SD_CS_DIS();
		   return(READ_BLOCK_ERROR); //����ʧ��
		  }
	 }while(temp!=0); 
   			
	 while(SPI_Read()!= 0xfe); //һֱ����������0xfeʱ��˵���������512�ֽڵ�������
 		   	   	
	 for(j=0;j<offset;j++)	 //������д�뵽���ݻ�������
	    SPI_Read();
	 for(;j<offset+len;j++)	 
		buffer[j]=SPI_Read();
	 for(;j<512;j++)	 
		SPI_Read();

	 SPI_Read();//��ȡ�����ֽڵ�CRCУ���룬���ù�������
	 SPI_Read();

	 SD_CS_DIS();  //SD���ر�Ƭѡ 

	 SPI_Read();//����SD���Ĳ���ʱ�������ﲹ8��ʱ��

	 return SD_TURE;
}
