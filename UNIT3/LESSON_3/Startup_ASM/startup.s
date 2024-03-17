.section .vector

.word 		0x20001000							/* address of sp (stack pointer)   */
.word 		_Reset								/* reset section 				   */
.word 		Vector_Handler						/* 2  NMI (non maskable interrupt) */
.word 		Vector_Handler 						/* 3  Hard Fault                   */
.word 		Vector_Handler 						/* 4  MM Fault (Memory Management) */
.word 		Vector_Handler 						/* 5  Bus Fault                    */
.word 		Vector_Handler 						/* 6  Usage Fault                  */
.word 		Vector_Handler 						/* 7  RESERVED                     */
.word 		Vector_Handler 						/* 8  RESERVED                     */
.word 		Vector_Handler 						/* 9  RESERVED                     */
.word 		Vector_Handler 						/* 10 RESERVED                     */
.word 		Vector_Handler 						/* 11 SV call                      */
.word 		Vector_Handler 						/* 12 Debug reserved               */
.word 		Vector_Handler 						/* 13 RESERVED                     */
.word 		Vector_Handler 						/* 14 PendSV                       */
.word 		Vector_Handler 						/* 15 SysTick                      */
.word 		Vector_Handler 						/* 16 IRQ0                         */
.word 		Vector_Handler 						/* 17 IRQ1                         */
.word 		Vector_Handler 						/* 18 IRQ2                         */
.word 		Vector_Handler						/* 19 ...                          */

.section .text

_Reset:
	bl main
	b .

.thumb_func

Vector_Handler:
	b _Reset