#ifndef __MENU_H
#define __MENU_H

#ifndef NULL
#define NULL ((void *)0)
#endif

#include <stdint.h>

typedef struct _MENU_OptionTypeDef // 选项结构体
{
    char *String;       // 选项字符串
    void (*func)(void); // 选项功能 函数指针
} MENU_OptionTypeDef;

/**********************************************************/
enum _menu_command
{
    BUFFER_DISPLAY, // 无参无返
    BUFFER_CLEAR,   // 无参无返
    SHOW_STRING,    // 可变参数列表对应顺序: x, y, string
    SHOW_CURSOR,    // 可变参数列表对应顺序: x, y, width, height;

    GET_EVENT_ENTER,     // 返回布尔
    GET_EVENT_BACK,      // 返回布尔
    GET_EVENT_DIRECTION, // 返回方向
    GET_EVENT_WHEEL,     // 返回有符号整型
};

int menu_command_callback(enum _menu_command command, ...);

/**********************************************************/

void MENU_RunMenu(MENU_OptionTypeDef *OptionList);

/**********************************************************/

void MENU_RunMainMenu(void);
void MENU_RunToolsMenu(void);
void MENU_RunGamesMenu(void);
void MENU_Information(void);

#endif
