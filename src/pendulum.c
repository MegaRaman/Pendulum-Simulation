#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <math.h>

#include "pendulum.h"
#include "pendulum_conf.h"


/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, __attribute__((unused)) int argc,
										__attribute__((unused)) char *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
	simulation_t *app = SDL_malloc(sizeof(simulation_t));

	app->p.acc_theta_ddot = 0;
	app->p.vel_theta_dot = 0;
	app->p.dev_theta = START_ANGLE;

	app->p.pos_x = TRAJ_CENTER_X + l_ROD_LEN_PIX * sin(app->p.dev_theta);
	app->p.pos_y = TRAJ_CENTER_Y + l_ROD_LEN_PIX * cos(app->p.dev_theta);

    if (!SDL_CreateWindowAndRenderer("pendulum", WINDOW_WIDTH, WINDOW_HEIGHT,
								SDL_WINDOW_RESIZABLE, &app->window, &app->renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(app->renderer, WINDOW_WIDTH, WINDOW_HEIGHT,
											SDL_LOGICAL_PRESENTATION_LETTERBOX);
	*appstate = (void*)app;

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(__attribute__((unused)) void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
	simulation_t *app = (simulation_t*)appstate;
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* new color, full alpha. */

    /* clear the window to the draw color. */
    SDL_RenderClear(app->renderer);

	pendulum_step(app);
	draw_rod(app);
	draw_ball(app);

	SDL_Delay(SIM_PERIOD_MS);

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(app->renderer);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, __attribute__((unused)) SDL_AppResult result)
{
	SDL_free(appstate);
	SDL_Quit();
    /* SDL will clean up the window/renderer for us. */
}

