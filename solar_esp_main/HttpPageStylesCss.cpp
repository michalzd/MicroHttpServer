#include <sys/types.h>
#include <stdio.h>
#include <stdint.h>
#include "microHttpServer.h"


/* główne style elementów strony 
 * stałe domyślne
 */
static const char mainStyle[] = R"=====(
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
    uint len = strlen(mainStyle);
    client.printf( "HTTP/1.1 200 OK\r\nContent-type:text/css\r\nContent-Length:%i\r\nConnection: close\r\n\r\n", len);
    client.print(mainStyle);

}


/* style dynamicznie zmieniane 
 * zależnie od motywu ale też jakieś kolory elementów tak samo
 */

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
    if(server->setting.motyw==HTTP_MOTYW_WHITE) css = motywWhite;
    // tu ewentualnie zamiana 'width: 60%' na  ;width: 100%' 

    uint len = strlen(css);
    client.printf( "HTTP/1.1 200 OK\r\nContent-type:text/css\r\nContent-Length:%i\r\nConnection: close\r\n\r\n", len);
    client.print(css);
     
}
