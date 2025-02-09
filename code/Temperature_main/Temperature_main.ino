#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

float ref_voltage = 5;

int green_pin = 11;
int blue_pin = 10;
int red_pin = 12;

int temp_c_pin = A0;
int temp_f_pin = A1;

float temp_c_value;
float temp_f_value;

float temp_c;
float temp_f;

float readTempC(){
  float val1 = 0;
  float val2 = 0;
  int readings = 80;
  for (int i = 0; i < readings; i++){
    val2 = analogRead(temp_c_pin);
    val1 = val1 + val2;
    delay (1);
  }
  val1 = val1/readings;
  return val1;
}

float readTempF(){
  float val3 = 0;
  float val4 = 0;
  int readings = 80;
  for (int i = 0; i < readings; i++){
    val4 = analogRead(temp_f_pin);
    val3 = val3 + val4;
    delay (1);
  }
  val3 = val3/readings;
  return val3;
}

void setup() {
  Serial.begin(115200);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x64
  display.clearDisplay();
  display.setTextSize(1.5);   
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true); 
  display.println("Initiating...");
  display.display();
  display.setTextSize(3);
  
  analogReference(DEFAULT);

  pinMode(temp_f_pin, INPUT);
  pinMode(temp_c_pin, INPUT);

  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  pinMode(red_pin, OUTPUT);

  digitalWrite(green_pin, 1);
  digitalWrite(blue_pin, 1);
  digitalWrite(red_pin, 1);

  delay(3000);
}

void loop() {
  temp_c_value = readTempC();
  temp_f_value = readTempF();

  temp_c = ((temp_c_value * ref_voltage) / 1023.0) * 100; 
  temp_f = ((temp_f_value * ref_voltage) / 1023.0) * 100; 

  display.clearDisplay();
  display.setCursor(0, 0);     // Start at top-left corner

  display.print(temp_c);
  display.write(248);
  display.println("C");
  display.print(temp_f);
  display.write(248);
  display.println("F");
  display.display();

  if(temp_f >= 80){
    digitalWrite(green_pin, 0);
    digitalWrite(blue_pin, 0);
    digitalWrite(red_pin, 1);
  }
  else if(temp_f <= 60){
    digitalWrite(green_pin, 0);
    digitalWrite(blue_pin, 1);
    digitalWrite(red_pin, 0);
  }
  else{
    digitalWrite(green_pin, 1);
    digitalWrite(blue_pin, 0);
    digitalWrite(red_pin, 0);
  }
  delay(10);
}
