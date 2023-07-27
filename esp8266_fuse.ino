#define BLINKER_PRINT Serial
#define BLINKER_WIFI
#define BLINKER_WITH_SSL

#include <Blinker.h>

const char auth[] = "ecc34d9000cf";
const char ssid[] = "这WIFI不给蹭";
const char pswd[] = "qazxswed";

// 新建组件对象
BlinkerButton ButtonPower("btn-power");
BlinkerButton ButtonForce("btn-force");

// Power按钮（正常按下）
void power_callback(const String & state) {
    for(int i = 0; i < 2; i++){
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      delay(300);
    }
    BLINKER_LOG("get button state: ", state);
    digitalWrite(D5, HIGH);
    delay(300);
    digitalWrite(D5, LOW);
    BLINKER_LOG("get button state: ", state);
    for(int i = 0; i < 2; i++){
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      delay(300);
    }
}

void force_callback(const String & state) {
    for(int i = 0; i < 4; i++){
     digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
     delay(300);
    }
    BLINKER_LOG("get button state: ", state);
    digitalWrite(D5, HIGH);
    delay(10000);
    digitalWrite(D5, LOW);
    BLINKER_LOG("get button state: ", state);
    for(int i = 0; i < 4; i++){
     digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
     delay(300);
    }
}

// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); //任意按钮开关灯
}

void setup() {
    // 初始化串口
    Serial.begin(115200);

    #if defined(BLINKER_PRINT)
        BLINKER_DEBUG.stream(BLINKER_PRINT);
    #endif
    
   
    pinMode(LED_BUILTIN, OUTPUT); // 初始化LED针脚
    pinMode(D5, OUTPUT); // 初始化继电器控制针脚
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(D5, LOW);

    // 初始化Blinker
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);
    
    ButtonPower.attach(power_callback);
    ButtonForce.attach(force_callback);
}

void loop() {
    Blinker.run();
}