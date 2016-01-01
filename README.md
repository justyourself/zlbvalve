# zlbvalve
stm8s207 cpu  M series valve
1.更好的显示英文菜单,可将结构体调整
typedef struct _MENUITEM_
{
	uint8_t MenuCount;							//结构体数组的元素个数(菜单个数)
	uint8_t *DisplayString1;					//第一种菜单显示信息
	uint8_t *DisplayString2;					//第二种菜单显示信息
	uint8_t *Status;							//状态栏显示状态信息
	void (*Display)();							//显示函数的指针
	void (*Fun)();								//执行函数的指针
	struct _MENUITEM_ *Childrenms;			    //指向子节点的指针
	struct _MENUITEM_ *Parentms;			    //指向父节点的指针
}MenuItem;
修改为:
typedef struct _MENUITEM_
{
	uint8_t MenuCount;							//结构体数组的元素个数(菜单个数)
	uint8_t *DisplayString;						//第一种菜单显示信息
	uint8_t *Status;							//状态栏显示状态信息
	void (*Display)();							//显示函数的指针
	void (*Fun)();								//执行函数的指针
	struct _MENUITEM_ *Childrenms;			    //指向子节点的指针
	struct _MENUITEM_ *Parentms;			    //指向父节点的指针
}MenuItem;
这里DisplayString可以采用赋地址的形式；
例如：
MenuItem Level1_Fun[3] = 
{
	{3,"基本设置","Basi_set","A00",Display_Level1,NULL,Basic_Fun,TopMenu},
	{3,"高级设置","Adv_set","A01",Display_Level1,NULL,Advanced_Fun,TopMenu},
	{3,"出厂设置","Fact_set","A02",Display_Level1,NULL,Factory_Fun,TopMenu},
};
可以修改为:
MenuItem Level1_Fun[3] = 
{
	{3,Level1_Chinese[0],"A00",Display_Level1,NULL,Basic_Fun,TopMenu},
	{3,Level1_Chinese[1],"A01",Display_Level1,NULL,Advanced_Fun,TopMenu},
	{3,Level1_Chinese[2],"A02",Display_Level1,NULL,Factory_Fun,TopMenu},
};
uint8_t *const Level1_Chinese[] =
{
	"基本设置",
	"高级设置",
	"出厂设置",
};
uint8_t *const Level1_English[] =
{
	"Basi_set",
	"Adv_set",
	"Fact_set",
};