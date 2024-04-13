#include "../include/AlgoritmoGrasp.h"

AlgoritmoGrasp::AlgoritmoGrasp(const std::string& nombre_problema,
                               int opcion_algoritmo)
    : problema_{nombre_problema},
      solucion_algoritmo_{problema_.getNumeroMaquinas()} {
  setEstructuraEntorno(opcion_algoritmo);
}

AlgoritmoGrasp::AlgoritmoGrasp(const std::string& nombre_problema,
                               int opcion_algoritmo, int maximo_iteraciones)
    : problema_{nombre_problema},
      solucion_algoritmo_{problema_.getNumeroMaquinas()} {
  setEstructuraEntorno(opcion_algoritmo);
  maximo_iteraciones_ = maximo_iteraciones;
}

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
  Solucion solucion_final;
  solucion_final.setCosteTotal(INT_MAX);
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
  if (solucion_final.getCosteTotal() > solucion_actual.getCosteTotal()) {
    solucion_final = solucion_actual;
  }
  return solucion_final;
}

void AlgoritmoGrasp::setEstructuraEntorno(int opcion_algoritmo) {
  switch (opcion_algoritmo) {
    case 1: {
      movimiento_entre_ = new IntercambioEntre{solucion_algoritmo_};
      tipo_movimiento_ = 1;
      break;
    }

    case 2: {
      movimiento_intra_ = new IntercambioIntra{solucion_algoritmo_};
      tipo_movimiento_ = 0;
      break;
    }

    case 3: {
      movimiento_entre_ = new ReinsercionEntre{solucion_algoritmo_};
      tipo_movimiento_ = 1;
      break;
    }

    default: {  // opción 4
      movimiento_intra_ = new ReinsercionIntra{solucion_algoritmo_};
      tipo_movimiento_ = 0;
      break;
    }
  }
}

/**
 * @brief Método que ejecuta el algoritmo con la fase constructiva y con la fase
 * de postprocesamiento para hallar una nueva solución
 * @return Solucion solucion encontrada después de ejecutar el algoritmo
 */
Solucion AlgoritmoGrasp::resolver() {
  solucion_algoritmo_ = faseConstructiva();
  (tipo_movimiento_ == 0) ? movimiento_intra_->setSolucion(solucion_algoritmo_)
                          : movimiento_entre_->setSolucion(solucion_algoritmo_);
  int numero_intentos{0};
  for (int i{0}; i < 1000; ++i) {
    if (tipo_movimiento_ == 0) {
      movimiento_intra_->setSolucion(faseConstructiva());
      movimiento_intra_->explorarVecindario(problema_, 10);
      // Fase actualización
      if (calcularTCTTotal() <
          calcularTCTTotalMaquinas(movimiento_intra_->getSolucion(),
                                   problema_.getValoresArcos())) {
        solucion_algoritmo_ = movimiento_intra_->getSolucion();
        numero_intentos = 0;
      } else {
        ++numero_intentos;
      }
    } else {
      movimiento_entre_->setSolucion(faseConstructiva());
      movimiento_entre_->explorarVecindario(problema_.getValoresArcos(), 10);
      // Fase actualización
      if (calcularTCTTotal() <
          calcularTCTTotalMaquinas(movimiento_entre_->getSolucion(),
                                   problema_.getValoresArcos())) {
        solucion_algoritmo_ = movimiento_entre_->getSolucion();
        numero_intentos = 0;
      } else {
        ++numero_intentos;
      }
    }
    if (numero_intentos == maximo_iteraciones_) {
      break;
    }
  }
  return solucion_algoritmo_;
}