#include "../include/AlgoritmoVoraz.h"

int AlgoritmoVoraz::calcularTCTTotal() {
  int tct_total{0};
  for (const auto& maquina : solucion_algoritmo_.getSolucion().first) {
    tct_total += calcularTCTMaquina(maquina, problema_.getValoresArcos());
  }
  return tct_total;
}

Solucion AlgoritmoVoraz::resolver() {
  int numero_maquinas{problema_.getNumeroMaquinas()},
      numero_tareas{problema_.getNumeroTareas()};
  // Seleccionamos las m tareas con menores valores de t0j
  for (int i{0}; i < numero_maquinas; ++i) {
    solucion_algoritmo_[i].emplace_back(0);
  }

  // Iteramos sobre todas las tareas para asignarlas
  for (int tarea{1}; tarea <= numero_tareas; ++tarea) {
    int incremento_minimo{INT_MAX}, maquina_optima, posicion_optima,
        tarea_asignada;
    // Busca la mejor posición y máquina para la tarea
    for (int maquina{0}; maquina < numero_maquinas; ++maquina) {
      for (int posicion{0}; posicion < solucion_algoritmo_[maquina].size();
           ++posicion) {
        int incremento{calcularTCTOptimo(maquina, posicion, tarea,
                                         solucion_algoritmo_,
                                         problema_.getValoresArcos())};
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
    solucion_algoritmo_[maquina_optima].emplace(it + posicion_optima + 1,
                                                tarea_asignada);
  }
  // Calculamos el coste total de la solución
  solucion_algoritmo_.setCosteTotal(calcularTCTTotal());
  return solucion_algoritmo_;
}
