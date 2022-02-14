   .data
strbuf:
   .space 80
pass_str:
   .asciiz "pass\n"
fail_str:
   .asciiz "fail\n"

   .text
main:
   li   $sp, 0x7ffffffc    # initialize $sp

   # PROLOGUE
   subu $sp, $sp, 8        # expand stack by 8 bytes
   sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
   sw   $fp, 4($sp)        # push $fp (4 bytes)
   addu $fp, $sp, 8        # set $fp to saved $ra

   li   $v0, 8             # read string into strbuf
   la   $a0, strbuf        # and nul-terminate it
   li   $a1, 80            # assumes input (including \n)
   syscall                 # is less than 80 chars

   jal  strlen

   move $a0, $v0           # print_int(a0)
   li   $v0, 1
   syscall
   li   $v0, 11            # print_char(\n)
   li   $a0, 10
   syscall

   # EPILOGUE
   move $sp, $fp           # restore $sp
   lw   $ra, ($fp)         # restore saved $ra
   lw   $fp, -4($sp)       # restore saved $fp
   j    $ra                # return to kernel
# strlen(str)

strlen:
   # PROLOGUE
   subu $sp, $sp, 8
   sw   $ra, 8($sp)
   sw   $fp, 4($sp)
   addu $fp, $sp, 8

   # BODY
   subu $sp, $sp, 8
   li   $t0, 0          # used to increment and count the number of chars in the string
   lbu  $t1, 0($a0)
   sw   $t1, 4($sp)
   sw   $t0, 8($sp)
loop:
   beqz $t1, endloop    # checks for the null terminator
   add  $t0, $t0, 1     # counts up by one
   add  $a0, $a0, 1     # loads the next char
   lbu  $t1, 0($a0)     # loads byte after each incrementation once
   j    loop
endloop:
   move $v0, $t0
   # EPILOGUE
   move $sp, $fp
   lw   $ra, ($fp)
   lw   $fp, -4($sp)
   jr   $ra
