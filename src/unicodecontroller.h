#ifndef UNICODECONTROLLER_H
#define UNICODECONTROLLER_H

#include "httprequesthandler.h"

using namespace stefanfrings;

class UnicodeController : public HttpRequestHandler
{
    Q_OBJECT
public:
    UnicodeController(QObject* parent = 0);
    void service(HttpRequest &request, HttpResponse &response);
};

#endif // UNICODECONTROLLER_H
