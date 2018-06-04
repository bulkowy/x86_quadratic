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

  mov QWORD [rbp-24], rdi
  mov DWORD [rbp-28], esi
  mov DWORD [rbp-32], edx
  mov QWORD [rbp-40], rcx
  movss DWORD [rbp-44], xmm0
  mov DWORD [rbp-48], r8d
  mov DWORD [rbp-4], 60
  jmp L2
L3:
  mov edx, DWORD [rbp-4]
  mov eax, edx
  add eax, eax
  add eax, edx
  movsx rdx, eax
  mov rax, QWORD [rbp-24]
  add rax, rdx
  movzx ecx, BYTE [rax]
  mov edx, DWORD [rbp-4]
  mov eax, edx
  add eax, eax
  add eax, edx
  movsx rdx, eax
  mov rax, QWORD [rbp-24]
  add rax, rdx
  lea edx, [rcx+100]
  mov BYTE [rax], dl
  add DWORD [rbp-4], 1
L2:
  cmp DWORD [rbp-4], 90
  jle L3
  nop

  pop rbp
  ret



