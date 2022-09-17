#ifndef __CAMADA_ENLACE_HPP
#define __CAMADA_ENLACE_HPP

#include "CamadaFisica.hpp"
#include "Common.hpp"

namespace enlace {

    /* Classe abstrata para representar uma codificação genérica
     * da camada física da comunicação. */ 
    class Enquadramento {
    public:
        Enquadramento() = default; 
        virtual ~Enquadramento() = default;

        // Assinatura dos métodos virtuais puros
        virtual std::vector<bit> enquadrar(std::vector<bit> &trem_de_bits) = 0;
        virtual std::vector<bit> desenquadrar(std::vector<bit> &quadro) = 0;
    };

    /* Classe que deriva a classe abstrata 'Codificacao' e implementa
     * métodos virtuais seguindo o padrão da codificação binária (NRZ). */
    class ContagemDeCaracteres : public Enquadramento {
    public:
        ContagemDeCaracteres() = default;
        ~ContagemDeCaracteres() = default;

        std::vector<bit> enquadrar(std::vector<bit> &trem_de_bits) override;
        std::vector<bit> desenquadrar(std::vector<bit> &quadro) override;
    };

    /* Classe que deriva a classe abstrata 'Codificacao' e implementa
     * métodos virtuais seguindo o padrão da codificação Manchester 
     * (NRZ XOR Clock). */
    class InsercaoDeBytes : public Enquadramento {
    public:
        InsercaoDeBytes() = default;
        ~InsercaoDeBytes() = default;

        std::vector<bit> enquadrar(std::vector<bit> &trem_de_bits) override;
        std::vector<bit> desenquadrar(std::vector<bit> &quadro) override;
    };

    /* Classe base que implementa funcionalidades compartilhadas
     * entre tranmissor e receptor do módulo da camada de enclace 
     * em si. Armazena informações como o quadro formado e a codificação
     * sendo usada. */
    class Modulo {
    public:
        Modulo() = default;
        ~Modulo();

        // Setters 
        void setEnquadramento(tipos_enquadramento tipo);
        void setQuadro(std::vector<bit> &quadro);
        void setTremDeBits(std::vector<bit> &trem_de_bits);

        // Getters para quadro e trem de bits
        std::vector<bit> getQuadro();
        std::vector<bit> getTremDeBits();

    protected:
        std::vector<bit> quadro;                // Quadro composto de bits (valor 0 ou 1)
        std::vector<bit> trem_de_bits;          // Trem de bits recebido/transmitido para a camada de aplicação
        Enquadramento *enquadramento = nullptr; // Codificação usada no módulo da camada física
    };

    /* Classe derivada de Modulo que implementa funcionalidades
     * específicas do transmissor da camada de enlace. */
    class Transmissor : public Modulo {
    public:
        Transmissor() = default;
        ~Transmissor() = default;

        void geraQuadro();
        void transmitir(fisica::Transmissor *transmissor);
    };

    /* Classe derivada de Modulo que implementa funcionalidades
     * específicas do receptor da camada enlace. */
    class Receptor : public Modulo {
    public:
        Receptor() = default;
        ~Receptor() = default;
        
        void geraTremDeBits();
        void receber(fisica::Receptor *receptor);
    };

}

#endif // __CAMADA_ENLACE_HPP
