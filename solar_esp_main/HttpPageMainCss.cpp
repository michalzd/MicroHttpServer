#include <sys/types.h>
#include <stdio.h>
#include <stdint.h>
#include "microHttpServer.h"


static const char kodHtml[] = R"=====(
p.c10 {text-align: center;}
table {border-collapse: collapse; margin-left: auto; margin-right: auto;}
td.c8 {width: 13%;}
td.c7 {width: 9%;}
td.c6 {width: 15%;}
td.c5 {width: 13%; text-align: center;}
td.c4 {width: 6%; text-align: center;}
td.c3 {width: 13%; text-align: center;}
td.c2 {width: 20%; text-align: center;}
td.c1 {width: 45%; text-align: center;}
)=====";


void HttpPageMainCss(HttpServer *server, WiFiClient& client)
{
    uint len = sizeof(kodHtml);
    client.printf( "HTTP/1.1 200 OK\r\nContent-type:text/css\r\nContent-Length:%i\r\nConnection: close\r\n\r\n", len);
    client.print(kodHtml);

}
