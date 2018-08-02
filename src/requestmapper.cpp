#include "requestmapper.h"

Logger* RequestMapper::logger = nullptr;
TemplateCache* RequestMapper::templateCache = nullptr;
HttpSessionStore* RequestMapper::sessionStore = nullptr;
StaticFileController* RequestMapper::staticFileController = nullptr;

RequestMapper::RequestMapper(QObject* parent)
    : HttpRequestHandler(parent)
{
    // empty
}

void RequestMapper::service(HttpRequest& request, HttpResponse& response)
{
    qInfo("RequestMapper:   path=%s", request.getPath().data());
    qInfo("RequestMapper: method=%s", request.getMethod().data());
    qInfo("RequestMapper: length=%s", request.getHeader("Content-Length").data());
    qInfo("RequestMapper:   body=\n%s", request.getBody().data());

    QByteArray path = request.getPath();
    HttpSession session = sessionStore->getSession(request, response, false);
    QString username = session.get("username").toString();
    logger->set("currentUser", username);

#if 0
    QByteArray sessionId = sessionStore->getSessionId(request, response);
    if(sessionId.isEmpty() && path != "/login")
    {
        qDebug("RequestMapper: redirect to login page");
        response.redirect("/login");
        return;
    }
#endif

    if(path=="/" || path=="/hello")
    {
        helloWorldController.service(request, response);
    }
    else if(path=="/list")
    {
        listDataController.service(request, response);
    }
    else if(path=="/login")
    {
        loginController.service(request, response);
    }
    else if(path=="/cookie")
    {
        cookieController.service(request, response);
    }
    else if(path.startsWith("/files"))
    {
        staticFileController->service(request,response);
    }
    else if(path=="/chinese")
    {
        unicodeController.service(request, response);
    }
    else if(path=="/template")
    {
        dataTemplateController.service(request, response);
    }
    else if(path=="/read_iaq")
    {
        helloWorldController.service(request, response);
    }
    else
    {
        response.setStatus(404, "Not found");
        response.write("The URL is wrong, no such document.");
    }

    qDebug("RequestMapper: finished request");
}

