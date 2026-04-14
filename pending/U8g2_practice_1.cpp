/*U8g2库小练习*/
#include <Arduino.h>
#include <U8g2lib.h>
//#include "u8g2_font_wqy.c"
#include <Wire.h>

// --- 硬件配置 ---
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C: U8g2 库，驱动芯片型号SSD1306，屏幕物理分辨率128X64，生产厂商NONAME，通信方式硬件HW_I2C
//字段      含义                            在代码中
//U8G2      固定前缀，代表 U8g2 库          U8G2
//SSD1306   驱动芯片型号	                SSD1306
//128X64	屏幕物理分辨率	                128X64
//NONAME	生产厂商，通用型号就是 NONAME	    NONAME
//F	        显存占用模式 (F=Full，全缓冲)	    F
//HW_I2C	通信方式 (HW=硬件，SW=软件模拟)	    HW_I2C

// --- 传参 ---
//U8G2_R0: 默认方向0°， U8X8_PIN_NONE: 无复位管脚
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// --- 引脚定义 ---
#define I2C_SDA 4     // SDA管脚: GPIO4
#define I2C_SCL 5     // SCL管脚: GPIO5

void setup() {
    // I2C初始化
    Wire.begin(I2C_SDA, I2C_SCL);
    Wire.setClock(400000);  // 设置 I2C 时钟频率为 400 kHz（快速模式），默认 100 kHz 
    // OLED 初始化
    u8g2.begin();
    u8g2.enableUTF8Print();
    u8g2.setFont(u8g2_font_wqy16_t_gb2312);
    u8g2.setFontPosTop();
}

void loop() {
        u8g2.firstPage();
    do {
        u8g2.setCursor(5, 5);
        u8g2.printf("u8g2 测试");
    } while (u8g2.nextPage());
}
