#include <iostream>
#include "CamadaFisica.hpp"

int main(int argc, char **argv) {
    std::cout << "Hello from main\n";

    camada_fis::Codificacao *cod; // Instância de Codificacao

    int tipo = COD_BINARIA; 

    switch (tipo) {
        case COD_BINARIA:    // Código Binário
            cod = new camada_fis::Binaria();
            break;
        case COD_MANCHESTER: // Código Manchester
            cod = new camada_fis::Manchester();
            break;
        case COD_BIPOLAR:    // Código Polar
            cod = new camada_fis::Bipolar();
            break;
        default:
            break;
    }
    delete cod;

    return 0;
} // fim da função main
