#include "../include/AlgoritmoGrasp.h"

int AlgoritmoGrasp::calcularTCTTotal() {
  int tct_total{0};
  for (const auto& maquina : solucion_algoritmo_.getSolucion().first) {
    tct_total += calcularTCTMaquina(maquina, problema_.getValoresArcos());
  }
  return tct_total;
}

Solucion AlgoritmoGrasp::resolver() {

  std::vector<int> tiempo_procesamiento{problema_.getTiempoProcesamientoTareas()}, tiempo_procesamiento_aux{tiempo_procesamiento};
  for (int i{0}; i < problema_.getNumeroMaquinas(); ++i) {
    solucion_algoritmo_[i].emplace_back(0);
  }
  // Motor de números aleatorios basado en una semilla
  std::random_device rd;
  std::mt19937 gen(rd());

  while (tiempo_procesamiento_aux.size() != 1) {
    std::uniform_int_distribution<> distribucion(
        1, tiempo_procesamiento_aux.size() - 1);
    int indice_aleatorio{distribucion(gen)}, tct_minimo{INT_MAX},
        maquina_optima, posicion_optima, tarea_asignada;
    for (int maquina{0}; maquina < problema_.getNumeroMaquinas(); ++maquina) {
      for (int posicion{0}; posicion < solucion_algoritmo_[maquina].size();
           ++posicion) {
        int tct{calcularTCTOptimo(maquina, posicion, indice_aleatorio,
                                  solucion_algoritmo_,
                                  problema_.getValoresArcos())};
        if (tct < tct_minimo) {
          tct_minimo = tct;
          maquina_optima = maquina;
          posicion_optima = posicion;
          tarea_asignada = indice_aleatorio;
        }
      }
    }
    // Insertamos la tarea en la mejor máquina y en la mejor posición
    // encontrada
    std::vector<int>::iterator it = solucion_algoritmo_[maquina_optima].begin();

    // Hallamos la posicion en el vector original
    auto iterador = std::find(tiempo_procesamiento.begin(),
                        tiempo_procesamiento.end(),
                        tiempo_procesamiento_aux[indice_aleatorio]);

    if (it != tiempo_procesamiento.end()) {
      // Si el elemento existe en el vector, calcula su posición
      int posicion = iterador - tiempo_procesamiento.begin();
      solucion_algoritmo_[maquina_optima].emplace(it + posicion_optima + 1,
                                                  posicion);
    }
    tiempo_procesamiento_aux.erase(tiempo_procesamiento_aux.begin() +
                                   indice_aleatorio);
  }
  solucion_algoritmo_.setCosteTotal(calcularTCTTotal());
  return solucion_algoritmo_;
}
