#include "../include/Herramientas.h"

/**
 * @brief Función que calcula cuánto se espera que aumente el TCT total para esa
 * máquina debido a la inserción de una nueva tarea en una posición especifica.
 * No devuelve un TCT nuevo, es el aumento respecto al TCT que ya existia
 * @param solucion solucion actual
 * @param maquina maquina a la que queremos introducirle la tarea
 * @param tarea tarea que queremos introducir a la máquina
 * @param posicion posición en la que queremos introducir la tarea
 * @param procesamiento_tareas vector que contiene el procesamiento de las tareas
 * @param tiempos_setup matriz que contiene los tiempos de setup
 * @return int, el incremento del TCT 
 */
int calcularIncrementoTCT(Solucion& solucion, int maquina, int tarea,
                          int posicion, std::vector<int> procesamiento_tareas,
                          std::vector<std::vector<int>> tiempos_setup) {
  int incremento_tct{0}, numero_tareas{solucion[maquina].size()};
  int tiempo_setup_inicial;
  if (posicion == 0) {
    // Igualamos la variable con con el tiempo de setup desde el estado inicial
    // hasta la tarea nueva
    tiempo_setup_inicial = tiempos_setup[0][tarea];
  } else {
    // Igualamos la variable con el tiempo de la tarea anterior a la tarea nueva
    tiempo_setup_inicial =
        tiempos_setup[solucion[maquina][posicion - 1]][tarea];
  }
  // Sumamos el tiempo de setup de la tarea con el tiempo de procesamiento de la
  // tarea y lo almacenamos en la variable "incremento_tct"
  incremento_tct += tiempo_setup_inicial + procesamiento_tareas[tarea];
  if (posicion < numero_tareas) {
    // Calcula el tiempo de setup necesario para cambiar de la nueva tarea
    // insertada a la siguiente tarea en la secuencia.
    int tiempo_setup_siguiente =
        tiempos_setup[tarea][solucion[maquina][posicion]];
    // Restamos el tiempo de setup actual, con el tiempo de setup de dos tareas
    // que no están actualmente conectadas, que son la tarea anterior a la que
    // queremos insertar y la posterior
    incremento_tct += tiempo_setup_siguiente -
                      tiempos_setup[solucion[maquina][posicion - 1]]
                                   [solucion[maquina][posicion]];
  } else {
    if (!solucion[maquina].empty()) {
      incremento_tct += tiempos_setup[solucion[maquina].size() - 1][tarea];
    }
  }
  return incremento_tct;
}