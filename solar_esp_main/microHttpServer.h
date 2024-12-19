/* serwer HTTP */
#pragma once
#include <stdint.h>
#include <WiFiServer.h>
#include <WiFiClient.h>


#define HTTP_DEFAULT_PORT     80
#define HTTP_READ_BUFFER_SZ   1024 

enum HTTP_MOTYW
{
    HTTP_MOTYW_BLACK = 0,
    HTTP_MOTYW_WHITE,
};



enum HTTP_METHOD
{
    HTTP_METHOD_NONE = 0,
    HTTP_METHOD_GET,
    HTTP_METHOD_POST,
    HTTP_METHOD_HEAD,
    HTTP_METHOD_PATCH,
    HTTP_METHOD_DELETE,
    HTTP_METHOD_OPTIONS,
};



class HttpServer;

struct HttpRequestHandler
{
    const char * requestUri;
    std::function<void(HttpServer* server, WiFiClient& client)> handlerFn;
};



struct Setting
{
  bool    client_UA;
  uint8_t motyw;
};


class HttpServer
{

  public:
    HttpServer();

    void SetMotyw( uint8_t n_motyw );
    void Begin();
    void Listen();
    char * GetReadData();

    uint8_t       method;
    uint8_t       request;
    struct Setting  setting;
    
  protected:
    void    ParseData(uint16_t dalalen);
    uint8_t GetRequestId( String& odebrane);
    void    BlinkLed();
  
};
