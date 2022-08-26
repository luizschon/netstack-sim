#ifndef __CAMADA_FISICA_HPP
#define __CAMADA_FISICA_HPP

#include <string>
#include <vector>
#include "Common.hpp"

namespace camada_fis {

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
        Modulo(tipos_codificacao tipo); // Valores possíveis: COD_BINARIA, COD_MANCHESTER, COD_BIPOLAR
        Modulo(Codificacao &codigo);
        Modulo() = default;
        ~Modulo() = default;

        // Setters para codificação e sinal
        void setCodigo(tipos_codificacao tipo); // Valores possíveis: COD_BINARIA, COD_MANCHESTER, COD_BIPOLAR
        void setCodigo(Codificacao &codigo);
        void setSinal(std::vector<volt> &sinal);

        // Getter para signal
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
        Transmissor(tipos_codificacao tipo);
        Transmissor(Codificacao &codigo);
        Transmissor() = default;
        ~Transmissor() = default;

        void geraSinal();
        void geraSinal(const std::string &mensagem);
    };

    /* Classe derivada de Modulo que implementa funcionalidades
     * específicas do receptor da camada física. */
    class Receptor : public Modulo {
    public:
        Receptor(tipos_codificacao tipo);
        Receptor(Codificacao &codigo);
        Receptor() = default;
        ~Receptor() = default;

        std::string interpretaSinal();
    };

    /* Classe que implementa meio de comunicação para transmitir sinal
     * codificado entre Transmissor e Receptor da camada física.
     * Armazena ponteiros para Transmissor e Receptor.*/
    class MeioComunicacao {
    public: 
        MeioComunicacao(Transmissor &transmissor, Receptor &receptor);
        MeioComunicacao() = default;
        ~MeioComunicacao() = default;

        /* Função que simula trasmissão do sinal entre transmissor e
         * receptor. */
        void transmitir();

        // Setters de transmissor e receptor
        void setTransmissor(Transmissor &transmissor);
        void setReceptor(Receptor &receptor);

    protected:
        Transmissor *transmissor = nullptr;
        Receptor *receptor = nullptr;
    };

}

#endif // __CAMADA_FISICA_HPP
