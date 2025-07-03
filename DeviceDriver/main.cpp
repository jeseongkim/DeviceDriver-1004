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


TEST(DeviceDriver, ReadFromHW_With5NormalValue) {
	MockFlashMemoryDevice mockhardware;
	EXPECT_CALL(mockhardware, read)
		.WillRepeatedly(Return(0));
	FlashMemoryDevice* hardware = &mockhardware;

	DeviceDriver driver{ hardware };
	int data = driver.read(0xFF);
	EXPECT_EQ(0, data);
}

TEST(DeviceDriver, ReadFromHW_With1Abnormal) {
	MockFlashMemoryDevice mockhardware;
	EXPECT_CALL(mockhardware, read)
		.WillOnce(Return(0))
		.WillOnce(Return(0))
		.WillOnce(Return(0))
		.WillOnce(Return(1))
		.WillOnce(Return(0));
	FlashMemoryDevice* hardware = &mockhardware;

	DeviceDriver driver{ hardware };
	try {
		int data = driver.read(0xFF);
		EXPECT_EQ(0, data);
		FAIL(); //Exception이 발생할 예정이기에, FAIL() 함수에 도달하지 않는다.
	}
	catch (ReadFailException& e) {
		//assert
		EXPECT_EQ(string{ e.what() }, string{ "Read Fail with exception" });
	}
	catch (std::runtime_error& e) {
	}

}




int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}