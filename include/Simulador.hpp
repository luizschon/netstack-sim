#ifndef __SIMULADOR_HPP
#define __SIMULADOR_HPP

#include "CamadaAplicacao.hpp"
#include "CamadaEnlace.hpp"
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
        ~Pilha();

        void simula(const std::string &msg, tipos_enquadramento tipo_enq, tipos_codificacao tipo_cod);
        
        // Getters para atributos da simulação
        std::string getOutput();
        std::string getInput();
        std::vector<bit> getQuadroInput();
        std::vector<bit> getQuadroOutput();
        std::vector<bit> getTremDeBitsInput();
        std::vector<bit> getTremDeBitsOutput();
        std::vector<volt> getSinalInput();
        std::vector<volt> getSinalOutput();

    private:
        void setEnquadramento(tipos_enquadramento tipo);
        void setCodigo(tipos_codificacao tipo);
        void enviaMensagem();
        void recebeMensagem();

        // Modulos que compões a pilha de comunicação sendo implementada
        aplicacao::Transmissor *trans_aplicacao = nullptr;
        aplicacao::Receptor *recep_aplicacao = nullptr;
        enlace::Transmissor *trans_enlace = nullptr;
        enlace::Receptor *recep_enlace = nullptr;
        fisica::Transmissor *trans_fisico = nullptr;
        fisica::Receptor *recep_fisico = nullptr;
        fisica::MeioComunicacao *meio = nullptr;

        // String de input e output
        std::string input, output;

        // Quadros e sinais gerados durante a simulação
        std::vector<bit> quadro_input, quadro_output;
        std::vector<bit> bits_input, bits_output;
        std::vector<volt> sinal_input, sinal_output;
    };

}

#endif // __SIMULADOR_HPP
