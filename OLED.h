#ifndef __OLED_H
#define __OLED_H

#define  u8 unsigned char
#define  u16 unsigned int
#define  u32 unsigned int

extern int oled_flag;

void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_DrawBMP(u8 x,u8 y,u8 sizex, u8 sizey,u8 BMP[]);
void OLED_ShowChinese(u8 x,u8 y,u8 no,u8 sizey);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 sizey);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 sizey);
u32 oled_pow(u8 m,u8 n);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 sizey);
void OLED_Clear(void);
void OLED_Clearline(int i);
void OLED_Display_Off(void);
void OLED_Display_On(void);
void OLED_Set_Pos(u8 x, u8 y);
void OLED_DisplayTurn(u8 i);
void OLED_ColorTurn(u8 i);
void delay_ms(unsigned int ms);
void OLED_ShowNum_buquan(u8 x,u8 y,u32 num);//补全数字，如7变成07，0也可以变为00，仅可用于6×12，

void OLED_Init(void);

#endif
