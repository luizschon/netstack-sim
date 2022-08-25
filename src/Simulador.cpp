#include <iostream>
#include <string>
#include "../include/CamadaFisica.hpp"
#include "../include/Common.hpp"

int main(int argc, char **argv) {
    camada_fis::Codificacao *cod; // Instância de Codificacao

    int tipo = COD_BINARIA; 
    std::string msg = "Hello from the other side\n";

    switch (tipo) {
        case COD_BINARIA:    // Código Binário
            cod = new camada_fis::Binaria(msg);
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

    std::cout << cod->decodificar();

    delete cod;

    return 0;
} // fim da função main
