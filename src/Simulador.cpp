#include <iostream>
#include <string>
#include "../include/CamadaFisica.hpp"
#include "../include/Common.hpp"

using namespace camada_fis;

int main(int argc, char **argv) {
    tipos_codificacao tipo = COD_BINARIA;

    Transmissor *trans = new Transmissor(tipo);
    Receptor *recep = new Receptor(tipo);
    std::string res;

    trans->geraSinal("Hello from the other side [BINARIO]\n");
    trans->transmitir(*recep);
    res = recep->interpretaSinal();
    std::cout << res;

    trans->setCodigo(COD_MANCHESTER);
    recep->setCodigo(COD_MANCHESTER);
    trans->geraSinal("Hello from the other side [MANCHESTER]\n");
    trans->transmitir(*recep);
    res = recep->interpretaSinal();
    std::cout << res;

    trans->setCodigo(COD_BIPOLAR);
    recep->setCodigo(COD_BIPOLAR);
    trans->geraSinal("Hello from the other side [BIPOLAR]\n");
    trans->transmitir(*recep);
    res = recep->interpretaSinal();
    std::cout << res;

    delete trans;
    delete recep;

    return 0;
} // fim da função main
