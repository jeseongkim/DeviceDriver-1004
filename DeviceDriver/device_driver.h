#pragma once
#include "flash_memory_device.h"
#include <stdexcept>
#include <vector>

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    virtual int read(long address);
    void write(long address, int data);

private:
    void checkReadException(std::vector<int>& nums);
    void getReadValueWithMaxReadCount(std::vector<int>& nums, long address);
    void checkWriteException(long address);
    const int READ_TRY_COUNT = 5;
    const int ERASED_STATE = 0xFF;

protected:
    FlashMemoryDevice* m_hardware;
};

class ReadFailException : public std::exception {};

class WriteFailException : public std::exception {};
