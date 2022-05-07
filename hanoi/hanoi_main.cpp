#include "cmd_console_tools.h"
#include "hanoi.h"

/* ----------------------------------------------------------------------------------

     本文件功能：
	1、放main函数
	2、初始化屏幕
	3、调用菜单函数（hanoi_menu.cpp中）并返回选项
	4、根据选项调用菜单各项对应的执行函数（hanoi_multiple_solutions.cpp中）

     本文件要求：
	1、不允许定义全局变量（含外部全局和静态全局，const及#define不在限制范围内）
	2、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	3、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	/* demo中首先执行此句，将cmd窗口设置为40行x120列（缓冲区宽度120列，行数9000行，即cmd窗口右侧带有垂直滚动杆）*/
	cct_setconsoleborder(120, 40, 120, 9000);

	int mod;	// 选择的运行模式
	while (1) {
		mod = menu();

		switch (mod) {
			case 1:
				mode1();
				break;
			case 2:
				mode2();
				break;
			case 3:
				mode3();
				break;
			case 4:
				mode4();
				break;
			case 5:
				mode5();
				break;
			case 6:
				mode6();
				break;
			case 7:
				mode7();
				break;
			case 8:
				mode8();
				break;
			case 9:
				mode9();
				break;
			case 0:
				mode0();
				break;
			default:
				break;
		}
		cct_cls();
	}


	return 0;
}

