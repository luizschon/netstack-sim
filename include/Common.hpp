#ifndef __COMMON_HPP
#define __COMMON_HPP

#include <vector>
#include <string>

/* Quantidade de bits em um byte. */
#define TAM_BYTE 8

/* Implementa tipo "bit" usando tipo bool representando 0 ou 1. 
 * Mesmo representando valores binários, o tipo booleano ocupa
 * 8 bits (1 byte de memória) para guardar informação de 1 bit.
 * O desperdício é custoso, porém 1 byte é a menor divisão de
 * memória em C/C++. */
typedef bool bit;

/* Implementa tipo "byte" usando tipo primitivo unsigned char. */
typedef unsigned char byte;

/* Tipo usado para representar energia do sinal gerado durante
 * a codificação. Como nessa simulação não há modulação, o sinal
 * será enviado da mesma forma que ele é codificado na camada 
 * física, com amplitudes de +/-5 Volts. */
typedef int volt;

/* Expressões constante para representar os pulsos elétricos 
 * codificados no sinal em volts. */
#define PULSO_POS 5
#define PULSO_NULO 0
#define PULSO_NEG -5

/* Enumerador para tornar a seleção do tipo de codificação
 * mais legível no código. */
typedef enum {
    COD_BINARIA, COD_MANCHESTER, COD_BIPOLAR
} tipos_codificacao;

/* Enumerador para tornar a seleção do tipo de enquadramento
 * mais legível no código. */
typedef enum {
    CONTAGEM_DE_CARAC, INSERCAO_DE_BYTES
} tipos_enquadramento;

typedef std::pair<float*, float*> eixos;

namespace utils {

    // Operação que transforma string em um trem de bits.
    std::vector<bit> string_para_bits(const std::string &str);

    // Operações com overload para capturar bytes no trem de bits.
    byte get_byte(std::vector<bit>::iterator it);
    byte get_byte(std::vector<bit> &trem_de_bits, unsigned int pos);

    // Operação para capturar e tratar uma sequência de bytes
    std::vector<byte> get_bytes(std::vector<bit> &trem_de_bits);
    std::string bytes_para_string(std::vector<byte> &bytes);
    std::string bits_para_string(std::vector<bit> &trem_de_bits);

    // Função de debug 
    void print_bits(std::vector<bit> &trem_de_bits);

    // Funções para gerar os eixos para o plot
    float * geraEixoX(std::vector<bit> &trem_de_bits, int amostras);
    float * geraEixoY(std::vector<bit> &trem_de_bits, int amostras);
    float * geraEixoX(std::vector<volt> &sinal, int amostras, tipos_codificacao tipo);
    float * geraEixoY(std::vector<volt> &sinal, int amostras);

};

#endif // __COMMON_HPP
