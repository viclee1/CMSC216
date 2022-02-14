# Victor Lee, 117213218, vlee842

fibonacci:
   # PROLOGUE
   subu $sp, $sp, 8
   sw   $ra, 8($sp)
   sw   $fp, 4($sp)
   addu $fp, $sp, 8

   # BODY
   beqz $a0, case0     # checks one of two base cases, if n == 0
   beq  $a0, 1, case1  # checks the other base case, if n == 1
   
   subu $sp, $sp, 4    # allocates space for $a0 to be stored
   sw   $a0, 4($sp)    # a0 gets stored so it can be modified again later
   
   sub  $a0, $a0, 1    # fibonacci(n-1)
   jal  fibonacci      # recursive call for n-1
   
   lw   $a0, -8($fp)  # restores $a0 for fibonacci(n-2)
   
   subu $sp, $sp, 4    # allocates space for $v0 to be reused and added
   sw   $v0, 4($sp)    # stores $v0

   sub  $a0, $a0, 2    # fibonacci(n-2)
   jal  fibonacci      # recursive call for n-2

   lw   $t0, -12($fp)    # value of fibonnaci(n-1)
   add  $v0, $t0, $v0  # fibonacci(n-1) + fibonacci(n-2)
   j    ret

case0:
   li   $v0, 0         # adds 0 on line 28 for when f(n-1) or f(n-2) becomes 0
   j    ret
case1:
   li   $v0, 1         # adds 1 on line 28 for when f(n-1) or f(n-2) becomes 1
   j    ret
ret:
   # EPILOGUE
   move $sp, $fp
   lw   $ra, ($fp)
   lw   $fp, -4($sp)
   jr   $ra

