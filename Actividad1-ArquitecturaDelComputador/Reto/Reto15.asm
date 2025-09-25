@R1
D=M //Tomo el tamaño de la región de memoria
@j
M=D //Lo guardo en j

(LOOP)
@R0
D=M //Inicio D en el valor de R0
@j
A=D+M //Sumo el valor de j a D y voy a esa posición (lo coloco en A)

M=-1 //Le asigno el valor -1 a la posición

//if j == 0
@j
D=M
@END //Salta a END
D;JEQ
//if j != 0
@j
M=M-1 //j -= 1
@LOOP //Salta a LOOP
0;JMP

(END)
@END //Finalización adecuada wooo
0;JMP