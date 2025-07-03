#include "device_driver.h"
using std::vector;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
	vector<int> nums;
	getReadValueWithMaxReadCount(nums, address);
	checkReadException(nums);
	return nums[0];
}

void DeviceDriver::checkReadException(std::vector<int>& nums)
{
	for (int trycount = 1; trycount < READ_TRY_COUNT; trycount++) {
		if (nums[trycount-1] != nums[trycount]) {
			throw ReadFailException("Read Fail with exception");
		}
	}
}

void DeviceDriver::getReadValueWithMaxReadCount(std::vector<int>& nums, long address) {
	for (int trycount = 0; trycount < READ_TRY_COUNT; trycount++) {
		nums.push_back((int)(m_hardware->read(address)));
	}
}

void DeviceDriver::write(long address, int data)
{
	int readData = read(address);
	if (readData == ERASED_STATE) {
		m_hardware->write(address, (unsigned char)data);
	}
}