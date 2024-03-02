  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
  
  # Notes:
  # Remove parenteses for PUSH and POP
  
.global hexasc  		# .global makes it so that a symbol can be used by everyone, both Mars and MCB32.
.global delay
.global time2string
.global enable_interrupt
  
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

# .data and .text , added
.data
.text
  #
  # Please add your own code below this line
  #

# hexasc  
hexasc:
 	li	$t1,10		# load 10 to $t1
 	bge 	$a0, $t1, handle_hexadecimal	# Check if the input is 10 or greater. Ff so, jump for a new start value
 	nop			# delay slot filler (just in case)
 	
 	li	$t0,0x30	# load 30 to $t0 (start value for 0-9 ASCII)
  	add	$v0,$t0,$a0	# add with argument to get the correct ASCII-value
  	j	return_function		
  	nop			# delay slot filler (just in case)
  	
handle_hexadecimal:
 	li 	$t0,0x37	# load 0x37 for the value needed for adding values over 10 to get correct ASCII-value
 	add	$v0,$t0,$a0	# add with argument to get the correct ASCII-value
  	
return_function:
  	jr	$ra		# jump back after where the subroutine was called
  	nop			# delay slot filler (just in case)


# delay
delay:
	#jr	$ra
	#nop
	
	PUSH 	$ra
	move 	$t4,$a0		# Let $t4 be ms
	li     	$t6, 4500      	# Set the loop condition (350 = 1000ms), our constant
	
	outer_loop:
		beq	$t4, $0, exit_delay	# If ms = 0, exit the function
		nop
		
		#subi	$t4,$t4,1	# ms = ms - 1	# Doesnt work in labwork.S
		sub	$t4,$t4,1
		addi 	$t5,$0,0	# Set i=0
	inner_loop:
		bge    	$t5, $t6, outer_loop  # Branch to outer_loop if i >= (constant)
		nop

    		# Body of the loop
    		# (any operations or instructions you want to perform inside the loop)

    		addi    $t5, $t5, 1     # i = i + 1
    		j       inner_loop      # Jump back to inner_loop
    		nop
		
	exit_delay:
		POP 	$ra
		jr	$ra	# Return back
		nop
	

# time2string	
time2string:
	PUSH $ra			# push $ra to stack, to obtain the correct value after hexasc modify $ra
	PUSH $s1
	PUSH $s0
	PUSH $a0
	PUSH $v0
	move 	$s1,$a1			# move $a1 to $s1 
	move 	$s0,$a0			# move $a0 to $s0 
	
	#First digit
	andi 	$t1,$s1,0xf000		# bit masking from 15 to 12 to create the tens for the minutes		(X.:..)
	srl 	$a0,$t1,12		# shift right 12 bits so hexasc can use the 4 bits
	jal 	hexasc			# calls hexasc to convert from hexadecimal to ASCII-value
	nop 
	sb 	$v0,0($s0)		# save return value from hexasc to 1st byte position
	
	#Second digit
	andi 	$t1,$s1,0x0f00		# bit masking from 11 to 8 to create the ones for the minutes			(.X:..)
	srl 	$a0,$t1,8		# shift right 8 bits so hexasc can use the 4 bits
	jal 	hexasc			# calls hexasc to convert from hexadecimal to ASCII-value
	nop
	sb 	$v0,1($s0)		# save return value from hexasc to 2nd byte position
	
	#Adding the semicolon
	li 	$t1,0x3a		# set ASCII-value for semicolon (:) to $t1
	sb 	$t1,2($s0)		# save $t1 value to 3rd byte position
	
	#Third digit
	andi 	$t1,$s1,0x00f0		# bit masking from 7 to 4 to create the tens for the seconds			(..:X.)
	srl 	$a0,$t1,4		# shift right 4 bits so hexasc can use the 4 bits
	jal 	hexasc			# calls hexasc to convert from hexadecimal to ASCII-value
	nop
	sb 	$v0,3($s0)		# save return value from hexasc to 4:th byte position
	
	#Fourth digit
	andi 	$t1,$s1,0x000f		# bit masking from 3 to 0 to create the ones for the seconds			(..:.X)
	move 	$a0, $t1		# no need for shifting, just move $t1 to $a0
	jal 	hexasc			# calls hexasc to convert from hexadecimal to ASCII-value
	nop
	sb 	$v0,4($s0)		# save return value from hexasc to 5:th byte position
	
	# Adding the NUL byte
	li	$t1, 0x00		# load the ASCII value of NULL to $t1
	sb 	$t1, 5($s0)		# save ASCII value of NUL to 6:th byte position
	j	exit_time2string	# jump to exit_time2string
	nop		
	
	# ends the subroutine and restores it from the stack to registers
	exit_time2string:
		POP	$v0
		POP	$a0																																																																																							
		POP	$s0
		POP	$s1
		POP	$ra
 		jr 	$ra			# jump after time2string was called
 		nop

# enable_interrupt
enable_interrupt:
	ei
	jr $ra
	nop
