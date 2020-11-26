#include <unity.h>

#include "rhio-flash.h"
namespace flash_test {

RhioFlash FLASH;

void begin_test() {
  Wire.begin();
  FLASH.beginMemory();
}

void read_manufacter_and_devide_id() {
  uint32_t jedecid;
  jedecid = FLASH.readManufacterAndDeviceID();
  TEST_ASSERT_EQUAL(526713088, jedecid);
}

void read_Block_Protection_Locked() {
  FLASH.setBlockProtectionLocked(1);
  TEST_ASSERT_EQUAL(1, FLASH.getBlockProtectionLocked());
}

void read_Write_Protect() { TEST_ASSERT_EQUAL(1, FLASH.getWriteProtect()); }

void read_Block_Protection() {
  FLASH.setBlockProtection(1);
  TEST_ASSERT_EQUAL(1, FLASH.getBlockProtection());
}

void read_Write_Enable() {
  FLASH.writeEnable();
  TEST_ASSERT_EQUAL(1, FLASH.getWriteEnable());
}

void write_and_read_byte() {
  uint8_t byte = 0xCC;
  uint32_t address = 0;
  FLASH.setBlockProtectionLocked(0);
  FLASH.setBlockProtection(0);
  FLASH.erase();
  Serial.print(FLASH.getBusyStatus());
  while (FLASH.getBusyStatus() == 1) {
  }
  FLASH.write(byte, address);

  TEST_ASSERT_EQUAL(byte, FLASH.read(address));
}

void init() {
  RUN_TEST(begin_test);
  RUN_TEST(read_manufacter_and_devide_id);
  RUN_TEST(read_Block_Protection_Locked);
  RUN_TEST(read_Block_Protection);
  RUN_TEST(read_Write_Protect);
  RUN_TEST(read_Write_Enable);
  RUN_TEST(write_and_read_byte);
}
void run() {}
}  // namespace flash_test
