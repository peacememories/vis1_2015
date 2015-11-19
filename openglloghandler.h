#ifndef OPENGLLOGHANDLER_H
#define OPENGLLOGHANDLER_H

#include <QObject>
#include <QOpenGLDebugMessage>

class OpenGLLogHandler : public QObject
{
    Q_OBJECT
public:
    explicit OpenGLLogHandler(QObject *parent = 0);

signals:

public slots:
    void handleLoggedMessage(const QOpenGLDebugMessage&);
};

#endif // OPENGLLOGHANDLER_H
