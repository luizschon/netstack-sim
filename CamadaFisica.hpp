#ifndef __CAMADA_FISICA_HPP
#define __CAMADA_FISICA_HPP

#include <string>
#include <vector>
#include "Common.hpp"

namespace camada_fis {

    /* Função de utilidade para transformar mensagem (string) em
     * um quadro composto de bits. */
    std::vector<bit> mensagem_para_quadro(const std::string &mensagem);

    /* Classe abstrata para representar uma codificação genérica
     * da camada física da comunicação. */
    class Codificacao {
    public:
        Codificacao(const std::string &mensagem);
        Codificacao() = default; 
        virtual ~Codificacao() = default;

        // Assinatura dos métodos virtuais puros
        virtual void codificar()          = 0;
        virtual std::string decodificar() = 0;

        // Setters e getter para o quadro
        void setQuadro(std::vector<bit> &quadro);
        void setQuadro(const std::string &mensagem);
        std::vector<bit> getQuadro();

    protected:
        std::vector<bit> quadro; // Quadro composto de bits (valor 0 ou 1)
    };

    /* Classe que deriva a classe abstrata 'Codificacao' e implementa
     * métodos virtuais seguindo o padrão da codificação binária (NRZ). */
    class Binaria : public Codificacao {
    public:
        Binaria(std::string mensagem);
        Binaria() = default;
        ~Binaria() = default;

        void codificar() override;
        std::string decodificar() override;
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
        std::string decodificar() override;
    };

    /* Classe que deriva a classe abstrata 'Codificacao' e implementa
     * métodos virtuais seguindo o padrão da codificação bipolar (AMI). */
    class Bipolar : public Codificacao {
    public:
        Bipolar(std::string mensagem);
        Bipolar() = default;
        ~Bipolar() = default;

        void codificar() override;
        std::string decodificar() override;
    };

}

namespace meio_comunicacao {
    /* Função que transmite trem de bits da camada física transmissora 
     * para a camada física receptora. */
    void transmitir(bit trem_de_bits[]);
}

#endif // __CAMADA_FISICA_HPP
