;set number of times to run test
NUMTESTS = 20
.data
clocks		qword ?						;pointer to results array
overhead	qword ?
TEST_COUNT dword NUMTESTS				;number of tests
public overhead
public TEST_COUNT
.code
Serial PROC
			; pointer to result list
			mov			clocks, rcx

			;dummy test loop without test code to measure overhead
			xor			r15d, r15d
			mov			r14, clocks
CLOOP1:
			xor			eax, eax
			cpuid						;serialize
			rdtsc						;read time stamp counter to EDX:EAX
			shl			rdx, 32
			or			rax, rdx
			mov			[r14+r15], rax	;save in list
			sub			eax, eax
			cpuid						;serialize again
	
			;void to measure overhead only

			sub			eax, eax
			cpuid						;serial
			rdtsc						;read time stamp counter to EDX:EAX
			shl			rdx, 32
			or			rax, rdx
			sub			rax, [r14+r15]	;save in list
			mov			[r14+r15], rax	;save difference in list
			xor			eax, eax
			cpuid						;serialize again

			add			r15d, 8
			cmp			r15d, NUMTESTS*8
			jb			CLOOP1			;dummy loop end

			;find smallest clock count:
			mov			r14, clocks
			or			rax, -1
IF NUMTESTS GT 1
			mov			[r14], rax		;exclude first count from minimum
ENDIF
			xor			r15d, r15d
MINLOOP:
			cmp			[r14+r15], rax
			cmovb		rax, [r14+r15]
			add			r15d, 8
			cmp			r15d, NUMTESTS*8
			jb			MINLOOP
			mov			overhead, rax
			;loop to measure cycle count of test code:
			xor			r15d, r15d
			mov			r14, clocks
CLOOP2:
			xor			eax, eax
			cpuid						;serialize
			rdtsc						;read time stamp counter to EDX:EAX
			shl			rdx, 32
			or			rax, rdx
			mov			[r14+r15], rax	;save in list
			xor			eax, eax
			cpuid						;serialize again

			;put your test code here:
			REPT 100
			shr rax, 5
			ENDM

			xor			eax, eax
			cpuid						;serialize
			rdtsc						;read time stamp counter to EDX:EAX
			shl			rdx, 32
			or			rax, rdx
			sub			rax, [r14+r15]
			mov			[r14+r15], rax	;save difference in list
			xor			eax, eax
			cpuid						;serialize again

			add			r15d, 8
			cmp			r15d, NUMTESTS*8
			jb			CLOOP2

			;substract overhead from clock count:
			xor r15d, r15d
			mov r14, clocks
			mov rax, overhead
OVHLOOP:
			sub [r14+r15], rax
			add r15d, 8
			cmp r15d, NUMTESTS*8
			jb OVHLOOP

			mov eax, NUMTESTS
			ret
Serial ENDP
END