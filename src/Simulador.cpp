#include <iostream>
#include <string>
#include "CamadaFisica.hpp"
#include "Common.hpp"

using namespace camada_fis;

int main(int argc, char **argv) {
    Transmissor *trans = new Transmissor();
    Receptor *recep = new Receptor();
    MeioComunicacao *meio = new MeioComunicacao(trans, recep);
    std::string res;

    meio->setCodigo(COD_BINARIA);
    trans->geraSinal("Hello from the other side [BINARIO]\n");
    meio->transmitir();
    res = recep->interpretaSinal();
    std::cout << res;

    meio->setCodigo(COD_MANCHESTER);
    trans->geraSinal("Hello from the other side [MANCHESTER]\n");
    meio->transmitir();
    res = recep->interpretaSinal();
    std::cout << res;

    meio->setCodigo(COD_BIPOLAR);
    trans->geraSinal("Hello from the other side [BIPOLAR]\n");
    meio->transmitir();
    res = recep->interpretaSinal();
    std::cout << res;

    delete trans;
    delete recep;

    return 0;
} // fim da função main
