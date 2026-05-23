.section .vectors
.global vector_table

vector_table:
    .word _estack
    .word reset_handler

.section .text
.global reset_handler

reset_handler:
    bl Reset_Handler

loop:
    b loop
