#include <QString>

#include "unicodecontroller.h"

UnicodeController::UnicodeController(QObject* parent)
    : HttpRequestHandler(parent)
{
    // empty
}

void UnicodeController::service(HttpRequest& request, HttpResponse& response)
{
    QString chinese = QString::fromUtf8("美丽的花朵需要重症监护");
    response.setHeader("Content-Type", "text/html; charset=UTF-8");
    response.write(chinese.toUtf8(),true);
}

