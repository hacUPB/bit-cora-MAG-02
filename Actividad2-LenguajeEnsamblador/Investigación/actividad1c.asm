//Bueno la idea es hacer un código simple. Veamos.
(LOOP)
    @69 //Char Code de "E"
    D=A
    @KBD
    D=M-D //Si se presiona "E", D == 0

    @DRAW //Salta a DRAW si D == 0
    D;JEQ
    @LOOP //Else, vuelve al LOOP
    0;JMP

(DRAW)
    @SCREEN //Va a la primera posición de screen
    D=A     //La almacena en D
    @j
    D=D+M   //Suma j a la posición en D
    A=D     //Va a la posición
    M=-1    //Escribe -1 (porque -1 llena ese pedazo de pantalla)

    @j
    M=M+1   //Incrementa j

    @LOOP
    0;JMP