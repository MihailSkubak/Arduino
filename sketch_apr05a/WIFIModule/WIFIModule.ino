#define REMOTEXY_MODE__ESP8266WIFI_LIB_POINT
#include <ESP8266WiFi.h> 

#include <RemoteXY.h> 
// настройки соединения  
#define REMOTEXY_WIFI_SSID "RemoteXY" 
#define REMOTEXY_WIFI_PASSWORD "12345678" 
#define REMOTEXY_SERVER_PORT 6377 


// конфигурация интерфейса   
#pragma pack(push, 1) 
uint8_t RemoteXY_CONF[] = 
  { 255,4,0,0,0,71,0,8,13,1,
  2,0,37,12,22,11,2,26,31,31,
  79,78,0,79,70,70,0,2,0,37,
  32,22,11,2,26,31,31,79,78,0,
  79,70,70,0,2,0,37,51,22,11,
  2,26,31,31,79,78,0,79,70,70,
  0,2,0,37,74,22,11,2,26,31,
  31,79,78,0,79,70,70,0 }; 
   
// структура определяет все переменные вашего интерфейса управления  
struct { 

    // input variable
  uint8_t switch_1; // =1 если переключатель включен и =0 если отключен 
  uint8_t switch_2; // =1 если переключатель включен и =0 если отключен 
  uint8_t switch_3; // =1 если переключатель включен и =0 если отключен 
  uint8_t switch_4; // =1 если переключатель включен и =0 если отключен 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY; 
#pragma pack(pop) 

///////////////////////////////////////////// 
//           END RemoteXY include          // 
///////////////////////////////////////////// 

#define PIN_SWITCH_1 D5
#define PIN_SWITCH_2 D6
#define PIN_SWITCH_3 D7
#define PIN_SWITCH_4 D0


void setup()  
{ 
  RemoteXY_Init ();  
   
  pinMode (PIN_SWITCH_1, OUTPUT);
  pinMode (PIN_SWITCH_2, OUTPUT);
  pinMode (PIN_SWITCH_3, OUTPUT);
  pinMode (PIN_SWITCH_4, OUTPUT);
   
  // TODO you setup code 
   
} 

void loop()  
{  
  RemoteXY_Handler (); 
   
  digitalWrite(PIN_SWITCH_1, (RemoteXY.switch_1==0)?LOW:HIGH);
  digitalWrite(PIN_SWITCH_2, (RemoteXY.switch_2==0)?LOW:HIGH);
  digitalWrite(PIN_SWITCH_3, (RemoteXY.switch_3==0)?LOW:HIGH);
  digitalWrite(PIN_SWITCH_4, (RemoteXY.switch_4==0)?LOW:HIGH);
   
  // TODO you loop code 
  // используйте структуру RemoteXY для передачи данных 


}
