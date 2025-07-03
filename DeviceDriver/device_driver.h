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

    const int READ_TRY_COUNT = 5;

protected:
    FlashMemoryDevice* m_hardware;
};

class ReadFailException : public std::exception {
public:
    explicit ReadFailException(char const* Message) : std::exception{ Message } {}
    char const* what() const override {
        return "Read Fail with exception";
    }
};