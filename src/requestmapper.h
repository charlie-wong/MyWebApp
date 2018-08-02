#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include "httprequesthandler.h"
#include "helloworldcontroller.h"
#include "listdatacontroller.h"
#include "logincontroller.h"
#include "httpsessionstore.h"
#include "cookietestcontroller.h"
#include "unicodecontroller.h"
#include "staticfilecontroller.h"
#include "templatecache.h"
#include "datatemplatecontroller.h"
#include "logger.h"

using namespace stefanfrings;

class RequestMapper : public HttpRequestHandler
{
    Q_OBJECT
public:
    static Logger* logger;
    static HttpSessionStore* sessionStore;
    static StaticFileController* staticFileController;
    static TemplateCache* templateCache;

    RequestMapper(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);

private:
    HelloWorldController helloWorldController;
    ListDataController listDataController;
    LoginController loginController;
    CookieTestController cookieController;
    UnicodeController unicodeController;
    DataTemplateController dataTemplateController;
};

#endif // REQUESTMAPPER_H
