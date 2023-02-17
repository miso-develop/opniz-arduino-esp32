#include <OpnizEsp32.h>
#include <lib/WiFiConnector.h>

const char* ssid = "<SSID>";         // WiFiのSSIDに書き換え
const char* password = "<PASSWORD>"; // WiFiのパスワードに書き換え
WiFiConnector wifiConnector(ssid, password); // WiFi接続ヘルパーインスタンス生成

const char* address = "192.168.0.1"; // Node.js SDKを実行する端末のIPアドレスを指定
const uint16_t port = 3000;          // Node.js SDKを実行する端末のポート番号を指定
Opniz::Esp32* opniz = new Opniz::Esp32(address, port); // opnizインスタンス生成



void setup() {
    Serial.begin(115200);
    
    wifiConnector.setTimeoutCallback([]() { esp_restart(); }); // WiFi接続タイムアウト時にリブート
    wifiConnector.connect(); // WiFi接続
    
    Serial.printf("opniz server address: %s\nopniz server port: %u\n\n", opniz->getAddress(), opniz->getPort()); // Node.js SDK接続情報を表示
    opniz->connect(); // Node.js SDKへ接続
}

void loop() {
    opniz->loop(); // opnizメインループ
    wifiConnector.watch(); // WiFi接続監視
}
