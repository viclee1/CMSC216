# Victor Lee, 117213218, vlee842

# A palindrome is a phrase that is the same forward as backwards
is_palindrome:
   # PROLOGUE
   subu $sp, $sp, 8
   sw   $ra, 8($sp)
   sw   $fp, 4($sp)
   addu $fp, $sp, 8

   # BODY
   subu $sp, $sp, 8
   li   $t0, 0         # i
   sw   $t0, 4($sp)    # stores i as a "local variable" in C
   move $t1, $a0       # foward iteration
   move $t2, $a0       # used for strlen
   li   $t3, 0         # strlen counter
   lbu  $t4, 0($a0)    # loads characters fowards
   lbu  $t5, 0($a0)    # loads characters backwards
   j    strlen
return:
   sub  $t3, $t3, 1    # removes null terminator as strlen counts it
   sw   $t3, 8($sp)    # stores strlen as a "local variable" in C
   add  $t2, $t1, $t3  # goes back so it doesn't load the null terminator
   lbu  $t5, 0($t2)    # loads very last character
   div  $t3, $t3, 2    # used to check end of loop
   li   $t6, 1         # true or false tracker 
palindrome_loop:
   beq  $t0, $t3, palindrome_endloop # if everything is iterated through and there are no disputes, returns 1
   bne  $t4, $t5, palindrome_endif   # if it placement of chars isn't exact, ends the loop
   add  $t0, $t0, 1                  # increments i
   sw   $t0, 4($sp)                  # updates i on stack
   add  $t1, $t1, 1                  # goes to next character
   sub  $t2, $t2, 1                  # goes back one character
   lbu  $t4, 0($t1)                  # loads the char at $t1
   lbu  $t5, 0($t2)                  # loads the char at $t2
   j    palindrome_loop              # loops back
palindrome_endif:
   sub  $t6, $t6, 1                  # if it is not a palindrome, subtract 1 so it returns 0
palindrome_endloop:
   move $v0, $t6                     # else returns 1
   # EPILOGUE
   move $sp, $fp
   lw   $ra, ($fp)
   lw   $fp, -4($sp)
   jr   $ra

strlen:
   beqz $t5, return     # checks for the null terminator
   add  $t3, $t3, 1     # counts up by one
   add  $t2, $t2, 1     # loads the next char
   lbu  $t5, 0($t2)     # loads byte after each incrementation once; additionally it gets us to the end of the string so it can be iterated backwards
   j    strlen
