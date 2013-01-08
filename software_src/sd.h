#ifndef __SD_H_
#define __SD_H_

#include "config.h"

#define SD_DDR  DDRB
#define SD_PORT PORTB
#define SD_PIN	 PINB

#define SD_CS  0

#define SD_CS_EN()  SD_PORT &= ~(1<<SD_CS) 
#define SD_CS_DIS() SD_PORT |=  (1<<SD_CS)
#define SD_DET() !((PINE>>5)&0X01)

#define DELAY_TIME 100 //SD���ĸ�λ���ʼ��ʱSPI����ʱ����������ʵ�������޸���ֵ����������SD����λ���ʼ��ʧ��
#define TRY_TIME 20    //��SD��д������֮�󣬶�ȡSD���Ļ�Ӧ����������TRY_TIME�Σ������TRY_TIME���ж�������Ӧ��������ʱ��������д��ʧ��
#define SD_TURE 0

/* SD�����Ͷ��� 
#define SD_TYPE_MMC     0
#define SD_TYPE_V1      1
#define SD_TYPE_V2      2
#define SD_TYPE_V2HC    4
*/

//�����붨��
//-------------------------------------------------------------
#define INIT_CMD0_ERROR     0x01 //CMD0����
#define INIT_CMD1_ERROR     0x02 //CMD1����
#define WRITE_BLOCK_ERROR   0x03 //д�����
#define READ_BLOCK_ERROR    0x04 //�������
//-------------------------------------------------------------

//SD��ָ���
/*------------------------------------------------------------
#define CMD0    0       //����λ
#define CMD9    9       //����9 ����CSD����
#define CMD10   10      //����10����CID����
#define CMD12   12      //����12��ֹͣ���ݴ���
#define CMD16   16      //����16������SectorSize Ӧ����0x00
#define CMD17   17      //����17����sector
#define CMD18   18      //����18����Multi sector
#define ACMD23  23      //����23�����ö�sectorд��ǰԤ�Ȳ���N��block
#define CMD24   24      //����24��дsector
#define CMD25   25      //����25��дMulti sector
#define ACMD41  41      //����41��Ӧ����0x00
#define CMD55   55      //����55��Ӧ����0x01
#define CMD58   58      //����58����OCR��Ϣ
#define CMD59   59      //����59��ʹ��/��ֹCRC��Ӧ����0x00
//-------------------------------------------------------------
*/


//SD��������
//-------------------------------------------------------------
UINT8 SD_Init(void);//SD��ʼ��	
UINT8 SD_Write_cmd(UINT8 *p);//SD��д����
UINT16 SD_Write_Sector(UINT32 addr, UINT8 *buffer);//SD��д����
UINT16 SD_Read_Sector(UINT32 addr,UINT8 *buffer); //SD��������
//-------------------------------------------------------------
UINT16 SD_Read_Sector_ndata(UINT32 addr,UINT8 *buffer,UINT16 offset,UINT16 len);//�������������

#endif
