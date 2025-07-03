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
	NiceMock<MockFlashMemoryDevice> mockhardware;
	DeviceDriver driver{ &mockhardware };

	void setAddrErased() {
		EXPECT_CALL(mockhardware, read)
			.WillOnce(Return(ERASED_STATE))
			.WillOnce(Return(ERASED_STATE))
			.WillOnce(Return(ERASED_STATE))
			.WillOnce(Return(ERASED_STATE))
			.WillOnce(Return(ERASED_STATE));
	}

	void setAddrProgramed() {
		EXPECT_CALL(mockhardware, read)
			.WillOnce(Return(PROGRAMED_STATE))
			.WillOnce(Return(PROGRAMED_STATE))
			.WillOnce(Return(PROGRAMED_STATE))
			.WillOnce(Return(PROGRAMED_STATE))
			.WillOnce(Return(PROGRAMED_STATE));
	}

	int address = 0xAD;
	const int ERASED_STATE = 0xFF;
	const int PROGRAMED_STATE = 0xDD;
};


TEST_F(DeviceDriverFixture, ReadFromHW_With5NormalValue) {
	EXPECT_CALL(mockhardware, read)
		.WillRepeatedly(Return(0));

	int data = driver.read(address);
	EXPECT_EQ(0, data);
}

TEST_F(DeviceDriverFixture, ReadFromHW_With1Abnormal) {
	EXPECT_CALL(mockhardware, read)
		.WillOnce(Return(0))
		.WillOnce(Return(0))
		.WillOnce(Return(0))
		.WillOnce(Return(1))
		.WillOnce(Return(0));

	EXPECT_THROW(driver.read(address), ReadFailException);
}

TEST_F(DeviceDriverFixture, WriteToHwhNormally) {
	setAddrErased();

	int data = 0xDD;
	try {
		driver.write(address, 0xDD);
	}
	catch(std::exception& e){
		FAIL();
	}
}

TEST_F(DeviceDriverFixture, WriteWithException) {
	setAddrProgramed();

	int data = 0xDD;
	EXPECT_THROW(driver.write(address, data), WriteFailException);
}




int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}