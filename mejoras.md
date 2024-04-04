GRASP:
1. Hacer bien la fase constructiva del grasp, es lo mismo que el greedy pero escogiendo 
en vez de la mejor tarea, meter los 3 mejores calculos del TCT por ejemplo, meterlo en un vector y escoger aleatoriamente el tct

2. Hacer que la fase constructiva del grasp no solo se ejecute una vez y obtenga una solución, si no que 
se ejecute varias veces y en el caso de que la solución encontrada sea mejor que la solución que ya tenemos,
la actualizamos

General:
1. El método de los algoritmos que calcula el TCT total, pasarlo a una función externa, en herramientas.h y usar esa función en 
los dos algoritmos. Eliminar el método en los dos algoritmos

2. Como en los dos algoritmos, metes la tarea 0 al principio, lo mejor sería que lo hicieras en el constructor de solución
y así no repites ese código 2 veces

3. Comentar mejor el código

4. Cambiar el nombre de la variable "incremento" dentro del algoritmo