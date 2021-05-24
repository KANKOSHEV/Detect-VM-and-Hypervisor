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



END