/* serwer HTTP */
#pragma once
#include <stdint.h>
#include <WiFiServer.h>
#include <WiFiClient.h>

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




// struct HttpRequestHandler
// {
//     const char * uri;
//     uint8_t      method;
//     std::function<void(void)> HandlerFunction;
// };

struct Parametry
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

    uint8_t       method;
    uint8_t       request;
    struct Parametry  parametr;
    

  protected:
    void    ParseData(uint16_t dalalen);
    uint8_t GetRequestId( String& odebrane);
    void    BlinkLed();
   
    void ParseKomenda( uint8_t cmdnr);

};
