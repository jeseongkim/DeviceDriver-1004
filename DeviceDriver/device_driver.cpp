#include "device_driver.h"

#include <vector>
using std::vector;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    vector<int> values;
    for (int i = 0; i < 5; i++) {
        values.push_back((int)(m_hardware->read(address)));
    }
    for (int i = 0; i < 4; i++) {
        //if(values[i] != values[i+1]) exception
    }
    return values[0];
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}