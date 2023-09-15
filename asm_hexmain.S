/* Hexdump main function, assembly language version */
/* Suha Patel spate186
   Eric Alvarado ealvara6 */

    .section .rodata

//we didn't know how to move strings into registers w/o seg faulting
newline_char:
    .string "\n"
    .section .data
space_bar:
    .string " "
colon_and_space_bar:
    .string ": "
three_space_bars:
    .string "   "
to_print:
    .fill 16
data_buffer:
    .fill 16
offset_amt:
    .fill 9
hex_buffer:
    .fill 2
   


    .section .text

    .globl main
main:
    subq $8, %rsp  // Allocate space on the stack for local variables
    xor %rbx, %rbx // Clear the value of register %rbx
    xor %r13, %r13 // Clear the value of register %r13
    cmp $0, %rbx // Compare the value of %rbx to 0
    je .while // If %rbx is equal to 0, jump to .while label

.while:
    movq $data_buffer, %rdi // Load the address of data_buffer into register %rdi
    call hex_read // Call the hex_read function to read hexadecimal data from input
    cmp $0, %rax // Compare the return value of hex_read to 0
    je .end // If hex_read returned 0, jump to .end label
    jmp .determine_offset // print the offset // Otherwise, jump to .determine_offset label

.restart_or_continue:
    xor %r14, %r14 // Clear the value of register %r14
    cmp %r15, %r14 // Compare the value of %r14 to %r15
    jl .for // If %r14 is less than %r15, jump to .for label
    jmp .first_condition // Otherwise, jump to .first_condition label

.determine_offset:
    movq %rax, %r15 // Move the return value of hex_read into register %r15
    movq %r13, %rdi // Move the value of %r13 into register %rdi
    movq $offset_amt, %rsi // Load the address of offset_amt into register %rsi
    call hex_format_offset //format the offset

    movq %rsi, %rdi // Move the formatted offset into register %rdi
    call hex_write_string // Call the hex_write_string function to print the offset
    jmp .add_offset // Jump to .add_offset label

.add_offset:
    movq $colon_and_space_bar, %rdi // Load the address of colon_and_space_bar into register %rdi
    call hex_write_string // Call the hex_write_string function to print ": "
    addq $16, %r13 // Increment the value of %r13 by 16
    pushq %r13 // Push the value of %r13 onto the stack
    jmp .restart_or_continue


.for:
    movq $data_buffer, %r13 // Load the address of data_buffer into register %r13
    movb (%r13, %r14), %dil // Move the byte at address (%r13 + %r14) into register %dil
    movq $hex_buffer, %rsi // Load the address of hex_buffer into register %rsi
    call hex_format_byte_as_hex // Call the hex_format_byte_as_hex function to format the byte as hexadecimal
    jmp .read_bytes_and_print_hex // Jump to .read_bytes_and_print_hex label

.read_bytes_and_print_hex:
    movq $hex_buffer, %rdi // Load the address of hex_buffer into register %rdi
    call hex_write_string // Call the hex_write_string function to print the formatted byte
    movq $space_bar, %rdi // Load the address of space_bar into register %rdi
    call hex_write_string
   
   //increment %r14 by 1, compare value of %r14 to %r15, and jump to .for if %r14 is less than %r15. Otherwise, jump to .first_condition.
    addq $1, %r14
    cmp %r15, %r14
    jl .for
    jmp .first_condition

// compare the value of %r15 to 16 and go to .if if %r15 is less than 16
.first_condition:
    cmp $16, %r15
    jl .if
    jmp .second_condition

//set the value of %r14 to 16 and subtract %r15 from %r14, else go to .if_compare
.if:
    movq $16, %r14
    subq %r15, %r14
    jmp .if_compare

.if_compare:
    xor %r13, %r13 //Set %r13 register to 0
    cmp %r14, %r13
   
.if_not_less_than_data_buffer:
    movq $three_space_bars, %rdi //Load the address of the string "   " (three space bars) into %rdi
    call hex_write_string // Call the hex_write_string function to print the string of three spaces
    addq $1, %r13 // Increment %r13 register by 1
    cmp %r14, %r13 // Compare if %r13 is less than %r14
    jl .if_not_less_than_data_buffer //If %r13 is less than %r14, jump back to the .if_not_less_than_data_buffer label
    jmp .second_condition //If not jump to .second_condition label to continue execution
   
// Print contents of r13 register, which is assumed to contain a null-terminated string
// After printing the string, print a newline charact then jumps to .third_condition
.write_string:
    movq %r13, %rdi
    call hex_write_string
    movq $newline_char, %rdi
    call hex_write_string
    jmp .third_condition

.print_and_increment:
    movq $to_print, %r13
    movb %al, (%r13, %r14)
    addq $1, %r14
    cmp %r15, %r14 //Compare the value in register %r14 with the value in register %r15
    jl .loop_print //Jump to .loop_print if the value in %r14 is less than %r15
    jmp .write_string //else jump to .write_string
   
.loop_print:
    movq $data_buffer, %r13
    movb (%r13, %r14), %dil //Move the byte at the address data_buffer[r14] into register dil
    call hex_to_printable
    jmp .print_and_increment

.second_condition:  
    movq $space_bar, %rdi
    call hex_write_string
    jmp .determine_if_printable_for

.determine_if_printable_for:
    xor %r14, %r14
    cmp %r15, %r14
    jl .loop_print
    jmp .third_condition

.third_condition:
    xor %r14, %r14
    cmp $16, %r14
    jl .end_with_null
    jmp .end


.end_with_null_conditional:
    addq $1, %r14
    cmp $16, %r14
    jl .end_with_null
    popq %r13
    jmp .end_while_conditional

//add null terminator
.end_with_null:
    movq $data_buffer, %r13
    movq $0, (%r13, %r14)
    movq $to_print, %r13
    movq $0, (%r13, %r14)
    jmp .end_with_null_conditional

.end_while_conditional:
    cmp $0, %rbx
    je .while
    jmp .end
   
.end:  
    movq $0, %rax
    addq $8, %rsp //align the stack
    ret

/* vim:ft=gas:
 */