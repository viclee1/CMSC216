   .data
str1:
   .asciiz "abba"
str2:
   .asciiz "racecar"
str3:
   .asciiz "swap paws",
str4:
   .asciiz "not a palindrome"
str5:
   .asciiz "another non palindrome"
str6:
   .asciiz "almost but tsomla"

# array of char pointers = {&str1, &str2, ..., &str6}
ptr_arr:
   .word str1, str2, str3, str4, str5, str6, 0

yes_str:
   .asciiz " --> Y\n"
no_str:
   .asciiz " --> N\n"

   .text

# main(): ##################################################
#   char ** j = ptr_arr
#   while (*j != 0):
#     rval = is_palindrome(*j)
#     printf("%s --> %c\n", *j, rval ? yes_str: no_str)
#     j++
#
main:
   li   $sp, 0x7ffffffc    # initialize $sp

   # PROLOGUE
   subu $sp, $sp, 8        # expand stack by 8 bytes
   sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
   sw   $fp, 4($sp)        # push $fp (4 bytes)
   addu $fp, $sp, 8        # set $fp to saved $ra

   subu $sp, $sp, 8        # save s0, s1 on stack before using them
   sw   $s0, 8($sp)        # push $s0
   sw   $s1, 4($sp)        # push $s1

   la   $s0, ptr_arr        # use s0 for j. init ptr_arr
main_while:
   lw   $s1, ($s0)         # use s1 for *j
   beqz $s1, main_end      # while (*j != 0):
   move $a0, $s1           #    print_str(*j)
   li   $v0, 4
   syscall
   move $a0, $s1           #    v0 = is_palindrome(*j)
   jal  is_palindrome
   beqz $v0, main_print_no #    if v0 != 0:
   la   $a0, yes_str       #       print_str(yes_str)
   b    main_print_resp
main_print_no:             #    else:
   la   $a0, no_str        #       print_str(no_str)
main_print_resp:
   li   $v0, 4
   syscall

   addu $s0, $s0, 4       #     j++
   b    main_while        # end while
main_end:

   # EPILOGUE
   move $sp, $fp           # restore $sp
   lw   $ra, ($fp)         # restore saved $ra
   lw   $fp, -4($sp)       # restore saved $fp
   j    $ra                # return to kernel
# end main ################################################
# Victor Lee, 117213218, vlee842

# A palindrome is a phrase that is the same forward as backwards
is_palindrome:
   # PROLOGUE
   subu $sp, $sp, 8
   sw   $ra, 8($sp)
   sw   $fp, 4($sp)
   addu $fp, $sp, 8

   # BODY
   li   $t0, 0         # i
   move $t1, $a0       # foward iteration
   move $t2, $a0       # used for strlen
   li   $t3, 0         # strlen counter
   lbu  $t4, 0($a0)    # loads characters fowards
   lbu  $t5, 0($a0)    # loads characters backwards
   j    strlen
return:
   sub  $t3, $t3, 1    # removes null terminator as strlen counts it
   add  $t2, $t1, $t3  # goes back so it doesn't load the null terminator
   lbu  $t5, 0($t2)    # loads very last character
   div  $t3, $t3, 2    # used to check end of loop
   li   $t6, 1         # true or false tracker
palindrome_loop:
   beq  $t0, $t3, palindrome_endloop # if everything is iterated through and there are no disputes, returns 1
   bne  $t4, $t5, palindrome_endif   # if it placement of chars isn't exact, ends the loop
   add  $t0, $t0, 1                  # increments i
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
