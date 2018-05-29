#ifndef MUMBLEPLUGIN_H
#define MUMBLEPLUGIN_H

// See: https://wiki.mumble.info/wiki/Link

#include <QObject>

struct MumblePositionAudio {
#ifdef _WIN32
    UINT32	uiVersion;
    DWORD	uiTick;
#else
    uint32_t uiVersion;
    uint32_t uiTick;
#endif
    float	fAvatarPosition[3];
    float	fAvatarFront[3];
    float	fAvatarTop[3];
    wchar_t	name[256];
    float	fCameraPosition[3];
    float	fCameraFront[3];
    float	fCameraTop[3];
    wchar_t	identity[256];
#ifdef _WIN32
    UINT32	context_len;
#else
    uint32_t context_len;
#endif
    unsigned char context[256];
    wchar_t description[2048];
};

class MumblePlugin: public QObject
{
    Q_OBJECT

public:
    explicit MumblePlugin(QObject *parent = nullptr);

public slots:
    void setPositionalAudio(double x, double y);

protected:
    MumblePositionAudio *position_ = NULL;
};


#endif // MUMBLEPLUGIN_H
