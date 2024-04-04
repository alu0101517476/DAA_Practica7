#include "../include/AlgoritmoGrasp.h"

int AlgoritmoGrasp::calcularTCTTotal() {
  int tct_total{0};
  for (const auto& maquina : solucion_algoritmo_.getSolucion().first) {
    tct_total += calcularTCTMaquina(maquina, problema_.getValoresArcos());
  }
  return tct_total;
}

Solucion AlgoritmoGrasp::resolver() {
  int numero_maquinas{problema_.getNumeroMaquinas()},
      numero_tareas{problema_.getNumeroTareas()};
  solucion_algoritmo_.setCosteTotal(INT_MAX);
  for (int ejecuciones{0}; ejecuciones < 10; ++ejecuciones) {
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
        std::sort(
            lista_candidatos_restringida.begin(),
            lista_candidatos_restringida.end(),
            [](const TernaTctGrasp& candidato1, const TernaTctGrasp& candidato2) {
              return candidato1.tct_ < candidato2.tct_;
            });
      }
      // Escogemos uno de los 3 mejores candidatos al azar
      int inicio_indice_aleatorio{0}, final_indice_aleatorio{0},
          numero_candidatos{lista_candidatos_restringida.size()};
      if (lista_candidatos_restringida.size() >= 3) {
        inicio_indice_aleatorio = numero_candidatos - 3,
        final_indice_aleatorio = numero_candidatos - 1;
      } else if (lista_candidatos_restringida.size() == 2) {
        inicio_indice_aleatorio = numero_candidatos - 2,
        final_indice_aleatorio = numero_candidatos - 1;
      }
      // Inicializa el generador de números aleatorios
      std::random_device rd;
      std::mt19937 gen(rd());
      // Define el rango de los números aleatorios que quieres generar
      std::uniform_int_distribution<> distrib(inicio_indice_aleatorio,
                                              final_indice_aleatorio);

      TernaTctGrasp candidato_aleatorio{lista_candidatos_restringida[distrib(gen)]};
      // Insertamos la tarea en la mejor máquina y en la mejor posición
      // encontrada
      std::vector<int>::iterator it =
          solucion_actual[candidato_aleatorio.maquina_].begin();
      solucion_actual[candidato_aleatorio.maquina_].emplace(
          it + candidato_aleatorio.posicion_ + 1, tarea);
    }
    solucion_actual.setCosteTotal(calcularTCTTotalMaquinas(solucion_actual, problema_.getValoresArcos()));
    if (solucion_algoritmo_.getCosteTotal() > solucion_actual.getCosteTotal()) {
      solucion_algoritmo_ = solucion_actual; 
    }
  }
  return solucion_algoritmo_;
}
