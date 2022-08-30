#ifndef __CAMADA_APLICACAO_HPP
#define __CAMADA_APLICACAO_HPP

#include "Common.hpp"
#include "CamadaFisica.hpp"

namespace camada_apl {

    /* Classe base que implementa funcionalidades compartilhadas
     * entre tranmissor e receptor do módulo da camada de aplicação.
     *
     * Esta é a classe usada para transmitir ou receber da camada
     * física os bits que compõem uma mensagem. */
    class Modulo {
    public:
        // Setters e getters para variáveis
        void setMensagem(const std::string mensagem);
        std::string getMensagem();

    private:
        std::string mensagem;
    };

    /* Classe derivada de Modulo que implementa funcionalidades
     * específicas do transmissor da camada de aplicação. */
    class Transmissor : public Modulo {
    public:
        void transmitir(camada_fis::Transmissor *transmissor);
    };

    /* Classe derivada de Modulo que implementa funcionalidades
     * específicas do receptor da camada de aplicação. */
    class Receptor : public Modulo {
    public:
        void receber(camada_fis::Receptor *receptor);
    };

}

#endif // __CAMADA_APLICACAO_HPP
