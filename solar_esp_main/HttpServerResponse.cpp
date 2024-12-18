#include "HttpServerResponse.h"



extern void HttpPageMain(HttpServer* server, WiFiClient& client);
extern void HttpPageMainCss(HttpServer* server, WiFiClient& client);
extern void HttpPageStylesCss(HttpServer *server, WiFiClient& client);


void HttpServerResponse( HttpServer* server, WiFiClient& client)
{ 
    uint8_t requestId = server->request;
    
    Serial.print("reqest ID: ");
    Serial.println(requestId);
    
    // wysyłam odpowiedni kod html 
    // zgodnie z listą: const char * RequestList[]
    switch (requestId) 
    {
      case 0:
        // page not found
        break;

      case 1:     // root lub index.html
        HttpPageMain(server, client);
        break;

      case 19:    // main.css
        HttpPageMainCss(server, client);
        break;

      case 20:    // styles.css
        HttpPageStylesCss(server, client);
        break;

      // cokolwiek innego, wysyła kod strony głównej  
      default:
        HttpPageMain(server, client);
        break;
    }

}