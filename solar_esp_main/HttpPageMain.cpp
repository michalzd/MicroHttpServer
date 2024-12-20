#include <sys/types.h>
#include <stdio.h>
#include <stdint.h>
#include "microHttpServer.h"


static const char kodHtml[] = R"=====(<!DOCTYPE html><html lang="pl" xmlns="http://www.w3.org/1999/xhtml" xml:lang="pl">
<head>
<title>Regulator PWM</title>
<meta http-equiv='content-type' content='text/html; charset=utf-8'>
<link rel='stylesheet' type='text/css' href='styles.css' />
<link rel='stylesheet' type='text/css' href='main.css' />
<script type="text/javascript" src="/xhr.js"></script>
</head>
<body onload='init();'>
<script type='text/javascript'>
function init() { XHR.poll(60,'/cgiinfo', '', axResponse ); }
function axResponse(x, json)
{ 
  if(json.ev) Object.keys(json.ev).forEach( function(id)
    { 
      var e=document.getElementById(id);  
      if(e) e.innerText=json.ev[id];         
    } ); 
  if(json.style) Object.keys(json.style).forEach( function(id)
    { 
      var e=document.getElementById(id);  
      if(e) e.style=json.style[id];         
    } ); 
} 
</script>
<table class='c9' border='1'>
<tbody>
<tr>
<td class='c1' colspan='4'><b>Pomiary</b></td>
<td class='c2' colspan='2'><b>Przebieg funkcji</b></td>
<td class='c2' colspan='2'><a title='Motyw' href='/MT'><b>Konfiguracja</b></a></td>
</tr>
<tr>
<td class='c3'><b>Parametr</b></td>
<td class='c4'><b>Pomiar</b></td>
<td class='c4'><a title='Zerowanie' href='/CL'><b>Max.</b></a></td>
<td class='c4'><b>Min.</b></td>
<td class='c4'><b>Funkcja</b></td>
<td class='c4'><b>ms/(N)OK</b></td>
<td class='c5'><b>Parametr</b></td>
<td class='c5'><b>Wartość</b></td>
</tr>
<tr>
<td class='c6'>Napięcie paneli [V]</td>
<td class='c4' id='C2R03'>C2R03</td>
<td class='c4' id='C3R03'>C3R03</td>
<td class='c4'></td>
<td class='c7'>pomiary()</td>
<td class='c4' id='C6R03'>C6R03</td>
<td class='c8'><a title='Zmiana IP' href='/IP'>Adres IP</a></td>
<td class='c5' id='C8R03'>C8R03</td>
</tr> 
<tr>
<td class='c6'>Prąd paneli [A]</td>
<td class='c4' id='C2R04'>C2R04</td>
<td class='c4' id='C3R04'>C3R04</td>
<td class='c4'></td>
<td class='c7'>serwer()</td>
<td class='c4' id='C6R04'>C6R04</td>
<td class='c8'>Firmware</td>
<td class='c5' id='C8R04'>C8R04</td>
</tr>
<tr>
<td class='c6'>Prąd wyjściowy [A]</td>
<td class='c4' id='C2R05'>C2R05</td>
<td class='c4' id='C3R05'>C3R05</td>
<td class='c4'></td>
<td class='c7'><a title='Zał/Wył' href='/ZA'>zapis()</a></td>
<td class='c4' id='C6R05'>C6R05</td>
<td class='c8'>Restart</td>
<td class='c5' id='C8R05'>C8R05</td>
</tr>
<tr>
<td class='c6'>Moc [W]</td>
<td class='c4' id='C2R06'>C2R06</td>
<td class='c4' id='C3R06'>C3R06</td>
<td class='c4'></td>
<td class='c7'>temperatura()</td>
<td class='c4' id='C6R06'>C6R06</td>
<td class='c8'><a title='Zmiana trybu' href='/AM'>Tryb</a>&nbsp;[Auto/Man]</td>
<td class='c5' id='C8R06'>C8R06</td>
</tr>
<tr>
<td class='c6'>Watogodziny [Wh]</td>
<td class='c4' id='C2R07'>C2R07</td>
<td class='c4'></td>
<td class='c4'></td>
<td class='c7'>rtc_alarm_chk()</td>
<td class='c4' id='C6R07'>C6R07</td>
<td class='c8'><a title='Zmiana Rx' href='/RX'>Rx</a>&nbsp;[Ω]</td>
<td class='c5' id='C8R07'>C8R07</td>
</tr>
<tr>
<td class='c6'>Wsp. wyp. [0-256]</td>
<td class='c4' id='C2R08'>C2R08</td>
<td class='c4'><a title='Przerwa' href='/PR'>Przerwa</a></td>
<td class='c4'><a title='Zwarcie' href='/ZW'>Zwarcie</a></td>
<td class='c7'>czas_ntp()</td>
<td class='c4'>--</td>
<td class='c8'>HPWR [W]</td>
<td class='c5' id='C8R08'>C8R08</td>
</tr>
<tr>
<td class='c6'>Wsp.wyp. [%]</td>
<td class='c4'>C2R09</td>
<td class='c4'><a href='/DP'>DT+</a></td>
<td class='c4'><a href='/DM'>DT-</a></td>
<td class='c7'></td>
<td class='c4'></td>
<td class='c8'>SPWR [W]</td>
<td class='c5' id='C8R09'>C8R09</td>
</tr>
<tr>
<td class='c6'>Napięcie ACS [V]</td>
<td class='c4' id='C2R10'>C2R10</td>
<td class='c4'></td>
<td class='c4'></td>
<td class='c7'></td>
<td class='c4'></td>
<td class='c8'>MINPVU [V]</td>
<td class='c5' id='C8R10'>C8R10</td>
</tr>
<tr>
<td class='c6'><a title='Rekalibracja' href='/KA'>Napięcie kalibracji</a>&nbsp;[V]</td>
<td class='c4'>C2R11</td>
<td class='c4'></td>
<td class='c4'></td>
<td class='c7'></td>
<td class='c4'></td>
<td class='c8'>MAX_WINDLIMIT_PWR [W]</td>
<td class='c5' id='C8R11'>C8R11</td>
</tr>
<tr>
<td class='c6'>Radiator [°C]</td>
<td class='c4' id='C2R12'>C2R12</td>
<td class='c4' id='C3R12'>C3R12</td>
<td class='c4'></td>
<td class='c2' colspan='2'><b>Alarmy RTC</b></td>
<td class='c8'>MIN_WINDLIMIT_PWR [W]</td>
<td class='c5' id='C8R12'>C8R12</td>
</tr>
<tr>
<td class='c6'>Kaloryfer [°C]</td>
<td class='c4' id='C2R13'>C2R13</td>
<td class='c4' id='C3R13'>C3R13</td>
<td class='c4'></td>
<td class='c7'><a title='Zał/Wył' href='/A1'>RTC_ALARM_1</a></td>
<td class='c4' id='C6R13'>C6R13</td>
<td class='c8'>MAX_WINDLIMIT_U [V]</td>
<td class='c5' id='C8R13'>C8R13</td>
</tr>
<tr>
<td class='c6'>Czas RTC</td>
<td class='c4' id='C2R14'>C2R14</td>
<td class='c4'></td>
<td class='c4'></td>
<td class='c7'><a title='Zał/Wył' href='/A2'>RTC_ALARM_2</a></td>
<td class='c4' id='C6R14'>C6R14</td>
<td class='c8'>MIN_WINDLIMIT_U [V]</td>
<td class='c5' id='C8R14'>C8R14</td>
</tr>
<tr>
<td class='c6'></td>
<td class='c4'></td>
<td class='c4'></td>
<td class='c4'></td>
<td class='c7'><a title='Zał/Wył' href='/A3'>RTC_ALARM_3</a></td>
<td class='c4' id='C6R15'>C6R15</td>
<td class='c8'>MAXTEMP [T1/T2]</td>
<td class='c5' id='C8R15'>C8R15</td>
</tr>
<tr>
<td class='c6'></td>
<td class='c4'></td>
<td class='c4'></td>
<td class='c4'></td>
<td class='c7'><a title='Zał/Wył' href='/A4'>RTC_ALARM_4</a></td>
<td class='c4' id='C6R16'>C6R16</td>
<td class='c8'></td>
<td class='c5'></td>
</tr>
</tbody>
</table>
</body>
</html>

)=====";


void HttpPageMain(HttpServer *server, WiFiClient& client)
{
    uint len = strlen(kodHtml);
    
    Serial.print("Content-Length:");
    Serial.println(len);

    client.printf( "HTTP/1.1 200 OK\r\nContent-type:text/html\r\nContent-Length:%i\r\nConnection: close\r\n\r\n", len);
    client.print(kodHtml);

}
