#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// --- 硬件配置 ---
// 根据你的屏幕型号选择正确的构造函数
// 以最常见的 I2C 接口的 0.96寸 SSD1306 屏幕为例：
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
// 如果你的屏幕是其他型号（如SH1106），请修改上面的构造函数。
// 更多构造函数请参考：https://github.com/olikraus/u8g2/wiki/u8g2setupcpp

// --- 引脚定义 ---
// ESP32-S3 的 I2C 引脚可以灵活定义，但为了避免冲突，请选择以下任意一对空闲 GPIO 作为 SDA 和 SCL。
// 常用推荐：SDA -> GPIO 4, SCL -> GPIO 5
// 备用方案：SDA -> GPIO 8, SCL -> GPIO 9
#define I2C_SDA 4
#define I2C_SCL 5

unsigned long lastSerialPrint = 0;
unsigned long lastScreenUpdate = 0;
int counter = 0;

void setup() {
  // 1. 串口初始化
  Serial.begin(115200);
  delay(1000); // 给串口一点初始化时间
  Serial.println(F("\nESP32-S3 系统正在启动..."));

  // 2. I2C 总线初始化
  Wire.begin(I2C_SDA, I2C_SCL);
  // Wire.setClock(400000); // 可选的 I2C 时钟设置，建议先注释，有问题再尝试

  // 3. OLED 初始化
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_unifont_t_chinese2);
  u8g2.setFontPosTop();

  // 测试屏幕是否能通信
  Serial.println("正在检测 OLED 屏幕...");
  u8g2.firstPage();
  do {
    u8g2.setCursor(5, 15);
    u8g2.print("屏幕初始化");
    u8g2.setCursor(5, 45);
    u8g2.print("  完成!");
  } while (u8g2.nextPage());
  delay(2000);
  Serial.println("系统初始化完成，进入主循环。\n");
}

void loop() {
  unsigned long now = millis();

  // --- 1. 串口打印测试 (每秒一次) ---
  if (now - lastSerialPrint >= 1000) {
    lastSerialPrint = now;
    counter++;

    Serial.print(F("[Serial Log] 运行时间: "));
    Serial.print(now / 1000);
    Serial.print(F(" 秒, 计数器值: "));
    Serial.println(counter);
  }

  // --- 2. 屏幕显示测试 (每0.2秒更新一次) ---
  if (now - lastScreenUpdate >= 200) {
    lastScreenUpdate = now;

    u8g2.firstPage();
    do {
      u8g2.setCursor(5, 5);
      u8g2.print("U8g2 测试");

      u8g2.setCursor(5, 3);
      u8g2.print("计数: ");
      u8g2.print(counter);

      u8g2.setCursor(5, 50);
      u8g2.print(now / 1000);

      u8g2.setCursor(5, 55);
      u8g2.print("秒");
    } while (u8g2.nextPage());
  }
}