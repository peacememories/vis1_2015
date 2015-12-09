#include "volumetricrenderer.h"
#include "volumetricview.h"

VolumetricView::VolumetricView()
{
    m_viewDirection = QVector3D(0,3,3);
    m_viewPosition = QVector3D(0, 0, 0);
    m_color1 = QVector4D(1.0, 0.0, 1.0, 1.0);
}

QQuickFramebufferObject::Renderer *VolumetricView::createRenderer() const
{
    return new VolumetricRenderer;
}

unsigned int VolumetricView::volumeId() const
{
    return m_volumeId;
}

QVector3D VolumetricView::viewDirection() const
{
    return m_viewDirection;
}

void VolumetricView::setViewDirection(const QVector3D dir)
{
    m_viewDirection = dir;
    update();
}

QVector3D VolumetricView::viewPosition() const
{
    return m_viewPosition;
}
void VolumetricView::setViewPosition(const QVector3D pos)
{
    m_viewPosition = pos;
    update();
}

QVector4D VolumetricView::color1() const
{
    return m_color1;
}

void VolumetricView::setColor1(QVector4D col)
{
         m_color1 = col;
         update();
}

void  VolumetricView::setRed1(float colR)
{
         m_color1.setX(colR);
         setColor1(m_color1);
}

void  VolumetricView::setGreen1(float colG)
{
    m_color1.setY(colG);
    setColor1(m_color1);
}

void  VolumetricView::setBlue1(float colB)
{
    m_color1.setZ(colB);
    setColor1(m_color1);
}

QVector4D VolumetricView::color2() const
{
    return m_color2;
}

void VolumetricView::setColor2(QVector4D col)
{
         m_color2 = col;
         update();
}

void  VolumetricView::setRed2(float colR)
{
         m_color2.setX(colR);
         setColor2(m_color2);
}

void  VolumetricView::setGreen2(float colG)
{
    m_color2.setY(colG);
    setColor2(m_color2);
}

void  VolumetricView::setBlue2(float colB)
{
    m_color2.setZ(colB);
    setColor2(m_color2);
}

QVector4D VolumetricView::color3() const
{
    return m_color3;
}

void VolumetricView::setColor3(QVector4D col)
{
         m_color3 = col;
         update();
}

void  VolumetricView::setRed3(float colR)
{
         m_color3.setX(colR);
         setColor3(m_color3);
}

void  VolumetricView::setGreen3(float colG)
{
    m_color3.setY(colG);
    setColor3(m_color3);
}

void  VolumetricView::setBlue3(float colB)
{
    m_color3.setZ(colB);
    setColor3(m_color3);
}

void VolumetricView::setUseMIP(bool MIP)
{
    m_useMIP = MIP;
    update();
}

bool VolumetricView::useMIP() const
{
    return m_useMIP;
}

QSharedPointer<const Volume> VolumetricView::volume() const
{
    return m_volume;
}

void VolumetricView::loadFile(QUrl url)
{
    QSharedPointer<Volume> newVolume(new Volume);
    newVolume->loadFromFile(url.toLocalFile(), &m_progress);
    m_volume = newVolume;
    m_volumeId = qrand();
    update();
}

