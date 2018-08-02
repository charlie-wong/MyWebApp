#include <QCoreApplication>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QString>

#include "httplistener.h"
#include "requestmapper.h"
#include "filelogger.h"

using namespace stefanfrings;

/// Search the configuration file.
/// Aborts the application if not found.
///
/// @return The valid filename
QString searchConfigFile()
{
    QString binDir = QCoreApplication::applicationDirPath();
    QString appName = QCoreApplication::applicationName();

    QFile file;
    file.setFileName(binDir + "/webapp.ini");
    if(!file.exists())
    {
        file.setFileName(binDir + "/etc/webapp.ini");
        if(!file.exists())
        {
            file.setFileName(binDir + "/../etc/webapp.ini");
            if(!file.exists())
            {
                file.setFileName(binDir + "/../" + appName + "/etc/webapp.ini");
                if(!file.exists())
                {
                    file.setFileName(binDir + "/../../" + appName + "/etc/webapp.ini");
                    if(!file.exists())
                    {
                        file.setFileName(binDir + "/../../../" + appName+"/etc/webapp.ini");
                        if(!file.exists())
                        {
                            file.setFileName(QDir::rootPath() + "etc/webapp.ini");
                        }
                    }
                }
            }
        }
    }

    if(file.exists())
    {
        QString configFileName=QDir(file.fileName()).canonicalPath();
        qDebug("using config file %s", qPrintable(configFileName));
        return configFileName;
    }
    else
    {
        qFatal("config file not found");
    }
}

static void startHttpListener(QCoreApplication *app, QString &configFileName)
{
    // HTTP server
    QSettings* listenerSettings =
        new QSettings(configFileName, QSettings::IniFormat, app);
    listenerSettings->beginGroup("listener-http");

    // Start the HTTP server
    new HttpListener(listenerSettings, new RequestMapper(app), app);
}

static void startHttpsListener(QCoreApplication *app, QString &configFileName)
{
    // HTTPs server
    QSettings* listenerSettings =
        new QSettings(configFileName, QSettings::IniFormat, app);
    listenerSettings->beginGroup("listener-https");

    // Start the HTTPs server
    new HttpListener(listenerSettings, new RequestMapper(app), app);
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Load the configuration file
    QString configFileName = searchConfigFile();

    // Configure logging
    QSettings* logSettings =
        new QSettings(configFileName, QSettings::IniFormat, &app);
    logSettings->beginGroup("logging");
    RequestMapper::logger = new FileLogger(logSettings, 10000, &app);
    RequestMapper::logger->installMsgHandler();

    // Log the library version
    qDebug("QtWebApp has version %s", getQtWebAppLibVersion());

    // Session store
    QSettings* sessionSettings =
        new QSettings(configFileName, QSettings::IniFormat, &app);
    sessionSettings->beginGroup("sessions");
    RequestMapper::sessionStore =
        new HttpSessionStore(sessionSettings, &app);

    // Static file controller
    QSettings* fileSettings =
        new QSettings(configFileName, QSettings::IniFormat, &app);
    fileSettings->beginGroup("files");
    RequestMapper::staticFileController =
        new StaticFileController(fileSettings, &app);

    // Configure template cache
    QSettings* templateSettings =
        new QSettings(configFileName,QSettings::IniFormat,&app);
    templateSettings->beginGroup("templates");
    RequestMapper::templateCache =
        new TemplateCache(templateSettings,&app);

    startHttpListener(&app, configFileName);
    startHttpsListener(&app, configFileName);

    return app.exec();
}
