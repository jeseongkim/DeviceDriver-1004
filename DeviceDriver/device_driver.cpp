#include "device_driver.h"

#include <vector>
using std::vector;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    vector<int> arr;
    int ret;
    for (int i = 0; i < 5; i++) {
        ret = (int)(m_hardware->read(address));
        arr.push_back(ret);
    }
    for (int i = 0; i < 4; i++) {
        //if(arr[i] != arr[i+1]) exception
    }
    return ret;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}