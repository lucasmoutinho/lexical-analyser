.table
char stringTeste__main [] = ""
int a__main
int true = 1
int false = 0
.code
mov $3, 1
inttofl $5, $3
mov $6, 1.0
mul $1, $5, $6
mov $5, 3.0
mov $3, 1
inttofl $6, $3
div $2, $5, $6
mov $3, 2
inttofl $5, $3
add $2, $5, $2
seq $0, $1, $2
mov a__main, $0
println a__main
nop
