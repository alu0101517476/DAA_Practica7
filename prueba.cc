#include <algorithm>  // Para std::sort
#include <iostream>
#include <random>
#include <utility>  // Para std::pair
#include <vector>   // Para std::vector

struct TernaTctGrasp {
  int tct_;
  int maquina_;
  int posicion_;
};

int main() {
  TernaTctGrasp tct1{1, 2, 11}, tct2{34, 3, 12},
      tct3{45, 4, 13}, tct4{2, 5, 14}, tct5{67, 6, 15},
      tct6{78, 7, 16}, tct7{89, 8, 17}, tct8{898, 9, 18},
      tct9{12, 10, 19};
  std::vector<TernaTctGrasp> vec = {{tct1}, {tct2}, {tct3}, {tct4}, {tct5}, {tct6}, {tct7}, {tct8}, {tct9}};

  std::sort(vec.begin(), vec.end(),
            [](const TernaTctGrasp& a, const TernaTctGrasp& b) {
              return a.tct_ < b.tct_;
            });
  // Escogemos uno de los 3 mejores candidatos al azar
  int inicio_indice_aleatorio{vec.size() - 3},
      final_indice_aleatorio{vec.size() - 1};
  // Inicializa el generador de números aleatorios
  std::random_device rd;
  std::mt19937 gen(rd());
  // Define el rango de los números aleatorios que quieres generar
  std::uniform_int_distribution<> distrib(inicio_indice_aleatorio,
                                          final_indice_aleatorio);
  TernaTctGrasp candidato_aleatorio{vec[distrib(gen)]};
  std::cout << "Candidato aleatorio entre los 3 primeros: " << std::endl;
  std::cout << candidato_aleatorio.tct_ << ',' << candidato_aleatorio.maquina_
            << ',' << candidato_aleatorio.posicion_ << std::endl;

  // Ahora vec está ordenado considerando solamente el primer elemento de los
  // pares.
  for (const auto& i : vec) {
    std::cout << i.tct_ << ',' << i.maquina_ << ',' << i.posicion_ << ' ';
  }
  std::cout << std::endl;
  return 0;
}
