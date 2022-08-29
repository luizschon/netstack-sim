#include <iostream>
#include "Simulador.hpp"
#include "Gui.hpp"

int main(int argc, char **argv) {
    gui::WindowInfo *w_info = gui::init();

    if (w_info) {
        gui::mainLoop(w_info);
        gui::shutdown(w_info);
    }

    return 0;
} // fim da função main
