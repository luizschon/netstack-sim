#include <iostream>
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

void Pilha::setControleDeErro(tipos_controle_erro tipo) {
    this->controle_de_erro = tipo;
    trans_enlace->setControleDeErro(tipo);
    recep_enlace->setControleDeErro(tipo);
} // fim do método Pilha::setControleDeErro

void Pilha::setCodigo(tipos_codificacao tipo) {
    trans_fisico->setCodigo(tipo);
    recep_fisico->setCodigo(tipo);
} // fim do método Pilha::setCodigo

/* Método responsável por transmitir a string de input da
 * camada de aplicação para a camada física, gerar o sinal
 * e transmití-lo através do meio de comunicação. */
void Pilha::enviaMensagem() {
    trans_aplicacao->setMensagem(input);          // Gera o trem de bits da correspondente a mensagem
    trans_aplicacao->transmitir(trans_enlace);    // Transmite o trem de bits para a camada de enlace
    trans_enlace->geraQuadro();                   // Enquadra o trem de bits original
    trans_enlace->geraQuadroCodificado();         // Codifica o quadro original usando controle de erro
    trans_enlace->transmitir(trans_fisico);       // Transmite o quadro codificado à camada física
    trans_fisico->geraSinal();                    // Geral sinal elétrico para transmitir o quadro
    meio->transmitir(trans_fisico, recep_fisico); // Usa meio de comunicação para transmitir bits

    // Salva resultados nos atributos privados
    bits_input = trans_enlace->getTremDeBits();
    quadro_input = trans_enlace->getQuadro();
    quadro_codificado_input = trans_enlace->getQuadroCodificado();
    sinal_input = trans_fisico->getSinal();
} // fim do método Pilha::enviaMensagem

/* Método resposável por gerar o quadro a partir da decodificacao
 * do sinal transmitido pelo meio, traduzir e mensagem a partir
 * dos bits do quadro, e inserir o resultado na string de output. */
void Pilha::recebeMensagem() {
    recep_fisico->geraQuadro();             // Gera quadro a partir do sinal recebido
    recep_enlace->receber(recep_fisico);    // Recebe quadro enviado pelo receptor da camada física

    // Tenta gerarQuadro original e lida com exceção quando um erro
    // é detectado. Caso o controle de erro seja código de Hamming,
    // corrige o quadro
    try {
        recep_enlace->geraQuadro();         // Gera quadro original a partir do quadro com controle de erro
    } catch (std::exception &exp) {
        if (controle_de_erro == HAMMING)
            recep_enlace->corrigeQuadro();  // Corrige erro no quadro
        else
            throw exp;
    }

    recep_enlace->geraTremDeBits();         // Gera quadro trem de bits a partir do quadro
    recep_aplicacao->receber(recep_enlace); // Recebe trem de bits pelo receptor da camada de enlace
     
    // Salva resultados nos atributos privados
    sinal_output = recep_fisico->getSinal();
    quadro_codificado_output = recep_enlace->getQuadroCodificado();
    quadro_output = recep_enlace->getQuadro();
    bits_output = recep_enlace->getTremDeBits();
    output = recep_aplicacao->getMensagem();
} // fim do método Pilha::recebeMensagem

/* Método responsável por receber uma string e tipo de codificação
 * do usuário e simular a comunicação entre transmissores e 
 * receptores implementados na pilha. os resultados são armazenados
 * nos atributos privados da instância de Pilha. */
void Pilha::simula(
        const std::string &msg,
        tipos_enquadramento tipo_enq,
        tipos_controle_erro tipo_err,
        tipos_codificacao tipo_cod
    )
{
    input = msg;
    setEnquadramento(tipo_enq);
    setControleDeErro(tipo_err);
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

std::vector<bit> Pilha::getQuadroCodificadoInput() {
    return quadro_codificado_input;
} // fim do método Pilha::getQuadroCodificadoInput

std::vector<bit> Pilha::getQuadroCodificadoOutput() {
    return quadro_codificado_output;
} // fim do método Pilha::getQuadroCodificadoOutput

std::vector<volt> Pilha::getSinalInput() {
    return sinal_input;
} // fim do método Pilha::getSinalInput

std::vector<volt> Pilha::getSinalOutput() {
    return sinal_output;
} // fim do método Pilha::getSinalOutput

