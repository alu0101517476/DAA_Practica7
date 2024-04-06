GRASP:
**Fase constructiva**



General:
1. El método de los algoritmos que calcula el TCT total, pasarlo a una función externa, en herramientas.h y usar esa función en 
los dos algoritmos. Eliminar el método en los dos algoritmos

2. Como en los dos algoritmos, metes la tarea 0 al principio, lo mejor sería que lo hicieras en el constructor de solución
y así no repites ese código 2 veces

3. Comentar mejor el código

4. Cambiar el nombre de la variable "incremento" dentro del algoritmo

5. Cambiar el paso tanto en el greedy como en la fase constructiva de GRASP de que para calcular el mejor TCT se calcula el TCT total de la máquina,
es mejor y más rápido calcular el incremento y escoger el que menor incremento tenga.