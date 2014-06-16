.section .data
message: .string "Hello World!\n"

.section .text

# this directive allows the linker to see the "main" label
# which is our entry point
.globl main

# this directive allows the eclipse gdb to see a function called "main"
.func main
main:
	mov $4, %eax
	mov $1, %ebx
	mov $message, %ecx
	mov $14, %edx
	int $0x80
	mov $0, %eax

