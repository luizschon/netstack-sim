#include <iostream>
#include <string>
#include "../include/CamadaFisica.hpp"
#include "../include/Common.hpp"

using namespace camada_fis;

int main(int argc, char **argv) {
    tipos_codificacao tipo = COD_BINARIA;

    Transmissor *trans = new Transmissor(tipo);
    Receptor *recep = new Receptor(tipo);
    MeioComunicacao *meio = new MeioComunicacao(*trans, *recep);

    trans->geraSinal("Hello from the other side\n");

    meio->transmitir();

    std::string res = recep->interpretaSinal();
    std::cout << res;

    delete trans;
    delete recep;
    delete meio;

    return 0;
} // fim da função main
