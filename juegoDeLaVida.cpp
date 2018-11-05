/******************************************************************************
 *                Juego de la vida toroidal - ALGO1-TT 2018c2                 *
 *                                                                            *
 *****************************************************************************/

#include <SDL.h>

#include <cmath>
#include <cstdlib>

#include "solucion.h"
#include "es.h"
#include "maxiopt.h"

#define TITLE "[ALGO1-TT] TPI: Juego de la vida toroidal (densidad: %f)"
#define MAX_TITLE 256

typedef enum { STOP, PLAY, PLAY_ONCE, LOAD, SAVE, QUIT } status;

static int width;
static int height;
static bool redraw = true;
static toroide t;

static SDL_Renderer *renderer;

static toroide nuevoToroide(const int filas, const int columnas)
{
	return toroide(filas, vector<bool>(columnas));
}

static void limpiarToroide(toroide &t)
{
	int filas = t.size();
	int columnas = t[0].size();

	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			t[i][j] = false;
		}
	}
}

static toroide cargarVistaToroide(const string &nombreArchivo)
{
	bool cargaOk = false;
	t = cargarToroide(nombreArchivo, cargaOk);
	if (!cargaOk) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error cargando toroide -> %s\n", nombreArchivo.c_str());
		exit(2);
	} else
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Toroide cargado de -> %s\n", nombreArchivo.c_str());

	return t;
}

static void guardarVistaToroide(const string &nombreArchivo, toroide t)
{
	if (!escribirToroide(nombreArchivo, t))
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error guardando toroide -> %s\n", nombreArchivo.c_str());
	else
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Toroide guardado en -> %s\n", nombreArchivo.c_str());
}


static void dibujarToroide(toroide &t)
{
	// copio valores globales
	int w = width;
	int h = height;
	SDL_Renderer *r = renderer;

	int xlen = w / t[0].size();
	int ylen = h / t.size();

	// size de las celdas
	SDL_Rect rect;
	rect.w = xlen-2;
	rect.h = ylen-2;

	// resetear fondo
	SDL_SetRenderDrawColor(r, 0xF0, 0xF0, 0xF0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(r);

	// grid
	SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);

	for (int x = 0; x < w; x += xlen) {
		SDL_RenderDrawLine(r, x-1, 0, x-1, h);
		SDL_RenderDrawLine(r, x, 0, x, h);
		SDL_RenderDrawLine(r, x+1, 0, x+1, h);
	}
	for (int y = 0; y < h; y += ylen) {
		SDL_RenderDrawLine(r, 0, y-1, w, y-1);
		SDL_RenderDrawLine(r, 0, y, w, y);
		SDL_RenderDrawLine(r, 0, y+1, w, y+1);
	}

	// celdas
	SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
	for (unsigned int i = 0; i < t.size(); i++) {
		for (unsigned int j = 0; j < t[0].size(); j++) {
			if (t[i][j]) {
				rect.x = j*xlen+2;
				rect.y = i*ylen+2;
				SDL_RenderFillRect(r, &rect);
			}
		}
	}

	SDL_RenderPresent(r);
}

static void ajustarWindowTitle(SDL_Window *win)
{
	char title[MAX_TITLE];
	snprintf(title, MAX_TITLE-1, TITLE, densidadPoblacion(t));
	SDL_SetWindowTitle(win, title);
}

static void ajustarWindowSize(SDL_Window *win)
{
	int old_width = width;
	int old_height = height;

	if (t.size() > 0) {
		// ajustar size segun cantidad de celdas
		width = (int)round((double)width / t[0].size()) * t[0].size() + 3;
		height = (int)round((double)height / t.size()) * t.size() + 3;
		if (old_width != width || old_height != height)
			SDL_SetWindowSize(win, width, height);
	}
}

static int resizingEventWatcher(void* data, SDL_Event* e)
{
	switch (e->type) {
		case SDL_WINDOWEVENT:
			if (e->window.event == SDL_WINDOWEVENT_RESIZED) {
				SDL_Window* win = SDL_GetWindowFromID(e->window.windowID);
				if (win == (SDL_Window*)data) {
					SDL_GetWindowSize(win, &width, &height);
					ajustarWindowSize(win);
				}

				SDL_DestroyRenderer(renderer);
				renderer = SDL_CreateRenderer(win, -1, 0);
				redraw = true;
			}
			break;
		default:
			break;
	}
	return 0;
}

static void mouseOver(toroide &t, int &i, int &j, int mouseX, int mouseY)
{
	int filas = t.size();
	int columnas = t[0].size();

	if (t.size() > 0) {
		int w = width;
		int h = height;

		int ylen = h / filas;
		int xlen = w / columnas;

		i = mouseY / ylen;
		j = mouseX / xlen;

		// ajusto para que quede siempre en rango
		if (i < 0) i = 0;
		if (i >= filas) i = filas-1;
		if (j < 0) j = 0;
		if (j >= columnas) j = columnas-1;
	}
}

static void procesarEventos(status &s)
{
	int i = 0;
	int j = 0;
	int delay = 5;
	int numEventos;
	SDL_Event e;

	if (SDL_WaitEventTimeout(&e, delay)) {
		numEventos = 10;
		do {
			switch (e.type) {
				case SDL_QUIT:
					s = QUIT; break;
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym) {
						case SDLK_e:
							s = PLAY_ONCE; break;
						case SDLK_p:
							s = PLAY; break;
						case SDLK_l:
							s = LOAD; break;
						case SDLK_s:
							if (e.key.keysym.mod & KMOD_SHIFT)
								s = SAVE;
							else
								s = STOP;
							break;
						default:
							break;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (e.button.button == SDL_BUTTON_LEFT) {
						mouseOver(t, i, j, e.motion.x, e.motion.y);
						t[i][j] = !t[i][j];
					}
					break;

				default:
					break;
			}
			redraw = true;
		} while (numEventos-- && SDL_PollEvent(&e));
	}
}

static void siguienteEstado(status &s, bool &nuevo, const string &nombreArchivo, toroide &t, SDL_Window *win, bool &redraw)
{
	switch (s) {
		case STOP:
		case QUIT:
			break;
		case PLAY_ONCE:
			s = STOP;
		case PLAY:
			evolucionToroide(t);
			redraw = true;
			break;
		case LOAD:
			if (nuevo)
				limpiarToroide(t);
			else {
				t = cargarVistaToroide(nombreArchivo);
				ajustarWindowSize(win);
			}
			redraw = true;
			s = STOP;
			break;
		case SAVE:
			nuevo = false;
			guardarVistaToroide(nombreArchivo, t);
			s = STOP;
			break;
	}

	if (redraw) {
		dibujarToroide(t);
		ajustarWindowTitle(win);
		SDL_UpdateWindowSurface(win);
		redraw = false;
	}
}

static void parsearSize(char *ptr, int *filas, int *columnas)
{
	bool found = false;
	char *start = ptr;
	while (!found && *ptr) {
		if (*ptr == ',') {
			*ptr = '\0';
			found = true;
		}
		ptr++;
	}
	sscanf(start, "%d", filas);
	if (*ptr) {
		sscanf(ptr, "%d", columnas);
	}
}

int main(int argc, char **argv)
{
	status s = STOP;
	bool cargaOk = false;
	bool nuevo = false;
	int filas = 0;
	int columnas = 0;
	int extra = 0;
	string nombreArchivo;

	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

	// cmdline
	maxiopt_t opts[] = {
		{'n', "--nuevo", 0},
		{'s', "--size", 1},
		{0, NULL, 0}
	};
	maxiopt_t *curopt = NULL;

	for (int idx = 1; idx < argc; idx++) {
		maxiopt(opts, argv[idx], &curopt, &extra);
		switch (curopt->shortname) {
			case 'n':
				SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Nuevo toroide!\n");
				nuevo = true;
				break;
			case 's':
				parsearSize(*(argv + idx) + extra, &filas, &columnas);
				SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Dimensiones toroide -> filas: %d columnas: %d\n", filas, columnas);
				break;
			default:
				if (!nombreArchivo.length()) {
					nombreArchivo = string(argv[idx]);
					SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Archivo toroide -> %s\n", nombreArchivo.c_str());
				}
				break;
		}
	}

	if (!nombreArchivo.length()) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Faltan argumentos obligatorios: nombreArchivo\n");
		exit(4);
	}

	if (nuevo) {
		if (!filas || !columnas) {
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Dimensiones invalidas -> filas: %d columnas: %d\n", filas, columnas);
			exit(3);
		}
		t = nuevoToroide(filas, columnas);
	} else
		t = cargarVistaToroide(nombreArchivo);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init falla con error: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_Window *win = SDL_CreateWindow("",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(win, -1, 0);
	SDL_AddEventWatch(resizingEventWatcher, win);
	SDL_GetWindowSize(win, &width, &height);
	ajustarWindowTitle(win);
	ajustarWindowSize(win);

	while (s != QUIT) {
		procesarEventos(s);
		siguienteEstado(s, nuevo, nombreArchivo, t, win, redraw);
	}
	
	if (renderer) SDL_DestroyRenderer(renderer);
	if (win) SDL_DestroyWindow(win);

	SDL_Quit();

	return 0;
}
