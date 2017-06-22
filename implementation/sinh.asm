BITS 64

GLOBAL era_sinh

section .rodata
precision:	dq 10000.0			;define constant precision

section .text

era_sinh:
	fstcw word [rsp-10]			;save the x87 Control Word to memory

	fninit					;initialize the x87 FPU

	movlps qword [rsp-8], xmm0		;get the double argument x from SSE Register xmm0 into memory to get it into the FPU
	
	;this was temporary to test out how many loops I need to run for a specific input x
	;mov rcx, rdi				;get the loop count in the register that can really use it...
	
	;this was used for the old way of ending the loop
	;fld qword [precision]			;st0 = precision
	fld qword [rsp-8]			;st0 = x, st1 = precision
	fxam					;if x=0 C3 = 1, if infinity C2 = C0 = 1
	fstsw ax				;store x87 FPU SW in ax
	sahf					;load EFLAGS from ah
						;important for here CF = C0 and ZF = C3
	jbe .end				;jump if (CF or ZF) = 1

	fld st0					;st0 = x, st1 = x, st2 = precision
						
	fabs					;st0 = |x|

	fdiv st1, st0				;st1 = x/|x|, eigther 1 or -1
	
	fld st0					;I can only get a 64 Bit Integer out of the FPU with popping, so dublicating x here
	fistp qword [rsp-8]			;get x as integer into memory
	fwait					;wait that that is done
	mov rcx, qword [rsp-8]			;then get that integer into rxc
	shr rcx, 3				;divide it by 8
	mov rax, rcx				;save that into rax
	shl rcx, 2				;now multiply rcx with 4
        add rcx, rax				;add rax to rcx
	add rcx, 45				;add 45 to rcx, so now rcx = 45+5/8x

	fld1					;load conatant 1
						;st0 = 1, st1 = x, st2 = sign, st3 = precision	

	fld st1					;result = x
						;st0 = result, st1= 1, st2 = x, st3 = sign, st4 = precision

	fld1					;i = 1
						;st0 = i, st1 = result, st2= 1, st3 = x, st4 = sign, st5 = precision

	fld st3					;previous = x
						;st0 = previous, st1 = i, st2 = result, st3= 1, st4 = x, st5 = sign, st6 = precision
	;fdivr st6, st0				;precision = x/precision
.loop:			
	fincstp					;st7= previous, st0 = i, st1 = result, st2 = 1, st3 = x, st4 = sign, st5 = precision
	fadd st0, st2				;i++
	fdecstp					;st0= previous, st1 = i, st2 = result, st3 = 1, st4 = x, st5 = sign, st6 = precision
	fdiv st0, st1				;previous = previous / i
	fmul st0, st4				;previous = previous * x

	fincstp					;st7= previous, st0 = i, st1 = result, st2 = 1, st3 = x, st4 = sign, st5 = precision
	fadd st0, st2				;i++
	fdecstp					;st0= previous, st1 = i, st2 = result, st3 = 1, st4 = x, st5 = sign, st6 = precision
	fdiv st0, st1				;previous = previous / i
	fmul st0, st4				;previous = previous * x

	fadd st2, st0				;result = result + previous

	;fcomi st0, st6				;if previous < precision CF = 1
	;jae .loop				;jump if CF = 0
	loop .loop

	fincstp
	fincstp					;st6= previous, st7 = i, st0 = result, st1 = 1, st2 = x, st3 = sign, st4 = precision
	fmul st0, st3				;st0 = result * sign

.end:
	fstp qword [rsp-8]			;save output into memory

	movlps xmm0, [rsp-8]			;load output from memory to xmm0 to return it
	fldcw word [rsp-10]			;restore the x87 FPU Control Word from memory
ret

