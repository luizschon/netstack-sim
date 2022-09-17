#include "Simulador.hpp"

using namespace sim;

/* Método construtor da Pilha da simulação, aloca memória
 * para os elementos trasmissores e receptores que serão
 * usados durante a simulação. */
Pilha::Pilha() {
    trans_aplicacao = new aplicacao::Transmissor;
    recep_aplicacao = new aplicacao::Receptor;
    trans_enlace = new enlace::Transmissor;
    recep_enlace = new enlace::Receptor;
    trans_fisico = new fisica::Transmissor;
    recep_fisico  = new fisica::Receptor;
    meio = new fisica::MeioComunicacao;
} // fim do método construtor Pilha::Pilha

/* Método destrutor da Pilha da simulação, deleta blocos
 * de memória alocados. */
Pilha::~Pilha() {
    delete trans_aplicacao;
    delete recep_aplicacao;
    delete trans_enlace;
    delete recep_enlace;
    delete trans_fisico;
    delete recep_fisico;
    delete meio;
} // fim do método construtor Pilha::~Pilha

void Pilha::setEnquadramento(tipos_enquadramento tipo) {
    trans_enlace->setEnquadramento(tipo);
    recep_enlace->setEnquadramento(tipo);
} // fim do método Pilha::setEnquadramento

void Pilha::setCodigo(tipos_codificacao tipo) {
    trans_fisico->setCodigo(tipo);
    recep_fisico->setCodigo(tipo);
} // fim do método Pilha::setCodigo

/* Método responsável por transmitir a string de input da
 * camada de aplicação para a camada física, gerar o sinal
 * e transmití-lo através do meio de comunicação. */
void Pilha::enviaMensagem() {
    trans_aplicacao->setMensagem(input);
    trans_aplicacao->transmitir(trans_enlace);
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
    recep_enlace->receber(recep_fisico);

    recep_enlace->geraTremDeBits();
    recep_aplicacao->receber(recep_enlace);

    // Salva resultados nos atributos privados
    bits_output = recep_enlace->getTremDeBits();
    quadro_output = recep_enlace->getQuadro();
    sinal_output = recep_fisico->getSinal();
    output = recep_aplicacao->getMensagem();
} // fim do método Pilha::recebeMensagem

/* Método responsável por receber uma string e tipo de codificação
 * do usuário e simular a comunicação entre transmissores e 
 * receptores implementados na pilha. os resultados são armazenados
 * nos atributos privados da instância de Pilha. */
void Pilha::simula(const std::string &msg, tipos_enquadramento tipo_enq, tipos_codificacao tipo_cod) {
    input = msg;
    setEnquadramento(tipo_enq);
    setCodigo(tipo_cod);

    enviaMensagem();
    recebeMensagem();
} // fim do método Pilha::simula

std::string Pilha::getInput() {
    return input;
} // fim do método Pilha::getInput

std::string Pilha::getOutput() {
    return output;
} // fim do método Pilha::getOutput

std::vector<bit> Pilha::getTremDeBitsInput() {
    return bits_input;
} // fim do método Pilha::getTremDeBitsInput
 
std::vector<bit> Pilha::getTremDeBitsOutput() {
    return bits_output;
} // fim do método Pilha::getTremDeBitsInput

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

