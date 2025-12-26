; Problem Matcher Test 3
    .module test_s
    .globl _asm_func

    .area _CODE
_asm_func:
    nop
    ; [TEST CASE 3] Invalid operand format (3 operands for LD)
    ld a, #0x55, #0xAA 
    ret
