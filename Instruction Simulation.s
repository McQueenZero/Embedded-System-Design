        EXPORT  Test            ; ������ʶ��        
            
        IMPORT  x   [DATA]      ; �����ʶ��

        AREA    ||.text||, CODE, READONLY, ALIGN=2
Test            PROC                    ; ����Test���
;		MOV     R0,#0x5678      ; װ�س�����R0�ĵ�16λ
;		MOVT    R0,#0x1234      ; װ�س�����R0�ĸ�16λ
;		MVN		R3,R0			; ��R0������ȡ�����ٴ��͸�R3
;		MRS		R4,APSR			; �������⹦�ܼĴ�����ֵ��R4
;		MSR		PSP,R4			; ����R4��ֵ�����⹦�ܼĴ���
;     	LDR     R1,=x           ; װ�ر���x�ĵ�ַ��R1
;		STR   	R0,[R1,#20]!    ; ����R0��ֵ��R1+20��ַ,Ȼ��R1=R1+20
;		STR   	R0,[R1],#-12    ; ����R0��ֵ��R1��ַ��,Ȼ��R1=R1-12
;		LDMIA	R2!,{R0-R1}		; ��R3����ȡ����֣�ÿ��һ���ֺ�R3����һ��
;		STMIA	R5!,{R0-R3}		; �洢����ֵ�R5����ÿ��һ���ֺ�R5����һ��
;		ADD		R6,R0,R1		; ����ӷ�R6=R0+R1
;		ADC		R6,R0,R1		; ����λ�ļӷ�R6=R0+R1
;		SUB 	R2,R1			; �������R2-=R1��R2=R2-R1��
;		SUB		R6,R0,R2		; �������R6=R0-R2
;		SBC		R6,R0,R2		; ����λ�ļ���R6=R0-R2
;		MUL		R6,R0,R1		; ����˷�R6=R0*R1
;		UDIV	R6,R2,R0		; Ӳ��֧�ֵ��޷��ų���R6=R2/R0������������
;		SDIV	R6,R2,R0		; Ӳ��֧�ֵĴ����ų���R6=R2/R0������������
;		AND		R1,R0			; ��λ�룬R1=R1&R0
;		ORR		R1,R0			; ��λ��R1=R1|R0
;		BIC		R3,R2			; λ���㣬R3=R3&~R2
;		ORN		R3,R2			; ��λ���룬R3=R3|~R2
;		EOR		R3,R2			; ��λ���R3=R3^~R2
;		LSL		R0,R2,#3		; R2�߼�����3λ����R0
;		LSR		R1,R2,#3		; R2�߼�����3λ����R1
;		ASR		R1,R2,#3		; R2��������3λ����R1
;		ROR		R0,R2			; R2ѭ�����Ƹ���R0
;		MOV     R0,#-23      	; װ�س�����R0
;		SXTH	R1,R0			; ��R0�����Ű���������չ��32λ��ֵ��R1
;		UXTH	R2,R0			; ��R0�޷��Ű���������չ��32λ��ֵ��R2
;		REV		R1,R0			; �����е����ֽ��򣬽������R1
;		LDR		R0,=0x1234FFFF	
;		BFC		R0,#4,#10		; λ������
;		LDR		R0,=0x12345678
;		LDR		R1,=0xAABBCCDD
;		BFI.W	R1,R0,#8,#16	; λ�����		
;		LDR		R1,=0xB4E10C23
;		RBIT.W	R0,R1			; ��λ��ת180��
;		LDR		R0,=0x5678ABCD
;		SBFX.W	R1,R0,#8,#4		; ����λ�򣬲���������չ��32λ
;		MOV		R0,#0x2000
;		SSAT.W	R1,#12,R0		; ��32λ�������͵�12λ����������
;		LDR		R0,=0xFFFFFB32
;		USAT	R1,#12,R0		; ��32λ�������͵�12λ�޷�������
;		ISB						; ָ��ͬ������
;		CMP		R0,R1			; �Ƚ�R0��R1
;		ITTEE	EQ				; IF-THEN ITָ���
;		ADDEQ 	R2,R0,R1		; ���ʱ�ӷ��������R2
;		ASREQ	R1,R1,#1		; ���ʱR1��������
;		ADDNE	R0,R1			; ����ʱ�ӷ��������R0
;		ASRNE	R0,R0,#1		; ����ʱR0��������
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
