
// C implementation of hexdump functions

#include <unistd.h>  // this is the only system header file you may include!
#include "hexfuncs.h"

// Read up to 16 bytes from standard input into data_buf.
// Returns the number of characters read.
unsigned hex_read(char data_buf[]) {
   //int file_descriptor = STDIN_FILENO; // File descriptor for standard input: 0
    ssize_t count = read(0, data_buf, 16); // Read up to 16 bytes from standard input
    return count;
}

// Write given nul-terminated string to standard output.
void hex_write_string(const char s[]) { 
    ssize_t result; 
    int count = 0;
    int lessThan16 = 1;
    
    //keep reading 
    while (s[count] != '\0' && lessThan16) {
        count++;
        if (count >= 16) {
            lessThan16 = 0;
        }
    } 
   result = write(1, s,count); 
}

 

// Format an unsigned value as an offset string consisting of exactly 8
// hex digits.  The formatted offset is stored in sbuf, which must
// have enough room for a string of length 8.
void hex_format_offset(unsigned offset, char sbuf[]){ 
    const char hex_digits[] = "0123456789abcdef";
    for (int i = 7; i >= 0; i--) {
        sbuf[i] = hex_digits[offset % 16];
        offset >>= 4; // right shift by 4 moves to next hex val
    }
    sbuf[8] = '\0';// Add null terminator

}

// Format a byte value (in the range 0-255) as string consisting
// of two hex digits.  The string is stored in sbuf.
void hex_format_byte_as_hex(unsigned char byteval, char sbuf[]) {
    unsigned char ind = (byteval >> 4) & 0x0f;
    unsigned char ind_2 = byteval & 0X0f; 
    const char hex_digits[] = "0123456789abcdef";
    sbuf[0] = hex_digits[ind];
    sbuf[1] = hex_digits[ind_2];
    sbuf[2] = '\0'; // null-terminate the string

} 

// Convert a byte value (in the range 0-255) to a printable character
// value.  If byteval is already a printable character, it is returned
// unmodified.  If byteval is not a printable character, then the
// ASCII code for '.' should be returned.
char hex_to_printable(unsigned char byteval) { 

    if (byteval >= 32 && byteval <= 126) {
        // byteval is a printable character
        return (char) byteval;
    } else {
        // byteval is not a printable character
        return '.';
    }
}

