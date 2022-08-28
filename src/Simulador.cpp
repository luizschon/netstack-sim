#include "Simulador.hpp"
#include "CamadaFisica.hpp"
#include "CamadaAplicacao.hpp"
#include "Common.hpp"

using namespace sim;

Pilha::Pilha() {
    trans_aplicacao = new camada_apl::Transmissor;
    recep_aplicacao = new camada_apl::Receptor;
    trans_fisico = new camada_fis::Transmissor;
    recep_fisico  = new camada_fis::Receptor;
    meio = new camada_fis::MeioComunicacao;
} // fim do método construtor Pilha::Pilha

void Pilha::setCodigo(tipos_codificacao tipo) {
    trans_fisico->setCodigo(tipo);
    recep_fisico->setCodigo(tipo);
} // fim do método Pilha::setCodigo

/* Método responsável por transmitir a string de input da
 * camada de aplicação para a camada física, gerar o sinal
 * e transmití-lo através do meio de comunicação. */
void Pilha::enviaMensagem() {
    trans_aplicacao->setMensagem(input);
    trans_aplicacao->transmitir(trans_fisico);
    trans_fisico->geraSinal();

    // Salva resultados nos atributos privados
    quadro_input = trans_fisico->getQuadro();
    sinal_input = trans_fisico->getSinal();

    meio->transmitir(trans_fisico, recep_fisico);
} // fim do método Pilha::enviaMensagem

/* Método resposável por gerar o quadro a partir da decodificacao
 * do sinal transmitido pelo meio, traduzir e mensagem a partir
 * dos bits do quadro, e inserir o resultado na string de output. */
void Pilha::recebeMensagem() {
    recep_fisico->geraQuadro();

    recep_aplicacao->receber(recep_fisico);

    // Salva resultados nos atributos privados
    quadro_output = recep_fisico->getQuadro();
    sinal_output = recep_fisico->getSinal();
    output = recep_aplicacao->getMensagem();
} // fim do método Pilha::recebeMensagem

/* Método responsável por receber uma string e tipo de codificação
 * do usuário e simular a comunicação entre transmissores e 
 * receptores implementados na pilha. os resultados são armazenados
 * nos atributos privados da instância de Pilha. */
void Pilha::simula(const std::string &msg, tipos_codificacao tipo) {
    input = msg;
    setCodigo(tipo);

    enviaMensagem();
    recebeMensagem();
} // fim do método Pilha::simula

std::string Pilha::getInput() {
    return input;
} // fim do método Pilha::getInput

std::string Pilha::getOutput() {
    return output;
} // fim do método Pilha::getOutput

std::vector<bit> Pilha::getQuadroInput() {
    return quadro_input;
} // fim do método Pilha::getQuadroInput

std::vector<bit> Pilha::getQuadroOutput() {
    return quadro_output;
} // fim do método Pilha::getQuadroOutput

std::vector<volt> Pilha::getSinalInput() {
    return sinal_input;
} // fim do método Pilha::getSinalInput

std::vector<volt> Pilha::getSinalOutput() {
    return sinal_output;
} // fim do método Pilha::getSinalOutput

