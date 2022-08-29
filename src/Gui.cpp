#include <string>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <implot.h>
#include <SDL_opengl.h>

#include "Gui.hpp"
#include "Simulador.hpp"

/* Função que inicializa janela e contexto gráfico do SDL e ImGui
 * para criar a GUI do simulador. */
gui::WindowInfo * gui::init() {
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return nullptr;
    }

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    // Cria janela com contexto gráfico
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    gui::WindowInfo *window_info = new gui::WindowInfo;

    window_info->window = SDL_CreateWindow("Simulador camada física - TR1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 500, window_flags);
    window_info->gl_context = SDL_GL_CreateContext(window_info->window);

    SDL_GL_MakeCurrent(window_info->window, window_info->gl_context);
    SDL_GL_SetSwapInterval(1); // Habilita VSync

    // Inicializa contexto do ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGui::StyleColorsDark();

    // Inicializa backend e plataforma gráfica
    ImGui_ImplSDL2_InitForOpenGL(window_info->window, window_info->gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return window_info;
}

/* Main loop da aplicação gráfica do simulador. Contém maior parte do
 * codigo para gerar elementos gráficos com que o usuário pode
 * interagir. */
void gui::mainLoop(gui::WindowInfo *window_info) {
    ImGuiWindowFlags imgui_window_flags = (ImGuiWindowFlags) (ImGuiWindowFlags_NoTitleBar
                                                            | ImGuiWindowFlags_NoResize);

    bool fim = false;
    while (!fim)
    {
        // Captura e lida com eventos da janela
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                fim = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window_info->window))
                fim = true;
        }

        // Inicia o frame do ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Assegura que a janela do ImGui cobre a janela do SDL por completo
        int width, height;
        SDL_GetWindowSize(window_info->window, &width, &height);
        ImGui::SetNextWindowSize(ImVec2(width, height)); 
        ImGui::SetNextWindowPos(ImVec2(0, 0));

        /* Mostra janela principal do programa, que processa mensagem e codificação
         * inseridos pelo usuário e mostra plot do quadro e sinais resultantes da
         * codificação das mensagens. */
        {
            static int codigo = COD_BINARIA;  // Inicializa código como Binário por padrão
            static char msg[256] = "";        // Mensagem recebida no input
            static std::string msg_erro = ""; // Mensagem de erro
            static bool show_plot = false;    // Booleano que controla visualização do plot
            static bool erro = false;         // Booleano que controla visualização da mensagem de erro

            // Inicia janela
            ImGui::Begin("Simulador camada física", 0, imgui_window_flags);
            
            ImGui::Text("Simulador de camada física da disciplina de Teleinformática e Redes 1 - UnB");
            ImGui::InputTextWithHint("Escreva sua mensagem", "Max 256 caracteres", msg, IM_ARRAYSIZE(msg));

            // Botões do tipo radio para selecionar codificação
            ImGui::RadioButton("Binária (NRZ)", &codigo, COD_BINARIA); ImGui::SameLine();
            ImGui::RadioButton("Manchester"   , &codigo, COD_MANCHESTER); ImGui::SameLine();
            ImGui::RadioButton("Bipolar (AMI)", &codigo, COD_BIPOLAR);
            
            // Inicia simulação ao pressionar botão
            if (ImGui::Button("Simular")) {
                if (strcmp(msg, "") != 0) {
                    show_plot = true;
                    erro = false;
                    msg_erro = "";
                } else {
                    show_plot = false;
                    erro = true;
                    msg_erro = "Mensagem vazia!";
                }
            }
            
            // Mostra plot do quadro e sinal caso exista uma mensagem
            if (show_plot && strcmp(msg, "") != 0) {
                gui::geraPlot(std::string(msg), (tipos_codificacao) codigo);
            }

            // Mostra mensagem de erro caso a mensagem de input seja vazia
            if (erro) {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Erro: %s", msg_erro.c_str());
            }
            ImGui::End();
        }

        // Renderização da janela
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window_info->window);
    }
}

/* Função que gera plots para quadros de entrada/saída e sinal
 * codificado a partir da simulação da pilha de protocolos 
 * simulada usando a mensagem e o tipo de codificação passados
 * como argumento. */
void gui::geraPlot(std::string msg, tipos_codificacao codigo) {
    // Inicializa pilha e simula usando valores recebidos como argumento
    sim::Pilha *pilha = new sim::Pilha;
    pilha->simula(msg, codigo);

    static int amostras = 100; // Número de amostras por valor dos vetores do quadro/sinal

    // Imprime mensagem recebida pela camada de aplicação receptora
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Mensagem recebida: %s", pilha->getOutput().c_str());

    /* Inicia plot do quadro composto pelos bits da mensagem. */
    if (ImPlot::BeginPlot("Quadro")) {
        auto quadro = pilha->getQuadroInput();
        
        // Calcula eixo X e Y para o plot em linha
        float * eixo_x = utils::geraEixoX(quadro, amostras);
        float * eixo_y = utils::geraEixoY(quadro, amostras);

        // Nomeia e estabelece limite ao eixos para facilitar legibilidade
        ImPlot::SetupAxes("bit","valor");
        ImPlot::SetupAxisLimits(ImAxis_X1, -1, quadro.size() + 1, ImGuiCond_Always);
        ImPlot::SetupAxisLimits(ImAxis_Y1, -1, 2);

        // Plot em linha dos eixos calculados para o quadro
        ImPlot::PlotLine("Quadro", eixo_x, eixo_y, quadro.size() * amostras);

        delete[] eixo_x;
        delete[] eixo_y;

        ImPlot::EndPlot();
    }

    /* Inicia plot do sinal gerado pela codificação do quadro. */
    if (ImPlot::BeginPlot("Sinal")) {
        auto sinal = pilha->getSinalInput();

        // Calcula eixo X e Y para o plot em linha
        float * eixo_x = utils::geraEixoX(sinal, amostras, codigo);
        float * eixo_y = utils::geraEixoY(sinal, amostras);

        // Nomeia os eixos para facilitar legibilidade
        ImPlot::SetupAxes("tempo","Volts");

        /* Caso a codificação seja Manchester, reduz o limite do eixo X pela metade, 
         * já que o sinal resultante tem o dobro de informação. */
        if (codigo == COD_MANCHESTER) {
            ImPlot::SetupAxisLimits(ImAxis_X1, -1, (float) sinal.size()/2 + 1, ImGuiCond_Always);
        } else {
            ImPlot::SetupAxisLimits(ImAxis_X1, -1, sinal.size() + 1, ImGuiCond_Always);
        }

        /* Caso a codificação seja bipolar, muda o limite do eixo Y para mostra
         * valores negativos. */ 
        if (codigo == COD_BIPOLAR) {
            ImPlot::SetupAxisLimits(ImAxis_Y1, -7, 7, ImGuiCond_Always);
        } else {
            ImPlot::SetupAxisLimits(ImAxis_Y1, -3, 8, ImGuiCond_Always);
        }

        // Plot em linha dos eixos calculados para o sinal
        ImPlot::PlotLine("Sinal", eixo_x, eixo_y, sinal.size() * amostras);

        delete[] eixo_x;
        delete[] eixo_y;

        ImPlot::EndPlot();
    }

    /* Inicia plot do quadro gerado pela decodificação do sinal. */
    if (ImPlot::BeginPlot("Quadro decodificado")) {
        auto quadro = pilha->getQuadroOutput();
        
        // Calcula eixo X e Y para o plot em linha
        float * eixo_x = utils::geraEixoX(quadro, amostras);
        float * eixo_y = utils::geraEixoY(quadro, amostras);

        // Nomeia e estabelece limite ao eixos para facilitar legibilidade
        ImPlot::SetupAxes("bit","valor");
        ImPlot::SetupAxisLimits(ImAxis_X1, -1, quadro.size() + 1, ImGuiCond_Always);
        ImPlot::SetupAxisLimits(ImAxis_Y1, -1, 2);
        
        // Plot em linha dos eixos calculados para o quadro
        ImPlot::PlotLine("Quadro decodificado", eixo_x, eixo_y, quadro.size() * amostras);

        delete[] eixo_x;
        delete[] eixo_y;

        ImPlot::EndPlot();
    }
    
    delete pilha;
}

/* Função responsável por destruir a janela e o contexto
 * gráfico criados na função gui::init. */
void gui::shutdown(gui::WindowInfo *window_info) {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(window_info->gl_context);
    SDL_DestroyWindow(window_info->window);
    SDL_Quit();

    delete window_info;
}
