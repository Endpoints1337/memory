#include <Windows.h>
#include <iostream>

int main()
{
    DWORD pid = 1234; // replace with actual process ID
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!processHandle)
    {
        std::cerr << "Error: Unable to open process with ID " << pid << std::endl;
        return 1;
    }

    // Read memory
    int address = 0x12345678; // replace with actual address to read
    int value = 0;
    SIZE_T bytesRead = 0;
    BOOL success = ReadProcessMemory(processHandle, (LPVOID)address, &value, sizeof(value), &bytesRead);
    if (!success || bytesRead != sizeof(value))
    {
        std::cerr << "Error: Unable to read memory at address " << std::hex << address << std::endl;
        CloseHandle(processHandle);
        return 1;
    }
    std::cout << "Value at address " << std::hex << address << ": " << value << std::endl;

    // Write memory
    int newValue = 12345; // replace with actual value to write
    SIZE_T bytesWritten = 0;
    success = WriteProcessMemory(processHandle, (LPVOID)address, &newValue, sizeof(newValue), &bytesWritten);
    if (!success || bytesWritten != sizeof(newValue))
    {
        std::cerr << "Error: Unable to write memory at address " << std::hex << address << std::endl;
        CloseHandle(processHandle);
        return 1;
    }
    std::cout << "New value at address " << std::hex << address << ": " << newValue << std::endl;

    CloseHandle(processHandle);
    return 0;
}
