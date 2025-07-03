#include "gmock/gmock.h"
#include "device_driver.h"

#include <string>
using std::string;
using namespace testing;

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class DeviceDriverFixture : public Test {

public:
	MockFlashMemoryDevice mockhardware;
	DeviceDriver driver{ &mockhardware };
};


TEST_F(DeviceDriverFixture, ReadFromHW_With5NormalValue) {
	EXPECT_CALL(mockhardware, read)
		.WillRepeatedly(Return(0));

	int data = driver.read(0xFF);
	EXPECT_EQ(0, data);
}

TEST_F(DeviceDriverFixture, ReadFromHW_With1Abnormal) {
	EXPECT_CALL(mockhardware, read)
		.WillOnce(Return(0))
		.WillOnce(Return(0))
		.WillOnce(Return(0))
		.WillOnce(Return(1))
		.WillOnce(Return(0));

	EXPECT_THROW(driver.read(0xFF), ReadFailException);
}




int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}