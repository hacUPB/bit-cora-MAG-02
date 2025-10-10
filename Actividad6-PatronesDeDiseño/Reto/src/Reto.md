# Reto

Desarrolla un proyecto de arte generativo interactivo en tiempo real. Diferente, lo más que puedas al caso de estudio.

## Requisitos

- Utilizando **C++** y **openFrameworks**.
- Aplica el patrón de diseño **Observer**.
- Aplica el patrón de diseño **Factory**.
- Aplica el patrón de diseño **State**.
- Realiza pruebas desde el inicio del desarrollo para garantizar el correcto funcionamiento de la aplicación.

## Desarrollo
Okay, modo reto, que rinda hoy x Diosito

### Estados
* **IsWhite:** Estado para la clase de partícula *Hole*, que los hace repeler partículas tipo *Planet* y *Comet*
* **IsBlack:** Lo mismo que *IsWhite*, pero ps pa' atraer las otras partículas lol
* **Normal:** Estado por defecto para *Planet* y *Comet*, que los hace moverse en una dirección aleatoria `onEnter()`.
* **Ignore:** Hace a las partículas *Planet* y *Comet* ignorar las partículas de tipo *Hole* y simplemente mantener su movimiento al momento de cambiar estados.
* **Attend:** Lo opuesto a *Ignore*.