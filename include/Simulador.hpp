#ifndef __SIMULADOR_HPP
#define __SIMULADOR_HPP

#include "CamadaAplicacao.hpp"
#include "CamadaFisica.hpp"

namespace sim {
    
    /* Classe que implementa pilha de protocolos de comunicação sendo
     * usadas na simulação.
     *
     * Responsável por simular o processo de comunicação e armazenar
     * os resultados em atributos privados, acessáveis pelos getters
     * de cada atributo. */
    class Pilha {
    public:
        Pilha();

        void simula(const std::string &msg, tipos_codificacao tipo);
        
        // Getters para atributos da simulação
        std::string getOutput();
        std::string getInput();
        std::vector<bit> getQuadroInput();
        std::vector<bit> getQuadroOutput();
        std::vector<volt> getSinalInput();
        std::vector<volt> getSinalOutput();

    private:
        void setCodigo(tipos_codificacao tipo);
        void enviaMensagem();
        void recebeMensagem();

        // Modulos que compões a pilha de comunicação sendo implementada
        camada_apl::Transmissor *trans_aplicacao = nullptr;
        camada_apl::Receptor *recep_aplicacao = nullptr;
        camada_fis::Transmissor *trans_fisico = nullptr;
        camada_fis::Receptor *recep_fisico = nullptr;
        camada_fis::MeioComunicacao *meio = nullptr;

        // String de input e output
        std::string input, output;

        std::vector<bit> quadro_input, quadro_output;
        std::vector<volt> sinal_input, sinal_output;
    };

}

#endif // __SIMULADOR_HPP
