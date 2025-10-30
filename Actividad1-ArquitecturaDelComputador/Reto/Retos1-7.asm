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
@100
D=M

@15
D=D-A

@100
M=D

//Reto 5: "Suma el contenido de la posición 0 de la RAM, el contenido de la posición 1 de la RAM y con la constante 69.
//          Guarda el resultado en la posición 2 de la RAM"
//Primero voy a ponerles contenido a las posiciones 0 y 1
@0
M=M+1
@1
M=M+1 //Simplecito porque soy un perezoso

@0
D=M
@1
D=D+M
@69
D=D+A
@2
M=D //Done!

//Reto 6: "Si el valor almacenado en D es igual a 0 salta a la posición 100 de la ROM"
@100
D;JEQ //Creo que no va a pasar absolutamente nada en este código, pero si D está en cero debería saltar o7

//Reto 7: "Si el valor almacenado en la posición 100 de la RAM es menor a 100 salta a la posición 20 de la ROM"
@100
D=M //Toma el valor almacenado en la pos 100
D=D-A //Le resta 100 para poder comparar respecto a 0

@20
D;JLT //Si el valor era >100 o 100, el resultado es >0 o 0. De lo contrario, es <0, y realiza el salto.