.code

sum proc
;int sum(int a, int b)
;RCX - a
;RDX - b
;�������: RAX


	mov eax, ecx
	add eax, edx

	ret

sum endp

end