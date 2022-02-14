   .data
# uint arrays, each terminated by -1 (which is not part of array)
data0:
   .word 1, 2, 3, 4, -1
data1:
   .word 2, 3, 4, 5, -1
data2:
   .word 5, 4, 3, 2,  -1
data3:
   .word 200456, 3345056, 1, 2, 1, 2, -1
overflow:
   .word 1, 1, 1, 1, 2147483646, -1

   .text

# main(): ##################################################
#   process_array(data0)
#   process_array(data1)
#   process_array(data2)
#   process_array(data3)
#   process_array(overflow)
#
main:
   # PROLOGUE
   subu $sp, $sp, 8        # expand stack by 8 bytes
   sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
   sw   $fp, 4($sp)        # push $fp (4 bytes)
   addu $fp, $sp, 8        # set $fp to saved $ra

   la   $a0, data0
   jal  process_array
   la   $a0, data1
   jal  process_array
   la   $a0, data2
   jal  process_array
   la   $a0, data3
   jal  process_array
   la   $a0, overflow
   jal  process_array

   # EPILOGUE
   move $sp, $fp           # restore $sp
   lw   $ra, ($fp)         # restore saved $ra
   lw   $fp, -4($sp)       # restore saved $fp
   j    $ra                # return to kernel
## end main ################################################

# process_array(uint* arr): #################################
#   print_array(arr)
#   reverse_prefix_sum(arr)
#   print_array(arr)
#
process_array:
   # PROLOGUE
   subu $sp, $sp, 8        # expand stack by 8 bytes
   sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
   sw   $fp, 4($sp)        # push $fp (4 bytes)
   addu $fp, $sp, 8        # set $fp to saved $ra

   subu $sp, $sp, 4        # save s0 on stack before using it
   sw   $s0, 4($sp)

   move $s0, $a0           # use s0 to save a0
   jal  print_array
   move $a0, $s0
   jal  reverse_prefix_sum
   move $a0, $s0
   jal  print_array

   lw   $s0, -8($fp)       # restore s0 from stack

   # EPILOGUE
   move $sp, $fp           # restore $sp
   lw   $ra, ($fp)         # restore saved $ra
   lw   $fp, -4($sp)       # restore saved $fp
   j    $ra                # return to kernel
## end process_array #######################################

# print_array(uint arr): ########################################
#   uint x
#   while (-1 != (x = *arr++)):
#     printf("%d ", x)
#   printf("\n")
#
print_array:
   # use t0 to hold arr. use t1 to hold *arr
   move $t0, $a0
print_array_while:
   lw   $t1, ($t0)
   beq  $t1, -1, print_array_endwhile
   move $a0, $t1           # print_int(*arr)
   li   $v0, 1
   syscall
   li   $a0, 32            # print_char(' ')
   li   $v0, 11
   syscall
   addu $t0, $t0, 4
   b    print_array_while
print_array_endwhile:
   li   $a0, 10            # print_char('\n')
   li   $v0, 11
   syscall
   jr   $ra
## end print_array #########################################
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

   lw   $t1, 4($sp)            # recovers arr at its current index

   addu $v0, $t1, $v0          # *arr + reverse_prefix_sum(arr+1)
   sub  $a0, $a0, 4

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
