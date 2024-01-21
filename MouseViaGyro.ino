#include <M5StickC.h>
#include <BleMouse.h>

float accX = 0;
float accY = 0;
float accZ = 0;

float gyroX = 0;
float gyroY = 0;
float gyroZ = 0;
float minGX = 0;
float minGY = 0;
float minGZ = 0;
float maxGX = 0;
float maxGY = 0;
float maxGZ = 0;

float temp = 0;

BleMouse bleMouse;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(40, 0);
  M5.Lcd.println("MPU6886 TEST");
  M5.Lcd.setCursor(0, 5);
  M5.Lcd.println("  X       Y       Z");
  M5.MPU6886.Init();
  M5.MPU6886.SetGyroFsr(0);
  
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleMouse.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  M5.MPU6886.getGyroData(&gyroX,&gyroY,&gyroZ);
  M5.MPU6886.getAccelData(&accX,&accY,&accZ);
  if (minGX > gyroX) minGX = gyroX;
  if (minGY > gyroY) minGY = gyroY;
  if (minGZ > gyroZ) minGZ = gyroZ;
  if (maxGX < gyroX) maxGX = gyroX;
  if (maxGY < gyroY) maxGY = gyroY;
  if (maxGZ < gyroZ) maxGZ = gyroZ;
  
  //if(bleMouse.isConnected()) {
  //  Serial.println("Scroll Down");
  //  bleMouse.move(gyroX,gyroY,0);
  //}
  
  M5.Lcd.setCursor(0, 15);
  M5.Lcd.printf("%.2f   %.2f   %.2f      ", gyroX, gyroY,gyroZ);
  //M5.Lcd.setCursor(140, 30);
  //M5.Lcd.print("o/s");
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.printf("%.2f   %.2f   %.2f      ",minGX, minGY, minGZ);
  //M5.Lcd.setCursor(140, 45);
  //M5.Lcd.print("mg");
  M5.Lcd.setCursor(0, 45);
  M5.Lcd.printf("%.2f   %.2f   %.2f      ",maxGX, maxGY, maxGZ);

  delay(100);
}
