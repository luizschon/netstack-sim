#include <iostream>
#include "Simulador.hpp"
#include "Gui.hpp"

int main(int argc, char **argv) {
    // sim::Pilha *pilha = new sim::Pilha();
    // std::vector<bit> quadro;
    // std::vector<volt> sinal;
    //
    // pilha->simula("Hello from binaria\n", COD_BINARIA);
    // std::cout << "Input: " << pilha->getInput();
    // std::cout << "Quadro input:\n";
    // quadro = pilha->getQuadroInput();
    // utils::print_bits(quadro);
    // std::cout << "Output: " << pilha->getOutput();
    // std::cout << "Quadro output:\n";
    // quadro = pilha->getQuadroOutput();
    // utils::print_bits(quadro);
    //
    // pilha->simula("Hello from manchester\n", COD_MANCHESTER);
    // std::cout << "Input: " << pilha->getInput();
    // std::cout << "Quadro input:\n";
    // quadro = pilha->getQuadroInput();
    // utils::print_bits(quadro);
    // std::cout << "Output: " << pilha->getOutput();
    // std::cout << "Quadro output:\n";
    // quadro = pilha->getQuadroOutput();
    // utils::print_bits(quadro);
    //
    // pilha->simula("Hello from bipolar\n", COD_BIPOLAR);
    // std::cout << "Input: " << pilha->getInput();
    // std::cout << "Quadro input:\n";
    // quadro = pilha->getQuadroInput();
    // utils::print_bits(quadro);
    // std::cout << "Output: " << pilha->getOutput();
    // std::cout << "Quadro output:\n";
    // quadro = pilha->getQuadroOutput();
    // utils::print_bits(quadro);

    gui::WindowInfo *w_info = gui::init();
    if (w_info) {
        gui::mainLoop(w_info);
        gui::shutdown(w_info);
    }

    return 0;
} // fim da função main
