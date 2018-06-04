section .text
global f
extern printf
section .data
	; rdi - PixelBuffer
	; rsi - Width
	; rdx - Height
	; xmm0 - a, xmm0+8 ? - b xmm0+16 ? - c
	; xmm1 - S
LC0: dd 10.0
section .text
f:
  push rbp
  mov rbp, rsp

  mov QWORD  [rbp-24], rdi
  mov DWORD  [rbp-28], esi
  mov DWORD  [rbp-32], edx
  mov DWORD  [rbp-36], ecx
  mov QWORD  [rbp-48], r8
  movss DWORD  [rbp-40], xmm0
  mov DWORD  [rbp-52], r9d
  mov eax, DWORD  [rbp-32]
  sub eax, 1
  imul eax, DWORD  [rbp-36]
  cdqe
  add QWORD  [rbp-24], rax
  mov DWORD  [rbp-4], 10
  jmp .L2
.L3:
  mov eax, DWORD  [rbp-4]
  movsx rdx, eax
  mov rax, QWORD  [rbp-24]
  add rax, rdx
  movzx edx, BYTE  [rax]
  mov eax, DWORD  [rbp-4]
  movsx rcx, eax
  mov rax, QWORD  [rbp-24]
  add rax, rcx
  add edx, 100
  mov BYTE  [rax], dl
  add DWORD  [rbp-4], 1
.L2:
  cmp DWORD  [rbp-4], 20000
  jle .L3
  nop

  pop rbp
  ret



