# Victor Lee, 117213218, vlee842

isqrt:
   # PROLOGUE
   subu $sp, $sp, 8
   sw   $ra, 8($sp)
   sw   $fp, 4($sp)
   addu $fp, $sp, 8

   # BODY
   blt  $a0, 2, ret_n            # base case when n is less than 2
   
   subu $sp, $sp, 4              # allocates space for n to be saved each recursive call
   sw   $a0, 4($sp)              # stores n onto the stack
   
   srl  $a0, $a0, 2              # move n 2 bits to the right
   jal  isqrt                    # recursively calls isqrt >> 2

   lw   $t0, -8($fp)             # restores n
   sll  $v0, $v0, 1              # move n 1 bit to the left
   
   subu $sp, $sp, 8              # space for small on the stack
   sw   $v0, 4($sp)              # stores small as a "local variable" as a direct translation from C
   
   add  $v0, $v0, 1              # large = small + 1
   sw   $v0, 8($sp)              # stores large as a "local variable" as a direct translation from C
   mulo $t1, $v0, $v0            # used in if statement for if large * large > n

   bgt  $t1, $t0, ret_small      # if true, return small
   j    ret                      # else keep large in $v0 and return that
   
ret_n:
   move $v0, $a0
   j    ret
ret_small:
   lw   $v0, 4($sp)              # restores small
ret:
   # EPILOGUE
   move $sp, $fp
   lw   $ra, ($fp)
   lw   $fp, -4($sp)
   jr   $ra
