#include "CamadaFisica.hpp"

using namespace camada_fis;

void mensagem_para_quadro(std::string mensagem) {

} // fim do método mensagem_para_quadro

Codificacao::Codificacao(std::string mensagem) {

} // fim do método construtor Codificacao

Codificacao::~Codificacao() {

} // fim do método destrutor ~Codificacao

void Codificacao::setQuadro(bit quadro[]) {

} // fim do método setQuadro

void Codificacao::setQuadro(std::string mensagem) {

} // fim do método setQuadro

bit * Codificacao::getQuadro() {

} // fim do método setQuadro

Binaria::Binaria(std::string mensagem) : Codificacao(mensagem) {

} // fim do método construtor Binaria
  
void Binaria::codificar() {

} // fim do método Binaria::transmitir

void Binaria::decodificar() {

} // fim do método Binaria::decodificar

Manchester::Manchester(std::string mensagem) : Codificacao(mensagem) {

} // fim do método construtor Manchester

void Manchester::codificar() {

} // fim do método Manchester::transmitir

void Manchester::decodificar() {

} // fim do método Manchester::decodificar

Bipolar::Bipolar(std::string mensagem) : Codificacao(mensagem) {

} // fim do método construtor Bipolar

void Bipolar::codificar() {

} // fim do método Bipolar::transmitir

void Bipolar::decodificar() {

} // fim do método Bipolar::decodificar

void meio_comunicacao::transmitir(bit trem_de_bits[]) {

} // fim do método meio_comunicacao::transmitir
