#include <iostream>
#include "CamadaEnlace.hpp"
#include "Common.hpp"

using namespace enlace;

std::vector<bit> ContagemDeCaracteres::enquadrar(std::vector<bit> &trem_de_bits) {
    std::cout << "Não implementado enquadrar (CONTAGEM DE CARACTERES)\n";
    return {};
} // fim do método ContagemDeCaracteres::enquadrar

std::vector<bit> ContagemDeCaracteres::desenquadrar(std::vector<bit> &quadro) {
    std::cout << "Não implementado desenquadrar (CONTAGEM DE CARACTERES)\n";
    return {};
} // fim do método ContagemDeCaracteres::desenquadrar

std::vector<bit> InsercaoDeBytes::enquadrar(std::vector<bit> &trem_de_bits) {
    std::cout << "Não implementado enquadrar (INSERCAO DE BYTES)\n";
    return {};
} // fim do método InsercaoDeBytes::enquadrar

std::vector<bit> InsercaoDeBytes::desenquadrar(std::vector<bit> &quadro) {
    std::cout << "Não implementado desenquadrar (INSERCAO DE BYTES)\n";
    return {};
} // fim do método InsercaoDeBytes::desenquadrar

Modulo::~Modulo() {
    delete enquadramento;
} // fim do método destructor Modulo::~Modulo

void Modulo::setEnquadramento(tipos_enquadramento tipo) {
    // Deleta codificação alocada caso exista
    if (enquadramento != nullptr)
        delete enquadramento;

    switch (tipo) {
        case CONTAGEM_DE_CARAC:
            enquadramento = new ContagemDeCaracteres();
            break;
        case INSERCAO_DE_BYTES:
            enquadramento = new InsercaoDeBytes();
            break;
    }
} // fim do método Modulo::setEnquadramento

void Modulo::setQuadro(std::vector<bit> &quadro) {
    this->quadro = quadro;
} // fim do método Modulo::setQuadro

void Modulo::setTremDeBits(std::vector<bit> &trem_de_bits) {
    this->trem_de_bits = trem_de_bits;
} // fim do método Modulo::setTremDeBits

std::vector<bit> Modulo::getQuadro() {
    return this->quadro; 
} // fim do método Modulo::getQuadro

std::vector<bit> Modulo::getTremDeBits() {
    return this->trem_de_bits; 
} // fim do método Modulo::getTremDeBits

void Transmissor::geraQuadro() {
    this->quadro = this->enquadramento->enquadrar(this->trem_de_bits);
} // fim do método Transmissor::geraQuadro

void Transmissor::transmitir(fisica::Transmissor *transmissor) {
    transmissor->setQuadro(quadro);
} // fim do método Transmissor::transmitir

void Receptor::geraTremDeBits() {
    this->trem_de_bits = this->enquadramento->desenquadrar(this->quadro);
} // fim do método Receptor::geraTremDeBits

void Receptor::receber(fisica::Receptor *receptor) {
    this->quadro = receptor->getQuadro();
} // fim do método Receptor::receber
