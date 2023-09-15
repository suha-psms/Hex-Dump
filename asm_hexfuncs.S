/* Suha Patel spate186
   Eric Alvarado ealvara6 */
   
/* Assembly language implementation of hexdump functions */

.section .rodata


/* TODO: add read-only data such as strings here */
string:
.string "0123456789abcdef"


.section .text

/* TODO: add functions here */

# Define the function and its name
.globl hex_to_printable
hex_to_printable:
//save the previous frame pointer and set up the new one
pushq %rbp
movq %rsp, %rbp

//Align the stack pointer to a 16-byte boundary
subq $8, %rsp

// Set up registers with the range of valid characters
movb $32, %r12b // lower bound (32 is the ASCII code for ' ')
movb $126, %r10b // upper bound (126 is the ASCII code for '~')

//Check if the input value is within the valid range
cmpb %r12b, %dil // compare input value with lower bound
jb .Lless // jump to .less if input value is less than lower bound
cmpb %r10b, %dil // compare input value with upper bound
ja .Lless // jump to .less if input value is greater than upper bound


movb %dil, %al // Convert the input value to a printable character


addq $8, %rsp // restore the stack pointer
popq %rbp //restore the previous frame pointer
ret // return the result

# If the input value is outside the valid range, return a period character
.Lless:
movb $46, %al // move the ASCII code for '.' to %al register
addq $8, %rsp //  restore the stack pointer
popq %rbp // restore the previous frame pointer
ret // return the result


.globl hex_format_byte_as_hex
hex_format_byte_as_hex:
subq $8, %rsp   // align stack pointer
movq %rdi, %r11  // move the first parameter to r11

shrb $4, %r11b  // divide by 16 to get the first hex digit

movq $string, %r9
movb (%r9, %r11), %r11b //move first index

movb %r11b, (%rsi)

movq %rdi, %r11 // divide r11 by 16 again to get the second hex digit
shlb $4, %r11b  // shift left 4 times
shrb $4, %r11b // shift right 4 times


//second index

movb (%r9, %r11), %r11b  //move second index
movb %r11b, 1(%rsi)

movb $0, 2(%rsi) // null-terminate the string

addq $8, %rsp   // restore stack pointer

ret



.globl hex_read

hex_read:

subq $8, %rsp

movq $16, %rdx // reads up to 16 bytes
movq %rdi, %rsi

movq $0, %rdi //file descriptor is 0 for stdin
movq $0, %rax //syscall
.done:
syscall
addq $8, %rsp
ret


.globl hex_write_string


hex_write_string:

subq $8, %rsp
xor %rcx, %rcx //counter
.loop_around:
cmpb $0, (%rdi, %rcx)
jne .increment //if not 0, increment
je .move_buffer //if 0, move buffer
 .increment:
addq $1, %rcx //increment counter
cmpq $16, %rcx //count <  16 else count >= 16
jl .loop_around //if less than 16, loop around
jmp .move_buffer
jmp .finish
.move_buffer:
movq %rdi, %rsi //move buffer
movq $1, %rdi  //file descriptor is 1 for stdout
movq %rcx, %rdx
movq $1, %rax  
syscall
.finish:
addq $8, %rsp // restore stack pointer
ret


.globl hex_format_offset

hex_format_offset:

subq $8, %rsp // align stack pointer
xor %r8, %r8 //count
cmp $8, %r8
jne .buff_create
je .calculate_offset

.buff_create:
movq $0, (%rsi, %r8) // create buffer
addq $1, %r8  
cmp $8, %r8
je .mod_offset // count == 8
jmp .buff_create // else loop around

.mod_offset:
movq $string, %r10 // hexadecimal string
xor %r11, %r11 // remainder
xor %r8, %r8 //counter

.calculate_offset:
movq %rdi, %rax  
xor %rdx, %rdx
movq $16, %r9
divq %r9
movq %rdx, %r11 //remainder
movq %rax, %rdi // quotient becomes the new offset
jmp .right_hex_digit

.right_hex_digit:
movb (%r10, %r11), %r9b
movq $7, %rcx
subq %r8, %rcx  
movb %r9b, (%rsi, %rcx)
addq $1, %r8
cmp $0, %rdi
jne .calculate_offset

.compare:
cmp $0, %rdi
jne .calculate_offset // // calculate offset
cmp $7, %r8 // offset = 0
jg .end
jmp .add_zeros // less than or equal to

.add_zeros:
movq $7, %rcx
subq %r8, %rcx
movb $48, (%rsi, %rcx)
addq $1, %r8
cmp $7, %r8
jg .end
jmp .add_zeros
.end:
addq $8, %rsp
ret


/* vim:ft=gas:
 */