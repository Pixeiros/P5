PAV - P5: síntesis musical polifónica
=====================================

Obtenga su copia del repositorio de la práctica accediendo a [Práctica 5](https://github.com/albino-pav/P5) y
pulsando sobre el botón `Fork` situado en la esquina superior derecha. A continuación, siga las instrucciones de la
[Práctica 3](https://github.com/albino-pav/P3) para crear una rama con el apellido de los integrantes del grupo de
prácticas, dar de alta al resto de integrantes como colaboradores del proyecto y crear la copias locales del
repositorio.

Como entrega deberá realizar un pull request con el contenido de su copia del repositorio. Recuerde que los
ficheros entregados deberán estar en condiciones de ser ejecutados con sólo ejecutar:

~~~~~~~~~~~~~~~~~~~.sh
  make release
~~~~~~~~~~~~~~~~~~~

A modo de memoria de la práctica, complete, en este mismo documento y usando el formato markdown, los ejercicios
indicados.

Ejercicios.
-----------

### Envolvente ADSR.

Tomando como modelo un instrumento sencillo (puede usar el InstrumentDumb), genere cuatro instrumentos que permitan
visualizar el funcionamiento de la curva ADSR.
  
   > Si analizamos InstrumentDumb, podemos visualizar perfectamente los parámetros de su curva ADSR. 
  
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.sh
      1	InstrumentDumb    ADSR_A=0.02; ADSR_D=0.1; ADSR_S=0.4; ADSR_R=0.1; N=40;
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   > - Ataque en 20ms → Ataca hasta llegar al nivel de 1 y tarda en hacerlo 20ms. 
    <img src="img/1.png" width="500" align="center">
   > 
   > - Caída en 0.1s → Cae hasta el nivel 0.4 en 0.1s.
    <img src="img/2.png" width="500" align="center">
   > 
   > - Mantenimiento en 0.4 → Mientras aguanta la nota, se mantiene en el nivel 0.4. Como el nivel maximo es 12901, * 0.4 =     5175 es aproximadamente el nivel en el que se mantiene.
    <img src="img/3.png" width="500" align="center">
   > 
   > - Liberación en 0.1s → En cuanto soltemos la nota cae respecto al nivel 0.1.
    <img src="img/4.png" width="500" align="center">
   > 
   > - N → número de muestras de la tabla en la que almacenaremos la forma de un periodo, es 40.
  
 
* Un instrumento con una envolvente ADSR genérica, para el que se aprecie con claridad cada uno de sus parámetros:
  ataque (A), caída (D), mantenimiento (S) y liberación (R).
  
  >  <img src="img/5.png" width="500" align="center">
  >
  >  - 0.0000000 0.0200291 Attack
  >  - 0.0200291 0.1200021 Decay
  >  - 0.1200021 0.5000164 Sustain
  >  - 0.5000164 0.6001235 Release

* Un instrumento percusivo, como una guitarra o un piano, en el que el sonido tenga un ataque rápido, no haya
  mantenimiemto y el sonido se apague lentamente.
  > Para el instrumento de percusion en el fichero.orc escribimos lo siguiente:
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.sh
     1	InstrumentDumb    ADSR_A=0.01; ADSR_D=5; ADSR_S=0; ADSR_R=0; N=250;
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  - Para un instrumento de este tipo, tenemos dos situaciones posibles:
    
    * El intérprete mantiene la nota pulsada hasta su completa extinción.
      > Y rellenamos la tabla .sco de la siguiente manera:
      >
      > |  0   |  9  |  1  | 67 | 100 |
      > |------|:---:|:---:|:--:|:---:|
      > | 1300 |  0  |  1  |  0 |  0  |
      >
      >  <img src="img/6.png" width="500" align="center">    
      >
      > - 0.0000000 0.0099670 Attack
      > - 0.0099670 4.9964091 Decay


    * El intérprete da por finalizada la nota antes de su completa extinción, iniciándose una disminución rápida del
      sonido hasta su finalización.
      
      > Y rellenamos la tabla .sco de la siguiente manera:
      >
      > |  0   |  9  |  1  | 67 | 100 |
      > |------|:---:|:---:|:--:|:---:|
      > |  900 |  0  |  1  |  0 |  0  |
      >
      >  <img src="img/7.png" width="500" align="center">
      >    
      > - 0.0000000 0.0110887 Attack
      > - 0.0110887 3.7479761 Decay_(cortado)

  - Debera representar en esta memoria *ambos* posibles finales de la nota.
  
* Un instrumento plano, como los de cuerdas frotadas (violines y semejantes) o algunos de viento. En ellos, el
  ataque es relativamente rápido hasta alcanzar el nivel de mantenimiento (sin sobrecarga), y la liberación también
  es bastante rápida.
  
  > Para el instrumento plano en el fichero.orc escribimos lo siguiente:
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.sh
     1	InstrumentDumb    ADSR_A=0.05; ADSR_D=0; ADSR_S=4; ADSR_R=0.05; N=250;
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  > Y rellenamos la tabla .sco de la siguiente manera:
  > 
  >   |  0  |  9  |  1  | 67 | 100 |
  >   |-----|:---:|:---:|:--:|:---:|
  >   | 400 |  8  |  1  | 67 | 100 |
  >   |  40 |  0  |  1  |  0 |  0  |
  >
  >
  >  <img src="img/8.png" width="500" align="center">
  >  
  > - 0.0000000 0.0499947 Attack
  > - 0.0499947 0.8312739 Sustain
  > - 0.8312739 0.8832403 Release

Para los cuatro casos, deberá incluir una gráfica en la que se visualice claramente la curva ADSR. Deberá añadir la
información necesaria para su correcta interpretación, aunque esa información puede reducirse a colocar etiquetas y
títulos adecuados en la propia gráfica (se valorará positivamente esta alternativa).

### Instrumentos Dumb y Seno.

Implemente el instrumento `Seno` tomando como modelo el `InstrumentDumb`. La señal *deberá* formarse mediante
búsqueda de los valores en una tabla.

- Incluya, a continuación, el código del fichero `seno.cpp` con los métodos de la clase Seno.
- Explique qué método se ha seguido para asignar un valor a la señal a partir de los contenidos en la tabla, e incluya
  una gráfica en la que se vean claramente (use pelotitas en lugar de líneas) los valores de la tabla y los de la
  señal generada.
- Si ha implementado la síntesis por tabla almacenada en fichero externo, incluya a continuación el código del método
  `command()`.

### Efectos sonoros.

- Incluya dos gráficas en las que se vean, claramente, el efecto del trémolo y el vibrato sobre una señal sinusoidal.
  Deberá explicar detalladamente cómo se manifiestan los parámetros del efecto (frecuencia e índice de modulación) en
  la señal generada (se valorará que la explicación esté contenida en las propias gráficas, sin necesidad de
  literatura).
- Si ha generado algún efecto por su cuenta, explique en qué consiste, cómo lo ha implementado y qué resultado ha
  producido. Incluya, en el directorio `work/ejemplos`, los ficheros necesarios para apreciar el efecto, e indique,
  a continuación, la orden necesaria para generar los ficheros de audio usando el programa `synth`.

### Síntesis FM.

Construya un instrumento basado en síntesis FM, siguiendo las explicaciones contenidas en el enunciado y el artículo
de [John M. Chowning](https://ccrma.stanford.edu/sites/default/files/user/jc/fm_synthesispaper-2.pdf). El instrumento
usará como parámetros *básicos* los números `N1` y `N2`, y el índice de modulación `I`, que deberá venir expresado
en semitonos.

- Use el instrumento para generar un vibrato de parámetros razonables e incluya una gráfica en la que se vea,
  claramente, la correspondencia entre los valores `N1`, `N2` e `I` con la señal obtenida.
- Use el instrumento para generar un sonido tipo clarinete y otro tipo campana. Tome los parámetros del sonido (N1,
  N2 e I) y de la envolvente ADSR del citado artículo. Con estos sonidos, genere sendas escalas diatónicas (fichero
  `doremi.sco`) y ponga el resultado en los ficheros `work/doremi/clarinete.wav` y `work/doremi/campana.work`.
  * También puede colgar en el directorio work/doremi otras escalas usando sonidos interesantes. Por ejemplo,
    violines, pianos, percusiones, espadas láser de la [Guerra de las Galaxias](https://www.starwars.com/), etc.

### Orquestación usando el programa synth.

Use el programa `synth` para generar canciones a partir de su partitura MIDI. Como mínimo, deberá incluir la
orquestación de la canción You've got a friend in me (fichero `ToyStory_A_Friend_in_me.sco`) del genial
[Randy Newman](https://open.spotify.com/artist/3HQyFCFFfJO3KKBlUfZsyW/about).

- En este (lamentable) arreglo, la pista 1 corresponde al instrumento solista (puede ser un piano, flautas, violines,
  etc.), y la 2 al bajo (bajo eléctrico, contrabajo, tuba, etc.).
- Coloque el resultado, junto con los ficheros necesarios para generarlo, en el directorio `work/music`.
- Indique, a continuación, la orden necesaria para generar la señal (suponiendo que todos los archivos necesarios
  están en direcotorio indicado).

También puede orquestar otros temas más complejos, como la banda sonora de Hawaii5-0 o el villacinco de John
Lennon Happy Xmas (War Is Over) (fichero `The_Christmas_Song_Lennon.sco`), o cualquier otra canción de su agrado
o composición. Se valorará la riqueza instrumental, su modelado y el resultado final.
- Coloque los ficheros generados, junto a sus ficheros `score`, `instruments` y `efffects`, en el directorio
  `work/music`.
- Indique, a continuación, la orden necesaria para generar cada una de las señales usando los distintos ficheros.
