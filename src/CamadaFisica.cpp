#include "CamadaFisica.hpp"
#include "Common.hpp"

using namespace camada_fis;

std::vector<volt> Binaria::codificar(std::vector<bit> &quadro) {
    /* A codificação NRZ (Non return zero) unipolar utiliza
     * somente um nível de tensão +5V (para bit 1) e, portanto,
     * é igual ao trem de bits original criado. */
    std::vector<volt> sinal;

    /* Para cada bit 1 do quadro, insere um pulso positivo no
     * sinal (+5V), e 0 para cada bit 0. */
    for (auto b : quadro) {
        sinal.push_back(b * PULSO_POS);
    }
    return sinal;
} // fim do método Binaria::codificar

std::vector<bit> Binaria::decodificar(std::vector<volt> &sinal) {
    std::vector<bit> quadro;

    /* Divide o pulso pelo valor de energia (+5V) em cada
     * pulso so sinal para recuperar o quadro. */
    for (auto s : sinal) {
        quadro.push_back(s/PULSO_POS);
    }
    return quadro;
} // fim do método Binaria::decodificar

std::vector<volt> Manchester::codificar(std::vector<bit> &quadro) {
    std::vector<volt> sinal;

    /* Na codificação Manchester, os bits 1 são codificados
     * para os bits 10 e os bits 0 são codificados para os
     * bits 01. */
    for (auto b : quadro) {
        if (b == 1)
            sinal.insert(sinal.end(), {PULSO_POS, PULSO_NULO});
        else
            sinal.insert(sinal.end(), {PULSO_NULO, PULSO_POS});
    }
    return sinal;
} // fim do método Manchester::codificar

std::vector<bit> Manchester::decodificar(std::vector<volt> &sinal) {
    std::vector<bit> quadro;

    for (auto it = sinal.begin(); it != sinal.end(); it += 2) {
        if (*it == PULSO_POS && *(it+1) == PULSO_NULO)
            quadro.push_back(1);
        else 
            quadro.push_back(0);
    }
    return quadro;
} // fim do método Manchester::decodificar

std::vector<volt> Bipolar::codificar(std::vector<bit> &quadro) {
    std::vector<volt> sinal;
    // Contador utilizado para alternar entre voltagem positiva e negativa
    int contador = 0;
    int val = PULSO_NULO; // Valor que será inserido no sinal a cada iteração

    /* Na codificação Bipolar (AMI), o pulso de voltagem é
     * alternada entre +5V e -5V a cada bit 1. Os bits 0 
     * são codificados como um pulso nulo. */
    for (auto b : quadro) {
        val = PULSO_NULO;
        if (b == 1) {
            if (contador % 2 == 0) 
                val = PULSO_POS;
            else
                val = PULSO_NEG;
        }
        sinal.push_back(val);
    }
    return sinal;
} // fim do método Bipolar::codificar

std::vector<bit> Bipolar::decodificar(std::vector<volt> &sinal) {
    std::vector<bit> quadro;

    /* Para decodificar um sinal Bipolar (AMI) basta reparar
     * que um pulso nulo representa o bit 0 e qualquer outro
     * pulso representa um bit 1. */
    for (auto s : sinal) {
        if (s == PULSO_NULO)
            quadro.push_back(0);
        else
            quadro.push_back(1);
    }
    return quadro;
} // fim do método Bipolar::decodificar

Modulo::Modulo(tipos_codificacao tipo) {
    switch (tipo) {
        case COD_BINARIA:
            codigo = new Binaria();
            break;
        case COD_MANCHESTER:
            codigo = new Manchester();
            break;
        case COD_BIPOLAR:
            codigo = new Bipolar();
            break;
    }
} // fim do método construtor Modulo::Modulo

void Modulo::setCodigo(tipos_codificacao tipo) {
    // Deleta codificação alocada caso exista
    if (this->codigo != nullptr)
        delete this->codigo;

    switch (tipo) {
        case COD_BINARIA:
            codigo = new Binaria();
            break;
        case COD_MANCHESTER:
            codigo = new Manchester();
            break;
        case COD_BIPOLAR:
            codigo = new Bipolar();
            break;
    }
} // fim do método Modulo::setCodigo

void Modulo::setQuadro(std::vector<bit> &quadro) {
    this->quadro = quadro;
} // fim do método Modulo::setQuadro

void Modulo::setSinal(std::vector<volt> &sinal) {
    this->sinal = sinal;
} // fim de método Modulo::setSinal

std::vector<volt> Modulo::getSinal() {
    return this->sinal;
} // fim do método Modulo::getSinal

std::vector<bit> Modulo::getQuadro() {
    return this->quadro; 
} // fim do método Modulo::getQuadro

Transmissor::Transmissor(tipos_codificacao tipo) 
: Modulo(tipo) {} // fim do método construtor Transmissor::Transmissor

void Transmissor::geraSinal() {
    this->sinal = this->codigo->codificar(this->quadro);
} // fim do método Transmissor::getSinal

Receptor::Receptor(tipos_codificacao tipo) 
: Modulo(tipo) {} // fim do método construtor Receptor::Receptor

void Receptor::geraQuadro() {
    this->quadro = this->codigo->decodificar(this->sinal);
} // fim do método Receptor::geraQuadro

void MeioComunicacao::transmitir(Transmissor *trans, Receptor *recep) {
    std::vector<volt> sinalTransmitido = trans->getSinal();
    std::vector<volt> sinalRecebido = recep->getSinal();

    sinalRecebido.clear();
    auto it = sinalTransmitido.begin();

    while(sinalTransmitido.size() != sinalRecebido.size()) {
        sinalRecebido.push_back(*it);
        it++;
    }
    recep->setSinal(sinalRecebido);
} // fim do método MeioComunicacao::transmitir

