//Reto 1: "Carga en D el valor 1978"
@1978
D=A

//Reto 2: "Guarda en la posición 100 de la RAM el número 69"
@69
D=A

@100
M=D //Porque M es el valor de la RAM en la posición 100

//Reto 3: "Guarda en la posición 200 de la RAM el contenido de la posición 24 de la RAM"
@420
D=A //Creo un valor cualquiera...
@24
M=D //...y lo guardo en la posición 24.

//@24 <-- No es necesario, ya que M ya tiene el valor de la posición 24
D=M
@200
M=D

//Reto 4: "Lee lo que hay en la posición 100 de la RAM, resta 15 y guarda el resultado en la posición 100 de la RAM"
