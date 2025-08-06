#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>

const char* ssid = "Phạm Hiếuu";
const char* password = "45678910jqk";

// Link file version.txt trên GitHub (Raw link)
const char* versionURL = "https://raw.githubusercontent.com/PhamHieuuuu/Firmwave-OTA/main/version.txt";

// Phiên bản hiện tại của firmware
String currentVersion = "v0.0.0.2";

void checkAndUpdateFirmware() {
  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient http;

  Serial.println("[DEBUG] Checking for firmware update...");
  http.begin(client, versionURL);
  int httpCode = http.GET();
  Serial.printf("[DEBUG] HTTP GET code: %d\n", httpCode);

  if (httpCode != HTTP_CODE_OK) {
    Serial.println("[ERROR] Failed to fetch version file.");
    http.end();
    return;
  }

  String latestVersion = http.getString();
  latestVersion.trim();
  http.end();

  Serial.printf("[DEBUG] Current: %s, Latest: %s\n", currentVersion.c_str(), latestVersion.c_str());

  if (latestVersion == currentVersion) {
    Serial.println("[INFO] Firmware is up to date.");
    return;
  }

  Serial.println("[INFO] New firmware available. Updating...");
  String firmwareURL = "https://github.com/PhamHieuuuu/Firmwave-OTA/releases/download/" + latestVersion + "/OTA_Laster.ino.bin"; 
  Serial.printf("[DEBUG] Firmware URL: %s\n", firmwareURL.c_str());

  client.setTimeout(20);
  httpUpdate.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

  t_httpUpdate_return ret = httpUpdate.update(client, firmwareURL);
  if (ret == HTTP_UPDATE_OK) {
    Serial.println("[INFO] Update successful. Rebooting...");
  } else {
    Serial.printf("[ERROR] Update failed: %s\n", httpUpdate.getLastErrorString().c_str());
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("[DEBUG] Booting...");

  WiFi.begin(ssid, password);
  Serial.println("[DEBUG] Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.printf("\n[DEBUG] Connected! IP: %s\n", WiFi.localIP().toString().c_str());

  // Gọi 1 hàm duy nhất để check & OTA
  checkAndUpdateFirmware();
}

void loop() {
  Serial.printf("[RUNNING] Firmware %s running...\n", currentVersion.c_str());
  delay(2000);
}
