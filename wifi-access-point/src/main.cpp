#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>

void setup()
{
    Serial.begin(115200);
    delay(10);

    //TODO
}

void get_client_details() {
    wifi_sta_list_t clients;
    esp_wifi_ap_get_sta_list(&clients);
    Serial.printf("Connected clients: %d\n", clients.num);

    // TODO
}

void loop()
{
    get_client_details();
    delay(1000);
}

