		.text
		.align	4
		.global main
main:
		movw	r4,#:lower16:a			;r4<-&a
		movt	r4,#:upper16:a
		movw	r5,#:lower16:b			;r5<-&b
		movt	r5,#:upper16:b
		movw	r6,#:lower16:n			;r6<-&n
		movt	r6,#:upper16:n
		movw	r7,#:lower16:tmp		;r7<-&tmp
		movt	r7,#:upper16:tmp
		movw	r8,#:lower16:fmt1		;r8<-&fmt1
		movt	r8,#:upper16:fmt1

		mov		r0,#0
		str		r0,[r6]					;n=0
		
		ldr		r1,[r5]					;r1<-b
		mov		r0,r8					;r0<-&fmt1
		bl		printf
		
while:
		ldr		r3,[r4]					;r3<-a
		ldr		r2,[r5]					;r2<-b
		add		r1,r3,r2				;r1<-a+b
		str		r1,[r7]					;tmp<-r1	(i.e., tmp<-a+b)
		cmp		r1,#0					;test tmp
		ble		endwhile				;if tmp <=0 go to endwhile
		
		str		r3,[r5]					;b<-a
		str		r1,[r4]					;a<-tmp
		
		cmp		r1,#1000				;compare a and 1000
		ldrgt	r3,[r6]					;if a>1000 r3<-n
		addgt	r3,r3,#1				;if a>1000 r3<-r3+1
		strgt	r3,[r6]					;if a>1000 n<-r3
		mov		r0,r8					;r0<-&fmt1
		bl		printf					;@rl is still a
		
		b		while
endwhile:
		movw	r0,#:lower16:fmt2
		movt	r0,#:upper16:fmt2		;r0<-&fmt2
		ldr		r1,[r6]					;r1<-n
		bl		printf
		
		ldr		r3,[r7]					;r3<-tmp
		ldr		r2,[r5]					;r2<-b
		ldr		r1,[r4]					;r1<-a
		movw	r0,#:lower16:fmt3
		movt	r0,#:upper16:fmt3		;r0<-&fmt3
		bl		printf
		
		mov		r0,#0
		bl		exit					;exit with argument 0
		
		.align 	4
		.comm	tmp,4,4					;uninitialized data
		.comm	n,4,4
		.data
		.align	4

b:		.word 	1						;initialized data
a:		.word 	1

fmt1:	.ascii	"%10d\012\000"
fmt2:	.ascii	"\012The number of values greater than 1000 is %d\012\000"
fmt3:	,ascii	"Final values are: a=0x%08X b=0x%08X tmp=0x%08X\012\000"