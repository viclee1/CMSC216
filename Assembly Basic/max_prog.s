# read x, read y (entered on separate lines)
# call max(x, y), passing args in registers a0, a1
# check that result is maximum of x and y

   .text
main:
   li   $sp, 0x7ffffffc    # initialize $sp

   # PROLOGUE
   subu $sp, $sp, 8        # expand stack by 8 bytes
   sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
   sw   $fp, 4($sp)        # push $fp (4 bytes)
   addu $fp, $sp, 8        # set $fp to saved $ra

   li   $v0, 5             # read x into a0
   syscall
   move $a0, $v0

   li   $v0, 5             # read y into a1
   syscall
   move $a1, $v0

#   lw   $a0, arg0          # a0 = arg0
#   lw   $a1, arg1          # a1 = arg1
   jal  max                 # v0 = max(arg0, arg1)

   move $a0, $v0           # print_int(rval)
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
# max(x, y)

max:
   # PROLOGUE
   subu $sp, $sp, 8
   sw   $ra, 8($sp)
   sw   $fp, 4($sp)
   addu $fp, $sp, 8

   # BODY
   subu $sp, $sp, 4
   move $t0, $a0
   sw   $t0, 4($sp)

   move $v0, $t0
   sub  $v0, $v0, $a1
   bltz $v0, else
   move $v0, $a0
   j    endif

else:
   move $v0, $a1
endif:
    # EPILOGUE
   move $sp, $fp
   lw   $ra, ($fp)
   lw   $fp, -4($sp)
   jr   $ra
