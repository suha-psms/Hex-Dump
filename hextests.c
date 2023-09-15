/* Suha Patel spate186
   Eric Alvarado ealvara6 */

// Unit tests for hex functions
// These tests should work for both your C implementations and your
// assembly language implementations

#include <stdio.h>
#include <stdlib.h>
#include "tctest.h"
#include "hexfuncs.h"

// test fixture object
typedef struct {
  char test_data_1[16];
} TestObjs;

// setup function (to create the test fixture)
TestObjs *setup(void) {
  TestObjs *objs = malloc(sizeof(TestObjs));
  strcpy(objs->test_data_1, "Hello, world!\n");
  return objs;
}

// cleanup function (to destroy the test fixture)
void cleanup(TestObjs *objs) {
  free(objs);
}

// Prototypes for test functions
void testFormatOffset(TestObjs *objs);
void testFormatByteAsHex(TestObjs *objs);
void testHexToPrintable(TestObjs *objs);
void testHexWriteStringSimple(TestObjs *objs);
void testHexWriteStringEmpty(TestObjs *objs);
void testHexWriteStringOneChar(TestObjs *objs);
void testHexWriteStringSixteenChar(TestObjs *objs);
void testHexWriteStringMoreThanSixteenChar(TestObjs *objs);
void testHexFormatOffsetZero();
void testHexFormatOffsetMax();
void testHexFormatOffsetMaxUnsigned();
void testHexFormatOffsetEmptyBuffer();
void testHexFormatByteValue0();
void testHexFormatByteValue255();
void testHexFormatByteValue16();
void testHexFormatByteValue85();
void testHexToPrintable(); 
int main(int argc, char **argv) {
  if (argc > 1) {
    tctest_testname_to_execute = argv[1];
  }

  TEST_INIT();

  TEST(testFormatOffset);
  TEST(testFormatByteAsHex);
  TEST(testHexToPrintable);
  
  //Added these manually

  TEST(testHexWriteStringSimple);
  TEST(testHexWriteStringEmpty);
  TEST(testHexWriteStringOneChar);
  TEST(testHexWriteStringSixteenChar);
  TEST(testHexWriteStringMoreThanSixteenChar);
  TEST(testHexFormatOffsetZero);
  TEST(testHexFormatOffsetMax);
  TEST(testHexFormatOffsetMaxUnsigned);
  TEST(testHexFormatOffsetEmptyBuffer);
  TEST(testHexFormatByteValue0);
  TEST(testHexFormatByteValue255);
  TEST(testHexFormatByteValue16);
  TEST(testHexFormatByteValue85);
  TEST(testHexToPrintable); 


  TEST_FINI();

  return 0;
}


void testHexWriteStringSimple(TestObjs *objs) {

  (void) objs;
  char str[] = "HI THERE";
  hex_write_string(str);
  ASSERT(strcmp(str, "HI THERE") == 0);
}

void testHexWriteStringEmpty(TestObjs *objs) {

  (void) objs;
  char str[] = "";
  hex_write_string(str);
  ASSERT(strcmp(str, "") == 0);
}


void testHexWriteStringOneChar(TestObjs *objs) {

  (void) objs;
  char str[] = "l";
  hex_write_string(str);
  ASSERT(strcmp(str, "l") == 0);
}

void testHexWriteStringSixteenChar(TestObjs *objs) {

  (void) objs;
  char str[] = "0123456789ABCDEF";
  hex_write_string(str);
  ASSERT(strcmp(str, "0123456789ABCDEF") == 0);
  }

void testHexWriteStringMoreThanSixteenChar(TestObjs *objs) {

  (void) objs;
  char str[] = "0123456789ABCDEF";
  hex_write_string(str);
  ASSERT(strcmp(str, "0123456789ABCDEF") == 0);
}

// Test with a value of 0
void testHexFormatOffsetZero() {
    char sbuf[9];
    hex_format_offset(0, sbuf);
    ASSERT(strcmp(sbuf, "00000000") == 0);
}

// Test with a value of 255
void testHexFormatOffsetMax() {
    char sbuf[9];
    hex_format_offset(0xffffffff, sbuf);
    ASSERT(strcmp(sbuf, "ffffffff") == 0);
} 

// Test with a value of 4294967295 (max 32-bit unsigned int)
void testHexFormatOffsetMaxUnsigned() {
    char sbuf[9];
    hex_format_offset(4294967295, sbuf);
    ASSERT(strcmp(sbuf, "ffffffff") == 0);
}

// Test with an empty buffer
void testHexFormatOffsetEmptyBuffer() {
  char buf[9];
  hex_format_offset(' ', buf);
  ASSERT(0 == strcmp(buf, "00000020"));
}

// Test 1: byteval is 0
void testHexFormatByteValue0() {


  char sbuf[3];
  hex_format_byte_as_hex(0, sbuf);
  ASSERT(strcmp(sbuf, "00") == 0);
  }

// Test 2: byteval is 255
void testHexFormatByteValue255() {

  char sbuf[3];
  hex_format_byte_as_hex(255, sbuf);
  ASSERT(strcmp(sbuf, "ff") == 0);

  }

// Test 3: byteval is 16
void testHexFormatByteValue16() {

  
  char sbuf[3];
  hex_format_byte_as_hex(16, sbuf);
  ASSERT(strcmp(sbuf, "10") == 0);
  
}

// Test 4: byteval is 85
void testHexFormatByteValue85() {


  char sbuf[3];
  hex_format_byte_as_hex(85, sbuf);
  ASSERT(strcmp(sbuf, "55") == 0);
}

void testFormatOffset(TestObjs *objs) {
  (void) objs; // suppress warning about unused parameter 
  char buf[16];
  hex_format_offset(0x00000001u, buf);
  ASSERT(0 == strcmp(buf, "00000001"));

  hex_format_offset(0xabcd1234u, buf);
  ASSERT(0 == strcmp(buf, "abcd1234"));
}

void testFormatByteAsHex(TestObjs *objs) {

  (void) objs;
  char buf[16];
  hex_format_byte_as_hex(objs->test_data_1[0], buf);
  ASSERT(0 == strcmp(buf, "48"));
}

void testHexToPrintable(TestObjs *objs) {

  (void) objs;
  ASSERT('H' == hex_to_printable(objs->test_data_1[0]));
  ASSERT('e' == hex_to_printable(objs->test_data_1[1]));
  ASSERT('l' == hex_to_printable(objs->test_data_1[2]));
  ASSERT('l' == hex_to_printable(objs->test_data_1[3]));
  ASSERT('o' == hex_to_printable(objs->test_data_1[4]));

  ASSERT(',' == hex_to_printable(objs->test_data_1[5]));
  ASSERT(' ' == hex_to_printable(objs->test_data_1[6]));
  ASSERT('w' == hex_to_printable(objs->test_data_1[7]));
  ASSERT('o' == hex_to_printable(objs->test_data_1[8]));
  ASSERT('r' == hex_to_printable(objs->test_data_1[9]));
  ASSERT('l' == hex_to_printable(objs->test_data_1[10]));
  ASSERT('d' == hex_to_printable(objs->test_data_1[11]));
  ASSERT('!' == hex_to_printable(objs->test_data_1[12]));
  ASSERT('.' == hex_to_printable(objs->test_data_1[13]));

}
