/* serwer HTTP */
#include "microHttpServer.h"
#include "HttpServerResponse.h"
#include <stdint.h>


// uint8_t HttpServer:Command;
// uint8_t HttpServer:Url;

WiFiServer server(HTTP_DEFAULT_PORT);
char readbuf[HTTP_READ_BUFFER_SZ]; 


HttpServer::HttpServer()
:method(HTTP_METHOD_NONE), request(0)
{
   this->setting.client_UA = false;
   this->setting.motyw = 0;
}


void HttpServer::Begin()
{
  server.begin();
}


void HttpServer::SetMotyw( uint8_t n_motyw )
{
  this->setting.motyw = n_motyw;
}


void HttpServer::BlinkLed()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
}


// listen for incoming clients
void HttpServer::Listen()
{
  int datalen;

  WiFiClient client = server.accept();
  if (client) 
  {
    //Serial.println("Connected to client");
    datalen = 0;
    this->method = HTTP_METHOD_NONE;
    this->request = 0;
    this->setting.client_UA = false;
    uint8_t* buf = reinterpret_cast<uint8_t*>(readbuf);

    if (client.connected())  datalen = client.read(buf, HTTP_READ_BUFFER_SZ);
    if(datalen>0) 
    {
      if(datalen>=HTTP_READ_BUFFER_SZ) datalen = HTTP_READ_BUFFER_SZ-1;
      buf[datalen] = 0;
      ParseData(datalen);
      HttpServerResponse(this, client);  
      BlinkLed();
    }
    client.stop();
  }
}

/* Rozpoznawanie metody http oraz request url
 * metody: GET / PUT / HEAD / DELETE / POST
 */
void HttpServer::ParseData(uint16_t dalalen)
{
    String odebrane = readbuf;
    
    Serial.println();
    Serial.print("data ");
    Serial.println(dalalen);
    Serial.println(readbuf);
    
    if (odebrane.indexOf("GET ") == 0) 
    {
        this->method = HTTP_METHOD_GET;

        // Wykrywanie klienta na smartfonie/tablecie
        if (odebrane.indexOf("Android")) this->setting.client_UA = true;
        // wykrywanie requesta
        this->request = GetRequestId(odebrane);
    }
}


uint8_t HttpServer::GetRequestId( String& odebrane)
{
    uint8_t requestId = 0;
    const char * requri; 

    for( uint8_t i=0; ; i++)
    {
      requri = RequestHandlerList[i].requestUri;
      if(requri==nullptr) break;
      if (odebrane.indexOf(requri) == 0) 
      {
        requestId = i;
        break;
      }
    }
    return requestId;
}


char * HttpServer::GetReadData()
{
    return readbuf;
}


