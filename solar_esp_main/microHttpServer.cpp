/* serwer HTTP */
#include "microHttpServer.h"
#include "HttpServerResponse.h"
#include <stdint.h>


#define HTTP_DEFAULT_PORT     80
#define HTTP_READ_BUFFER_SZ   1024 

// uint8_t HttpServer:Command;
// uint8_t HttpServer:Url;

WiFiServer server(HTTP_DEFAULT_PORT);
char readbuf[HTTP_READ_BUFFER_SZ]; 

/* tutaj jest zbiór wszystkich mozliwych requestów klienta
 * index tablicy jest jednoczesnie identyfikatorem 
 */
const char * RequestList[] = 
{
 /* 0*/ "NOT_FOUND",
 /* 1*/ "GET / ",     // strona ROOT  ID: 1
        "GET /CL ",
        "GET /PR ",
        "GET /ZW ",
        "GET /KA ",
        "GET /AM ",  
        "GET /RX ",
        "GET /DP ",
        "GET /DM ",
/*10*/  "GET /LOG ",  
        "GET /IP ",
        "GET /MT ",
        "GET /A1 ",
        "GET /A2 ",
        "GET /A3 ",
        "GET /A4 ",
        "GET /ZA ",
        "GET /favicon.ico ",
        "GET /main.css ",     
 /*20*/ "GET /styles.css ",   
        "GET /cgiinfo ",
                  // tutaj dodajemy kolejne requesty
        nullptr         // koniec tablicy
};
  




HttpServer::HttpServer()
:method(HTTP_METHOD_NONE), request(0)
{
   this->parametr.client_UA = false;
   this->parametr.motyw = 0;
}


void HttpServer::Begin()
{
  server.begin();
}


void HttpServer::SetMotyw( uint8_t n_motyw )
{
  this->parametr.motyw = n_motyw;
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
    this->parametr.client_UA = false;
    uint8_t* buf = reinterpret_cast<uint8_t*>(readbuf);

    if (client.connected())  datalen = client.read(buf, HTTP_READ_BUFFER_SZ);
    if(datalen>0) 
    {
      if(datalen>=HTTP_READ_BUFFER_SZ) datalen = HTTP_READ_BUFFER_SZ-1;
      buf[datalen] = 0;
      ParseData(datalen);
      ParseKomenda(this->request);
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
        if (odebrane.indexOf("Android")) this->parametr.client_UA = true;
        // wykrywanie requesta
        this->request = GetRequestId(odebrane);
    }
}


uint8_t HttpServer::GetRequestId( String& odebrane)
{
    uint8_t requestId = 0;
    const char * rlist; 

    for( uint8_t i=0; ; i++)
    {
      rlist = RequestList[i];
      if(rlist==nullptr) break;
      if (odebrane.indexOf(rlist) == 0) 
      {
        requestId = i;
        break;
      }
    }
    return requestId;
}


void HttpServer::ParseKomenda( uint8_t cmdnr)
{
  --cmdnr;  // request id jest o jeden większy niz numer komendy 
  // tutaj wywołanie Twojej funkcji 'komenda'  
}

