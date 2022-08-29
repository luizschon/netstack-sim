#include <cstring>
#include <string>
#include <iostream>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <implot.h>
#include <SDL_opengl.h>

#include "Common.hpp"
#include "Gui.hpp"

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

/* Main loop da aplicação gráfica do simulador. */
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
            
            // Mostra plot do quadro e sinal
            if (show_plot) {
                if (ImPlot::BeginPlot("My Plot")) {
                    ImPlot::EndPlot();
                }
            }

            // Mostra mensagem de erro caso a mensagem de input seja vazia
            if (erro) {
                ImGui::SameLine();
                ImGui::Text("Erro: %s", msg_erro.c_str());               // Display some text (you can use a format strings too)
            }
            ImGui::End();
        }

        // Renderiza janela
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window_info->window);
    }
}

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
