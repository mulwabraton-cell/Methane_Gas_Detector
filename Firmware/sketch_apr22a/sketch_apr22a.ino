#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ================= OLED CONFIGURATION =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ================= PIN ALLOCATIONS =================
#define MQ4_PIN     34   // Analog Input
#define BUZZER_PIN  25   // Alarm Sound

#define LED_GREEN   26   // SAFE
#define LED_YELLOW  27   // WARNING
#define LED_RED     14   // DANGER

#define SDA_PIN     21   // I2C Data
#define SCL_PIN     22   // I2C Clock

// ================= THRESHOLDS =================
const int THRESHOLD_LOW  = 1200;
const int THRESHOLD_HIGH = 2500;

// ================= VARIABLES =================
int gasValue = 0;

// =====================================================
// SETUP
// =====================================================
void setup() {

  Serial.begin(115200);

  // Configure ADC range for ESP32
  analogSetAttenuation(ADC_11db);

  // Pin Modes
  pinMode(MQ4_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  // Initialize I2C
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  // Startup Screen
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(10, 15);
  display.println("METHANE DETECTOR");

  display.setCursor(10, 35);
  display.println("SYSTEM INITIALIZING");

  display.display();

  delay(2000);

  // MQ-4 Warmup
  display.clearDisplay();

  display.setCursor(10, 20);
  display.println("WARMING SENSOR");

  display.setCursor(10, 40);
  display.println("PLEASE WAIT...");

  display.display();

  delay(30000);
}

// =====================================================
// MAIN LOOP
// =====================================================
void loop() {

  // ===== Sensor Averaging for Stable Readings =====
  long total = 0;

  for(int i = 0; i < 10; i++) {
    total += analogRead(MQ4_PIN);
    delay(5);
  }

  gasValue = total / 10;

  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  // ===== OLED DISPLAY =====
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("METHANE MONITOR");

  display.drawLine(0, 10, 128, 10, WHITE);

  // Gas Value
  display.setTextSize(2);
  display.setCursor(15, 20);

  display.print(gasValue);
  display.print(" ADC");

  // ===== STATUS LOGIC =====
  if (gasValue < THRESHOLD_LOW) {

    statusSafe();

  }
  else if (gasValue >= THRESHOLD_LOW &&
           gasValue < THRESHOLD_HIGH) {

    statusWarning();

  }
  else {

    statusDanger();

  }

  display.display();

  delay(300);
}

// =====================================================
// SAFE STATUS
// =====================================================
void statusSafe() {

  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);

  digitalWrite(BUZZER_PIN, LOW);

  display.setTextSize(1);

  display.setCursor(0, 55);
  display.print("STATUS: SAFE");
}

// =====================================================
// WARNING STATUS
// =====================================================
void statusWarning() {

  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_RED, LOW);

  digitalWrite(BUZZER_PIN, LOW);

  display.setTextSize(1);

  display.setCursor(0, 55);
  display.print("STATUS: WARNING");
}

// =====================================================
// DANGER STATUS
// =====================================================
void statusDanger() {

  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, HIGH);

  // Buzzer Pulse
  digitalWrite(BUZZER_PIN, HIGH);
  delay(50);
  digitalWrite(BUZZER_PIN, LOW);

  display.setTextSize(1);

  display.setCursor(0, 55);
  display.print("STATUS: DANGER");
}