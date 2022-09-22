#ifndef __CAMADA_ENLACE_HPP
#define __CAMADA_ENLACE_HPP

#include "CamadaFisica.hpp"
#include "Common.hpp"

namespace enlace {

    /* Classe abstrata para representar um enquadramento genérico
     * da camada de enlace. */ 
    class Enquadramento {
    public:
        Enquadramento() = default; 
        virtual ~Enquadramento() = default;

        // Assinatura dos métodos virtuais puros
        virtual std::vector<bit> enquadrar(std::vector<bit> &trem_de_bits) = 0;
        virtual std::vector<bit> desenquadrar(std::vector<bit> &quadro) = 0;
    };

    class ContagemDeCaracteres : public Enquadramento {
    public:
        ContagemDeCaracteres() = default;
        ~ContagemDeCaracteres() = default;

        std::vector<bit> enquadrar(std::vector<bit> &trem_de_bits) override;
        std::vector<bit> desenquadrar(std::vector<bit> &quadro) override;
    };

    class InsercaoDeBytes : public Enquadramento {
    public:
        InsercaoDeBytes() = default;
        ~InsercaoDeBytes() = default;

        std::vector<bit> enquadrar(std::vector<bit> &trem_de_bits) override;
        std::vector<bit> desenquadrar(std::vector<bit> &quadro) override;
    };

    class ControleDeErro {
    public:
        ControleDeErro() = default; 
        virtual ~ControleDeErro() = default;

        // Assinatura dos métodos virtuais puros
        virtual std::vector<bit> codificar(std::vector<bit> &trem_de_bits) = 0;
        virtual bool detectar(std::vector<bit> &quadro) = 0;
        virtual std::vector<bit> decodificar(std::vector<bit> &quadro) = 0;
    };

    class BitDeParidadePar : public ControleDeErro {
    public:
        BitDeParidadePar() = default;
        ~BitDeParidadePar() = default;

        std::vector<bit> codificar(std::vector<bit> &quadro) override;
        bool detectar(std::vector<bit> &quadro) override;
        std::vector<bit> decodificar(std::vector<bit> &quadro) override;
    };

    class CRC : public ControleDeErro {
    public:
        CRC() = default;
        ~CRC() = default;

        std::vector<bit> codificar(std::vector<bit> &quadro) override;
        bool detectar(std::vector<bit> &quadro) override;
        std::vector<bit> decodificar(std::vector<bit> &quadro) override;
    };

    class Hamming : public ControleDeErro {
    public:
        Hamming() = default;
        ~Hamming() = default;

        std::vector<bit> codificar(std::vector<bit> &quadro) override;
        bool detectar(std::vector<bit> &quadro) override;
        std::vector<bit> corrigir(std::vector<bit> &quadro);
        std::vector<bit> decodificar(std::vector<bit> &quadro) override;
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
        void setControleDeErro(tipos_controle_erro tipo);
        void setQuadroCodificado(std::vector<bit> &quadro_codificado);
        void setQuadro(std::vector<bit> &quadro);
        void setTremDeBits(std::vector<bit> &trem_de_bits);

        // Getters para quadro e trem de bits
        std::vector<bit> getQuadroCodificado();
        std::vector<bit> getQuadro();
        std::vector<bit> getTremDeBits();

    protected:
        std::vector<bit> quadro;                 // Quadro composto de bits (valor 0 ou 1)
        std::vector<bit> quadro_codificado;      // Quadro codificado usando controle de erro
        std::vector<bit> trem_de_bits;           // Trem de bits recebido/transmitido para a camada de aplicação
        Enquadramento *enquadramento = nullptr;  // Enquadramento usado no módulo camada de enlace
        ControleDeErro *controle_erro = nullptr; // Controle de erro usado no módulo camada de enlace
    };

    /* Classe derivada de Modulo que implementa funcionalidades
     * específicas do transmissor da camada de enlace. */
    class Transmissor : public Modulo {
    public:
        Transmissor() = default;
        ~Transmissor() = default;

        void geraQuadro();
        void geraQuadroCodificado();
        void transmitir(fisica::Transmissor *transmissor);
    };

    /* Classe derivada de Modulo que implementa funcionalidades
     * específicas do receptor da camada enlace. */
    class Receptor : public Modulo {
    public:
        Receptor() = default;
        ~Receptor() = default;
        
        void corrigeQuadro();
        void geraQuadro();
        void geraTremDeBits();
        void receber(fisica::Receptor *receptor);
    };

}

#endif // __CAMADA_ENLACE_HPP
