#ifndef __GUI_HPP
#define __GUI_HPP

#include <SDL.h>

namespace gui {

    /* Struct que armazena variáveis importantes para criar 
     * janela e contexto gráfico da interface. */
    struct WindowInfo {
        SDL_Window *window; 
        SDL_GLContext gl_context;
    };
  
    WindowInfo * init();
    void mainLoop(WindowInfo *window_info);
    void shutdown(WindowInfo *window_info);

}

#endif // __GUI_HPP

