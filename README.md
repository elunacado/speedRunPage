# Página de SpeedRuns 3.00
Este proyecto se basa en la página web Speedrun.com donde el usuario puede registrar su Run y buscarse en la leaderboard general y ver las leaderboards de mayor porcentaje y la de menor tiempo

## SICT0301 Evalúa los componentes
###  Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa.

En el de Mostrar Leaderboard se utiliza el metodo de ordenamiento de Merge Sort, el cual se encarga de ordenar los valores de menor a mayor, por lo tanto, su complejidad es de O(nlog(n)) lo significa que el tiempo de ordenamiento sera de el logaritmo de los datos por el numero de datos (se reducira la complejidad confome incremente el numero de datos) 

Y el de buscarmeEnLeaderboard nos dará una complejidad en el ordenamiento de O(n log(n)) y luego en la búsqueda nos dará una complejidad de O(n) lo que significa que la complejidad aumentará mientras mayor sea el número de datos

### Hace un análisis de complejidad correcto y completo todas las estructuras de datos y cada uno de sus usos en el programa
En la clase History utilizamos listas ligadas para agregar las Runs agregadas por el usuario cuyos cambios se iran agregando al final de la lista con una complejidad de O(1) haciendo que la complejidad siempre sea constante (ademas agregue un par de destructores para un correcto uso de la memoria)

### Hace un análisis de complejidad correcto y completo para todos los demás componentes del programa y determina la complejidad final del programa.
Las funciones que se utilizan son las siguientes
#### Historial

#### Cargar Runs desde DB

#### Agregar Runs

#### Merge Sort

#### Mostrar LeaderBoard

#### buscarmeEnLeaderboard

#### Complejidad Total
## SICT0302 Toma decisiones
### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.
Utiliza el metodo de ordenamiento de Merge Sort .

### Selecciona una estructura de datos adecuada al problema y lo usa correctamente.
Utilize la lista ligada en la clase historial (opción 4) la cual nos dara una lista ligada con los cambios realizados en esta sesión

## SICT0303 Implementa acciones directas
### Implementa mecanismos para consultar información de las estructuras correctos
El programa plantea la opción de consultar la posición del usuario en la leaderboard general siempre y cuando este proporcione el username con el que registro la run

### Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta
Las runs se registran en una base de datos, las cuales se leen cuando el usuario lo desee

### Implementa mecanismos de escritura de archivos para guardar los datos  de las estructuras de manera correcta
El programa tiene la opción de agregar runs a la base de datos (DB.txt) con la función de agregar nuevas runs permanentemente.
El programa tiene la opción de leer la base de datos (DB.txt)
