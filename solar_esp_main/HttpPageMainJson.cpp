#include <sys/types.h>
#include <stdio.h>
#include <stdint.h>
#include "microHttpServer.h"

/* przykładowy json z wartościami  oraz stylami dla elementów tabeli
 * to oczywiście trzeba zbudować dymanicznie
 * to wyłącznie test
 */
static const char json[] = R"=====({
  ev:{'C2R03':'123,3', 'C3R03':'125,0', 'C6R03':'111', 'C8R03':'192.168.1.123', 'C2R04':'8,2'}, 
  style:{'C3R03':'color:red;'} 
} )=====";


void HttpPageMainCgi(HttpServer *server, WiFiClient& client)
{
    uint len = strlen(json);
    
    Serial.print("Content-Length:");
    Serial.println(len);

    client.printf( "HTTP/1.1 200 OK\r\nContent-type:application/json; charset=utf-8\r\nContent-Length:%i\r\nConnection: close\r\n\r\n", len);
    client.print(json);

}
