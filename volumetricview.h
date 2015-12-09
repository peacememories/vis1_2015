#ifndef VOLUMETRICVIEW_H
#define VOLUMETRICVIEW_H

#include <QQuickFrameBufferObject>
#include <QProgressBar>
#include <QMatrix4x4>
#include <memory>
#include "Volume.h"
#include <QVector4D>

class VolumetricView : public QQuickFramebufferObject
{
    Q_OBJECT

public:
    Q_PROPERTY(QVector3D viewDirection READ viewDirection WRITE setViewDirection)
    Q_PROPERTY(QVector3D viewPosition READ viewPosition WRITE setViewPosition)
    Q_PROPERTY(QVector4D color1 READ color1 WRITE setColor1)
    Q_PROPERTY(QVector4D color2 READ color2 WRITE setColor2)
    Q_PROPERTY(QVector4D color3 READ color3 WRITE setColor3)
    Q_PROPERTY(bool useMIP READ useMIP WRITE setUseMIP)

    VolumetricView();
    Renderer *createRenderer() const;

    unsigned int volumeId() const;
    QVector3D viewDirection() const;
    void setViewDirection(const QVector3D dir);
    QVector3D viewPosition() const;
    void setViewPosition(const QVector3D pos);
    QVector4D color1() const;
    QVector4D color2() const;
    QVector4D color3() const;
    bool useMIP() const;
    Q_INVOKABLE void setRed1(float colR);
    Q_INVOKABLE void setGreen1(float colG);
    Q_INVOKABLE void setBlue1(float colB);
    Q_INVOKABLE void setRed2(float colR);
    Q_INVOKABLE void setGreen2(float colG);
    Q_INVOKABLE void setBlue2(float colB);
    Q_INVOKABLE void setRed3(float colR);
    Q_INVOKABLE void setGreen3(float colG);
    Q_INVOKABLE void setBlue3(float colB);
    Q_INVOKABLE void setUseMIP(bool MIP);
    QSharedPointer<const Volume> volume() const;
public slots:
    void loadFile(QUrl);
signals:
    void progressValueChanged(int);
private:
     void setColor1(QVector4D col);
     void setColor2(QVector4D col);
     void setColor3(QVector4D col);
    QProgressBar m_progress;
    QSharedPointer<const Volume> m_volume;
    unsigned int m_volumeId;
    QVector3D m_viewDirection;
    QVector3D m_viewPosition;
    QVector4D m_color1;
    QVector4D m_color2;
    QVector4D m_color3;
    bool m_useMIP;
private slots:
};

#endif // VOLUMETRICVIEW_H
