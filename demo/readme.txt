
����С�ܵ�һ����ĩ��Ŭ�������ڷ���STM8S���ܿ��̵�ԭ���ˡ�����STM8S�Ŀ��̣���Ҫ�ѳ������RAM�����С�������������ûѧ�����ģ�Ҳ���˽������ԭ��ģ�ֻ֪����C����дд��������ѡ��е�������ͷ�ԡ���ô����ó�����RAM�������أ�
���ǿ���STM8S�Ŀ⺯������֪���ˡ������ǿ⺯���Ĵ��롣

IN_RAM(void FLASH_EraseBlock(uint16_t BlockNum, FLASH_MemType_TypeDef FLASH_MemType));

�Ҹտ�ʼ�ͱ�������������ƭ�ˡ���Ϊ����IN_RAM( )���Ϳ�����RAM�������ˡ����ǿ��� IN_RAM() �Ķ���
  #define IN_RAM(a)  a
��Ĭ������£���ʲô��û�ɡ���ϸһ�£���Ĭ������£��ǲ��⺯������RAM�����г���Ĺ��ܸ������ˡ�

/* Uncomment the line below to enable the FLASH functions execution from RAM */
#if !defined (RAM_EXECUTION)
/*#define RAM_EXECUTION  (1) */
#endif /* RAM_EXECUTION */


ȡ�������ע�;Ϳ����ˡ��������

/* Uncomment the line below to enable the FLASH functions execution from RAM */
#if !defined (RAM_EXECUTION)
   #define RAM_EXECUTION  (1) 
#endif /* RAM_EXECUTION */


����IN_RAM�����Ķ���ͱ����
  #define IN_RAM(a)   __ramfunc  a

��ȥ���Գ��򡣾ͺ��ˡ�

�Լ�д������ʵ�����ں���ǰ�����  __ramfunc  


�������Ҳ��Գɹ��ĳ���


uint8_t  block_buff[128];

__ramfunc  void  WriteBlock(void)
{
  uint8_t i;

    FLASH_Unlock(FLASH_MEMTYPE_DATA); 
    FLASH->CR2 |= FLASH_CR2_PRG;
    FLASH->NCR2 &= (uint8_t)(~FLASH_NCR2_NPRG);

  for(i=0; i<128; i++)
  {
    *((PointerAttr uint8_t*) (MemoryAddressCast)0x4000 + i) = block_buff[i];
  }

   FLASH_Lock(FLASH_MEMTYPE_DATA);
}


ף��������̵������Ǻ��ˣ���������


   
