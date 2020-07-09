/*
 * Zeynep Ülkü Kılıç
 * 
 * sdlView.c
 * some parts are taken from libsdl.org
 *  Created on: Nov 26, 2018
 *      Author: adaskin
 */



#include "SDL2/SDL.h"
#include <stdio.h>

/*these are given in model.c */
int addPoint(double, double);
extern int polygonDone;
extern int np;
extern int done;
extern double points[][2];
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event;
int curMouseX, curMouseY; /*current mouse position*/

/**
 * initializes  window and renderer
 * window size is (windowHeight x windowWidth)
 */
int initSDLWindow(int width, int height){
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		if (SDL_CreateWindowAndRenderer(width, height,
				0, &window, &renderer) == 0) {
			SDL_SetWindowTitle(window, "Area of Polygon in Medeniyet");
			done = 0;
		}

	}
	return done;
}

/**
 * destroys window and renderer
 */
int quitSDLAll(){
	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}

	SDL_Quit();

	return 0;
}



/**
 * checks for and handles mouse events
 */
int checkMouseEvents(){
	while (SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			done = SDL_TRUE; /*the game is over*/
			quitSDLAll();
		}
		else if(event.type == SDL_MOUSEMOTION){
			curMouseX = event.motion.x;
			curMouseY = event.motion.y;
			char str[50] = {'\0'};
			sprintf(str, "Mouse x: %d, y: %d", curMouseX, curMouseY);
			SDL_SetWindowTitle(window, str);
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN){
			/* handle mouse buttons */
			if(event.button.button ==  SDL_BUTTON_LEFT ) {
				addPoint(event.button.x,event.button.y);
			}
			else if(event.button.button ==  SDL_BUTTON_RIGHT){
				polygonDone = SDL_TRUE;
				SDL_Log("polygon: %d", polygonDone);
			}
		}
	}
	return done;
}

int showArea(double area){
	char str[100]={'\0'};  sprintf(str, "alan: %lf", area);
	SDL_Log("%.100s",str);
	const SDL_MessageBoxButtonData buttons[] = {
			/* .flags, .buttonid, .text */
			{SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "New" },
			{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Quit" },
	};

	const SDL_MessageBoxData messageboxdata = {
			SDL_MESSAGEBOX_INFORMATION, /* .flags */
			window, /* .window */
			"Girilen cokgenin alani", /* .title */
			str, /* .message */
			SDL_arraysize(buttons), /* .numbuttons */
			buttons, /* .buttons */
			NULL /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
		return 1;
	}
	if (buttonid == -1) {
		SDL_Log("no selection");
		done = SDL_TRUE;
	}
	else if (buttonid == 0){
		SDL_Log("%.30s", buttons[buttonid].text);
		polygonDone = SDL_FALSE;
	}
	else {
		SDL_Log("%.30s", buttons[buttonid].text);
		done = SDL_TRUE;
	}
	return 0;
}

/**
 * for a given (x, y) coordinates with points  and number of points np,
 * draws a polygon defined by points to the black screen and
 * mouse motion
 */
void drawPolygon(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); /*black*/
	SDL_RenderClear(renderer); /*black window*/

	SDL_SetRenderDrawColor(renderer, 255, 255, 255,SDL_ALPHA_OPAQUE);/*white*/
	for(int i = 0; i < np-1; i++){
		SDL_RenderDrawLine(renderer,
				points[i][0], points[i][1],
				points[i+1][0], points[i+1][1]);
	}
	/*last edge*/
	if(np > 2){
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(renderer,
				points[0][0],points[0][1],
				points[np-1][0], points[np-1][1]);
	}
	if(np > 0 && polygonDone == SDL_FALSE){
		/*mouse motion*/
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(renderer,
				points[np-1][0], points[np-1][1],
				curMouseX, curMouseY);
	}
	SDL_RenderPresent(renderer);
}

