.table
char stringTeste__main [] = ""
int a__main
int true = 1
int false = 0
.code
add $1, 1, 3
mul $2, 1, 4
seq $0, $1, $2
and $0, $0, true
mov $1, 1
mov $2, 2
seq $4, $1, $2
or $0, $0, $4
mov a__main, $0
println a__main
nop
