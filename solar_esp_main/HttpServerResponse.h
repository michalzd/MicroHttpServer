#pragma once
#include "microHttpServer.h"

extern const struct HttpRequestHandler  RequestHandlerList[];
extern void HttpServerResponse(HttpServer* server, WiFiClient& client);
