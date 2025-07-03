#include "gmock/gmock.h"
#include "device_driver.h"

using namespace testing;

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};


TEST(DeviceDriver, ReadFromHW_Add0) {
	MockFlashMemoryDevice mockhardware;
	EXPECT_CALL(mockhardware, read)
		.WillRepeatedly(Return(0));
	FlashMemoryDevice* hardware = &mockhardware;

	DeviceDriver driver{ hardware };
	int data = driver.read(0xFF);
	EXPECT_EQ(0, data);
}



int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}