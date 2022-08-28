#include "CamadaAplicacao.hpp"

using namespace camada_apl;

void Modulo::setMensagem(const std::string mensagem) {
    this->mensagem = mensagem;
} // fim do método Modulo::setMensagem

std::string Modulo::getMensagem() {
    return this->mensagem;
} // fim do método Modulo::getMensagem

/* Transforma mensagem em quadro (composto de bits) e transmite
 * para o transmissor da camada física. */
void Transmissor::transmitir(camada_fis::Transmissor *transmissor) {
    std::vector<bit> quadro = utils::string_para_bits(this->getMensagem());
    transmissor->setQuadro(quadro);
} // fim do método Transmissor::transmitir

/* Recebe um quadro (composto de bits) do receptor da camada
 * física e traduz para uma string. */
void Receptor::receber(camada_fis::Receptor *receptor) {
    std::vector<bit> quadro = receptor->getQuadro();
    std::string mensagem = utils::bits_para_string(quadro);
    this->setMensagem(mensagem);
} // fim do método Receptor::receber

