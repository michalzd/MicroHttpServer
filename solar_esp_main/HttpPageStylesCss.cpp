#include <sys/types.h>
#include <stdio.h>
#include <stdint.h>
#include "microHttpServer.h"

static const char motywBlack[] = R"=====(
body { background-color: black; color: green;} 
table.c9 {width: 60%;}
)=====";

static const char motywWhite[] = R"=====(
body { background-color: white; color: green;} 
table.c9 {width: 60%;}
)=====";


void HttpPageStylesCss(HttpServer *server, WiFiClient& client)
{
    const char* css = motywBlack;
    if(server->parametr.motyw==HTTP_MOTYW_WHITE) css = motywWhite;
    // tu ewentualnie zamiana 'width: 60%' na  ;width: 100%' 

    uint len = sizeof(css);
    client.printf( "HTTP/1.1 200 OK\r\nContent-type:text/css\r\nContent-Length:%i\r\nConnection: close\r\n\r\n", len);
    client.print(css);
     
}
