#include "../include/AlgoritmoGrasp.h"

/**
 * @brief Método que calcula el TCT total de la solución
 * @return int TCT total
 */
int AlgoritmoGrasp::calcularTCTTotal() {
  int tct_total{0};
  for (const auto& maquina : solucion_algoritmo_.getSolucion().first) {
    tct_total += calcularTCTMaquina(maquina, problema_.getValoresArcos());
  }
  return tct_total;
}

/**
 * @brief Fase constructiva del algoritmo GRASP que nos da una solución
 * apoyándonos en las soluciones que nos va dando el algoritmo voraz
 * @return Solucion Solución después de haber hecho la fase constructiva
 */
Solucion AlgoritmoGrasp::faseConstructiva() {
  int numero_maquinas{problema_.getNumeroMaquinas()},
      numero_tareas{problema_.getNumeroTareas()};
  solucion_algoritmo_.setCosteTotal(INT_MAX);
  Solucion solucion_actual{problema_.getNumeroMaquinas()};
  // Seleccionamos las m tareas con menores valores de t0j
  for (int i{0}; i < numero_maquinas; ++i) {
    solucion_actual[i].emplace_back(0);
  }
  // Iteramos sobre todas las tareas para asignarlas
  for (int tarea{1}; tarea <= numero_tareas; ++tarea) {
    // Busca la mejor posición y máquina para la tarea
    std::vector<TernaTctGrasp> lista_candidatos_restringida;
    for (int maquina{0}; maquina < numero_maquinas; ++maquina) {
      for (int posicion{0}; posicion < solucion_actual[maquina].size();
            ++posicion) {
        int tct{calcularTCTOptimo(maquina, posicion, tarea, solucion_actual,
                                  problema_.getValoresArcos())};
        // Introducimos los posibles candidatos
        TernaTctGrasp candidato{tct, maquina, posicion};
        lista_candidatos_restringida.emplace_back(candidato);
      }
      std::sort(lista_candidatos_restringida.begin(),
                lista_candidatos_restringida.end(),
                [](const TernaTctGrasp& candidato1,
                    const TernaTctGrasp& candidato2) {
                  return candidato1.tct_ < candidato2.tct_;
                });
    }
    // Escogemos uno de los 3 mejores candidatos al azar
    int inicio_indice_aleatorio{0}, final_indice_aleatorio{0},
        numero_candidatos{lista_candidatos_restringida.size()};
    if (lista_candidatos_restringida.size() >= 3) {
      final_indice_aleatorio = 2;
    } else if (lista_candidatos_restringida.size() == 2) {
      final_indice_aleatorio = 1;
    }
    // Inicializa el generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    // Define el rango de los números aleatorios que quieres generar
    std::uniform_int_distribution<> distrib(inicio_indice_aleatorio,
                                            final_indice_aleatorio);

    TernaTctGrasp candidato_aleatorio{
        lista_candidatos_restringida[distrib(gen)]};
    // Insertamos la tarea en la mejor máquina y en la mejor posición
    // encontrada
    std::vector<int>::iterator it =
        solucion_actual[candidato_aleatorio.maquina_].begin();
    solucion_actual[candidato_aleatorio.maquina_].emplace(
        it + candidato_aleatorio.posicion_ + 1, tarea);
  }
  solucion_actual.setCosteTotal(
      calcularTCTTotalMaquinas(solucion_actual, problema_.getValoresArcos()));
  if (solucion_algoritmo_.getCosteTotal() > solucion_actual.getCosteTotal()) {
    solucion_algoritmo_ = solucion_actual;
  }
  return solucion_algoritmo_;
}

/**
 * @brief Método que ejecuta el algoritmo con la fase constructiva y con la fase
 * de postprocesamiento para hallar una nueva solución
 * @return Solucion solucion encontrada después de ejecutar el algoritmo
 */
Solucion AlgoritmoGrasp::resolver() {
  /*
  do {
    faseConstructiva();
    exploracionVecindarioReinsertando();
    // Fase de actualización en caso de que la solución encontrada sea mejor
  } while (false);
  */
  faseConstructiva();
  ReinsercionIntra reinsercion_intra{solucion_algoritmo_};
  movimiento_intra_ = &reinsercion_intra;
  movimiento_intra_->explorarVecindario(problema_, 10);
  /*
  ReinsercionEntre reinsercion_entre{solucion_algoritmo_};
  movimiento_entre_ = &reinsercion_entre;
  movimiento_entre_->explorarVecindario(problema_.getValoresArcos());
  */
  return solucion_algoritmo_;
}