# max(x, y)

max:
   # PROLOGUE
   subu $sp, $sp, 8
   sw   $ra, 8($sp)
   sw   $fp, 4($sp)
   addu $fp, $sp, 8

   # BODY
   subu $sp, $sp, 4
   move $t0, $a0     	#t0 = a0
   sw   $t0, 4($sp)

   move $v0, $t0
   sub  $v0, $v0, $a1   #subtracts y from x
   bltz $v0, else       #if x - y is less than 0 then doesn't jump to else
   move $v0, $a0        
   j    endif           #jumps to epilogue

else:
   move $v0, $a1
endif:
   # EPILOGUE
   move $sp, $fp
   lw   $ra, ($fp)
   lw   $fp, -4($sp)
   jr   $ra
