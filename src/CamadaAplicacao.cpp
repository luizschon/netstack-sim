#include "CamadaAplicacao.hpp"

using namespace aplicacao;

void Modulo::setMensagem(const std::string mensagem) {
    this->mensagem = mensagem;
} // fim do método Modulo::setMensagem

std::string Modulo::getMensagem() {
    return this->mensagem;
} // fim do método Modulo::getMensagem

/* Transforma mensagem em quadro (composto de bits) e transmite
 * para o transmissor da camada física. */
void Transmissor::transmitir(enlace::Transmissor *transmissor) {
    std::vector<bit> trem_de_bits = utils::string_para_bits(this->getMensagem());
    transmissor->setTremDeBits(trem_de_bits);
} // fim do método Transmissor::transmitir

/* Recebe um quadro (composto de bits) do receptor da camada
 * física e traduz para uma string. */
void Receptor::receber(enlace::Receptor *receptor) {
    std::vector<bit> trem_de_bits = receptor->getTremDeBits();
    std::string mensagem = utils::bits_para_string(trem_de_bits);
    this->setMensagem(mensagem);
} // fim do método Receptor::receber

