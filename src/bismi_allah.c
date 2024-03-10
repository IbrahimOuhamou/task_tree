//بسم الله الرحمن الرحيم

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

#include <SDL2/SDL.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_RENDERER_IMPLEMENTATION
#include "../submodules/Nuklear/nuklear.h"
#include "../submodules/Nuklear/demo/sdl_renderer/nuklear_sdl_renderer.h"

#include "../submodules/task_tree_lib/include/task_t.h"
#include "../submodules/task_tree_lib/include/tlist.h"

int main()
{
    printf("in the name of Allah\n");
    struct tlist_t tlist;
    task_tree_tlist_init(&tlist);

    //struct nk_colorf background_color;
    struct nk_colorf font_color;
    float font_scale = 1;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("la ilaha illa Allah", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800,SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
    if(NULL == window)
    {
        SDL_Log("error SDL_CreateWindow() %s", SDL_GetError());
        exit(-1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if(NULL == renderer)
    {
        SDL_Log("error SDL_CreateRenderer() %s", SDL_GetError());
        exit(-1);
    }

    /* scale the renderer output for High-DPI displays */
    {
        int render_w, render_h;
        int window_w, window_h;
        float scale_x, scale_y;
        SDL_GetRendererOutputSize(renderer, &render_w, &render_h);
        SDL_GetWindowSize(window, &window_w, &window_h);
        scale_x = (float)(render_w) / (float)(window_w);
        scale_y = (float)(render_h) / (float)(window_h);
        SDL_RenderSetScale(renderer, scale_x, scale_y);
        font_scale = scale_y;
    }

    struct nk_context *nk_ctx = nk_sdl_init(window, renderer);
    {
        struct nk_font_atlas *atlas;
        struct nk_font_config config = nk_font_config(0);
        struct nk_font *font;

        nk_sdl_font_stash_begin(&atlas);
        font = nk_font_atlas_add_default(atlas, 13, &config);

        nk_sdl_font_stash_end();

        /*nk_style_load_all_cursors(nk_ctx, atlas->cursors);*/
        nk_style_set_font(nk_ctx, &font->handle);

        /* this hack makes the font appear to be scaled down to the desired
         * size and is only necessary when font_scale > 1 */
        font->handle.height /= font_scale;
        /*nk_style_load_all_cursors(nk_ctx, atlas->cursors);*/
        nk_style_set_font(nk_ctx, &font->handle);
    }

    char *task_name_buffer = (char*)malloc(sizeof(tlist.data[0]->name));
    task_name_buffer[0]='\0';
    int task_name_buffer_length = 0;
    int control_panel = 1;
    int running = 1;
    while(running)
    {
        SDL_Event event;
        nk_input_begin(nk_ctx);
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT: running = 0; break;
                case SDL_KEYDOWN:
                    if(SDL_SCANCODE_P == event.key.keysym.scancode) control_panel = !control_panel;
                    break;
            }
            nk_sdl_handle_event(&event);

        }
        nk_input_end(nk_ctx);

        if(control_panel)
        {
            if(nk_begin(nk_ctx, "la ilaha illa Allah", nk_rect(50, 50, 230, 250), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
            {
                nk_layout_row_dynamic(nk_ctx, 30, 1);
                nk_edit_string(nk_ctx, NK_EDIT_SIMPLE, task_name_buffer, &task_name_buffer_length, sizeof(tlist.data[0]->name), nk_filter_default);
                
                nk_layout_row_dynamic(nk_ctx, 30, 1);
                if(nk_button_label(nk_ctx, "la ilaha illa Allah") && '\0' != task_name_buffer[0] && sizeof(tlist.data[0]->id) == task_tree_tlist_search_name(&tlist, task_name_buffer))
                {
                    printf("la ilaha illa Allah\n");
                    task_tree_tlist_add_task(&tlist, task_tree_task_new(task_name_buffer));
                    task_name_buffer = (char*)malloc(sizeof(tlist.data[0]->name));
                    task_name_buffer[0]='\0';
                    task_name_buffer_length = 0;
                }
            }nk_end(nk_ctx);
        }

        //show all widgets by the will of Allah
        for(int i = 0; i < tlist.size; i++)
        {
            if(nk_begin(nk_ctx, tlist.data[i]->name, nk_rect(100, 100, 230, 250), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
            {
                nk_layout_row_dynamic(nk_ctx, 30, 1);
                nk_label(nk_ctx, tlist.data[i]->name, NK_TEXT_LEFT);
            }nk_end(nk_ctx);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        nk_sdl_render(NK_ANTI_ALIASING_ON);

        SDL_RenderPresent(renderer);
    }

    nk_sdl_shutdown();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

