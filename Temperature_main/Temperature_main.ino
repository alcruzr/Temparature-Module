#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

float ref_voltage = 1.1;

int temp_f_pin = A1;
int temp_c_pin = A0;

float temp_c_value;
float temp_f_value;

float temp_c;
float temp_f;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x64
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  
  analogReference(INTERNAL);

  pinMode(temp_f_pin, INPUT);
  pinMode(temp_c_pin, INPUT);
  delay(1000);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  temp_c_value = analogRead(deg_c_pin);
  temp_f_value = analogRead(deg_f_pin);

  temp_c = (temp_c_value * ref_voltage) / 1024.0; 
  temp_f = (temp_f_value * ref_voltage) / 1024.0; 

  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner

  display.print(temp_c * 100);
  display.println(" C");
  display.println(temp_f * 100);
  display.println(" F");

  delay(500);

}
