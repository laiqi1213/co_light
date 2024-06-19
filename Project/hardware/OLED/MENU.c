/* *********************************************************
 * 多级菜单v2.0
 * 作者:Adam
 *
 * 移植方法
 *
 * 0. 显示器驱动需要使用缓冲区机制, 如 u8g2
 *
 * 1. 配置菜单宏定义, 兼容不同显示器及布局, 例如:
    #define MENU_WIDTH 128 // 菜单宽度
    #define MENU_HEIGHT 64 // 菜单高度
 *
 * 2. 实现 menu_command_callback() 对应的指令功能以完成移植, 有些指令是有参数的, 参数已经提取好, 按需使用参数即可
 *      详情可看CSDN博客:https://blog.csdn.net/AdminAdam/article/details/138232161
 *
 * 使用方法
 *
 * 3. 创建选项列表,并直接初始化, 每个选项对应其名字和功能(功能为函数指针, 直接填写函数名), 例如:
    static MENU_OptionTypeDef MENU_OptionList[] = {{"<<<", NULL},                     // 固定格式, 用于退出
                                                   {"Tools", MENU_RunToolsMenu},      // 工具
                                                   {"Games", MENU_RunGamesMenu},      // 游戏
                                                   {"Setting", MENU_RunSettingMenu},  // 设置
                                                   {"Information", MENU_Information}, // 信息
                                                   {"..", NULL}};                     // 固定格式, 用于计算选项列表长度和退出
 *
 * 4. 调用 MENU_RunMenu() 运行菜单, 参数为选项列表
    MENU_RunMenu(MENU_OptionList);
 *
 * 5. 为了实现多级菜单, 可使用一个函数来封装 第3 第4 步, 封装好的函数可作为功能被其他菜单调用, 以此实现不限层级多级菜单,
 *    例如 void MENU_RunToolsMenu(void) 被选项 {"Tools", MENU_RunToolsMenu} 调用;
 *
 *
 * 视频教程:https://www.bilibili.com/video/BV1Y94y1g7mu?p=2
 * CSDN博客:https://blog.csdn.net/AdminAdam/article/details/138232161
 *
 * 下载链接
 * 百度网盘:https://pan.baidu.com/s/1bZPWCKaiNbb-l1gpAv6QNg?pwd=KYWS
 * GitHub:https://github.com/AdamLoong/Embedded_MENU_Simple
 *
 * B站UP:加油哦大灰狼
 * 如果此程序对你有帮助记得给个一键三连哦! ( •̀ ω •́ )✧
 ********************************************************* */

#include "MENU.h"
#include "oled.h"
#include "u8g2.h"
#include "key.h"
#include "freertos.h"
#include "task.h"
#include "queue.h"

/* 配置菜单 */
#define MENU_X 0       // 菜单位置X
#define MENU_Y 0       // 菜单位置Y
#define MENU_WIDTH 128 // 菜单宽度
#define MENU_HEIGHT 64 // 菜单高度

#define MENU_LINE_H 16 // 行高
#define MENU_PADDING 2 // 内边距

#define MENU_FONT_W 8  // 字体宽度
#define MENU_FONT_H 16 // 字体高度

#define CURSOR_CEILING ((MENU_HEIGHT / MENU_LINE_H) - 1) // 光标限位

/** Port 移植接口 * **************************************************************/
/* 依赖头文件 */
#include "Key.h"
#include "OLED.h"
extern u8g2_t u8g2;
/// @brief 菜单指令回调函数
/// @param  command 指令
/// @param  ... 可变参数列表根据指令定义
/// @return  返回值根据指令定义
int menu_command_callback(enum _menu_command command, ...)
{
    int retval = 0;

    switch (command)
    {
        /* Output */
    case BUFFER_DISPLAY:
			u8g2_ClearDisplay(&u8g2);//显示
        break;

    case BUFFER_CLEAR:
       u8g2_ClearDisplay(&u8g2);//清
        break;

    case SHOW_STRING:
    {
        /* 提取参数列表 */
        int *arg_list = ((int *)&command) + 1;  //参数量
        int show_x = arg_list[0];
        int show_y = arg_list[1];
        char *show_string = (char *)arg_list[2];

        /* 按需使用参数 */
//        OLED_Printf(show_x, show_y, MENU_FONT_W, show_string);
				u8g2_DrawUTF8(&u8g2,show_x,show_y,show_string);//写显存
        break;
    }

    case SHOW_CURSOR://显示光标
    {
        /* 提取参数列表 */
        int *arg_list = ((int *)&command) + 1;
        int cursor_x = arg_list[0];
        int cursor_y = arg_list[1];
        int cursor_width = arg_list[2];
        int cursor_height = arg_list[3];

        /* 按需使用参数 */
				u8g2_DrawBox(&u8g2, cursor_x, cursor_y,cursor_width,cursor_height);//画光标，画完后当行字体需要反显
       // OLED_ReverseArea(cursor_x, cursor_y, cursor_width, cursor_height);//
        break;
    }

        /* Input */
    case GET_EVENT_ENTER:
       
        break;

    case GET_EVENT_BACK:
       
        break;

    case GET_EVENT_WHEEL:
     
        break;

    default:
        break;
    }

    return retval;
}

/* ***************************************************** Port 移植接口 ** */

/* ******************************************************** */

/// @brief 菜单运行函数
/// @param OptionList 选项列表
void MENU_RunMenu(MENU_OptionTypeDef *OptionList)
{
    int8_t Catch_i = 1;      // 选中下标默认为1,(因为OptionList[0]为"<<<")
    int8_t Cursor_i = 0;     // 光标下标默认为0
    int8_t Show_i = 0;       // 显示(遍历)起始下标
    int8_t Wheel_Event = 0;  // 记录菜单滚动事件
    int8_t Option_Max_i = 0; // 选项列表长度

    for (Option_Max_i = 0; OptionList[Option_Max_i].String[0] != '.'; Option_Max_i++) // 计算选项列表长度
    {
        ;
    }

    Option_Max_i--; // 不显示".."

    while (1)
    {
        /* ******************************************************** */

        if (menu_command_callback(GET_EVENT_ENTER))
        {
            /* 如果功能不为空则执行功能,否则返回 */
            if (OptionList[Catch_i].func != NULL)
                OptionList[Catch_i].func(); // 执行选中选项的功能函数
            else
                return;
        }

        if (menu_command_callback(GET_EVENT_BACK))
            return;

        Wheel_Event = -menu_command_callback(GET_EVENT_WHEEL);

        /* 根据按键事件更改选中下标和光标下标 */
        if (Wheel_Event)
        {
            /* 更新下标 */
            Cursor_i += Wheel_Event;
            Catch_i += Wheel_Event;

            /* 限制选中下标 */
            if (Catch_i > Option_Max_i)
                Catch_i = Option_Max_i;

            if (Catch_i < 0)
                Catch_i = 0;

            /* 限制光标下标 */
            if (Cursor_i > CURSOR_CEILING)
                Cursor_i = CURSOR_CEILING;

            if (Cursor_i > Option_Max_i)
                Cursor_i = Option_Max_i;

            if (Cursor_i > Catch_i)
                Cursor_i = Catch_i;

            if (Cursor_i < 0)
                Cursor_i = 0;
        }

        /* 计算显示起始下标 */
        Show_i = Catch_i - Cursor_i; // 详解 https://www.bilibili.com/read/cv32114635/?jump_opus=1

        /* ******************************************************** */

        menu_command_callback(BUFFER_CLEAR); // 擦除缓存

        for (uint8_t i = 0; i <= CURSOR_CEILING; i++) // 遍历显示 选项
        {
            if (Show_i + i > Option_Max_i)
                break;

            /* 显示选项 */
            uint8_t x = MENU_X + MENU_PADDING;
            uint8_t y = MENU_Y + (i * MENU_LINE_H) + ((MENU_LINE_H - MENU_FONT_H) / 2);
            char *str = OptionList[Show_i + i].String;
            menu_command_callback(SHOW_STRING, x, y, str);
        }

        /* 显示光标 */
        uint8_t cursor_x = MENU_X;
        uint8_t cursor_y = MENU_Y + (Cursor_i * MENU_LINE_H);
        uint8_t cursor_width = MENU_WIDTH;
        uint8_t cursor_height = MENU_LINE_H;
        menu_command_callback(SHOW_CURSOR, cursor_x, cursor_y, cursor_width, cursor_height);

        menu_command_callback(BUFFER_DISPLAY); // 更新缓存至显示器

        /* ******************************************************** */
    }
}

/* ******************************************************** */

/* ******************************************************** */
/* 应用 */

void MENU_RunMainMenu(void)
{
    static MENU_OptionTypeDef MENU_OptionList[] = {{"<<<"},
                                                   {"Tools", MENU_RunToolsMenu},      // 工具
                                                   {"Setting", NULL},                 // 设置
                                                   {"Information", MENU_Information}, // 信息
																								//	 {"Back",MENU_Back},
                                                   {".."}};

    MENU_RunMenu(MENU_OptionList);
}

void MENU_RunToolsMenu(void)
{
    static MENU_OptionTypeDef MENU_OptionList[] = {{"<<<"},
                                                   {"Seria", NULL},         // 串口
                                                   {"Oscilloscope ", NULL}, // 示波器
                                                   {"PWM Output", NULL},    // PWM 输出
                                                   {"PWM Input", NULL},     // PWM 输入
                                                   {"ADC Input", NULL},     // ADC 输入
																								//	 {"Back",MENU_Back},
                                                   {".."}};

    MENU_RunMenu(MENU_OptionList);
}

void MENU_Information(void)
{
    menu_command_callback(BUFFER_CLEAR);
    menu_command_callback(SHOW_STRING, 5, 0, "menu v2.0\nBy:Adam\nbilibili\nUP:加油哦大灰狼");
    menu_command_callback(BUFFER_DISPLAY);

    while (1)
    {

        if (menu_command_callback(GET_EVENT_ENTER))
            return;

        if (menu_command_callback(GET_EVENT_BACK))
            return;
    }
}

/**********************************************************/
