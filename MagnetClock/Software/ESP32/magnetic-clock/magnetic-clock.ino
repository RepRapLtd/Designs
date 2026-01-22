#include <WiFi.h>
#include <Wire.h>
#include <time.h>
#include <Stepper.h>

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "heltec.h"

// WiFi creds
const char* WIFI_SSID = "sew";
const char* WIFI_PASS = "1Sgdttsa";

// NTP servers
const char* NTP1 = "pool.ntp.org";
const char* NTP2 = "time.google.com";
const char* NTP3 = "time.cloudflare.com";

// UK timezone with DST
static const char* UK_TZ = "GMT0BST,M3.5.0/1,M10.5.0/2";

// Heltec OLED pins (common WiFi Kit 32)
static const int OLED_SDA = 4;
static const int OLED_SCL = 15;
static const int OLED_RST = 16;

const int IN1 = 13;
const int IN2 = 12;
const int IN3 = 14;
const int IN4 = 27;

const int stepsPerRevolution = 2048;

Stepper myStepper = Stepper(stepsPerRevolution, IN1, IN3, IN2, IN4);


AsyncWebServer server(80);

// Cached time (updated in loop, served instantly)
String g_cachedTime = "Time not synced yet";
volatile bool g_timeValid = false;

// OLED update request (set by handler, done in loop)
volatile bool g_oledUpdatePending = false;
String g_oled1, g_oled2, g_oled3;

static unsigned long g_lastNtpKickMs = 0;
static const unsigned long NTP_KICK_INTERVAL_MS = 10UL * 60UL * 1000UL;

static unsigned long g_lastTimeRefreshMs = 0;
static const unsigned long TIME_REFRESH_INTERVAL_MS = 250UL;

void initHeltecOLEDHard() {
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(50);
  digitalWrite(OLED_RST, HIGH);
  delay(50);

  Wire.begin(OLED_SDA, OLED_SCL);

  Heltec.display->init();
  Heltec.display->clear();
  Heltec.display->setContrast(255);
  Heltec.display->display();
}

void showOnOLED(const String& l1, const String& l2="", const String& l3="") {
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, l1);
  if (l2.length()) Heltec.display->drawString(0, 14, l2);
  if (l3.length()) Heltec.display->drawString(0, 28, l3);
  Heltec.display->display();
}

void queueOled(const String& l1, const String& l2, const String& l3) {
  g_oled1 = l1; g_oled2 = l2; g_oled3 = l3;
  g_oledUpdatePending = true;
}

static inline bool timeLooksValid(time_t t) {
  return t > 1700000000; // ~2023-11
}

void kickNtpIfDue() {
  unsigned long nowMs = millis();
  if (nowMs - g_lastNtpKickMs >= NTP_KICK_INTERVAL_MS) {
    configTime(0, 0, NTP1, NTP2, NTP3); // kick only, no waiting
    g_lastNtpKickMs = nowMs;
  }
}

void refreshCachedTimeIfDue() {
  unsigned long nowMs = millis();
  if (nowMs - g_lastTimeRefreshMs < TIME_REFRESH_INTERVAL_MS) return;
  g_lastTimeRefreshMs = nowMs;

  time_t now = time(nullptr);
  if (!timeLooksValid(now)) {
    g_timeValid = false;
    g_cachedTime = "Time not synced yet";
    return;
  }

  g_timeValid = true;
  struct tm tminfo;
  localtime_r(&now, &tminfo);

  char buf[16];
  strftime(buf, sizeof(buf), "%H:%M:%S", &tminfo);
  g_cachedTime = String(buf);
}





void setup() {
  Heltec.begin(true, false, true);
  Serial.begin(115200);

  // 28BYJ-48 stepper controller

  // start with motor off
  // Make them low BEFORE switching them on
  



  initHeltecOLEDHard();
  showOnOLED("Booting...", "Starting WiFi");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println();

  WiFi.setSleep(false);

  setenv("TZ", UK_TZ, 1);
  tzset();

  // Kick NTP at boot
  configTime(0, 0, NTP1, NTP2, NTP3);
  g_lastNtpKickMs = millis();

  String ipStr = WiFi.localIP().toString();
  showOnOLED("WiFi connected!", "IP address:", ipStr);

  // Async handler: serve immediately from cached string, then request OLED update
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    String html;
    html.reserve(512);
    html += "<!doctype html><html><head><meta charset='utf-8'>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<title>Heltec ESP32</title></head><body>";
    html += "<h1>Hello, world!</h1>";
    html += "<p><b>UK time (24h):</b> ";
    html += g_cachedTime;
    html += "</p></body></html>";

    request->send(200, "text/html", html);

    if (g_timeValid) queueOled("UK time:", g_cachedTime, WiFi.localIP().toString());
    else            queueOled("UK time:", g_cachedTime, "Waiting for NTP");
  });

  server.begin();
}

void loop() {

  // Rotate CW slowly at 5 RPM
  myStepper.setSpeed(5);
  myStepper.step(stepsPerRevolution);
  delay(1000);

  // Rotate CCW quickly at 10 RPM
  myStepper.setSpeed(10);
  myStepper.step(-stepsPerRevolution);
  delay(1000);
/*
  // No server.handleClient() in Async
  kickNtpIfDue();
  refreshCachedTimeIfDue();

  if (g_oledUpdatePending) {
    g_oledUpdatePending = false;
    showOnOLED(g_oled1, g_oled2, g_oled3);
  }

  delay(1);
  */
}
