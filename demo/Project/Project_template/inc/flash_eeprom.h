/******************** (C) COPYRIGHT  风驰iCreate嵌入式开发工作室 **************
 * 文件名  ：flash_eeprom.c
 * 描述    ：Flash内部Data ROM读写实验   
 * 实验平台：风驰STM8开发板
 * 库版本  ：V2.1.0
 * 作者    ：风驰  QQ：779814207
 * 博客    ：
 * 淘宝    ：http://shop71177993.taobao.com/
 * 修改时间 ：2012-12-10
*******************************************************************************/
#ifndef __FLASH_EEPROM_H
#define __FLASH_EEPROM_H

/* 包含系统头文件 */

/* 包含自定义头文件 */
#include "stm8s.h"
#include "stm8s_flash.h"

/* 自定义新类型 */
typedef struct _MENU_DATA_
{
  uint8_t  language;					//语言选择
  uint16_t allopen;						//全开
  uint16_t allclose;					//全关
  uint16_t out4ma;						//输出4mA校准
  uint16_t out20ma;						//输出20mA校准
  uint8_t  deadzone;					//死区
  uint8_t  errtype;						//信号故障类型
  uint16_t errplace;					//信号故障位置
  uint8_t  powerofftype;				//断电动作类型
  uint16_t poweroffplace;				//断电故障位置
  uint8_t  rlstatus;					//远方就地状态
  uint8_t  startoption;				//开机选项
  uint8_t  logic;						//正反作用
  uint8_t  maxspeed;					//最大速度
  uint8_t  minspeed;					//最小速度
  uint8_t  esdtype;						//ESD类型
  uint8_t  esdplace;					//ESD定位
  uint8_t  alarm1;						//报警信号1
  uint8_t  alarm2;						//报警信号2
  uint8_t  alarm3;						//报警信号3  
  uint8_t  alarm4;						//报警信号4  
  uint8_t  alarm5;						//报警信号5  
  uint8_t  alarm6;						//报警信号6 
  uint8_t  alarmplace;					//报警定位
  uint8_t  signaltype;					//信号类型
  uint16_t addr;						//设备地址
}MenuDataStr;
typedef struct _FACTORY_DATA_
{
  uint8_t  password[3];				//密码设置
  uint8_t  slowrange;					//减速范围
  uint8_t  moment;						//力矩校准
  uint8_t  momentunits;				//力矩单位
  uint8_t  openmoment;					//开力矩
  uint8_t  closemoment;				//关力矩
  uint8_t  overmoment1;				//过力矩系数1
  uint8_t  overmoment2;				//过力矩系数2
  uint16_t in4ma;						//输入4ma校准
  uint16_t in20ma;						//输入20ma校准
  uint8_t  *number;						//产品编号地址
  uint8_t  factor;						//系数
  uint8_t  overdelay;					//过力矩延时

}FactoryDataStr;
typedef enum{
  
  #if defined (STM8S208) || defined(STM8S207) || defined(STM8S007) \
      || defined (STM8AF52Ax) || defined (STM8AF62Ax)
  Block_0,
  Block_1,
  Block_2,
  Block_3,
  Block_4,
  Block_5,
  Block_6,
  Block_7,
  Block_8,
  Block_9,
  Block_10,
  Block_11,
  Block_12,
  Block_13,
  Block_14,
  Block_15
  #endif /* STM8S208, STM8S207, STM8S007, STM8AF52Ax, STM8AF62Ax */
  #if defined(STM8S105) || defined(STM8S005) || defined(STM8AF626x)
  Block_0,
  Block_1,
  Block_2,
  Block_3,
  Block_4,
  Block_5,
  Block_6,
  Block_7 
  #endif /* STM8S105 or STM8AF626x */
  #if defined(STM8S103) || defined(STM8S003) ||  defined(STM8S903)
  Block_0,
  Block_1,
  Block_2,
  Block_3,
  Block_4,
  Block_5,
  Block_6,
  Block_7,
  Block_8,
  Block_9
  #endif /* STM8S103, STM8S903 */
  
}BlockStartAddress_TypeDef;
/* 自定义宏 */

/* 全局变量定义 */

void WriteMultiBlockByte(BlockStartAddress_TypeDef BlockStartAddress,FLASH_MemType_TypeDef FLASH_MemType, 
                FLASH_ProgramMode_TypeDef FLASH_ProgMode, uint8_t *Buffer,uint8_t BlockNum);
void ReadMultiBlockByte(BlockStartAddress_TypeDef BlockStartAddress,uint8_t BlockNum,
                        uint8_t ReadBlockByte[]);

#endif

/******************* (C) COPYRIGHT 风驰iCreate嵌入式开发工作室 *****END OF FILE****/