#include <AsyncElegantOTA.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <Update.h>
#include <WiFi.h>

class WebServer {
   public:
    void setup();

   private:
    void otaSetup();
};