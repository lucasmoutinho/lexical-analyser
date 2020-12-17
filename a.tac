.table
char stringTeste__main [] = ""
int a__main
int true = 1
int false = 0
.code
mov $5, 3.0
mov $3, 1
inttofl $6, $3
div $3, $5, $6
mov $3, 2
inttofl $5, $3
add $3, $5, $3
fltoint $0, $3
mov a__main, $0
println a__main
nop
