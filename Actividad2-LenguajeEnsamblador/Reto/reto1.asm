//Sumar los primeros 100 naturales usando una variable i y una sum
@i
M=1 //i empieza en 1, mientras que sum empieza en 0

(LOOP)    
    @100
    D=A
    @i
    D=D-M //Resta a D (que es 100) el valor de i.

    @END
    D;JLT //Salta a END si la resta da menos que 0 --> not (i <= 100)

    //else
    @i
    D=M
    @sum
    M=D+M //Suma i a sum

    @i
    M=M+1

    @LOOP
    0;JMP

(END)
    @END
    0;JMP
