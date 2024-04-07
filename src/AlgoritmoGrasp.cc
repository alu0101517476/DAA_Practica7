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
  for (int ejecuciones{0}; ejecuciones < 60; ++ejecuciones) {
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
  }
  return solucion_algoritmo_;
}

/**
 * @brief Método que explora las soluciones vecinas pero con un enofoque
 * aleatorio
 * @return Solucion
 */
Solucion AlgoritmoGrasp::exploracionVecindarioAleatorio() {
  int menor_numero_tareas{INT_MAX}, mayor_numero_tareas{0}, indice_menor_tareas,
      indice_mayor_tareas;
  // Escogemos la máquina con menor y mayor tareas asignadas
  std::vector<std::vector<int>> matriz_solucion{
      solucion_algoritmo_.getSolucion().first};
  for (int i{0}; i < matriz_solucion.size(); ++i) {
    if (menor_numero_tareas > matriz_solucion[i].size()) {
      menor_numero_tareas = matriz_solucion[i].size();
      indice_menor_tareas = i;
    }
    if (mayor_numero_tareas < matriz_solucion[i].size()) {
      mayor_numero_tareas = matriz_solucion[i].size();
      indice_mayor_tareas = i;
    }
  }
  std::vector<int> maquina_menor_tareas{
      solucion_algoritmo_[indice_menor_tareas]},
      maquina_mayor_tareas{solucion_algoritmo_[indice_mayor_tareas]};

  // Se escoge una tarea aleatoria de la máquina pequeña
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distribucion(0,
                                               maquina_menor_tareas.size() - 1);
  int indice_aleatorio{distribucion(gen)},
      tarea_aleatoria{maquina_menor_tareas[indice_aleatorio]};
  // Se escoge una tarea aleatoria de la máquina grande
  std::uniform_int_distribution<> distribucion2(
      0, maquina_mayor_tareas.size() - 1);
  int indice_aleatorio_max{distribucion2(gen)},
      tarea_aleatoria_max{maquina_mayor_tareas[indice_aleatorio_max]};
  // Se eliminan las dos tareas de las máquinas

  maquina_menor_tareas.erase(maquina_menor_tareas.begin() + indice_aleatorio);
  maquina_mayor_tareas.erase(maquina_mayor_tareas.begin() +
                             indice_aleatorio_max);
  // Calculamos la mejor posición en donde poner la tarea en la máquina pequeña
  int tct_minimo{INT_MAX}, posicion;
  for (int i{0}; i < maquina_menor_tareas.size(); ++i) {
    int tct{calcularTCTOptimo(indice_menor_tareas, i, tarea_aleatoria_max,
                              solucion_algoritmo_,
                              problema_.getValoresArcos())};
    if (tct < tct_minimo) {
      tct_minimo = tct;
      posicion = i;
    }
  }
  maquina_menor_tareas.emplace(maquina_menor_tareas.begin() + posicion + 1,
                               tarea_aleatoria_max);
  // Calculamos la mejor posición en donde poner la tarea en la máquina grande
  tct_minimo = INT_MAX;
  for (int i{0}; i < maquina_mayor_tareas.size(); ++i) {
    int tct{calcularTCTOptimo(indice_mayor_tareas, i, tarea_aleatoria,
                              solucion_algoritmo_,
                              problema_.getValoresArcos())};
    if (tct < tct_minimo) {
      tct_minimo = tct;
      posicion = i;
    }
  }
  maquina_mayor_tareas.emplace(maquina_mayor_tareas.begin() + posicion + 1,
                               tarea_aleatoria);
  // Establecemos la solución vecina y la devolvemos
  matriz_solucion[indice_mayor_tareas] = maquina_mayor_tareas;
  matriz_solucion[indice_menor_tareas] = maquina_menor_tareas;
  Solucion solucion_vecina{
      {matriz_solucion,
       calcularTCTTotalMaquinas(matriz_solucion, problema_.getValoresArcos())}};
  return solucion_vecina;
}

/**
 * @brief Método que va reinsertando una tarea en una máquina para comprobar si
 * mejora el TCT de la máquina
 *
 * @param maquina maquina a la que queremos cambiar la posición de la tare
 * @return true en caso de que se mejore el TCT de la máquina
 * @return false en caso de que no se mejore el TCT de la máquina
 */
bool AlgoritmoGrasp::solucionVecinaEncontrada(std::vector<int>& maquina) {
  int tct_maquina{calcularTCTMaquina(maquina, problema_.getValoresArcos())},
      i{0};
  for (int i{0}; i < maquina.size(); ++i) {
    // Eliminamos la tarea
    int indice_tarea{i}, tarea{maquina[i]};
    maquina.erase(maquina.begin() + i);
    for (int j{0}; j < maquina.size(); ++j) {
      maquina.emplace(maquina.begin() + j + 1, tarea);
      int tct{calcularTCTMaquina(maquina, problema_.getValoresArcos())};
      if (tct < tct_maquina) return true;
      maquina.erase(maquina.begin() + j + 1);
    }
    // no ha mejorado el tct, por lo que devolvemos la tarea a su posición
    // original
    maquina.emplace(maquina.begin() + i, tarea);
  }
  return false;
}

/**
 * @brief Método que encuentra soluciones vecinas reinsertando las mismas tareas
 * de la máquina pero en distintas posiciones para ver si mejora la solución que
 * ya tenemos
 *
 * @return Solucion
 */
Solucion AlgoritmoGrasp::exploracionVecindarioReinsertando(
    int numero_maximo_intentos) {
  // Primero encontramos una solución vecina inicial en alguna de las máquinas
  int maquina_mejorada;
  for (int i{0}; i < solucion_algoritmo_.getSolucion().first.size(); ++i) {
    if (solucionVecinaEncontrada(solucion_algoritmo_.getSolucion().first[i])) {
      maquina_mejorada = i;
      break;
    }
  }
  // A partir de la solución econtrada anteriormente seguimos buscando
  // soluciones
  int numero_intentos{0};
  for (int maquina{maquina_mejorada};
       maquina < solucion_algoritmo_.getSolucion().first.size(); ++maquina) {
    while (numero_intentos < numero_maximo_intentos) {
      (solucionVecinaEncontrada(solucion_algoritmo_[maquina]))
          ? numero_intentos = 0
          : ++numero_intentos;
    }
  }
  solucion_algoritmo_.setCosteTotal(calcularTCTTotal());
  return solucion_algoritmo_;
}

/**
 * @brief Método que ejecuta el algoritmo con la fase constructiva y con la fase
 * de postprocesamiento para hallar una nueva solución
 * @return Solucion solucion encontrada después de ejecutar el algoritmo
 */
Solucion AlgoritmoGrasp::resolver() {
  faseConstructiva();
  exploracionVecindarioReinsertando();
  return solucion_algoritmo_;
}