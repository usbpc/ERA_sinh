BITS 64

GLOBAL era_sinh

section .text

era_sinh:
	fstcw word [rsp-10]			;save the x87 Control Word to memory, we need to save it according to the API

	fninit					;initialize the x87 FPU

	movlps qword [rsp-8], xmm0		;get the double argument x from SSE Register xmm0 into memory to get it into the FPU
	

	fld qword [rsp-8]			;st0 = x
	fxam					;if x==0 then C3 = 1, if x == infinity C2 = C0 = 1
	fstsw ax				;store x87 FPU SW in ax
	sahf					;load EFLAGS from ah
						;important for here CF now has the value C0 had and ZF has the value C3 had
	jbe .end				;jump to end if (CF or ZF) == 1

	fld st0					;st0 = x, st1 = x
						
	fabs					;st0 = |x|

	fdiv st1, st0				;st1 = x/|x|, either 1 or -1
						
						;From here when the comments say x it really means |x|

						;Note for here:
						;The following lines untill .cont calculate how often we will go through the loop to make the result
						;more precise. For that we calculate 45+5/8 * (int) x. We arrived at that formula after testing our
						;function with diffrent amount of repititions and this seems to run as few as possible while still
						;beeing accurate enough.


	fld st0					;I can only get a 64 Bit integer out of the FPU with popping, so duplicating x here to not loose it
	fistp qword [rsp-8]			;get x as integer into memory
	fwait					;wait that that is done
	mov rcx, qword [rsp-8]			;then get that integer into rcx
	shr rcx, 3				;divide it by 8
	mov rax, rcx				;save that into rax
	shl rcx, 2				;now multiply rcx with 4
	add rcx, rax				;add rax to rcx
	add rcx, 45				;add 45 to rcx, so now rcx = 45+5/8x
	cmp rcx, 489				;compare rcx with 489
	jbe .cont				;skip the next instruction if rcx <= 489
	mov rcx, 489				;if rcx was bigger set it to 489, this is done so that inputs > 710 don't run forever 
						;and still output +/- infinity
	
.cont:	

	fld1					;load conatant 1
						;st0 = 1, st1 = x, st2 = sign

	fld st1					;result = x
						;st0 = result, st1= 1, st2 = x, st3 = sign

	fld1					;i = 1
						;st0 = i, st1 = result, st2= 1, st3 = x, st4 = sign

	fld st3					;previous = x
						;st0 = previous, st1 = i, st2 = result, st3= 1, st4 = x, st5 = sign
.loop:			
	fincstp					;st7= previous, st0 = i, st1 = result, st2 = 1, st3 = x, st4 = sign
	fadd st0, st2				;i++
	fdecstp					;st0= previous, st1 = i, st2 = result, st3 = 1, st4 = x, st5 = sign
	fdiv st0, st1				;previous = previous / i
	fmul st0, st4				;previous = previous * x

	fincstp					;st7= previous, st0 = i, st1 = result, st2 = 1, st3 = x, st4 = sign
	fadd st0, st2				;i++
	fdecstp					;st0= previous, st1 = i, st2 = result, st3 = 1, st4 = x, st5 = sign
	fdiv st0, st1				;previous = previous / i
	fmul st0, st4				;previous = previous * x

	fadd st2, st0				;result = result + previous

	dec ecx					;decrement ecx
	jnz .loop				;jump to .loop if ecx != 0

	fincstp
	fincstp					;st6= previous, st7 = i, st0 = result, st1 = 1, st2 = x, st3 = sign
	fmul st0, st3				;st0 = result * sign

.end:
	fstp qword [rsp-8]			;save output into memory

	movlps xmm0, [rsp-8]			;load output from memory to xmm0 to return it
	fldcw word [rsp-10]			;restore the x87 FPU Control Word from memory
ret

