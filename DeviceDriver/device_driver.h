#pragma once
#include "flash_memory_device.h"
#include <stdexcept>
#include <vector>

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    virtual int read(long address);
    void read5times(std::vector<int>& nums, long address);
    void write(long address, int data);

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