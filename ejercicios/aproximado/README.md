# Contrador aproximado #

## Archivos disponibles ##

Para el desarrollo de esta parte del laboratorio se proporsionan los siguientes 3 archivos:
1. [counter.h](counter.h): Archivo cabecera del contador aproximado (tomado del texto guia - **Ver nota abajo**). 
2. [counter.c](counter.c) Archivo fuente del contador aproximado (tomado del texto guia - **Ver nota abajo**).
3. [test_aproximate_counter.c](test_aproximate_counter.c): Archivo a completar con el fin de analizar el impacto en el desempeño al crear hilos que usen el contador simple (archivo a completar).
4. [Makefile](Makefile): Makefile para ahorar el proceso de compilación y enlazado.

* **Nota importante**: Recuerde que en el contador aproximado:
  
  ```C
  typedef struct __counter_t {
      int global; // global count
      pthread_mutex_t glock; // global lock
      int local[NUMCPUS]; // per-CPU count
      pthread_mutex_t llock[NUMCPUS]; // ... and locks
      int threshold; // update frequency
  } counter_t;
  ```
  Depende del numero de CPUs (NUMCPUS) que hay en su maquina, por lo tanto modifique el valor de esta constante para que este de acuerdo los requerimientos de su maquina.

Adicionalmente se recomienda que tenga los siguientes documentos a la mano:
1. [27. Interlude: Thread API](https://ceunican.github.io/aos/27.Interlude_Thread_API.pdf)
2. [29. Lock-based Concurrent Data Structures](https://ceunican.github.io/aos/29.Lock-based_Concurrent_Data_Structures.pdf)

## Procedimiento ##

### Paso 1 ###

Complete el archivo [test_aproximate_counter.c](test_aproximate_counter.c) empleando 1024 como valor del humbral (S) de tal manera que permita ingresar desde linea de comandos los siguientes parametros:
1. Valor maximo del contador: ```MAXCNT```
2. Numero de hilos que seran lanzados: ```NUMTHREADS```
   
Segun lo anterior, la forma de pasar argumentos a la aplicación será la siguiente una vez este completamente terminada:  

```
./NOMBRE_EJECUTABLE <MAXCNT> <NUMTHREADS>
```

A continuación (para su comodidad) se muestra el esqueleto del código a completar ([test_aproximate_counter.c](test_aproximate_counter.c)) de modo que lo único que usted tendra que hacer es llenar el codigo siguiendo las instrucciones dadas en el esqueleto:

```C
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "counter.h"

#define THRESHOLD 1024

/* structs */
// code here (if you required it)...

/* start_routine header */
// code here...

/* Global variables */
// code here (if you required it)...

int main(int argc, char *argv[]) { 

    /* get the command's line parameters */
    // code here...


    /* Declaration of struct timeval variables */
    // code here...


    /* Initializing conter */
    // code here...


    /* Threads handlers */
    // code here...


    /* Thread creation */
    // code here...


    /* Time starts counting */
    // code here...


    /* Creating a Threads */
    // code here...
   

    /* Threads joins */
    // code here...


    /* Time stops counting here */
    // code here...


    /* get the end time */
    // code here...
    

    /* get the elapset time (end_time - start_time) */
    // code here...


    /* print the results (number threads employed, counter value, elasep time) */
    // code here...


    return 0;
}

/* start_routine definition */
// code here...





```

Compile y pruebe las veces que crea necesario hasta que tenga la certeza de que su programa hace lo que quiere (guiese de los que aprendió en el capitulo [Lock-based Concurrent Data Structures](http://pages.cs.wisc.edu/~remzi/OSTEP/threads-locks-usage.pdf) **en la sección de Concurrent Counters**. 

Para la compilación ejecute el comando ```make```:

```
make
```

### Paso 2 ###

Una vez tenga el programa listo, ejecutelo para los casos en los cuales se van a manejar 1, 2, 4, 8 y 16 hilos y pase como valor maximo del contador el valor de 10000000. Anote en una tabla los valores asociados al numero de hilos, el valor del contador logrado con estos y el tiempo gastado para cada caso.

### Resultados ###

Nota: Cada hilo aumenta el contador 1 millón de veces, el número máximo del contador para los resultados es de 20.000.000, se tiene un threshold de 1024, y una configuración de 4 cpus. Las capturas de pantalla como evidencia se encuentras en la carpeta ```pantallazos/aproximado```

| Nro hilos        | Contador           | Tiempo  |
| ------------- |:-------------:| -----:|
| 1  | 999.424 | 53 milisegundos |
| 2  | 1.998.848 | 71 milisegundos |
| 4  | 3.997.696 | 113 milisegundos |
| 8  | 7.999.488 | 188 milisegundos |
| 16 | 15.998.976 | 333 milisegundos |

