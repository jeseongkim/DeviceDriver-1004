#include "device_driver.h"
#include <stdexcept>
#include <vector>
using std::vector;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    vector<int> nums;
    for (int i = 0; i < 5; i++) {
        nums.push_back((int)(m_hardware->read(address)));
    }
    for (int i = 0; i < 4; i++) {
        if (nums[i] != nums[i + 1]) {
            throw std::runtime_error("Read Fail with exception");
        }
    }
    return nums[0];
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}