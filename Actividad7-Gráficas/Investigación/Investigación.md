# Experiencia de Aprendizaje 7: Gráficas

## Introducción
En esta unidad vas a interactuar con un dispositivo del computador que te permite pintar en pantalla a altas velocidades. Este dispositivo es la tarjeta gráfica o Graphics Processing Unit (GPU). La GPU es un dispositivo que se encarga de procesar y enviar señales de video a la pantalla del computador. Es un dispositivo especializado en procesar gráficos y video. Aunque actualmente también se usa, y mucho, para trabajar con inteligencia artificial y aprendizaje profundo.  
La idea de esta experiencia de aprendizaje es que te familiarices con los conceptos básicos de la programación de la GPU, es decir, que experimentes a nivel introductorio con ***shaders*** y que además veas cómo comunicar la CPU con la GPU para realizar aplicaciones interactivas.

> Así irán las conclusiones que haga al comparar respuestas con ChatGPT

## Actividad 1
#### ¿Qué son los vértices?
Coordenadas en un plano 3D, que también pueden tener otra info pero ps mayormente son solo coordenadas.
> También puede contener color, normales, coordenadas de textura, etc.
#### ¿Con qué figura geométrica se dibuja en 3D?
Triángulos!
> Correct! El conjunto de triángulos es la *mesh*
#### ¿Qué es un shader?
Programas cortos que se ejecutan en la GPU. En el tutorial *"Introducing Shaders"*, mencionan que estos son escritos en **GLSL**.
> Correcto as well. Específicamente sirven para decidir cómo se dibujan los vértices y cómo se colorean los píxeles, y se escriben en lenguajes como GLSL, HLSL o Metal.
#### ¿Cómo se le llaman a los grupos de píxeles de un mismo triángulo?
Creo que se les llama "fragments".
> Yes, y cada fragmento representa un posible píxel del triángulo antes de decidir si se dibuja o no (dependiendo de profundidad, transparencia, etc.).
#### ¿Qué es un fragment shader?
Uno de estos fragmentos de código de **GLSL**, específicamente dirigido a los triángulos que se forman entre vértices.
> Específicamente es quien decide qué color tendrá cada fragmento. Aquí se aplican texturas, luces, sombras y efectos visuales.
#### ¿Qué es un vertex shader?
Otro fragmento de código de **GLSL**, específicamente dirigido a los vértices.
> Sí es pero no dije qué hace. El vertex shader es el programa que se ejecuta una vez por cada vértice. Su función es transformar la posición del vértice desde el espacio 3D hasta la posición en pantalla, además de calcular cosas como normales o coordenadas de textura.
#### ¿Al proceso de determinar qué pixels del display va a cubrir cada triángulo de una mesh se le llama?
Resterización!
> Correct! La rasterización convierte los triángulos (definidos por vértices en 3D) en fragmentos (píxeles en 2D) para poder pintarlos en el framebuffer.
#### ¿Qué es el render pipeline?
Es el "paso a paso" o el "orden de actividades" que siguen la mayoría de videojuegos modernos para mostar un solo frame en la pantalla del usuario. Este proceso está sucediendo constantemente, por lo general 60 veces por segundo.
> Yes, y algunas de sus etapas son:
> 1. Procesar vértices (vertex shader)
> 2. Ensamblar triángulos
> 3. Rasterizar (convertir triángulos a píxeles)
> 4. Calcular color de cada fragmento (fragment shader)
> 5. Escribir los resultados en el framebuffer
#### ¿Hay alguna diferencia entre aplicar un color a una superficie de una mesh o aplicar una textura?
Generalmente las texturas traen más información (como valores normales, de altura, etc.), pero realmente se hace de la misma manera, que es asignando este color o textura a un grupo de triángulos para así afectar su render final (creo que afectaría la rasterización más que nada).
> Pa' ser más específico:
> Un color puede ser único o uniforme para todo el objeto o vértice, mientras que una textura es una imagen (bitmap) que se “envuelve” sobre la superficie del modelo, usando coordenadas UV.  
> En otras palabras, una textura es una fuente de color mucho más detallada y variable.
#### ¿Cuál es la diferencia entre una textura y un material?
Un material puede contener texturas. Los materiales se le aplican a objetos en un ambiente 3D y las texturas son tan solo una parte de la información que puede cargar un material.
> Yeah, correct! Un material es un conjunto de propiedades físicas o visuales que definen cómo responde un objeto a la luz (puede incluir varias texturas, reflectividad, rugosidad, etc.).
#### ¿Qué transformaciones se requieren para mover un vértice del 3D world al View Screen?
Se convierten las *coordenadas locales* a *coordenadas del mundo*, luego se convierten en coordenadas en la imágen (cámara), y finalmente se envían al *View Screen*.
> Correcto! Según *ChatGPT*, a este proceso se le llama *"MVP Matrix"*, MVP siendo *"Model-View-Projection"*. 
#### ¿Al proceso de convertir los triángulos en fragmentos se le llama?
Rasterización también? Ahí sí me perdí :c
> Sí es rasterización! Wooo. La definición de ChatGPT dice "Es la etapa en la que se determinan los píxeles que corresponden a cada triángulo".
#### ¿Qué es el framebuffer?
Es la "fila" de frames que están listos para mostrarse al usuario.
> Lo que dije no está mal, pero sí muy simplificado. ChatGPT dijo:  
> "El framebuffer es una región de memoria donde se almacena la imagen final renderizada, antes de ser mostrada en pantalla. Contiene buffers para color, profundidad (Z-buffer) y, a veces, transparencia o stenci".
#### ¿Para qué se usa el Z-buffer o depth buffer en el render pipeline?
Para diferenciar qué objeto debería verse en pantalla, y qué objetos en realidad están siendo cubiertos por otro objeto.
> Correct! Se podría decir que guarda la profundidad, es decir, la distancia a la cámara. 
### Luego de ver el segundo video entiendes por qué la GPU tiene que funcionar tan rápido y de manera paralela. ¿Por qué?
El trabajo en paralelo es nada más una cuestión de que la GPU necesita realizar muchísimos cálculos al mismo tiempo. ¿Por qué tiene que hacer todo eso? Porque es la encargada de dar el feeback visual al usuario, y ps ese tiene que ser muy muy rápido y consistente.
> Resumen, cortesía de ChatGPT:  
> "En resumen: la GPU tiene que ser rápida **porque** debe procesar enormes volúmenes de datos gráficos en muy poco tiempo; y debe ser paralela **porque** esos datos (píxeles, vértices) muchas veces requieren el mismo tipo de operación aplicada a cada uno, lo que se puede distribuir entre muchos núcleos simultáneamente".

Comentario no relacionado: ¿Por qué ChatGPT decidió resaltar los "porque"? Que palabra tan mid.

## Actividad 2
#### ¿Cómo funciona?
El código simplemente carga los shaders en `setup()` y en `draw()` crea un rectángulo de color blanco, pero antes de crearlo llama a los shaders para que empiecen.
#### ¿Qué resultados obtuviste?
Al hacer el experimento de comentar los llamados de shaders, simplemente aparecía un rectángulo blanco, pero al incluir los shaders el rectángulo pasaba a tener un difuminado de colores bastante lindo.
#### ¿Estás usando un vertex shader?
En teoría sí, pero realmente no veo qué está logrando. Según yo, el rectángulo creado ya existe en la posición necesaria, pero quizá el vertex shader está considerándolo como 2 triángulos? No estoy seguro del todo, so:
> Chat GPT dice que, aunque no aporte mucho, el shader sí se está utilizando. El pipeline de OpenGL siempre pasa por ambos shaders.
#### ¿Estás usando un fragment shader?
Claro que sí! Cuando comentamos el `shader.begin()` y `shader.end()` solo se vio un rectángulo blanco, entonces el fragment shader sí o sí tiene que estar haciendo algo.
#### Analiza el código de los shaders. ¿Qué hace cada uno?
`shader.vert`:  
No sé que es un `uniform` *(sé que lo vamos a ver ahorita pero ajá)*, pero lo llama primero. Luego, multiplica ese `uniform` por la posición del *vertex*, y ps ya.  
`shader.frag`:  
Toma la coordenada *x* del *fragment* y la divide entre *1024*, luego divide la *y* entre *768*, y luego asigna esos resultados al valor de rojo *r* y el de verde *g* del *fragment* respectivamente. Esto es lo que causa el degradado de colores, pues el color final del *fragment* está cambiando levemente según la coordenada.

## Actividad 3
#### ¿Qué es un uniform?
Pues por solo lógica y a punta de adivinar, diré que un uniform es casi como un "static", en el sentido de que se puede cambiar de manera general para todo el código.
> En *GLSL*, un `uniform` es una **variable global de solo lectura** que el **programa C++ (`ofApp`)** le envía al shader **desde la CPU hacia la GPU** antes de dibujar algo.
#### ¿Cómo funciona el código de aplicación, los shaders y cómo se comunican estos?
El código, en muy resumidas cuentas, está creando un plano de vértices y cambiando constantemente la variable `globalColor` llamando `ofSetColor()`. El color se determina según la coordenada en *x* del mouse, y la rotación del plano según la *y*.  
Los shaders cambiaron papeles esta vez, y ahora el vertex es el que más cosas está haciendo:  
`shader.vert`:  
Está tomando una variable `time` que le envió el programa como un `uniform`. Usando eso y la posición actual en *x* del *vertex* específico, crea una onda de seno en el plano, ya la va moviendo hacia la derecha afectando las posiciones en *y* de los distintos *vertex*.  
`shader.frag`:  
Este no es que no esté haiciendo nada, solo está haciendo mucho menos que la anterior :p Esta vez él se encarga de cambiar el color de salida los `fragments` a `globalColor`, y yap :>
#### Modifica el código de la actividad para cambiar el color de cada uno de los píxeles de la pantalla personalizando el fragment shader.
