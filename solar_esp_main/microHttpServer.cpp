/* serwer HTTP */
#include "microHttpServer.h"
#include "HttpServerPages.h"
#include <stdint.h>


#define HTTP_DEFAULT_PORT     80
#define HTTP_READ_BUFFER_SZ   1024
#define HTTP_WRITE_BUFFER_SZ  1024

// uint8_t HttpServer:Command;
// uint8_t HttpServer:Url;

WiFiServer server(HTTP_DEFAULT_PORT);
char readbuf[HTTP_READ_BUFFER_SZ];
char writebuf[HTTP_WRITE_BUFFER_SZ];

/* tutaj jest zbiór wszystkich mozliwych requestów klienta
 * index tablicy jest jednoczesnie identyfikatorem 
 */
const char * RequestList[] = 
{
  nullptr,
  "GET /CL",
  "GET /PR",
  "GET /ZW",
  "GET /KA",
  "GET /AM",  
  "GET /RX",
  "GET /DP",
  "GET /DM",
  "GET /LOG",
  "GET /IP",
  "GET /MT",
  "GET /A1",
  "GET /A2",
  "GET /A3",
  "GET /A4",
  "GET /ZA",
  "GET /favicon.ico",
  "GET /styles.css",
  "GET /styles.css",
  "GET /cgiinfo",
                  // tutaj dodajemy kolejne requesty
  nullptr         // koniec tablicy
};
  

HttpServer::HttpServer()
:method(HTTP_METHOD_NONE), request(0)
{
   this->client_UA = false;
}

void HttpServer::Begin()
{
  server.begin();
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
    this->client_UA = false;
    uint8_t* buf = reinterpret_cast<uint8_t*>(readbuf);

    if (client.connected())  datalen = client.read(buf, HTTP_READ_BUFFER_SZ);
    if(datalen>0) 
    {
      ParseData(datalen);
      Response(client);
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
    
    if (odebrane.indexOf("GET /")) 
    {
        this->method = HTTP_METHOD_NONE;

        // Wykrywanie klienta na smartfonie/tablecie
        if (odebrane.indexOf("Android")) this->client_UA = true;
        // wykrywanie requesta
        this->request = GetRequestId(odebrane);
    }
}


uint8_t HttpServer::GetRequestId( String& odebrane)
{
    uint8_t requestId = 0;
    const char * rlist;
    for( uint8_t i=1; ; i++)
    {
       rlist = RequestList[i];
       if(rlist==nullptr) break;
       if (odebrane.indexOf(rlist)) 
       {
          requestId = i;
          break;
       }
    }
    return requestId;
}


void HttpServer::Response(WiFiClient& client)
{
    if(this->request==0) return;

    ParseKomenda(this->request);

    // wysyłam odpowiedni kod html 
    switch (this->request) 
    {
      case 1:
        HttpPageMain(this, client);
        break;
      default:
        // page not found
        break;
    }

}


void HttpServer::ParseKomenda( uint8_t cmdnr)
{
  // tutaj wywołanie Twojej funkcji 'komenda'  
}

