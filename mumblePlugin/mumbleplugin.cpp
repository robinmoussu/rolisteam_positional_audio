#include "mumbleplugin.h"

#include <iostream>
#include <cstring> // for memcpy

#ifdef _WIN32
#   include <windows.h>
#else
#   include <fcntl.h> /* For O_* constants */
#   include <sys/mman.h>
#   include <sys/stat.h> /* For mode constants */
#   include <sys/types.h>
#   include <unistd.h>
#endif // _WIN32

using namespace std;

MumblePlugin::MumblePlugin(QObject *parent) :
    QObject(parent)
{
#ifdef _WIN32
    HANDLE hMapObject = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"MumbleLink");
    if (hMapObject == NULL)
        return;
    position_ = (MumblePositionAudio *) MapViewOfFile(hMapObject, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(MumblePositionAudio));
    if (position_ == NULL) {
        CloseHandle(hMapObject);
        hMapObject = NULL;
        return;
    }
#else
    char memname[256];
    snprintf(memname, 256, "/MumbleLink.%d", getuid());
    int shmfd = shm_open(memname, O_RDWR, S_IRUSR | S_IWUSR);
    if (shmfd < 0) {
        return;
    }
    position_ = (MumblePositionAudio *)(mmap(NULL, sizeof(struct MumblePositionAudio), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd,0));
    if (position_ == (void *)(-1)) {
        position_ = NULL;
        return;
    }
#endif
}

void MumblePlugin::setPositionalAudio(double x, double y)
{
    cout << "x: " << x << ", y: " << y << endl;

    if (! position_)
        return;

    if(position_->uiVersion != 2) {
        wcsncpy(position_->name, L"TestLink", 256);
        wcsncpy(position_->description, L"TestLink is a test of the Link plugin.", 2048);
        position_->uiVersion = 2;
    }

    position_->uiTick++;

    // Left handed coordinate system.
    // X positive towards "right".
    // Y positive towards "up".
    // Z positive towards "front".
    //
    // 1 unit = 1 meter

    // Unit vector pointing out of the avatar's eyes aka "At"-vector.
    position_->fAvatarFront[0] = 1000.0f;
    position_->fAvatarFront[1] = 1000.0f;
    position_->fAvatarFront[2] = 1000.0f;

    // Unit vector pointing out of the top of the avatar's head aka "Up"-vector (here Top points straight up).
    position_->fAvatarTop[0] = 1000.0f;
    position_->fAvatarTop[1] = 1000.0f;
    position_->fAvatarTop[2] = 1000.0f;

    // Position of the avatar (here standing slightly off the origin)
    position_->fAvatarPosition[0] = 1000.001f;
    position_->fAvatarPosition[1] = 1000.0f;
    position_->fAvatarPosition[2] = 1000.5f;

    // Same as avatar but for the camera.
    position_->fCameraPosition[0] = 0.0f;
    position_->fCameraPosition[1] = 0.0f;
    position_->fCameraPosition[2] = 0.0f;

    position_->fCameraFront[0] = 0.0f;
    position_->fCameraFront[1] = 0.0f;
    position_->fCameraFront[2] = 1.0f;

    position_->fCameraTop[0] = 0.0f;
    position_->fCameraTop[1] = 1.0f;
    position_->fCameraTop[2] = 0.0f;

    // Identifier which uniquely identifies a certain player in a context (e.g. the ingame name).
    wcsncpy(position_->identity, L"Robin", 256);
    // Context should be equal for players which should be able to hear each other positional and
    // differ for those who shouldn't (e.g. it could contain the server+port and team)
    const char ctx[] = "1";
    cout << "ctx: " << ctx << ", size: " << sizeof(ctx) << endl;
    std::memcpy(position_->context, ctx, sizeof(ctx));
    position_->context_len = 16;
}
