#ifndef __CAMADA_FISICA_HPP
#define __CAMADA_FISICA_HPP

/* Enumerador para tornar a seleção do tipo de codificação
 * mais legível no código. */
enum {
    COD_BINARIA, COD_MANCHESTER, COD_BIPOLAR
};

namespace camada_fis {

    /* Classe abstrata para representar uma codificação genérica
     * da camada física da comunicação. */
    class Codificacao {
    public:
        virtual ~Codificacao() {};
        virtual void transmitir() = 0;
        virtual void decodificar() = 0;
    };

    /* Classe que deriva a classe abstrata 'Codificacao' e implementa
     * métodos virtuais seguindo o padrão da codificação binária (NRZ). */
    class Binaria : public Codificacao {
    public:
        Binaria() {};
        ~Binaria() {};

        void transmitir() override;
        void decodificar() override;
    };

    /* Classe que deriva a classe abstrata 'Codificacao' e implementa
     * métodos virtuais seguindo o padrão da codificação Manchester 
     * (NRZ XOR Clock). */
    class Manchester : public Codificacao {
    public:
        Manchester() {};
        ~Manchester() {};

        void transmitir() override;
        void decodificar() override;
    };

    /* Classe que deriva a classe abstrata 'Codificacao' e implementa
     * métodos virtuais seguindo o padrão da codificação bipolar (AMI). */
    class Bipolar : public Codificacao {
    public:
        Bipolar() {};
        ~Bipolar() {};

        void transmitir() override;
        void decodificar() override;
    };

}

#endif // __CAMADA_FISICA_HPP
