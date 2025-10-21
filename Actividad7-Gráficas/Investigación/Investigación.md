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
#### ¿Qué es el framebuffer?
Es la "fila" de frames que están listos para mostrarse al usuario.
#### ¿Para qué se usa el Z-buffer o depth buffer en el render pipeline?
Para diferenciar qué objeto debería verse en pantalla, y qué objetos en realidad están siendo cubiertos por otro objeto.

### Luego de ver el segundo video entiendes por qué la GPU tiene que funcionar tan rápido y de manera paralela. ¿Por qué?
El trabajo en paralelo es nada más una cuestión de que necesita realizar muchísimos cálculos al mismo tiempo. ¿Por qué tiene que hacer todo eso? Porque es la encargada de dar feeback muy directo al Usuario. 