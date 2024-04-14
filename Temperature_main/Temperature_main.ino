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

int green_pin = 12;
int blue_pin = 11;
int red_pin = 10;

int temp_c_pin = A0;
int temp_f_pin = A1;

float temp_c_value;
float temp_f_value;

float temp_c;
float temp_f;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x64
  display.clearDisplay();
  display.setTextSize(1.5);   
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true); 
  display.println("Initiating...");
  display.display();
  display.setTextSize(3);
  
  analogReference(INTERNAL);

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
  // put your main code here, to run repeatedly:
  temp_c_value = analogRead(temp_c_pin);
  temp_f_value = analogRead(temp_f_pin);

  temp_c = (temp_c_value * ref_voltage) / 1024.0; 
  temp_f = (temp_f_value * ref_voltage) / 1024.0; 

  display.clearDisplay();
  display.setCursor(0, 0);     // Start at top-left corner

  display.print(temp_c * 100);
  display.write(248);
  display.println("C");
  display.print(temp_f * 100);
  display.write(248);
  display.println("F");
  display.display();

  delay(500);

}
