.CODE
BEShit PROC ;BE Shit 
pushfq
or dword ptr[rsp],10100h
popfq
db 0fh
db 0a2h
nop
nop
nop
ret
BEShit ENDP


CheckInd PROC
pushfq
cli
push 1                 ; Set cache data
wbinvd                 ; Flush writeback data set from previous instruction to system memory.
mov byte ptr [rsp], 0  ; Set memory to 0. This is in WB memory so it will not be in system memory.
invd                   ; Flush the caches but do not write back to system memory. Real hardware will result in loss of previous operation.
pop rax                ; Proper system behaviour will have AL = 1; Hypervisor/emulator that uses WBINVD or does nothing will have AL = 0.
popfq
ret
CheckInd ENDP




LBRVirt PROC
 mov rcx, 01D9h
    xor rdx, rdx
    wrmsr
    rdmsr
    shl rdx, 20h	; EDX:EAX for wrmsr
    or rax, rdx
    jmp check_msr

check_msr:
    test al, 1
    jnz no_detect
    mov al, 1
    ret
    
no_detect:
    xor rax, rax
    xor rdx, rdx
    mov rdx, 01D9h
    wrmsr
    ret
LBRVirt ENDP


END