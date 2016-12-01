/*========================================================================================
*                                                                                      *
*               Copyright(c) 2016, Steve.Cha, All rights reserved.                     *
*                                                                                      *
* Permission to use, copy, modify, and distribute this software in source and binary   *
* forms and its documentation for any purpose and without fee is hereby granted,       *
* provided that the above copyright notice appear in all copies and that both that     *
* copyright notice and this permission notice appear in supporting documentation.      *
*                                                                                      *
* THIS SOFTWARE IS PROVIDED BY THE Steve.Cha AND CONTRIBUTORS "AS IS" AND ANY          *
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED            *
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.   *
* IN NO EVENT SHALL Steve.Cha OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,      *
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT         *
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,          *
* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF            *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE      *
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,                    *
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                   *
*                                                                                      *
========================================================================================*/

#include "co_kernel.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////

__ASM__ VOID chaos_svc_handler(VOID)
{
    TST     LR, #4                  // LR 비트 2 안에 있는 EXE_RETURN 번호를 테스트
    ITE     EQ                      // 만약 0(같으면) 이면,
    MRSEQ   R1, MSP                 // 메인 스택이 사용되고, MSP를 R0에 넣음
    MRSNE   R1, PSP                 // 그렇지 않으면 PSP를 R0에 넣음

    LDR     R0, [R1, #24]           // PC 값을 얻음
    LDRB    R0, [R0, #-2]           // SVC 번호를 얻음

    LDR     R2, =__cpp(_handler_svc)
    BX      R2
}




__ASM__ VOID chaos_pendsvc_handler(VOID)
{
    IMPORT          g_kernel;

    PUSH        {R14}

    // Load Current and Next task pointer
    LDR         R1, =g_kernel       // R1 : Current Task pointer
    ADDS        R2, R1, #4          // R2 : Next Task pointer

    LDR         R0, [R1]
    LDR         R3, [R2]
    CMP         R0, R3
    BEQ         exit_pend_svc

#if 1
    /* get PSP(process stack pointer) of current task */
    MRS         R0, PSP
    ISB

    /* load address of current task */
//    LDR         R1, =g_kernel
//    ADDS        R2, R1, #4
//    LDR         R2, [R3]

    /* save FPU/System registers */
    TST         R14, #0x10
    IT          EQ
    VSTMDBEQ    R0!, {S16-S31}
    STMDB       R0!, {R4-R11, R14}

    /* save new SP of current task */
    LDR         R3, [R1]
    STR         R0, [R3]


    /* load SP of next task */
    LDR         R0, [R2]
    LDR         R0, [R0]

    /* restore FUP/System registers */
    LDMIA       R0!, {R4-R11, R14}
    TST         R14, #0x10
    IT          EQ
    VLDMIAEQ    R0!, {S16-S31}

    /* set PSP(process stack pointer) of new task */
    MSR         PSP, R0

    LDR         R0, [R2]
    STR         R0, [R1]
#endif

exit_pend_svc
    POP         {R14}
    BX          R14
}

VOID chaos_systick_handler(VOID)
{
    _handler_systick();

    //chaos_pendsvc_handler();
}
//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

