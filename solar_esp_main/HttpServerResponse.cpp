#include "HttpServerResponse.h"


void HttpPageNotFound(HttpServer* server, WiFiClient& client);
extern void HttpPageMain(HttpServer* server, WiFiClient& client);
extern void HttpPageMainCss(HttpServer* server, WiFiClient& client);
extern void HttpPageStylesCss(HttpServer *server, WiFiClient& client);



/* tutaj jest zbiór wszystkich mozliwych requestów klienta 
 * jako tablica struktur zawierających request URI, oraz handler obługi
 * index tablicy jest jednoczesnie identyfikatorem requestId
 */
const struct HttpRequestHandler  RequestHandlerList[] = 
{
 /* 0*/ {"NotFound",   HttpPageNotFound},
        { "GET / ",    HttpPageMain },     // strona ROOT  ID: 1
        { "GET /CL ",  HttpPageMain },
        { "GET /PR ",  HttpPageMain },
        { "GET /ZW ",  HttpPageMain },
        { "GET /KA ",  HttpPageMain },
        { "GET /AM ",  HttpPageMain },        
        { "GET /RX ",  HttpPageMain },        
        { "GET /DP ",  HttpPageMain },        
        { "GET /DM ",  HttpPageMain },        
/*10*/  { "GET /LOG ", HttpPageMain },        
        { "GET /IP ",  HttpPageMain },        
        { "GET /MT ",  HttpPageMain },        
        { "GET /A1 ",  HttpPageMain },        
        { "GET /A2 ",  HttpPageMain },        
        { "GET /A3 ",  HttpPageMain },        
        { "GET /A4 ",  HttpPageMain },        
        { "GET /ZA ",  HttpPageNotFound },        
        { "GET /favicon.ico ",  HttpPageNotFound },        
        { "GET /main.css ",     HttpPageMainCss },        
        { "GET /styles.css ",   HttpPageStylesCss }, 
        { "GET /cgiinfo ",      HttpPageMain }, 
        
        {nullptr, nullptr}         // koniec tablicy
};
  

static
void ParseKomenda( HttpServer* server, uint8_t requestId )
{
  //uint8_t cmdnr = requestId - 1;             // request id jest o jeden większy niz numer komendy 
  //String  readData = server->GetReadData();  // odczytane pelne dane wraz z nagłówkiem 
  // tutaj wywołanie Twojej funkcji 'komenda'  
}



void HttpServerResponse( HttpServer* server, WiFiClient& client)
{ 
    uint8_t requestId = server->request;
    
    Serial.print("reqest ID: ");
    Serial.println(requestId);
    
    ParseKomenda(server, requestId);

    // wysyłam odpowiedni kod html 
    // zgodnie z listą handlerów
    const struct HttpRequestHandler reqestHandler = RequestHandlerList[requestId];
    if (reqestHandler.handlerFn !=nullptr) reqestHandler.handlerFn(server, client);
 
}


/* handler nieistniejących stron */
void HttpPageNotFound(HttpServer* server, WiFiClient& client)
{
    static const char kodHtml[] = "<!doctype html><head><title>404 STRONA NIE ISTNIEJE</title></head><body>STRONA NIE ISTNIEJE</body></html>\r\n\r\n"; 
    uint len = sizeof(kodHtml);
    client.printf( "HTTP/1.1 404 Not Found\r\nContent-type:text/html\r\nContent-Length:%i\r\nConnection: close\r\n\r\n", len);
    client.print(kodHtml);
} 
