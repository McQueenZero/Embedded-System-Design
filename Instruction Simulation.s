        EXPORT  Test            ; 导出标识符        
            
        IMPORT  x   [DATA]      ; 导入标识符

        AREA    ||.text||, CODE, READONLY, ALIGN=2
Test            PROC                    ; 函数Test入口
;		MOV     R0,#0x5678      ; 装载常量到R0的低16位
;		MOVT    R0,#0x1234      ; 装载常量到R0的高16位
;		MVN		R3,R0			; 把R0的数据取反后再传送给R3
;		MRS		R4,APSR			; 加载特殊功能寄存器的值到R4
;		MSR		PSP,R4			; 储存R4的值到特殊功能寄存器
;     	LDR     R1,=x           ; 装载变量x的地址到R1
;		STR   	R0,[R1,#20]!    ; 保存R0的值到R1+20地址,然后R1=R1+20
;		STR   	R0,[R1],#-12    ; 保存R0的值到R1地址处,然后R1=R1-12
;		LDMIA	R2!,{R0-R1}		; 从R3处读取多个字，每读一个字后R3自增一次
;		STMIA	R5!,{R0-R3}		; 存储多个字到R5处，每存一个字后R5自增一次
;		ADD		R6,R0,R1		; 常规加法R6=R0+R1
;		ADC		R6,R0,R1		; 带进位的加法R6=R0+R1
;		SUB 	R2,R1			; 常规减法R2-=R1（R2=R2-R1）
;		SUB		R6,R0,R2		; 常规减法R6=R0-R2
;		SBC		R6,R0,R2		; 带借位的减法R6=R0-R2
;		MUL		R6,R0,R1		; 常规乘法R6=R0*R1
;		UDIV	R6,R2,R0		; 硬件支持的无符号除法R6=R2/R0，余数被丢弃
;		SDIV	R6,R2,R0		; 硬件支持的带符号除法R6=R2/R0，余数被丢弃
;		AND		R1,R0			; 按位与，R1=R1&R0
;		ORR		R1,R0			; 按位或，R1=R1|R0
;		BIC		R3,R2			; 位清零，R3=R3&~R2
;		ORN		R3,R2			; 按位或反码，R3=R3|~R2
;		EOR		R3,R2			; 按位异或，R3=R3^~R2
;		LSL		R0,R2,#3		; R2逻辑左移3位赋给R0
;		LSR		R1,R2,#3		; R2逻辑右移3位赋给R1
;		ASR		R1,R2,#3		; R2算术右移3位赋给R1
;		ROR		R0,R2			; R2循环右移赋给R0
;		MOV     R0,#-23      	; 装载常量到R0
;		SXTH	R1,R0			; 把R0带符号半字整数扩展到32位赋值给R1
;		UXTH	R2,R0			; 把R0无符号半字整数扩展到32位赋值给R2
;		REV		R1,R0			; 在字中调整字节序，结果赋给R1
;		LDR		R0,=0x1234FFFF	
;		BFC		R0,#4,#10		; 位域清零
;		LDR		R0,=0x12345678
;		LDR		R1,=0xAABBCCDD
;		BFI.W	R1,R0,#8,#16	; 位域插入		
;		LDR		R1,=0xB4E10C23
;		RBIT.W	R0,R1			; 按位旋转180°
;		LDR		R0,=0x5678ABCD
;		SBFX.W	R1,R0,#8,#4		; 拷贝位域，并带符号扩展到32位
;		MOV		R0,#0x2000
;		SSAT.W	R1,#12,R0		; 把32位整数饱和到12位带符号整数
;		LDR		R0,=0xFFFFFB32
;		USAT	R1,#12,R0		; 把32位整数饱和到12位无符号整数
;		ISB						; 指令同步隔离
;		CMP		R0,R1			; 比较R0和R1
;		ITTEE	EQ				; IF-THEN IT指令块
;		ADDEQ 	R2,R0,R1		; 相等时加法，结果给R2
;		ASREQ	R1,R1,#1		; 相等时R1算术右移
;		ADDNE	R0,R1			; 不等时加法，结果给R0
;		ASRNE	R0,R0,#1		; 不等时R0算术右移
		LDR		R0,=0x00000002
		LDR		R1,=0x00000001
Function1		
		SUB		R0,R1
Loop
		CBZ 	R0,LoopExit
		BL		Function1
		B 		Loop
LoopExit
        ENDP

        AREA ||.data||, DATA, ALIGN=2
y
        DCD      0x00000000

        END
