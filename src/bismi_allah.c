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

#define TASK_WIDGET_WIDTH 150
#define TASK_WIDGET_HEIGHT 100

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

    task_tree_tlist_file_load(&tlist, ".data");

    int running = 1;
    struct task_t *task_to_add_child_to = NULL;
    struct task_t *task_to_add_parent_to = NULL;
    while(running)
    {
        SDL_Event event;
        nk_input_begin(nk_ctx);
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT: running = 0; break;
            }
            nk_sdl_handle_event(&event);

        }
        nk_input_end(nk_ctx);

        //handle input
        //incha2Allah handle node connections
        if(nk_input_is_mouse_down(&nk_ctx->input, NK_BUTTON_LEFT))
        {
            int selected_a_node = 0;
            for(uint32_t i = 0; i < tlist.size; i++)
            {
                struct task_t *task = tlist.data[i];
                int node_x = nk_ctx->input.mouse.pos.x - (task->pos_x + TASK_WIDGET_WIDTH/2);
                int node_y = nk_ctx->input.mouse.pos.y - task->pos_y + 10;
                //clicked parents' node
                if(0 < node_x && node_x < 10 && 0 < node_y && node_y < 10)
                {
                    task_to_add_parent_to = task;
                    selected_a_node = 1;
                    break;
                }
                //clicked childrens' node
                node_y -= 10 + TASK_WIDGET_HEIGHT;
                if(0 < node_x && node_x < 10 && 0 < node_y && node_y < 10)
                {
                    task_to_add_child_to = task;
                    selected_a_node = 1;
                    break;
                }
            }
            if(!selected_a_node)
            {
                task_to_add_child_to = NULL;
                task_to_add_parent_to = NULL;
            }
        }

        //conect parent and child if there both are not NULL
        if(NULL != task_to_add_parent_to && NULL != task_to_add_child_to)
        {
            task_tree_tlist_task_children_id_list_add_id(&tlist, task_to_add_child_to->id, task_to_add_parent_to->id);
            task_to_add_parent_to = NULL;
            task_to_add_child_to = NULL;
        }

        if(nk_begin(nk_ctx, "la ilaha illa Allah", nk_rect(50, 50, 230, 250), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
        {
            static char task_name_buffer[sizeof(tlist.data[0]->name)] = {'\0'};
            nk_layout_row_dynamic(nk_ctx, 30, 1);
            nk_edit_string_zero_terminated(nk_ctx, NK_EDIT_SIMPLE, task_name_buffer, sizeof(tlist.data[0]->name), nk_filter_default);
            
            nk_layout_row_dynamic(nk_ctx, 30, 1);
            if(nk_button_label(nk_ctx, "la ilaha illa Allah") && '\0' != task_name_buffer[0])
            {
                task_tree_tlist_add_task(&tlist, task_tree_task_new(task_name_buffer));
                task_name_buffer[0]='\0';
            }
        }nk_end(nk_ctx);

        //show all widgets by the will of Allah
        for(int i = 0; i < tlist.size; i++)
        {
            struct task_t *task = tlist.data[i];
            static char window_name_buffer[10] = {'\0'};
            window_name_buffer[0] = '\0';
            snprintf(window_name_buffer, sizeof(window_name_buffer), "task %d", task->id);
            if(nk_begin(nk_ctx, window_name_buffer, nk_rect((float)task->pos_x, (float)task->pos_y, TASK_WIDGET_WIDTH, TASK_WIDGET_HEIGHT), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_TITLE))
            {
                nk_layout_row_dynamic(nk_ctx, 30, 1);
                nk_edit_string_zero_terminated(nk_ctx, NK_EDIT_SIMPLE, task->name, sizeof(task->name), nk_filter_default);
                //progress
                nk_layout_row_dynamic(nk_ctx, 15, 1);
                int progress = 0;
                progress = task->progress;
                nk_property_int(nk_ctx, "progress", 0, &progress, 100, 1, 5);
                if(progress != task->progress)
                {
                    task_tree_tlist_task_set_progress(&tlist, task->id, progress);
                }

                //add child

                //update the task's pos_x and pos_y
                struct nk_rect rect = nk_window_get_bounds(nk_ctx);
                task->pos_x = (uint16_t)rect.x;
                task->pos_y = (uint16_t)rect.y;
            }nk_end(nk_ctx);

        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //draw lines
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for(int i = 0; i < tlist.size; i++)
        {
            struct task_t *task = tlist.data[i];
            for(uint32_t i = 0; i < task->children_id_list_size; i++)
            {
                SDL_RenderDrawLine(renderer, task->pos_x + TASK_WIDGET_WIDTH / 2 + 5, task->pos_y + TASK_WIDGET_HEIGHT + 5, tlist.data[task->children_id_list[i]]->pos_x + TASK_WIDGET_WIDTH / 2 + 5, tlist.data[task->children_id_list[i]]->pos_y - 5);
            }
        }

        if(NULL != task_to_add_parent_to)
        {
            SDL_RenderDrawLine(renderer, task_to_add_parent_to->pos_x + TASK_WIDGET_WIDTH / 2 - 5, task_to_add_parent_to->pos_y + 5, nk_ctx->input.mouse.pos.x + 5, nk_ctx->input.mouse.pos.y - 5);
        }
        if(NULL != task_to_add_child_to)
        {
            SDL_RenderDrawLine(renderer, task_to_add_child_to->pos_x + TASK_WIDGET_WIDTH / 2 - 5, task_to_add_child_to->pos_y + TASK_WIDGET_HEIGHT + 5, nk_ctx->input.mouse.pos.x + 5, nk_ctx->input.mouse.pos.y - 5);
        }

        nk_sdl_render(NK_ANTI_ALIASING_ON);

        //draw nodes
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        for(int i = 0; i < tlist.size; i++)
        {
            struct task_t *task = tlist.data[i];
            SDL_Rect rect = {.w=10, .h=10};
            /*
            rect.x = task->pos_x + TASK_WIDGET_WIDTH / 2;
            rect.y = task->pos_y - 10;
            */
            rect.x = task->pos_x + TASK_WIDGET_WIDTH/2;
            rect.y = task->pos_y - 10;
            SDL_RenderFillRect(renderer, &rect);
            rect.y += TASK_WIDGET_HEIGHT + 10;
            SDL_RenderFillRect(renderer, &rect);
        }
        SDL_RenderPresent(renderer);
    }

    task_tree_tlist_file_save(&tlist, ".data");
    nk_sdl_shutdown();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

