@sum
@j //Inicializo sum y j primero para que no estorben en el array
@arr //Ahpora inicializo el array para poder llenar de aquí en adelante

//Voy a volver a llenar el array en reversa profe, paila JAJAJAJJA
@10
D=A
@j
M=D //Asigno a j el valor 10 para poder recorrer los 10 espacios del array

(LOOP)
//if j == 0
@j
D=M
@END
D;JEQ //Saltar a END

//else
@arr
D=A
@j
D=D+M //D será igual a la posición final del array, y se devolverá 1 puesto en cada iteración
A=D //Ir a esa posición

D=M //Tomar el valor en esa posición
@sum
M=D+M //Sumarlo a sum **NOTA PERSONAL:** Acá toca poner D+M, porque M+D manda un error en Nand2Tetris

@j
M=M-1 //Disminuye j
@LOOP
0;JMP //Repetir el ciclo

(END)
@END
0;JMP //Fin adecuado