;******************************************************************************
;* C7x G3 C/C++ Codegen                                                PC v5.0.0.LTS *
;* Date/Time created: Mon Sep  1 10:07:05 2025                                *
;******************************************************************************
	.compiler_opts --abi=eabi --endian=little --hll_source=on --mma_version=1 --object_format=elf --silicon_version=7100 --symdebug:none 

;******************************************************************************
;* GLOBAL FILE PARAMETERS                                                     *
;*                                                                            *
;*   Architecture      : C7100                                                *
;*   MMA               : MMA1
;*   Endian            : Little                                               *
;*   Pipelining        : Enabled                                              *
;*   Debug Info        : No Debug Info                                        *
;*                                                                            *
;******************************************************************************

	.asg	D14, FP
	.asg	D15, SP
	.global	$bss

	.global	||global_array||
	.sect	".data:global_array", RW
	.align	4
	.elfsym	||global_array||,SYM_SIZE(12)
||global_array||:
	.bits		0x1,32
			; global_array[0] @ 0
	.bits		0x2,32
			; global_array[1] @ 32
	.bits		0x3,32
			; global_array[2] @ 64

	.sect	".const:$P$T0$1"
	.align	4
	.elfsym	||$P$T0$1||,SYM_SIZE(12)
||$P$T0$1||:
	.bits		0x1,32
			; $P$T0$1[0] @ 0
	.bits		0x2,32
			; $P$T0$1[1] @ 32
	.bits		0x3,32
			; $P$T0$1[2] @ 64

	.sect	".const:$P$T1$2"
	.align	4
	.elfsym	||$P$T1$2||,SYM_SIZE(12)
||$P$T1$2||:
	.bits		0x1,32
			; $P$T1$2[0] @ 0
	.bits		0x2,32
			; $P$T1$2[1] @ 32
	.bits		0x3,32
			; $P$T1$2[2] @ 64

;	opt7x C:\\Users\\dx\\AppData\\Local\\Temp\\{DA668544-AA86-420E-97D5-104EA2F646FD} C:\\Users\\dx\\AppData\\Local\\Temp\\{BD5AA658-EDDA-4A25-A96B-B9AD69589416} --advice:performance=stdout 
;	acpia7x -@C:\\Users\\dx\\AppData\\Local\\Temp\\{BB8A4D8C-F56B-4B2F-86C5-5239E9EC475A} 
	.sect	".text"
	.clink
	.global	||main||

;******************************************************************************
;* FUNCTION NAME: main                                                        *
;*                                                                            *
;*   Regs Modified     : A0,A1,A2,A4,VB0,VB1,AL0,AL1,D0,D1,D2,D3,SP,P0,P1     *
;*   Regs Used         : A0,A1,A2,A4,VB0,VB1,AL0,AL1,D0,D1,D2,D3,SP,P0,P1     *
;*   Local Frame Size  : 0 Args + 36 Auto + 0 Save = 36 byte                  *
;******************************************************************************
||main||:
;** --------------------------------------------------------------------------*
;*** 22	-----------------------    a = $P$T0$1;
;*** 23	-----------------------    b = $P$T1$2;
;***  	-----------------------    U$16 = a = &a[0];
;***  	-----------------------    U$18 = b = &b[0];
;***  	-----------------------    U$21 = out = &out[0];
;*** 14	-----------------------    L$1 = 3;  // [1]
;***  	-----------------------    #pragma MUST_ITERATE(3, 3, 3)
;***  	-----------------------    #pragma UNROLL(1)
;***  	-----------------------    #pragma LOOP_FLAGS(4096u)
;***	-----------------------g2:
;*** 16	-----------------------    *U$21++ = *U$16+++*U$18++;  // [1]
;*** 14	-----------------------    if ( L$1 = L$1-1 ) goto g2;  // [1]
           ADDKPC  .D1     $PCR_OFFSET((||$P$T0$1||+0)),D3 ; [A_D1] |22| 

           VLD16B  .D1     *D3++(64),VB1     ; [A_D1] |22| 
||         ADDKPC  .D2     $PCR_OFFSET((||$P$T1$2||+0)),D2 ; [A_D2] |23| 

           VLD16B  .D1     *D2++(64),VB0     ; [A_D1] |23| 
           MASKB   .P2     0xc,P1            ; [B_P] |22| 

           ADDD    .D1     SP,0xffffffd8,SP  ; [A_D1] 
||         MASKB   .P2     0xc,P0            ; [B_P] |23| 


           ADDD    .D1     SP,0x1c,A2        ; [A_D1] 
||         ADDD    .D2     SP,0x10,D0        ; [A_D2] |22| 

           ADDD    .D1     SP,0x1c,D0        ; [A_D1] |23| 
||         VSTP16B .D2     P1,VB1,*D0(0)     ; [A_D2] |22| 


           VSTP16B .D2     P0,VB0,*D0(0)     ; [A_D2] |23| 
||         ADDD    .D1     SP,0x10,A1        ; [A_D1] 

           MV      .D1     A2,D2             ; [A_D1] 
||         MV      .D2     A1,D1             ; [A_D2] 


           LDW     .D1     *D2++(4),AL1      ; [A_D1] |16| <0,1> 
||         LDW     .D2     *D1++(4),AL0      ; [A_D2] |16| <0,1> 

           UNPROT          0x1               ; [A_U] 
;*----------------------------------------------------------------------------*
;*  SOFTWARE PIPELINE INFORMATION
;*    Loop found in file               : weighted_sum.cpp
;*    Loop source line                 : 14
;*    Loop opening brace source line   : 15
;*    Loop closing brace source line   : 17
;*
;*    Summary:
;*      - The compiler successfully software pipelined this loop.
;*      - The compiler cannot start scheduling attempts at an ii lower
;*        than 2 due to a resource limitation (partitioned resource bound).
;*
;*    Known Minimum Iteration Count    : 3
;*    Known Maximum Iteration Count    : 3
;*    Known Max Iteration Count Factor : 3
;*    Loop Carried Dependency Bound(^) : 0
;*    Partitioned Resource Bound       : 2 (pre-sched)
;*
;*    Searching for software pipeline schedule at ...
;*      ii = 2  Schedule found with 3 iterations in parallel (pruning)
;*
;*    Partitioned Resource Bound(*)    : 2 (post-sched)
;*
;*    Resource Partition (may include "post-sched" split/spill moves):
;*
;*                                                A-side   B-side
;*
;*      Bound(.C2)                                   -        0     
;*      Bound(.P2)                                   -        0     
;*      Bound(.D)                                    2*       -     
;*      Bound(.M .N .MN)                             0        0     
;*      Bound(.L .S .LS)                             0        0     
;*      Bound(.L .S .C .LS .LSC)                     0        0     
;*      Bound(.L .S .C .M .LS .LSC .LSCM)            0        0     
;*      Bound(.L .S .C .M .D .LS .LSC .LSCM .LSCMD)  1        0     
;*
;*    Done
;*
;*
;*    Minimum safe iteration count    : 3 (pruned)
;*    (The compiler performed iteration pruning because the iteration count is
;*    precisely known and the number of iterations in parallel would be
;*    greater than the iteration count with ordinary software pipelining. 
;*    Iteration pruning makes this schedule legal in these circumstances.
;*     Some or all of the loop control instructions have been removed.)
;*----------------------------------------------------------------------------*
;*      SINGLE SCHEDULED ITERATION
;*
;*      ||$C$C32||:
;*   1              LDW     .D1     *D1++(4),AL0      ; [A_D1] |16| 
;*     ||           LDW     .D2     *D2++(4),AL1      ; [A_D2] |16| 
;*   2              NOP             0x5               ; [A_B] 
;*   7              ADDW    .L1     AL1,AL0,D3        ; [A_L1] |16| 
;*   8              STW     .D1     D3,*D0++(4)       ; [A_D1] |16| 
;*   9              ; BRANCHCC OCCURS {||$C$C32||}    ; [] |14| 
;*----------------------------------------------------------------------------*
||$C$L1||:    ; PIPED LOOP PROLOG

           LDW     .D1     *D1++(4),AL0      ; [A_D1] |16| <1,1> 
||         LDW     .D2     *D2++(4),AL1      ; [A_D2] |16| <1,1> 

           ADDD    .D1     SP,0x28,A0        ; [A_D1] 

           LDW     .D1     *D1++(4),AL0      ; [A_D1] |16| <2,1> 
||         LDW     .D2     *D2++(4),AL1      ; [A_D2] |16| <2,1> 

           MV      .D1     A0,D0             ; [A_D1] 
;** --------------------------------------------------------------------------*
||$C$L2||:    ; PIPED LOOP KERNEL
           ADDW    .L1     AL1,AL0,D3        ; [A_L1] |16| <0,7> 
           STW     .D1     D3,*D0++(4)       ; [A_D1] |16| <0,8> 
;** --------------------------------------------------------------------------*
||$C$L3||:    ; PIPED LOOP EPILOG
;*** 29	-----------------------    return 0;

           MVKU32  .S1     0,A4              ; [A_S1] |29| 
||         ADDD    .D1     SP,0x28,SP        ; [A_D1] 
||         ADDW    .L1     AL1,AL0,D1        ; [A_L1] |16| <1,7> 

           STW     .D1     D1,*D0++(4)       ; [A_D1] |16| <1,8> 
           ADDW    .L1     AL1,AL0,D1        ; [A_L1] |16| <2,7> 
           STW     .D1     D1,*D0++(4)       ; [A_D1] |16| <2,8> 

           RET     .B1     ; [A_B] 
||         PROT                               ; [A_U] 

           ; RETURN OCCURS {RP}              ; [] 
;* Inlined function references:
;* [1] _Z12weighted_sumPiS_S_iii
