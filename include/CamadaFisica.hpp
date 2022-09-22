#ifndef __CAMADA_FISICA_HPP
#define __CAMADA_FISICA_HPP

#include "Common.hpp"

namespace fisica {

    /* Classe abstrata para representar uma codificação genérica
     * da camada física da comunicação. */ 
    class Codificacao {
    public:
        Codificacao() = default; 
        virtual ~Codificacao() = default;

        // Assinatura dos métodos virtuais puros
        virtual std::vector<volt> codificar(std::vector<bit> &quadro) = 0;
        virtual std::vector<bit> decodificar(std::vector<volt> &sinal) = 0;
    };

    /* Classe que deriva a classe abstrata 'Codificacao' e implementa
     * métodos virtuais seguindo o padrão da codificação binária (NRZ). */
    class Binaria : public Codificacao {
    public:
        Binaria() = default;
        ~Binaria() = default;

        std::vector<volt> codificar(std::vector<bit> &quadro) override;
        std::vector<bit> decodificar(std::vector<volt> &sinal) override;
    };

    /* Classe que deriva a classe abstrata 'Codificacao' e implementa
     * métodos virtuais seguindo o padrão da codificação Manchester 
     * (NRZ XOR Clock). */
    class Manchester : public Codificacao {
    public:
        Manchester() = default;
        ~Manchester() = default;

        std::vector<volt> codificar(std::vector<bit> &quadro) override;
        std::vector<bit> decodificar(std::vector<volt> &sinal) override;
    };

    /* Classe que deriva a classe abstrata 'Codificacao' e implementa
     * métodos virtuais seguindo o padrão da codificação bipolar (AMI). */
    class Bipolar : public Codificacao {
    public:
        Bipolar() = default;
        ~Bipolar() = default;

        std::vector<volt> codificar(std::vector<bit> &quadro) override;
        std::vector<bit> decodificar(std::vector<volt> &sinal) override;
    };

    /* Classe base que implementa funcionalidades compartilhadas
     * entre tranmissor e receptor do módulo da camada física em si 
     * Armazena informações como o quadro formado e a codificação
     * sendo usada.
     *
     * Esta é a classe usada pelo meio de comunicação para transferir
     * as informações contidas no quadro. */
    class Modulo {
    public:
        Modulo() = default;
        ~Modulo();

        // Setters para codificação e sinal
        void setCodigo(tipos_codificacao tipo);
        void setQuadro(std::vector<bit> &quadro);
        void setSinal(std::vector<volt> &sinal);

        // Getters para quadro e sinal
        std::vector<bit> getQuadro();
        std::vector<volt> getSinal();

    protected:
        std::vector<bit> quadro;       // Quadro composto de bits (valor 0 ou 1)
        std::vector<volt> sinal;       // Sinal transmitido entre transmissor e receptor
        Codificacao *codigo = nullptr; // Codificação usada no módulo da camada física
    };

    /* Classe derivada de Modulo que implementa funcionalidades
     * específicas do transmissor da camada física. */
    class Transmissor : public Modulo {
    public:
        Transmissor() = default;
        ~Transmissor() = default;

        void geraSinal();
    };

    /* Classe derivada de Modulo que implementa funcionalidades
     * específicas do receptor da camada física. */
    class Receptor : public Modulo {
    public:
        Receptor() = default;
        ~Receptor() = default;

        void geraQuadro();
    };

    /* Classe que implementa interface para transmissão de sinal
     * de um transmissor para um receptor */
    class MeioComunicacao {
    public:
        MeioComunicacao() = default;        
        ~MeioComunicacao() = default;        

        void setPorcentagemErro(int porcentagem);
        void transmitir(Transmissor *trans, Receptor *recep);

    private:
        int porcentagem_de_erro; // Porcentagem de ocorrer um erro na comunicação
    };

}

#endif // __CAMADA_FISICA_HPP
