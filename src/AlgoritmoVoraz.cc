#include "../include/AlgoritmoVoraz.h"

Solucion AlgoritmoVoraz::resolver() {
  int numero_maquinas{problema_.getNumeroMaquinas()},
      numero_tareas{problema_.getNumeroTareas()};
  // Seleccionamos las m tareas con menores valores de t0j
  for (int j{0}; j < numero_maquinas; ++j) {
    solucion_algoritmo_.agregarTarea(j, problema_.getValoresArcos()[0][j]);
  }
  // Creamos un vector para saber que tareas están asignadas
  std::vector<bool> tareas_asignadas(numero_tareas, false);
  // Marcamos las tareas iniciales como asignadas en el vector de tareas
  // asignadas
  for (int i{0}; i < numero_maquinas; ++i) {
    if (!solucion_algoritmo_[i].empty()) {
      tareas_asignadas[solucion_algoritmo_[i][0]] = true;
    }
  }
  // Iteramos sobre todas las tareas para asignarlas
  for (int tarea{0}; tarea < numero_tareas; ++tarea) {
    if (!tareas_asignadas[tarea]) {  // Si la tarea no está asignada
      int incremento_minimo{INT_MAX}, maquina_optima, posicion_optima;
      // Busca la mejor posición y máquina para la tarea
      for (int maquina{0}; maquina < numero_maquinas; ++maquina) {
        for (int posicion{0}; posicion < solucion_algoritmo_[maquina].size();
             ++posicion) {
          int incremento{calcularIncrementoTCT(
              solucion_algoritmo_, maquina, tarea, posicion,
              problema_.getTiempoProcesamientoTareas(),
              problema_.getTiemposSetup())};
          if (incremento < incremento_minimo) {
            incremento_minimo = incremento;
            maquina_optima = maquina;
            posicion_optima = posicion;
          }
        }
      }
      // Insertamos la tarea en la mejor máquina y en la mejor posición
      // encontrada
      solucion_algoritmo_[maquina_optima].insert(
          solucion_algoritmo_[maquina_optima].begin() + posicion_optima, tarea);
      // Asignamos la tarea que hemos colocado 
      tareas_asignadas[tarea] = true;
    }
  }
}
