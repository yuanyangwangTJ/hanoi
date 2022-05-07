#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include "cmd_console_tools.h"

using namespace std;

#define SLEEP 100
const int offset = 17;

void get_input(int input[], int);

// 特殊宏定义，解决无法使用指针的问题
#define READ_INPUT		\
	get_input(input, mod);	\
	n = input[0];			\
	src = input[1];			\
	tmp = input[2];			\
	dst = input[3]	

/* ----------------------------------------------------------------------------------

     本文件功能：
	1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

     本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

// 定义全局变量
int t[3][10] = { 0 };
int top[3] = { 0 }, cnt = 0, delay;

// 结束一次的暂停
void pause()
{
    cct_setcolor();
    cct_setcursor(CURSOR_VISIBLE_NORMAL);
    cout << endl << "按回车键继续";
    while (_getch() != '\r')
        ;
    return;
}

// 根据不同的模式获取输入
void get_input(int input[], int mod)
{
    int n;
    char src, dst, tmp;

    while (1) {
        cout << "请输入汉诺塔的层数(1-10)" << endl;
        if (cin >> n && n >= 1 && n <= 10) {
            while (cin.get() != '\n')
                ;
            break;
        }
        else {
            cin.clear();
            while (cin.get() != '\n')
                ;
        }
    }
    while (1) {
        cout << "请输入起始柱(A-C)" << endl;
        if (cin >> src && ((src >= 'A' && src <= 'C') || (src >= 'a' && src <= 'c'))) {
            src = src > 'Z' ? src - 32 : src;
            while (cin.get() != '\n')
                ;
            break;
        }
        else {
            cin.clear();
            while (cin.get() != '\n')
                ;
        }
    }
    while (1) {
        cout << "请输入目标柱(A-C)" << endl;
        if (cin >> dst && ((dst >= 'A' && dst <= 'C') || (dst >= 'a' && dst <= 'c'))) {
            dst = dst > 'Z' ? dst - 32 : dst;
            while (cin.get() != '\n')
                ;

            if (src == dst) {
                cout << "目标柱(" << dst << ")" << "不能与起始柱(" << src << ")相同" << endl;
                continue;
            }
            break;
        }
        else {
            cin.clear();
            while (cin.get() != '\n')
                ;
        }
    }

    if (src != 'A' && dst != 'A')
        tmp = 'A';
    else if (src != 'B' && dst != 'B')
        tmp = 'B';
    else if (src != 'C' && dst != 'C')
        tmp = 'C';

    // 初始化数组
    cnt = 0;
    for (int i = 0; i < 3; i++) {
        top[i] = 0;
    }
    for (int i = 0; i < n; i++)
        t[src - 'A'][i] = n - i;
    top[src - 'A'] = n;


    if (mod == 4 || mod == 8) {
		cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)" << endl;
		while (1) {
			if (cin >> delay && delay >= 0 && delay <= 5) {
				while (cin.get() != '\n')
					;
				break;
			}
			else {
				cin.clear();
				while (cin.get() != '\n')
					;
			}
		}
    }
    else {
        // 无延时
        delay = 5;
    }


    // 将输入的值通过数组返回
    input[0] = n;
    input[1] = src;
    input[2] = tmp;
    input[3] = dst;

    return;
}

void print_by_mode(int n, char src, char dst, int mod);
void update_tower(char src, char dst);

// hanoi
void hanoi(int n, char src, char tmp, char dst, int mod)
{
    if (n) {
        hanoi(n - 1, src, dst, tmp, mod);
        cnt++;
        update_tower(src, dst);
        print_by_mode(n, src, dst, mod);
        hanoi(n - 1, tmp, src, dst, mod);
    }
    return;
}

// 更新数组
void update_tower(char src, char dst)
{
    t[dst - 'A'][top[dst - 'A']++] = t[src - 'A'][--top[src - 'A']];
    return;
}

// 打印横向汉诺塔
void print_tower_horizon()
{
    for (int u = 0; u < 3; u++) {
        cout << char(u + 'A') << ":";
        for (int i = 0; i < 10; i++) {
            if (i < top[u])
                cout << setw(2) << t[u][i];
            else
                cout << "  ";
        }
    }
    return;
}

// 打印竖向汉诺塔，flag表示是否为第一次打印
void print_tower_vertical(int n, char src, char dst, int dy, int flag = 0)
{
    cct_setcolor();
    // 进行初始打印
    if (flag) {
        for (int u = 9; u >= 0; u--) {
            if (u + 1 <= n) {
                for (int i = 0; i <= src - 'A'; i++)
                    cout << "          ";
                cout << setw(2) << n - u << endl;
            }
            else
                cout << endl;
        }
        cout << "         =========================" << endl;
        cout << "           A         B         C" << endl;
        cct_gotoxy(0, offset + dy);
        cout << "初始：";
        print_tower_horizon();
    }
    else {
        // 进行非首次打印
        cct_gotoxy((src - 'A' + 1) * 10, dy + 11 - top[src - 'A']);
        cout << "  ";
        cct_gotoxy((dst - 'A' + 1) * 10, dy + 12 - top[dst - 'A']);
        cout << setw(2) << t[dst - 'A'][top[dst - 'A'] - 1];
        cct_gotoxy(0, offset + dy);
        cout << "第" << setw(4) << cnt << " 步(" << n << "#: " << src << "-->" << dst << ")  ";
        print_tower_horizon();
    }

    return;
}

// 打印汉诺塔柱子
void draw_tower_post()
{
    // 将光标隐藏
    cct_setcursor(CURSOR_INVISIBLE);
    for (int i = 0; i < 3; i++) {
        cct_showstr(i * 32 + 1, 15, NULL, COLOR_HYELLOW, COLOR_BLACK, 1, 23);
        Sleep(100);
    }
    for (int i = 11; i >= 0; i--) {
        for (int j = 0; j < 3; j++) {
            cct_showch(j * 32 + 12, i + 3, ' ', COLOR_HYELLOW, COLOR_BLACK);
            Sleep(50);
        }
    }
    return;
}

// 打印汉诺塔
void draw_tower(int n, char src)
{
    for (int i = 0; i < n; i++) {
        cct_showstr((src - 'A') * 32 + 12 - n + i, 14 - i, NULL, n - i, COLOR_BLACK, 1, 2 * (n - i) + 1);
        Sleep(100);
    }
    return;
}

// 画出汉诺塔一块的移动
void draw_tower_move(char src, char dst)
{
    int layer = top[dst - 'A'];
    // 圆盘向上移动
    for (int i = 14 - top[src - 'A']; i > 1; i--)
    {
        cct_showstr(12 + 32 * (src - 'A') - layer, i, NULL, COLOR_BLACK, COLOR_BLACK, 1, 2 * layer + 1);
        if (i > 2)
            cct_showch(12 + 32 * (src - 'A'), i, ' ', COLOR_HYELLOW, COLOR_BLACK, 1);
        cct_showstr(12 + 32 * (src - 'A') - layer, i - 1, NULL, layer, COLOR_BLACK, 1, 2 * layer + 1);

        // 根据延迟进行休眠
		if (delay == 0)
			Sleep(100);
		else
			Sleep(SLEEP * (5 - delay));
    }

    // 
    for (int i = 12 + 32 * (src - 'A'); i != 12 + 32 * (dst - 'A'); src > dst ? i-- : i++)
    {
        cct_showch(i + (src > dst ? layer : -layer), 1, ' ', COLOR_BLACK, COLOR_BLACK, 1);
        cct_showch(i + (src > dst ? -layer - 1 : layer + 1), 1, ' ', layer, COLOR_BLACK, 1);

        // 根据延迟进行休眠
		if (delay == 0)
			Sleep(100);
		else
			Sleep(SLEEP * (5 - delay));
    }

    for (int i = 1; i <= 14 - top[dst - 'A']; i++)
    {
        cct_showstr(12 + 32 * (dst - 'A') - layer, i, NULL, COLOR_BLACK, COLOR_BLACK, 1, 2 * layer + 1);
        if (i > 2)
            cct_showch(12 + 32 * (dst - 'A'), i, ' ', COLOR_HYELLOW, COLOR_BLACK, 1);
        cct_showstr(12 + 32 * (dst - 'A') - layer, i + 1, NULL, layer, COLOR_BLACK, 1, 2 * layer + 1);

        // 根据延迟进行休眠
		if (delay == 0)
			Sleep(100);
		else
			Sleep(SLEEP * (5 - delay));
    }

    return;
}

// 根据模式进行相应的输出
void print_by_mode(int n, char src, char dst, int mod)
{
    // 输出前半部分
    if (mod == 2 || mod == 3) {
        cout << "第" << setw(4) << cnt << " 步( ";
    }
    if (mod == 1 || mod == 2 || mod == 3)
        cout << n << "# " << src << "-->" << dst;

    // 根据情形进行休眠操作
    if (delay) {
        if (mod >= 4)
            Sleep(SLEEP * (5 - delay));
    }
    else {
        while (_getch() != '\r')
            ;
    }

    // 输出后半部分
    if (mod == 2 || mod == 3)
        cout << ")";
    if (mod == 3) {
        cout << " ";
        print_tower_horizon();
    }
    if (mod == 4)
        print_tower_vertical(n, src, dst, 0);

    if (mod == 8) {
        cct_setcolor();
        print_tower_vertical(n, src, dst, 15);
        draw_tower_move(src, dst);
        
    }

    cout << endl;

}

void wait_for_next()
{
    if (delay)
        Sleep(SLEEP * (5 - delay));
    else
        while (_getch() != '\r')
            ;
}


// 根据模式进行操作
void mode1()
{
    // 汉诺塔的相关变量
    int n;
    char src, dst, tmp;
	int input[4];		// 无法使用指针，曲线救国获取输入
    int mod = 1;
    READ_INPUT;
    hanoi(n, src, tmp, dst, mod);
    pause();
}

void mode2()
{
    // 汉诺塔的相关变量
    int n;
    char src, dst, tmp;
    int input[4];		// 无法使用指针，曲线救国获取输入
    int mod = 2;
    READ_INPUT;
    hanoi(n, src, tmp, dst, mod);
    pause();
}

void mode3()
{
    // 汉诺塔的相关变量
    int n;
    char src, dst, tmp;
    int input[4];		// 无法使用指针，曲线救国获取输入
    int mod = 3;
    READ_INPUT;
    hanoi(n, src, tmp, dst, mod);
    pause();

}
void mode4()
{
    // 汉诺塔的相关变量
    int n;
    char src, dst, tmp;
    int input[4];		// 无法使用指针，曲线救国获取输入
    int mod = 4;
    READ_INPUT;
    cct_cls();
    cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层，延时设置为 " << delay << endl << endl;
    print_tower_vertical(n, src, dst, 0, 1);
    hanoi(n, src, tmp, dst, mod);
    cct_gotoxy(0, 32);
    pause();
}

void mode5()
{
    cct_cls();
    draw_tower_post();
    cct_gotoxy(0, 32);
    pause();
}

void mode6() 
{
    // 汉诺塔的相关变量
    int n;
    char src, dst, tmp;
    int input[4];		// 无法使用指针，曲线救国获取输入
    int mod = 6;
    READ_INPUT;
    cct_cls();
    cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层 " << endl;
    draw_tower_post();
    draw_tower(n, src);
    cct_gotoxy(0, 32);
    pause();
}

void mode7()
{
    // 汉诺塔的相关变量
    int n;
    char src, dst, tmp;
    int input[4];		// 无法使用指针，曲线救国获取输入
    int mod = 7;
    READ_INPUT;
    delay = 0;
    cct_cls();
    cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层 " << endl;
    draw_tower_post();
    draw_tower(n, src);
    // 只移动一块
    dst = n % 2 ? dst : tmp;
    // 手动刷新，模拟移动一次的场景
    update_tower(src, dst);
    Sleep(SLEEP);
    draw_tower_move(src, dst);
    cct_gotoxy(0, 32);
    pause();
}

void mode8()
{
    // 汉诺塔的相关变量
    int n;
    char src, dst, tmp;
    int input[4];		// 无法使用指针，曲线救国获取输入
    int mod = 8;
    READ_INPUT;
    //delay = 0;
    cct_cls();
    cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层 " << endl;
    draw_tower_post();
    draw_tower(n, src);
    // 打印汉诺塔竖形
    cct_gotoxy(0, offset);
    print_tower_vertical(n, src, dst, 0, 1);
    
    // 开始汉诺塔移动
    cct_setcolor();
    hanoi(n, src, tmp, dst, mod);

    // 结束
    cct_gotoxy(0, 32);
    pause();
}

void mode9()
{

}

void mode0()
{
    exit(0);
}
