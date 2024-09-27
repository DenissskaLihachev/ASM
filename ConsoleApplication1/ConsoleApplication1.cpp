#include <windows.h>
#include <stdio.h>

int main(void)
{
    HANDLE std_handle, screen_buffer_handle;
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info{};
    //CHAR_INFO chiBuffer[160];
    CHAR_INFO* screen_buffer;
    COORD screen_buffer_pos{};
    int screen_buffer_size;
    BOOL fSuccess;


    std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    screen_buffer_handle = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ |FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
    if (std_handle == INVALID_HANDLE_VALUE ||
        screen_buffer_handle == INVALID_HANDLE_VALUE)
    {
        printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
        return 1;
    }


    if (!SetConsoleActiveScreenBuffer(screen_buffer_handle))
    {
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
        return 1;
    }


    if (!GetConsoleScreenBufferInfo(screen_buffer_handle, &screen_buffer_info))
    {
        printf("GetConsoleScreenBufferInfo failed - (%d)\n", GetLastError());
        return 1;
    }

    screen_buffer_size = (int)screen_buffer_info.dwSize.X * (int)screen_buffer_info.dwSize.Y;
    screen_buffer = new CHAR_INFO[screen_buffer_size];
    memset(screen_buffer, 0, screen_buffer_size * sizeof(CHAR_INFO));


    screen_buffer[0].Char.UnicodeChar = L'W';
    screen_buffer[0].Attributes = 0x50;

    fSuccess = WriteConsoleOutput(screen_buffer_handle,screen_buffer, screen_buffer_info.dwSize, screen_buffer_pos,&screen_buffer_info.srWindow);  
    if (!fSuccess)
    {
        printf("WriteConsoleOutput failed - (%d)\n", GetLastError());
        return 1;
    }
    Sleep(5000);


    if (!SetConsoleActiveScreenBuffer(std_handle))
    {
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
        return 1;
    }

    return 0;
}