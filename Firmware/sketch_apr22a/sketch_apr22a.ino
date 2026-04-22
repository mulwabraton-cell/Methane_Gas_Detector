#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- DISPLAY SETTINGS ---
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

// SPI Pins 
#define OLED_MOSI   23
#define OLED_CLK    18
#define OLED_CS      5
#define OLED_DC     16
#define OLED_RESET  17 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// --- HARDWARE PINS ---
#define GAS_SENSOR_PIN 34  // Analog Input
#define BUZZER_PIN     25  // Output
#define RED_LED        13  // Output (ALARM)
#define BLUE_LED       12  // Output (OK STATUS)

// --- THRESHOLDS ---
int gasThreshold = 1800;

void setup() {
  Serial.begin(115200);

  // Initialize Hardware Pins
  pinMode(GAS_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Initial LED State
  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(RED_LED, LOW);

  // Initialize Display
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 20);
  display.println("SYSTEM STARTING...");
  display.display();
  
  delay(2000); // Sensor pre-heat delay
}

void loop() {
  // 1. Read the Sensor
  int rawValue = analogRead(GAS_SENSOR_PIN);
  
  // 2. Update Serial Monitor for debugging
  Serial.print("Methane Raw Value: ");
  Serial.println(rawValue);

  // 3. Update OLED Display
  updateDisplay(rawValue);

  // 4. Alert Logic
  if (rawValue > gasThreshold) {
    triggerAlarm(true);
  } else {
    triggerAlarm(false);
  }

  delay(200); // Fast response time
}

void updateDisplay(int value) {
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("METHANE MONITOR");
  display.drawLine(0, 10, 128, 10, WHITE);

  display.setTextSize(2);
  display.setCursor(20, 30);
  display.print("VAL: ");
  display.print(value);

  display.setTextSize(1);
  display.setCursor(0, 55);
  if(value > gasThreshold) {
    display.print("STATUS: !!! DANGER !!!");
  } else {
    display.print("STATUS: NORMAL");
  }
  
  display.display();
}

void triggerAlarm(bool active) {
  if (active) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
    
    // Pulsing Buzzer
    digitalWrite(BUZZER_PIN, HIGH);
    delay(50);
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
  }
}