#ifndef __GUI_HPP
#define __GUI_HPP

#include "Common.hpp"
#include <SDL.h>

namespace gui {

    /* Struct que armazena variáveis importantes para criar 
     * janela e contexto gráfico da interface do simulador. */
    struct WindowInfo {
        SDL_Window *window; 
        SDL_GLContext gl_context;
    };
  
    WindowInfo * init();
    void mainLoop(WindowInfo *window_info);
    void geraPlot(std::string msg, tipos_enquadramento tipo_enq, tipos_codificacao tipo_cod);
    void shutdown(WindowInfo *window_info);

}

#endif // __GUI_HPP

