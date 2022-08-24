#include <iostream>
#include "CamadaFisica.hpp"
#include "Common.hpp"

using namespace camada_fis;

std::vector<bit> camada_fis::mensagem_para_quadro(const std::string &mensagem) {
    std::vector<bit> quadro;

    for (auto &c : mensagem) {
        for(int i = 0; i < TAM_BYTE; i++) {
            /* Para cada caractere da mensagem, insere os bits do byte do caracter
             * na ordem big-endian -> little-endian. */
            quadro.push_back(((c << i) & 0x80));
        }
    }
    return quadro;
} // fim do método mensagem_para_quadro

Codificacao::Codificacao(const std::string &mensagem) {
    std::cout << "From codificacao: " << mensagem << "\n";
    this->quadro = mensagem_para_quadro(mensagem);
    std::cout << "Quadro size: " << quadro.size() << "bits or " << quadro.size()/8 << " bytes\n";
} // fim do método construtor Codificacao

void Codificacao::setQuadro(std::vector<bit> &quadro) {
    this->quadro = quadro;
} // fim do método setQuadro

void Codificacao::setQuadro(const std::string &mensagem) {
    this->quadro = mensagem_para_quadro(mensagem);
} // fim do método setQuadro

std::vector<bit> Codificacao::getQuadro() {
    return quadro;
} // fim do método setQuadro

Binaria::Binaria(std::string mensagem) : Codificacao(mensagem) {

} // fim do método construtor Binaria
  
void Binaria::codificar() {

} // fim do método Binaria::transmitir

std::string Binaria::decodificar() {

} // fim do método Binaria::decodificar

Manchester::Manchester(std::string mensagem) : Codificacao(mensagem) {

} // fim do método construtor Manchester

void Manchester::codificar() {

} // fim do método Manchester::transmitir

std::string Manchester::decodificar() {

} // fim do método Manchester::decodificar

Bipolar::Bipolar(std::string mensagem) : Codificacao(mensagem) {

} // fim do método construtor Bipolar

void Bipolar::codificar() {

} // fim do método Bipolar::transmitir

std::string Bipolar::decodificar() {

} // fim do método Bipolar::decodificar

void meio_comunicacao::transmitir(bit trem_de_bits[]) {

} // fim do método meio_comunicacao::transmitir
