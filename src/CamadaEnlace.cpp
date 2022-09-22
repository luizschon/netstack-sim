#include <iostream>
#include <stdexcept>
#include "CamadaEnlace.hpp"
#include "Common.hpp"

using namespace enlace;

std::vector<bit> ContagemDeCaracteres::enquadrar(std::vector<bit> &trem_de_bits) {
    int length = trem_de_bits.size()/TAM_BYTE;

    std::vector<bit> cabecalho = utils::int_para_bits(length+1);
    cabecalho.insert(cabecalho.end(), trem_de_bits.begin(), trem_de_bits.end());

    return cabecalho;
} // fim do método ContagemDeCaracteres::enquadrar

std::vector<bit> ContagemDeCaracteres::desenquadrar(std::vector<bit> &quadro) {
    std::vector<bit> cabecalho(quadro.begin(), quadro.begin() + TAM_BYTE);
    std::vector<bit> trem_de_bits;
    int length = utils::bits_para_int(cabecalho);

    for (int i = 0; i < TAM_BYTE*(length-1); i++) {
        trem_de_bits.push_back(quadro[i+TAM_BYTE]);
    }

    return trem_de_bits;
} // fim do método ContagemDeCaracteres::desenquadrar

std::vector<bit> InsercaoDeBytes::enquadrar(std::vector<bit> &trem_de_bits) {
    std::vector<bit> quadro;

    // Insere flag no início do quadro
    utils::insere_byte(FLAG, quadro);

    for (auto it = trem_de_bits.begin(); it != trem_de_bits.end();) {
        // Lê cada byte do trem de bits
        byte curr_byte = utils::get_byte(it);

        // Caso o byte seja o byte usado como flag, insere um ESC antes de inserir o byte
        if (curr_byte == FLAG)
            utils::insere_byte(ESC, quadro);

        // Finalmente, insere o byte lido ao quadro
        utils::insere_byte(curr_byte, quadro);
    }

    // Insere flag no final do quadro
    utils::insere_byte(FLAG, quadro);

    return quadro;
} // fim do método InsercaoDeBytes::enquadrar

std::vector<bit> InsercaoDeBytes::desenquadrar(std::vector<bit> &quadro) {
    std::vector<bit> trem_de_bits;

    for (auto it = quadro.begin(); it != quadro.end();) {
        byte curr_byte = utils::get_byte(it);

        for (int i = 0; i < TAM_BYTE; i++) {
            std::cout << (0x1 & curr_byte >> (TAM_BYTE-(i+1)));
        }

        if (curr_byte != FLAG) {
            throw std::runtime_error("Flag não encontrada no início do quadro!");
            break; 
        }

        bool end_flag_found = false;

        // Lê e insere bytes até encontrar byte da flag
        while (not end_flag_found) {
            // Lança excessão caso a FLAG final não tenha sido encontrada
            if (it == quadro.end()) {
                std::cout << "[ERR] Flag no final do quadro não encontrado!\n";
                throw std::runtime_error("Flag não encontrada no fim do quadro!");
            }
                
            bool before_esc = false;

            // Lê bytes do quadro
            curr_byte = utils::get_byte(it);
            for (int i = 0; i < TAM_BYTE; i++) {
                std::cout << (0x1 & curr_byte >> (TAM_BYTE-(i+1)));
            }
            std::cout << "\n";

            // Verifica se o byte ESC ou FLAG foram encontrados
            if (curr_byte == ESC) {
                before_esc = true;
            } else if (curr_byte == FLAG and not before_esc) {
                end_flag_found = true;
            } else {
                // Insere no trem de bits caso não seja a FLAG final ou ESC
                utils::insere_byte(curr_byte, trem_de_bits);
            }
        }
    }

    return trem_de_bits;
} // fim do método InsercaoDeBytes::desenquadrar

std::vector<bit> BitDeParidadePar::codificar(std::vector<bit> &trem_de_bits) {
    int bits_um = 0;
    std::vector<bit> codificado(trem_de_bits);

    for (auto bit : trem_de_bits) {
        if (bit == 1)
            bits_um++;
    }

    // Insere bit de paridade par no trem de bits
    codificado.push_back(bits_um % 2);
    return codificado;
} // fim do método BitDeParidadePar::codificar

bool BitDeParidadePar::detectar(std::vector<bit> &quadro) {
    bit bit_paridade = quadro[quadro.size() - 1];
    int bits_um = 0;

    // Recalcula o bit de paridade
    for (auto bit : quadro) {
        if (bit == 1)
            bits_um++;
    }

    // Compara bit de paridade calculado com o recebido no fim do trem de bits
    if (bit_paridade == bits_um % 2)
        return true;
    
    return false;
} // fim de método BitDeParidadePar::detectar

std::vector<bit> BitDeParidadePar::decodificar(std::vector<bit> &quadro_codificado) {
    // Remove bit de paridade no final do quadro codificado
    std::vector<bit> quadro(quadro_codificado.begin(), quadro_codificado.end() - 1);
    return quadro;
} // fim de método BitDeParidadePar::decodificar

std::vector<bit> CRC::codificar(std::vector<bit> &trem_de_bits) {
    std::cout << "Nao implementado codificar (CRC)\n";
    throw std::runtime_error("Nao implementado codificar (CRC)");
    return {};
} // fim do método CRC::codificar

bool CRC::detectar(std::vector<bit> &quadro) {
    std::cout << "Nao implementado detectar (CRC)\n";
    throw std::runtime_error("Nao implementado detectar (CRC)");
    return true;
} // fim de método CRC::detectar

std::vector<bit> CRC::decodificar(std::vector<bit> &quadro) {
    std::cout << "Nao implementado decodificar (CRC)\n";
    throw std::runtime_error("Nao implementado decodificar (CRC)");
    return {};
} // fim de método CRC::decodificar

std::vector<bit> Hamming::codificar(std::vector<bit> &quadro) {
    std::cout << "Nao implementado codificar (HAMMING)\n";
    throw std::runtime_error("Nao implementado codificar (HAMMING)");
    return {};
} // fim do método Hamming::codificar

bool Hamming::detectar(std::vector<bit> &quadro) {
    std::cout << "Nao implementado detectar (HAMMING)\n";
    throw std::runtime_error("Nao implementado detectar (HAMMING)");
    return true;
} // fim do método Hamming::detectar

std::vector<bit> Hamming::corrigir(std::vector<bit> &quadro) {
    std::cout << "Nao implementado corrigir (HAMMING)\n";
    throw std::runtime_error("Nao implementado corrigir (HAMMING)");
    return {};
} // fim do método Hamming::corrigir

std::vector<bit> Hamming::decodificar(std::vector<bit> &quadro) {
    std::cout << "Nao implementado decodificar (HAMMING)\n";
    throw std::runtime_error("Nao implementado decodificar (HAMMING)");
    return {};
} // fim de método Hamming::decodificar

Modulo::~Modulo() {
    delete enquadramento;
    delete controle_erro;
} // fim do método destructor Modulo::~Modulo

void Modulo::setEnquadramento(tipos_enquadramento tipo) {
    // Deleta instância de enquadramento alocada caso exista
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

void Modulo::setControleDeErro(tipos_controle_erro tipo) {
    // Deleta instância de controle de erro alocada caso exista
    if (controle_erro != nullptr)
        delete controle_erro;

    switch (tipo) {
        case BIT_PARIDADE:
            controle_erro = new BitDeParidadePar();
            break;
        case CRC_32:
            controle_erro = new CRC();
            break;
        case HAMMING:
            controle_erro = new Hamming();
            break;
    }
} // fim do método Modulo::setControleDeErro

void Modulo::setQuadroCodificado(std::vector<bit> &quadro_codificado) {
    this->quadro_codificado = quadro_codificado;
} // fim de método Modulo::setQuadroCodificado

void Modulo::setQuadro(std::vector<bit> &quadro) {
    this->quadro = quadro;
} // fim do método Modulo::setQuadro

void Modulo::setTremDeBits(std::vector<bit> &trem_de_bits) {
    this->trem_de_bits = trem_de_bits;
} // fim do método Modulo::setTremDeBits

std::vector<bit> Modulo::getQuadroCodificado() {
    return this->quadro_codificado; 
} // fim do método Modulo::getQuadroCodificado

std::vector<bit> Modulo::getQuadro() {
    return this->quadro; 
} // fim do método Modulo::getQuadro

std::vector<bit> Modulo::getTremDeBits() {
    return this->trem_de_bits; 
} // fim do método Modulo::getTremDeBits

void Transmissor::geraQuadro() {
    this->quadro = this->enquadramento->enquadrar(this->trem_de_bits);
} // fim do método Transmissor::geraQuadro
 
void Transmissor::geraQuadroCodificado() {
    this->quadro_codificado = this->controle_erro->codificar(this->quadro);
} // fim do método Transmissor::geraCodificado

void Receptor::corrigeQuadro() {
    std::cout << "Não implementado Receptor::corrigeQuadro\n";
    throw std::runtime_error("Não implementado Receptor::corrigeQuadro");
}

void Transmissor::transmitir(fisica::Transmissor *transmissor) {
    transmissor->setQuadro(quadro_codificado);
} // fim do método Transmissor::transmitir

void Receptor::geraQuadro() {
    this->quadro = this->controle_erro->decodificar(this->quadro_codificado);
} // fim do método Receptor::geraQuadro
  //
void Receptor::geraTremDeBits() {
    this->trem_de_bits = this->enquadramento->desenquadrar(this->quadro);
} // fim do método Receptor::geraTremDeBits

void Receptor::receber(fisica::Receptor *receptor) {
    this->quadro_codificado = receptor->getQuadro();
} // fim do método Receptor::receber
