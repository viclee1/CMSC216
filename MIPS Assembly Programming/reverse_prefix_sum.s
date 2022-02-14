# Victor Lee, 117213218, vlee842

reverse_prefix_sum:
   # PROLOGUE
   subu $sp, $sp, 8
   sw   $ra, 8($sp)
   sw   $fp, 4($sp)
   addu $fp, $sp, 8

   # BODY
   subu $sp, $sp, 8            # allocates space for $a0 and r
   
   lw   $t0, 0($a0)            # loads value of int at index 0 of *arr
   sw   $t0, 4($sp)            # stores value at current index to be restored later
   beq  $t0, -1, terminate     # checks for terminator of -1


   add  $a0, $a0, 4            # recursive call for reverse_prefixsum(arr+1)
   jal  reverse_prefix_sum

   lw   $t1, -12($fp)            # recovers arr at its current index

   addu $v0, $t1, $v0          # *arr + reverse_prefix_sum(arr+1)
   sub  $a0, $a0, 4            # returns arr to original index

   sw   $v0, 8($sp)            # stores r as it is a local variable in C   
   sw   $v0, 0($a0)            # *arr = r

   j    ret

terminate:
   li   $v0, 0                 # returns 0 if *arr == -1
ret:
   # EPILOGUE
   move $sp, $fp
   lw   $ra, ($fp)
   lw   $fp, -4($sp)
   jr   $ra
