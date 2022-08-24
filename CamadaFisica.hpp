#ifndef __CAMADA_FISICA_HPP
#define __CAMADA_FISICA_HPP

#include <string>

/* Implementa tipo "bit" usando tipo primitivo bool
 * (booleano) representando 0 ou 1. */
typedef bool bit;

/* Enumerador para tornar a seleção do tipo de codificação
 * mais legível no código. */
enum {
    COD_BINARIA, COD_MANCHESTER, COD_BIPOLAR
};

namespace camada_fis {

    /* Função de utilidade para transformar mensagem (string) em
     * um quadro composto de bits. */
    int* mensagem_para_quadro(std::string mensagem);

    /* Classe abstrata para representar uma codificação genérica
     * da camada física da comunicação. */
    class Codificacao {
    public:
        Codificacao(std::string mensagem);
        Codificacao() = default; 
        virtual ~Codificacao();

        // Assinatura dos métodos virtuais puros
        virtual void codificar()   = 0;
        virtual void decodificar() = 0;

        // Setters e getter para o quadro
        void setQuadro(bit quadro[]);
        void setQuadro(std::string mensagem);
        bit* getQuadro();

    protected:
        bit *quadro = nullptr; // Quadro composto de bits (valor booleano 0 ou 1)
    };

    /* Classe que deriva a classe abstrata 'Codificacao' e implementa
     * métodos virtuais seguindo o padrão da codificação binária (NRZ). */
    class Binaria : public Codificacao {
    public:
        Binaria(std::string mensagem);
        Binaria() = default;
        ~Binaria() = default;

        void codificar() override;
        void decodificar() override;
    };

    /* Classe que deriva a classe abstrata 'Codificacao' e implementa
     * métodos virtuais seguindo o padrão da codificação Manchester 
     * (NRZ XOR Clock). */
    class Manchester : public Codificacao {
    public:
        Manchester(std::string mensagem);
        Manchester() = default;
        ~Manchester() = default;

        void codificar() override;
        void decodificar() override;
    };

    /* Classe que deriva a classe abstrata 'Codificacao' e implementa
     * métodos virtuais seguindo o padrão da codificação bipolar (AMI). */
    class Bipolar : public Codificacao {
    public:
        Bipolar(std::string mensagem);
        Bipolar() = default;
        ~Bipolar() = default;

        void codificar() override;
        void decodificar() override;
    };

}

namespace meio_comunicacao {
    /* Função que transmite trem de bits da camada física transmissora 
     * para a camada física receptora. */
    void transmitir(bit trem_de_bits[]);
}

#endif // __CAMADA_FISICA_HPP
