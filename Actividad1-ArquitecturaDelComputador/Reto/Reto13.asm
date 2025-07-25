//Ya encontré el ejemplo respectivo en el doc, que bendición
@R0
D=M //Guarda el contenido de R0 en D
@POS
D;JGE //Salta a POS si D es >= 0

@R1 //Esta parte se ejecuta si D < 0
M=-1
@END
0;JMP //Salta al final si logra llegar acá

(POS)
@R1 //Esta parte solo se ejecuta si se saltó, es decir,
M=1 //si D era >= 0

(END) //Para saltarse el cambio de valor de R1.

//Voy a escribir primero la parte del loop y la bajo :p
(LOOP)
@LOOP
0;JMP //Esta estuvo facilita