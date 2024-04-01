#include "../include/AlgoritmoVoraz.h"

int AlgoritmoVoraz::calcularTCTTotal() {
  int tct_total{0};
  for (const auto& maquina : solucion_algoritmo_.getSolucion().first) {
    if (!maquina.empty()) {
      // Añadimos el tiempo de setup inicial para la primera tarea
      int tct_maquina{problema_.getTiemposSetup()[0][maquina[0]]};
      for (int i{0}; i < maquina.size(); ++i) {
        tct_maquina += problema_.getTiempoProcesamientoTareas()[maquina[i]];
        // Si no es la ultima tarea, se suma el tiempo de setup
        if (i < maquina.size() - 1) {
          tct_maquina += problema_.getTiemposSetup()[maquina[i]][maquina[i + 1]];
        }
      }
      tct_total += tct_maquina;
    }
  }
  return tct_total;
}


Solucion AlgoritmoVoraz::resolver() {
  std::cout << "SOLUCION: " << solucion_algoritmo_ << std::endl;
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
  std::cout << "NUMERO TAREAS: " << numero_tareas << std::endl;
  for (int tarea{0}; tarea < numero_tareas; ++tarea) {
    if (!tareas_asignadas[tarea]) {  // Si la tarea no está asignada
      int incremento_minimo{INT_MAX}, maquina_optima, posicion_optima, tarea_asignada;
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
            tarea_asignada = tarea;
          }
        }
      }
      // Insertamos la tarea en la mejor máquina y en la mejor posición
      // encontrada
      std::vector<int>::iterator it = solucion_algoritmo_[maquina_optima].begin();
      solucion_algoritmo_[maquina_optima].insert(it + posicion_optima, tarea_asignada);
      // Asignamos la tarea que hemos colocado 
      tareas_asignadas[tarea_asignada] = true;
    }
  }
  // Calculamos el coste total de la solución
  solucion_algoritmo_.setCosteTotal(calcularTCTTotal());
  return solucion_algoritmo_;
}
