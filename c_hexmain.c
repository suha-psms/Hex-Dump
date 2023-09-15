/* Suha Patel spate186
   Eric Alvarado ealvara6 */

#include "hexfuncs.h" 

int main(void) {
  char buf[17] = ""; // Buffer to hold the hexadecimal data
  unsigned num_chars; // Number of characters read from input
  unsigned position = 0; // Current offset position in the input file
  char offset_buf[9] = ""; // Buffer to hold the offset as a hexadecimal string

  do {
    // Read up to 16 hexadecimal characters from the input file
    num_chars = hex_read(buf);

    if(num_chars > 0) {

      // Convert the current offset to a hexadecimal string
      hex_format_offset(position, offset_buf);
      hex_write_string(offset_buf);

      // Update the offset for the next iteration
      position += 16;
        
      // Print a separator between the offset and the data
      hex_write_string(": ");

      // Print the data as a sequence of 2-digit hexadecimal numbers
      char sbuf[3] = ""; // Buffer to hold a 2-digit hexadecimal number and a space
      for(int i = 0; i < 16; i++){
        if(i < num_chars){ 
          // Convert the current byte to a 2-digit hexadecimal number
          hex_format_byte_as_hex((buf[i]), sbuf);
          hex_write_string(sbuf); // Print the number and a space
          hex_write_string(" ");
        } else { // Pad with spaces if there is no more data
          hex_write_string("   ");
        }
      }
        
      // Print a separator between the data and the ASCII representation
      hex_write_string(" ");

      // Print the data as ASCII characters, replacing non-printable characters with a dot
      char print[17] = "";
      for(int j = 0; j < num_chars; j++){
        print[j] = hex_to_printable(buf[j]);
   
      }

      //PRINT NEW BUFFER
      hex_write_string(print);

      // Print a newline character to separate each line of output
      hex_write_string("\n");


    }
  } while (num_chars > 0);

  for (int i = 0; i < 17; i++) {
    buf[i] = '\0';
  }

  for (int i = 0; i < 9; i++) {
    offset_buf[i] = '\0';
  }


  // End of program
  return 0;
}
