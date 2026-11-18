*Este proyecto ha sido creado como parte del currículo de 42 por cyelmo-l.*

# Get Next Line

> **Leer una línea de un descriptor de archivo es demasiado tedioso.**  
> Este proyecto aborda la creación de una función altamente útil en C que permite leer el contenido de un archivo (o entrada estándar) línea por línea, introduciendo el concepto de las variables estáticas.

---

## Descripción

El objetivo de este proyecto es programar la función `get_next_line`, la cual devuelve una línea leída desde un descriptor de archivo (file descriptor o `fd`). 

Llamar a esta función de manera repetida dentro de un bucle permite procesar el contenido completo de un archivo de texto de forma secuencial y controlada. Es un ejercicio fundamental para comprender la gestión de memoria, la lectura mediante buffers y, sobre todo, el comportamiento de las **variables estáticas** en C. Estas variables son cruciales aquí, ya que permiten a la función "recordar" el texto que se ha leído más allá de un salto de línea entre diferentes llamadas.

El proyecto también incluye una versión **Bonus** que amplía la funcionalidad para gestionar múltiples descriptores de archivo simultáneamente, alternando entre ellos sin perder el hilo de lectura de ninguno.

---

## Instrucciones de Uso y Compilación

Dado que `get_next_line` es una función y no un programa independiente, necesitas compilarla junto con un archivo principal (`main.c`) que la invoque. Elige el archivo `main.c` que prefieras según lo que quieras probar:

### Opción 1: Lectura normal desde un archivo único
Este ejemplo lee un archivo de texto línea por línea e imprime el número de línea actual junto con su contenido.

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;
    int     line_num;

    fd = open("archivo_de_prueba.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error: Asegurate de crear 'archivo_de_prueba.txt' primero.\n");
        return (1);
    }

    line_num = 1;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("[Linea %d] %s", line_num++, line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Opción 2: Lectura desde STDIN (Entrada estándar - Sin Bonus)
Este ejemplo procesa lo que escribas por teclado de forma interactiva, numerando cada línea introducida.

```c
#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
    char    *line;
    int     line_num;

    printf("Escribe algo y presiona Enter (Ctrl+D para terminar):\n");
    line_num = 1;
    while ((line = get_next_line(0)) != NULL)
    {
        printf("[Linea %d] %s", line_num++, line);
        free(line);
    }
    return (0);
}
```

### Opción 3: Versión Bonus (Múltiples archivos simultáneos sin STDIN)
Este ejemplo demuestra cómo el bonus alterna la lectura entre dos archivos distintos (`archivo1.txt` y `archivo2.txt`) de forma intercalada, manteniendo un contador de línea independiente para cada uno.

```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd1;
    int     fd2;
    char    *line1;
    char    *line2;
    int     num1 = 1;
    int     num2 = 1;

    fd1 = open("archivo1.txt", O_RDONLY);
    fd2 = open("archivo2.txt", O_RDONLY);

    if (fd1 == -1 || fd2 == -1)
    {
        printf("Error: Asegurate de crear 'archivo1.txt' y 'archivo2.txt'.\n");
        return (1);
    }

    // Leemos alternadamente de ambos descriptores para demostrar el bonus
    while (1)
    {
        line1 = get_next_line(fd1);
        if (line1)
        {
            printf("[Archivo 1 - Linea %d] %s", num1++, line1);
            free(line1);
        }

        line2 = get_next_line(fd2);
        if (line2)
        {
            printf("[Archivo 2 - Linea %d] %s", num2++, line2);
            free(line2);
        }

        if (!line1 && !line2)
            break;
    }

    close(fd1);
    close(fd2);
    return (0);
}
```

---

### Compilación y Ejecución
Es obligatorio poder definir el tamaño del buffer en tiempo de compilación utilizando el indicador `-D BUFFER_SIZE=n`.

* **Para la parte obligatoria (ejemplo 1 o 2):**
  ```bash
  cc -Wall -Werror -Wextra -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
  ./gnl
  ```

* **Para la parte bonus (ejemplo 3):**
  ```bash
  cc -Wall -Werror -Wextra -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl
  ./gnl
  ```

---

## Justificación del Algoritmo

El algoritmo implementado se divide en tres fases lógicas, separadas en distintas funciones para mantener el código modular y cumplir con la Norma de 42:

-   **Lectura y acumulación (`whileout`)**: 
    Se utiliza un bucle que permanece activo mientras no se encuentre un salto de línea (`\n`) en el texto acumulado y la función `read` siga devolviendo datos. En cada iteración, se reserva memoria según el `BUFFER_SIZE`, se lee del descriptor de archivo, y el resultado se concatena de forma segura a la variable estática principal utilizando `ft_strjoingnl`.

-   **Extracción de la línea (`justline` y `linefabric`)**: 
    Cuando el bucle se detiene (ya sea por encontrar un `\n` o llegar al final del archivo), se debe extraer la línea exacta. La función `justline` analiza la cadena acumulada y reserva la memoria justa hasta el primer salto de línea, aislándolo para ser devuelto al usuario.

-   **Gestión de remanentes (`leftovers`)**: 
    Dado que la función `read` suele capturar caracteres adicionales posteriores al primer `\n`, es vital no perder esta información. La función `leftovers` localiza dónde terminó la línea extraída y guarda todo el texto sobrante en una nueva asignación de memoria. La variable estática se actualiza con este remanente, quedando preparado para la próxima vez que se llame a la función.

**Gestión de múltiples FD (Bonus):**
Para la parte bonus, la única variable estática se transforma en un array de punteros: `static char *cad[1024] = {NULL};`. En sistemas Unix, los descriptores de archivo son números enteros secuenciales. Al utilizar el propio `fd` como índice del array, el algoritmo es capaz de aislar los remanentes (`leftovers`) de hasta 1024 archivos simultáneos. Esto garantiza un seguimiento independiente del estado de lectura de cada documento sin que los buffers se mezclen.

---
## Recursos y Referencias

-   **Documentación de C:** Se han consultado asiduamente las páginas del manual de Unix (`man 2 read`, `man 3 malloc`, `man 3 free`) para asegurar el manejo correcto de la memoria y la captura de errores del sistema.
-   **Inteligencia Artificial:** Se ha utilizado IA exclusivamente como asistente de redacción y formato para estructurar este archivo `README.md`, garantizando la claridad expositiva y el cumplimiento de los requisitos de documentación de 42. El desarrollo lógico, la arquitectura del código y la resolución de problemas técnicos son producto de trabajo y razonamiento propio.
