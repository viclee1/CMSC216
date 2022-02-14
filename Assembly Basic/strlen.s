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
   lbu  $t1, 0($a0)     # loads the first character in a string
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
