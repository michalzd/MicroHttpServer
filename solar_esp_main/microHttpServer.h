/* serwer HTTP */
#pragma once
#include <stdint.h>
#include <WiFiServer.h>
#include <WiFiClient.h>

class HttpServer
{

  protected:
    enum HTTP_METHOD
    {
        HTTP_METHOD_NONE = 0,
        HTTP_METHOD_GET,
        HTTP_METHOD_PUT
    };

  public:
    HttpServer();

    void Begin();
    void Listen();

  protected: 
    uint8_t method;
    uint8_t request;

    bool    client_UA;

  protected:
    void ParseData(uint16_t dalalen);
    uint8_t GetRequestId( String& odebrane);
    void Response(WiFiClient& client);

    void ParseKomenda( uint8_t cmdnr);

};
