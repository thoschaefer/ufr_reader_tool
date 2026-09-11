#include "ufr-lib/include/uFCoder.h"
#include <cstdio>

int main()
{
    UFR_STATUS status = ReaderOpen();
    std::printf("ReaderOpen() -> %s\n", UFR_Status2String(status));
    if (status != UFR_OK)
    {
        return 1;
    }

    uint8_t off_color[3] = {0, 0, 0};
    status = SetCustomUiConfig(CUSTOM_UI_IDLE_MODE_NONE, CUSTOM_UI_DETECTED_MODE_NONE, off_color, off_color, 1);
    std::printf("SetCustomUiConfig(NONE, NONE) -> %s\n", UFR_Status2String(status));

    status = SetDisplayIntensity(0);
    std::printf("SetDisplayIntensity(0) -> %s\n", UFR_Status2String(status));

    ReaderClose();
    return 0;
}
