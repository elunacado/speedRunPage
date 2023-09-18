# Página de SpeedRuns 1.00
Este proyecto se basa en la página web Speedrun.com donde el usuario puede registrar su Run y buscarse en la leaderboard general y ver las leaderboards de mayor porcentaje y la de menor tiempo

## SICT0301 Evalúa los componentes
###  Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa.

En el de Mostrar Leaderboard y highestPercentLeaderboard se utiliza la función Sort, la cual se encarga de ordenar los valores de menor a mayor con una mezcla de ordenamientos de Merge Sort, Quick Sort e Insertion Sort según el tamaño de los datos, por lo tanto, su complejidad es de O(n log(n)) lo significa que el tiempo que lleva ordenar los elementos aumenta de manera logarítmica a medida que aumenta el tamaño de la secuencia

Y el de buscarmeEnLeaderboard nos dará una complejidad en el ordenamiento de O(n log(n)) y luego en la búsqueda nos dará una complejidad de O(n) lo que significa que la complejidad aumentará mientras mayor sea el número de datos

### Hace un análisis de complejidad correcto y completo todas las estructuras de datos y cada uno de sus usos en el programa

### Hace un análisis de complejidad correcto y completo para todos los demás componentes del programa y determina la complejidad final del programa.

## SICT0302 Toma decisiones
### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.
Utiliza la función sort de la (standard table library) que según la investigación que he realizado es una combinación entre el Merge Sort, Quick Sort e Insertion Sort y utilizara la herramienta que más se adecúe a la cantidad de datos.

### Selecciona una estructura de datos adecuada al problema y lo usa correctamente.


## SICT0303 Implementa acciones directas
### Implementa mecanismos para consultar información de las estructuras correctos
El programa plantea la opción de consultar la posición del usuario en la leaderboard general siempre y cuando este proporcione el username con el que registro la run

### Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta
Las runs se registran en una base de datos, las cuales se leen cuando el usuario lo desee

### Implementa mecanismos de escritura de archivos para guardar los datos  de las estructuras de manera correcta
El programa tiene la opción de agregar runs a la base de datos (DB.txt) con la función de agregar nuevas runs permanentemente.
