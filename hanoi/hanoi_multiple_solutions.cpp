#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include "cmd_console_tools.h"

using namespace std;

#define SLEEP 100
const int offset = 17;

void get_input(int input[], int);

// ����궨�壬����޷�ʹ��ָ�������
#define READ_INPUT		\
	get_input(input, mod);	\
	n = input[0];			\
	src = input[1];			\
	tmp = input[2];			\
	dst = input[3]	

/* ----------------------------------------------------------------------------------

     ���ļ����ܣ�
	1����ű� hanoi_main.cpp �и��ݲ˵�����ֵ���õĸ��˵����Ӧ��ִ�к���

     ���ļ�Ҫ��
	1�����������ⲿȫ�ֱ�����const��#define�������Ʒ�Χ�ڣ�
	2�������徲̬ȫ�ֱ�����������Ҫ��������Ҫ�����ĵ���ʾ��ȫ�ֱ�����ʹ��׼���ǣ����á����á��ܲ��þ������ã�
	3����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	4���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------------------------------------------------- */


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/

// ����ȫ�ֱ���
int t[3][10] = { 0 };
int top[3] = { 0 }, cnt = 0, delay;

// ����һ�ε���ͣ
void pause()
{
    cct_setcolor();
    cct_setcursor(CURSOR_VISIBLE_NORMAL);
    cout << endl << "���س�������";
    while (_getch() != '\r')
        ;
    return;
}

// ���ݲ�ͬ��ģʽ��ȡ����
void get_input(int input[], int mod)
{
    int n;
    char src, dst, tmp;

    while (1) {
        cout << "�����뺺ŵ���Ĳ���(1-10)" << endl;
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
        cout << "��������ʼ��(A-C)" << endl;
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
        cout << "������Ŀ����(A-C)" << endl;
        if (cin >> dst && ((dst >= 'A' && dst <= 'C') || (dst >= 'a' && dst <= 'c'))) {
            dst = dst > 'Z' ? dst - 32 : dst;
            while (cin.get() != '\n')
                ;

            if (src == dst) {
                cout << "Ŀ����(" << dst << ")" << "��������ʼ��(" << src << ")��ͬ" << endl;
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

    // ��ʼ������
    cnt = 0;
    for (int i = 0; i < 3; i++) {
        top[i] = 0;
    }
    for (int i = 0; i < n; i++)
        t[src - 'A'][i] = n - i;
    top[src - 'A'] = n;


    if (mod == 4 || mod == 8) {
		cout << "�������ƶ��ٶ�(0-5: 0-���س�������ʾ 1-��ʱ� 5-��ʱ���)" << endl;
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
        // ����ʱ
        delay = 5;
    }


    // �������ֵͨ�����鷵��
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

// ��������
void update_tower(char src, char dst)
{
    t[dst - 'A'][top[dst - 'A']++] = t[src - 'A'][--top[src - 'A']];
    return;
}

// ��ӡ����ŵ��
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

// ��ӡ����ŵ����flag��ʾ�Ƿ�Ϊ��һ�δ�ӡ
void print_tower_vertical(int n, char src, char dst, int dy, int flag = 0)
{
    cct_setcolor();
    // ���г�ʼ��ӡ
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
        cout << "��ʼ��";
        print_tower_horizon();
    }
    else {
        // ���з��״δ�ӡ
        cct_gotoxy((src - 'A' + 1) * 10, dy + 11 - top[src - 'A']);
        cout << "  ";
        cct_gotoxy((dst - 'A' + 1) * 10, dy + 12 - top[dst - 'A']);
        cout << setw(2) << t[dst - 'A'][top[dst - 'A'] - 1];
        cct_gotoxy(0, offset + dy);
        cout << "��" << setw(4) << cnt << " ��(" << n << "#: " << src << "-->" << dst << ")  ";
        print_tower_horizon();
    }

    return;
}

// ��ӡ��ŵ������
void draw_tower_post()
{
    // ���������
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

// ��ӡ��ŵ��
void draw_tower(int n, char src)
{
    for (int i = 0; i < n; i++) {
        cct_showstr((src - 'A') * 32 + 12 - n + i, 14 - i, NULL, n - i, COLOR_BLACK, 1, 2 * (n - i) + 1);
        Sleep(100);
    }
    return;
}

// ������ŵ��һ����ƶ�
void draw_tower_move(char src, char dst)
{
    // ��겻�ɼ�
    cct_setcursor(CURSOR_INVISIBLE);

    // ��Ҫ�ƶ���Բ�̱��(1-10)
    int num = t[dst - 'A'][top[dst - 'A'] - 1];
    // Բ�������ƶ�
    for (int i = 14 - top[src - 'A']; i > 1; i--)
    {
        cct_showstr(12 + 32 * (src - 'A') - num, i, NULL, COLOR_BLACK, COLOR_BLACK, 1, 2 * num + 1);
        if (i > 2)
            cct_showch(12 + 32 * (src - 'A'), i, ' ', COLOR_HYELLOW, COLOR_BLACK, 1);
        cct_showstr(12 + 32 * (src - 'A') - num, i - 1, NULL, num, COLOR_BLACK, 1, 2 * num + 1);

        // �����ӳٽ�������
		if (delay == 0)
			Sleep(100);
		else
			Sleep(SLEEP * (5 - delay));
    }

    // Բ�������ƶ�
    for (int i = 12 + 32 * (src - 'A'); i != 12 + 32 * (dst - 'A'); src > dst ? i-- : i++)
    {
        cct_showch(i + (src > dst ? num : -num), 1, ' ', COLOR_BLACK, COLOR_BLACK, 1);
        cct_showch(i + (src > dst ? -num - 1 : num + 1), 1, ' ', num, COLOR_BLACK, 1);

        // �����ӳٽ�������
		if (delay == 0)
			Sleep(100);
		else
			Sleep(SLEEP * (5 - delay));
    }

    // Բ�������ƶ�
    for (int i = 1; i <= 14 - top[dst - 'A']; i++)
    {
        cct_showstr(12 + 32 * (dst - 'A') - num, i, NULL, COLOR_BLACK, COLOR_BLACK, 1, 2 * num + 1);
        if (i > 2)
            cct_showch(12 + 32 * (dst - 'A'), i, ' ', COLOR_HYELLOW, COLOR_BLACK, 1);
        cct_showstr(12 + 32 * (dst - 'A') - num, i + 1, NULL, num, COLOR_BLACK, 1, 2 * num + 1);

        // �����ӳٽ�������
		if (delay == 0)
			Sleep(100);
		else
			Sleep(SLEEP * (5 - delay));
    }
    
    cct_setcursor(CURSOR_VISIBLE_NORMAL);

    return;
}

// ����ģʽ������Ӧ�����
void print_by_mode(int n, char src, char dst, int mod)
{
    // ���ǰ�벿��
    if (mod == 2 || mod == 3) {
        cout << "��" << setw(4) << cnt << " ��( ";
    }
    if (mod == 1 || mod == 2 || mod == 3)
        cout << n << "# " << src << "-->" << dst;

    // �������ν������߲���
    if (delay) {
        if (mod >= 4)
            Sleep(SLEEP * (5 - delay));
    }
    else {
        while (_getch() != '\r')
            ;
    }

    // �����벿��
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


// ����ģʽ���в���
void mode1()
{
    // ��ŵ������ر���
    int n;
    char src, dst, tmp;
	int input[4];		// �޷�ʹ��ָ�룬���߾ȹ���ȡ����
    int mod = 1;
    READ_INPUT;
    hanoi(n, src, tmp, dst, mod);
    pause();
}

void mode2()
{
    // ��ŵ������ر���
    int n;
    char src, dst, tmp;
    int input[4];		// �޷�ʹ��ָ�룬���߾ȹ���ȡ����
    int mod = 2;
    READ_INPUT;
    hanoi(n, src, tmp, dst, mod);
    pause();
}

void mode3()
{
    // ��ŵ������ر���
    int n;
    char src, dst, tmp;
    int input[4];		// �޷�ʹ��ָ�룬���߾ȹ���ȡ����
    int mod = 3;
    READ_INPUT;
    hanoi(n, src, tmp, dst, mod);
    pause();

}
void mode4()
{
    // ��ŵ������ر���
    int n;
    char src, dst, tmp;
    int input[4];		// �޷�ʹ��ָ�룬���߾ȹ���ȡ����
    int mod = 4;
    READ_INPUT;
    cct_cls();
    cout << "�� " << src << " �ƶ��� " << dst << "���� " << n << " �㣬��ʱ����Ϊ " << delay << endl << endl;
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
    // ��ŵ������ر���
    int n;
    char src, dst, tmp;
    int input[4];		// �޷�ʹ��ָ�룬���߾ȹ���ȡ����
    int mod = 6;
    READ_INPUT;
    cct_cls();
    cout << "�� " << src << " �ƶ��� " << dst << "���� " << n << " �� " << endl;
    draw_tower_post();
    draw_tower(n, src);
    cct_gotoxy(0, 32);
    pause();
}

void mode7()
{
    // ��ŵ������ر���
    int n;
    char src, dst, tmp;
    int input[4];		// �޷�ʹ��ָ�룬���߾ȹ���ȡ����
    int mod = 7;
    READ_INPUT;
    delay = 0;
    cct_cls();
    cout << "�� " << src << " �ƶ��� " << dst << "���� " << n << " �� " << endl;
    draw_tower_post();
    draw_tower(n, src);
    // ֻ�ƶ�һ��
    dst = n % 2 ? dst : tmp;
    // �ֶ�ˢ�£�ģ���ƶ�һ�εĳ���
    update_tower(src, dst);
    Sleep(SLEEP);
    draw_tower_move(src, dst);
    cct_gotoxy(0, 32);
    pause();
}

void mode8()
{
    // ��ŵ������ر���
    int n;
    char src, dst, tmp;
    int input[4];		// �޷�ʹ��ָ�룬���߾ȹ���ȡ����
    int mod = 8;
    READ_INPUT;
    //delay = 0;
    cct_cls();
    cout << "�� " << src << " �ƶ��� " << dst << "���� " << n << " �� " << endl;
    draw_tower_post();
    draw_tower(n, src);
    // ��ӡ��ŵ������
    cct_gotoxy(0, offset);
    print_tower_vertical(n, src, dst, 15, 1);
    
    // ��ʼ��ŵ���ƶ�
    cct_setcolor();
    hanoi(n, src, tmp, dst, mod);

    // ����
    cct_gotoxy(0, 32);
    pause();
}

// ��Ϸ����
bool game_over(char dst, int n)
{
    if (top[dst - 'A'] == n)
        return true;
    return false;
}

// ���ڿ���ʹ��ָ��
// ������Ϸ����ȡ��src��dst����Ϸ�˳�src='Q'
void game_run(char *begin, char *end)
{
    cct_gotoxy(0, 34);
    cct_setcursor(CURSOR_VISIBLE_NORMAL);
    cout << "�������ƶ�������(������ʽ��AC=A���˵������ƶ���C��Q=�˳�) ��";
    cout << "                 ";
    cct_gotoxy(60, 34);

    char src = 0, tmp, dst = 0;
    int cnt = 0;
    int game_errno = 0;
    /*
    * 0  ��ȷ
    * 1  ����ȴ���
    * 2  ����ѹС�̣��Ƿ��ƶ���
    * 3  Դ��Ϊ��
    */

    for (; ; cnt++) {

        // ����������ַ�
        if (cnt > 15) {
            // ����������ƺ�����
            src = dst = 0;
            game_errno = 0;
            cnt = 0;
            cct_gotoxy(60, 34);
            cout << "                      ";
            cct_gotoxy(60, 34);
        }


        tmp = _getche();
        if (!((tmp >= 'A' && tmp <= 'C') || (tmp >= 'a' && tmp <= 'c') || tmp == '\r' || tmp == 'q' || tmp == 'Q')) {
            game_errno = 1;     // �Ƿ��ַ��������
        }
        if (tmp >= 'a' && tmp <= 'z') {
            tmp -= 32;
        }

        // ������жϽ�����game_errnoΪ0��������
        if (game_errno == 0 && tmp >= 'A' && tmp <= 'Z') {
            if (dst != 0)
                game_errno = 1;     // ���볬�������ַ�������
            if (src == 0) {
                src = tmp;
                // ���ܳ���Ϊ Q ������
                if (src < 'A' && src > 'C')
                    game_errno = 1;
                // �ڴ��������ж�Դ���Ƿ�Ϊ��
                else if (src >= 'A' && src <= 'C' && top[src - 'A'] == 0 && game_errno == 0)
                    game_errno = 3;     // Դ��Ϊ��
            }
            else if (game_errno == 0) {
                dst = tmp;
                if (dst < 'A' || dst > 'C' || src == dst)
                    game_errno = 1; // �ַ��ظ����Ƿ�����

                if (dst >= 'A' && dst <= 'C' && src >= 'A' && src <= 'C') {
					// �ж��߼�����
					int top1, top2;
					top1 = top[src - 'A'];
					top2 = top[dst - 'A'];

					if (game_errno == 0 && top1 > 1 && top2 > 0 && t[dst - 'A'][top2 - 1] < t[src - 'A'][top1 - 1])
						game_errno = 2;     // ����ѹС�̣��Ƿ��ƶ��� 
                }

            }

        }

        if (tmp == '\r') {
            // ֻ��һ���س������δ���
            if (src == 0)
                game_errno = 1;

            if (game_errno) {
                cout << endl;
				if (game_errno == 2)
                    cout << "����ѹС�̣��Ƿ��ƶ���";
                if (game_errno == 3)
                    cout << "Դ��Ϊ�գ�";
                // �˳�
                if (game_errno == 1 && src == 'Q' && dst == 0) {
                    *begin = src;
                    break;
                }

                // ��ʱ����մ���
                if (game_errno != 1) {
                    Sleep(1000);
                    cct_gotoxy(0, 35);
                    cout << "                              ";
                }

                // ���¶�ȡ����
                game_errno = 0;
                src = dst = 0;
                cnt = 0;
                cct_gotoxy(60, 34);
                cout << "                 ";
                cct_gotoxy(60, 34);
                continue;
            }
            else {

                // �޴�������ѭ��
                *begin = src;
                *end = dst;
                break;
            }
        }
    }
}

void mode9()
{
    // ��ŵ������ر���
    int n;
    char src, dst, tmp;
    int input[4];		// �޷�ʹ��ָ�룬���߾ȹ���ȡ����
    int mod = 8;
    READ_INPUT;
    //delay = 0;
    cct_cls();
    cout << "�� " << src << " �ƶ��� " << dst << "���� " << n << " �� " << endl;
    draw_tower_post();
    draw_tower(n, src);
    // ��ӡ��ŵ������
    cct_gotoxy(0, offset);
    print_tower_vertical(n, src, dst, 15, 1);

	char begin = 0, end = 0;
    while (!game_over(dst, n)) {
        cct_setcolor();
        game_run(&begin, &end);
        if (begin == 'Q')
            break;
        update_tower(begin, end);
        print_tower_vertical(n, begin, end, 15, 0);
        draw_tower_move(begin, end);
    }
    // �����������
    cct_gotoxy(0, 35);
    cct_setcolor();
    if (begin == 'Q')
        cout << "��Ϸ��ֹ������";
    else 
		cout << "��Ϸ������";

    cct_gotoxy(0, 37);
    // ����
    pause();
}

void mode0()
{
    exit(0);
}
