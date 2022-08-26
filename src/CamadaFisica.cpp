#include <iostream>
#include "../include/CamadaFisica.hpp"
#include "../include/Common.hpp"

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

} // fim do método Manchester::codificar

std::vector<bit> Manchester::decodificar(std::vector<volt> &sinal) {

} // fim do método Manchester::decodificar

std::vector<volt> Bipolar::codificar(std::vector<bit> &quadro) {

} // fim do método Bipolar::codificar

std::vector<bit> Bipolar::decodificar(std::vector<volt> &sinal) {

} // fim do método Bipolar::decodificar
  //
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

Modulo::Modulo(Codificacao &codigo) {
    this->codigo = &codigo;    
} // fim do método construtor Modulo::Modulo

void Modulo::setCodigo(tipos_codificacao tipo) {
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

void Modulo::setCodigo(Codificacao &codigo) {
    this->codigo = &codigo;    
} // fim do método Modulo::setCodigo

void Modulo::setSinal(std::vector<volt> &sinal) {
    this->sinal = sinal;
}

std::vector<volt> Modulo::getSinal() {
    return this->sinal;
} // fim do método Modulo::setCodigo

Transmissor::Transmissor(tipos_codificacao tipo) 
: Modulo(tipo) {} // fim do método construtor Transmissor::Transmissor

Transmissor::Transmissor(Codificacao &codigo)
: Modulo(codigo) {} // fim do método construtor Transmissor::Transmissor
                    //
void Transmissor::geraSinal() {
    this->sinal = this->codigo->codificar(this->quadro);
} // fim do método Transmissor::getSinal

void Transmissor::geraSinal(const std::string &mensagem) {
    this->quadro = utils::string_para_bits(mensagem);
    this->sinal = this->codigo->codificar(this->quadro);
} // fim do método Transmissor::getSinal

Receptor::Receptor(tipos_codificacao tipo) 
: Modulo(tipo) {} // fim do método construtor Receptor::Receptor

Receptor::Receptor(Codificacao &codigo)
: Modulo(codigo) {} // fim do método construtor Receptor::Receptor

std::string Receptor::interpretaSinal() {
    this->quadro = this->codigo->decodificar(this->sinal);
    return utils::bits_para_string(this->quadro);
} // fim do método Receptor::interpretaSinal

MeioComunicacao::MeioComunicacao(Transmissor &transmissor, Receptor &receptor) {
    this->transmissor = &transmissor;
    this->receptor = &receptor;
} // fim do método construtor MeioComunicacao::MeioComunicacao

void MeioComunicacao::setTransmissor(Transmissor &transmissor) {
    this->transmissor = &transmissor;
} // fim do método MeioComunicacao::setTransmissor

void MeioComunicacao::setReceptor(Receptor &receptor) {
    this->receptor = &receptor;
} // fim do método MeioComunicacao::setReceptor

void MeioComunicacao::transmitir() {
    std::vector<volt> sinalTransmitido = transmissor->getSinal();
    std::vector<volt> sinalRecebido = receptor->getSinal();
    auto it = sinalTransmitido.begin();


    while(sinalTransmitido.size() != sinalRecebido.size()) {
        sinalRecebido.push_back(*it);
        it++;
    }

    receptor->setSinal(sinalRecebido);
} // fim do método MeioComunicacao::transmitir

