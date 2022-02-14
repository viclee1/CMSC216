# mash(x, y)

mash:
   # PROLOGUE
   subu $sp, $sp, 8
   sw   $ra, 8($sp)
   sw   $fp, 4($sp)
   addu $fp, $sp, 8

   # BODY
   mulo $t0, $t0, 10  # multiplies x by 10  
   add  $t0, $t0, $t1 # "mashes" y to x by adding it
   move $v0, $t0 

   # EPILOGUE
   move $sp, $fp
   lw   $ra, ($fp)
   lw   $fp, -4($sp)
   jr   $ra
