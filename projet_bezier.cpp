#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL2/SDL.h>
/** #include <SDL2/SDL_image.h> */

/**
 * Sous Ubuntu, compile avec: 'g++ GHOUL_BOUM_projet_bezier.cpp -lSDL2 -lSDL2_image',
 * Dépendance nécessaire: sudo apt-get install libsdl2-2.0-0
 * Sous Windows, il peut être installé depuis http://libsdl.org/download-2.0.php
 **/
/// Définit le temps d'affichage de chaque lettres (ms)
#define TEMPS_AFFICHAGE 500

/**
 * Contient un couple de coordonnées.
 */
typedef struct {
    double x, y;
} coord;


/**
 * Définit les informations nécessaires au calcul de la
 * trajectoire (début, fin, controle), et un pointeur
 * vers le résultat (trajectoire)
 */
typedef struct {
    coord from, to, control;
    coord *points;
} curve;


/**
 * Définit les informations nécessaires au traçage d'une lettre,
 * à savoir une liste de courbes et un nombre de courbes.
 */
typedef struct {
    curve *curves;
    size_t numberOfCurves;
} letter;


/**
 * Définit un alphabet de 26 lettres, et un nombre de points par courbe.
 */
typedef struct {
    letter letters[26]; // 26
    size_t numberOfPointsPerCurve;
} police;

/**
 * Genere une trajectoire à partir des points de référence
 * @param c Un pointeur vers une courbe à dessiner
 * @param numberOfPoints Le nombre de points à calculer par courbe
 **/
void traceBezier(curve *c, size_t numberOfPoints) {
    c->points = static_cast<coord *>(calloc(numberOfPoints, sizeof(coord)));
    coord a1, a2;
    double x;
    for (int i = 0; i < numberOfPoints; ++i) {
        x = (double) i / (numberOfPoints - 1);
        a1.x = (c->to.x * x) + (c->control.x * (1 - x));
        a1.y = (c->to.y * x) + (c->control.y * (1 - x));
        a2.x = (c->control.x * x) + (c->from.x * (1 - x));
        a2.y = (c->control.y * x) + (c->from.y * (1 - x));
        c->points[i].x = (a1.x * x) + (a2.x * (1 - x));
        c->points[i].y = (a1.y * x) + (a2.y * (1 - x));
    }
}

/**
 * Initialise un objet de type `police`, en définissant chacune des lettres
 * comme des listes de courbes.
 * @param police Un pointeur vers une instance de type `police`
 * @param nombreDePoints Le nombre de points à calculer par courbe
 */

void genererPremierePolice(police *p, size_t nombrePoints = 1000);
void genererPremierePolice(police *p, size_t nombrePoints) {
    p->numberOfPointsPerCurve = nombrePoints;
    p->letters[0].curves = static_cast<curve *>(calloc(3, sizeof(curve)));
    p->letters[0].numberOfCurves = 3;
    p->letters[0].curves[0] = {{0.5,  0}, {0,    1}, {0.25, 0.5}};
    p->letters[0].curves[1] = {{0.5,  0}, {1,    1}, {0.75, 0.5}};
    p->letters[0].curves[2] = {{0.25, 0.5}, {0.75, 0.5}, {0.5,  0.5}};

    // B
    p->letters[1].curves = static_cast<curve *>(calloc(7, sizeof(curve)));
    p->letters[1].numberOfCurves = 7;
    p->letters[1].curves[0] = {{0,  0}, {0.5, 0}, {0.25,  0}};
    p->letters[1].curves[1] = {{0.5,  0}, {0.9, 0.25}, {0.9,  0}};
    p->letters[1].curves[2] = {{0.9,  0.25}, {0.5, 0.5}, {0.9,  0.5}};
    p->letters[1].curves[3] = {{0.5,  0.5}, {1, 0.75}, {1,  0.5}};
    p->letters[1].curves[5] = {{1,  0.75}, {0.5, 1}, {1, 1}};
    p->letters[1].curves[4] = {{0.5,  1}, {0, 1}, {0.25,  1}};
    p->letters[1].curves[6] = {{0,  1}, {0, 0}, {0,  0.5}};

    // C
    p->letters[2].curves = static_cast<curve *>(calloc(4, sizeof(curve)));
    p->letters[2].numberOfCurves = 4;
    p->letters[2].curves[0] = {{1,  0.25}, {0.5, 0}, {1,  0}};
    p->letters[2].curves[1] = {{0.5,  0}, {0, 0.5}, {0,  0}};
    p->letters[2].curves[2] = {{0,  0.5}, {0.5, 1}, {0,  1}};
    p->letters[2].curves[3] = {{0.5,  1}, {1, 0.75}, {1,  1}};

    p->letters[3].curves = static_cast<curve *>(calloc(5, sizeof(curve)));
    p->letters[3].numberOfCurves = 5;
    p->letters[3].curves[0] = {{0,  0}, {0.5, 0}, {0.25,  0}};
    p->letters[3].curves[1] = {{0.5,  0}, {1, 0.5}, {1,  0}};
    p->letters[3].curves[2] = {{1,  0.5}, {0.5, 1}, {1,  1}};
    p->letters[3].curves[3] = {{0.5,  1}, {0, 1}, {0.25,  1}};
    p->letters[3].curves[4] = {{0,  1}, {0, 0}, {0,  0.5}};

    p->letters[4].curves = static_cast<curve *>(calloc(4, sizeof(curve)));
    p->letters[4].numberOfCurves = 4;
    p->letters[4].curves[0] = {{0,  0}, {1, 0}, {0.5,  0}};
    p->letters[4].curves[1] = {{0,  0.5}, {0.9, 0.5}, {0.45,  0.5}};
    p->letters[4].curves[2] = {{0,  1}, {1, 1}, {1,  1}};
    p->letters[4].curves[3] = {{0,  1}, {0, 0}, {0,  0.5}};

    // F
    p->letters[5].curves = static_cast<curve *>(calloc(3, sizeof(curve)));
    p->letters[5].numberOfCurves = 3;
    p->letters[5].curves[0] = {{0,  0}, {1, 0}, {0.5,  0}};
    p->letters[5].curves[1] = {{0,  0.5}, {0.9, 0.5}, {0.45,  0.5}};
    p->letters[5].curves[2] = {{0,  1}, {0, 0}, {0,  0.5}};

    // G
    p->letters[6].curves = static_cast<curve *>(calloc(5, sizeof(curve)));
    p->letters[6].numberOfCurves = 5;
    p->letters[6].curves[0] = {{1,  0.25}, {0.5, 0}, {1,  0}};
    p->letters[6].curves[1] = {{0.5,  0}, {0, 0.5}, {0,  0}};
    p->letters[6].curves[2] = {{0,  0.5}, {0.5, 1}, {0,  1}};
    p->letters[6].curves[3] = {{0.5,  1}, {1, 0.5}, {1,  1}};
    p->letters[6].curves[4] = {{1,  0.5}, {0.5, 0.5}, {0.75,  0.5}};

    // H
    p->letters[7].curves = static_cast<curve *>(calloc(3, sizeof(curve)));
    p->letters[7].numberOfCurves = 3;
    p->letters[7].curves[0] = {{1,  0}, {1, 1}, {1,  0.5}};
    p->letters[7].curves[1] = {{0,  0.5}, {1, 0.5}, {0.45,  0.5}};
    p->letters[7].curves[2] = {{0,  1}, {0, 0}, {0,  0.5}};

    // I
    p->letters[8].curves = static_cast<curve *>(calloc(1, sizeof(curve)));
    p->letters[8].numberOfCurves = 1;
    p->letters[8].curves[0] = {{0.5,  0}, {0.5, 1}, {0.5,  0.5}};

    // J
    p->letters[9].curves = static_cast<curve *>(calloc(3, sizeof(curve)));
    p->letters[9].numberOfCurves = 3;
    p->letters[9].curves[0] = {{0,  0.75}, {0.5, 1}, {0,  1}};
    p->letters[9].curves[1] = {{0.5,  1}, {1, 0.75}, {1,  1}};
    p->letters[9].curves[2] = {{1,  0.75}, {1, 0}, {1,  0.75 / 2}};

    // K
    p->letters[10].curves = static_cast<curve *>(calloc(3, sizeof(curve)));
    p->letters[10].numberOfCurves = 3;
    p->letters[10].curves[0] = {{0,  0}, {0, 1}, {0,  0.5}};
    p->letters[10].curves[1] = {{0,  0.6}, {1, 0}, {0.5,  0.3}};
    p->letters[10].curves[2] = {{0.5,  0.3}, {1, 1}, {0.75,  0.65}};

    // L
    p->letters[11].curves = static_cast<curve *>(calloc(2, sizeof(curve)));
    p->letters[11].numberOfCurves = 2;
    p->letters[11].curves[0] = {{0,  1}, {1, 1}, {0.5,  1}};
    p->letters[11].curves[1] = {{0,  1}, {0, 0}, {0,  0.5}};

    // M
    p->letters[12].curves = static_cast<curve *>(calloc(4, sizeof(curve)));
    p->letters[12].numberOfCurves = 4;
    p->letters[12].curves[0] = {{0,  1}, {0, 0}, {0,  0.5}};
    p->letters[12].curves[1] = {{0,  0}, {0.5, 0.5}, {0.25,  0.25}};
    p->letters[12].curves[2] = {{0.5, 0.5}, {1, 0}, {0.75,  0.25}};
    p->letters[12].curves[3] = {{1, 0}, {1, 1}, {1, 0.5}};

    // N
    p->letters[13].curves = static_cast<curve *>(calloc(3, sizeof(curve)));
    p->letters[13].numberOfCurves = 3;
    p->letters[13].curves[0] = {{0,  1}, {0, 0}, {0,  0.5}};
    p->letters[13].curves[1] = {{0,  0}, {1, 1}, {0.5,  0.5}};
    p->letters[13].curves[2] = {{1, 1}, {1, 0}, {1,  0.5}};

    // O
    p->letters[14].curves = static_cast<curve *>(calloc(4, sizeof(curve)));
    p->letters[14].numberOfCurves = 4;
    p->letters[14].curves[0] = {{1,  0.5}, {0.5, 0}, {1,  0}};
    p->letters[14].curves[1] = {{0.5,  0}, {0, 0.5}, {0,  0}};
    p->letters[14].curves[2] = {{0,  0.5}, {0.5, 1}, {0,  1}};
    p->letters[14].curves[3] = {{0.5,  1}, {1, 0.5}, {1,  1}};

    // P
    p->letters[15].curves = static_cast<curve *>(calloc(5, sizeof(curve)));
    p->letters[15].numberOfCurves = 5;
    p->letters[15].curves[0] = {{0,  0}, {0.5, 0}, {0.25,  0}};
    p->letters[15].curves[1] = {{0.5,  0}, {0.9, 0.25}, {0.9,  0}};
    p->letters[15].curves[2] = {{0.9,  0.25}, {0.5, 0.5}, {0.9,  0.5}};
    p->letters[15].curves[3] = {{0.5,  0.5}, {0, 0.5}, {0.25,  0.5}};
    p->letters[15].curves[4] = {{0,  1}, {0, 0}, {0,  0.5}};

    // Q
    p->letters[16].curves = static_cast<curve *>(calloc(5, sizeof(curve)));
    p->letters[16].numberOfCurves = 5;
    p->letters[16].curves[0] = {{1,  0.5}, {0.5, 0}, {1,  0}};
    p->letters[16].curves[1] = {{0.5,  0}, {0, 0.5}, {0,  0}};
    p->letters[16].curves[2] = {{0,  0.5}, {0.5, 1}, {0,  1}};
    p->letters[16].curves[3] = {{0.5,  1}, {1, 0.5}, {1,  1}};
    p->letters[16].curves[4] = {{0.9,  0.9}, {1, 1}, {0.45,  0.45}};

    // R
    p->letters[17].curves = static_cast<curve *>(calloc(6, sizeof(curve)));
    p->letters[17].numberOfCurves = 6;
    p->letters[17].curves[0] = {{0,  0}, {0.5, 0}, {0.25,  0}};
    p->letters[17].curves[1] = {{0.5,  0}, {0.9, 0.25}, {0.9,  0}};
    p->letters[17].curves[2] = {{0.9,  0.25}, {0.5, 0.5}, {0.9,  0.5}};
    p->letters[17].curves[3] = {{0.5,  0.5}, {0, 0.5}, {0.25,  0.5}};
    p->letters[17].curves[4] = {{0,  1}, {0, 0}, {0,  0.5}};
    p->letters[17].curves[5] = {{0.5, 0.5}, {1, 1}, {0.75,  0.75}};

    // S
    p->letters[18].curves = static_cast<curve *>(calloc(6, sizeof(curve)));
    p->letters[18].numberOfCurves = 6;
    p->letters[18].curves[0] = {{1,  0.25}, {0.5, 0}, {1,  0}};
    p->letters[18].curves[1] = {{0.5,  0}, {0, 0.25}, {0,  0}};
    p->letters[18].curves[2] = {{0,  0.25}, {0.5, 0.5}, {0,  0.5}};
    p->letters[18].curves[3] = {{0.5,  0.5}, {1, 0.75}, {1,  0.5}};
    p->letters[18].curves[4] = {{1,  0.75}, {0.5, 1}, {1,  1}};
    p->letters[18].curves[5] = {{0.5,  1}, {0, 0.75}, {0,  1}};


    // T
    p->letters[19].curves = static_cast<curve *>(calloc(2, sizeof(curve)));
    p->letters[19].numberOfCurves = 2;
    p->letters[19].curves[0] = {{0,  0}, {1, 0}, {0.5,  0}};
    p->letters[19].curves[1] = {{0.5,  1}, {0.5, 0}, {0.5,  0.5}};

    // U
    p->letters[20].curves = static_cast<curve *>(calloc(4, sizeof(curve)));
    p->letters[20].numberOfCurves = 4;
    p->letters[20].curves[0] = {{0,  0}, {0, 0.5}, {0,  0.25}};
    p->letters[20].curves[1] = {{1,  0}, {1, 0.5}, {1,  0.25}};
    p->letters[20].curves[2] = {{1,  0.5}, {0.5, 1}, {1,  1}};
    p->letters[20].curves[3] = {{0.5,  1}, {0, 0.5}, {0,  1}};

    // V
    p->letters[21].curves = static_cast<curve *>(calloc(2, sizeof(curve)));
    p->letters[21].numberOfCurves = 2;
    p->letters[21].curves[0] = {{0,  0}, {0.5, 1}, {0.25,  0.5}};
    p->letters[21].curves[1] = {{0.5,  1}, {1, 0}, {0.75,  0.5}};

    // W
    p->letters[22].curves = static_cast<curve *>(calloc(4, sizeof(curve)));
    p->letters[22].numberOfCurves = 4;
    p->letters[22].curves[0] = {{0,  0}, {0.25, 1}, {0.125,  0.5}};
    p->letters[22].curves[1] = {{0.25,  1}, {0.5, 0.125}, {(0.25 + 0.5) / 2,  1.125 / 2}};
    p->letters[22].curves[2] = {{0.5, 0.125}, {0.75, 1}, {(0.5 + 0.75) / 2,  1.125 / 2}};
    p->letters[22].curves[3] = {{0.75, 1}, {1, 0}, {1.75/2,  0.5}};

    // X
    p->letters[23].curves = static_cast<curve *>(calloc(2, sizeof(curve)));
    p->letters[23].numberOfCurves = 2;
    p->letters[23].curves[0] = {{0,  0}, {1, 1}, {0.5,  0.5}};
    p->letters[23].curves[1] = {{1,  0}, {0, 1}, {0.5, 0.5}};

    // Y
    p->letters[24].curves = static_cast<curve *>(calloc(3, sizeof(curve)));
    p->letters[24].numberOfCurves = 3;
    p->letters[24].curves[0] = {{0,  0}, {0.5, 0.5}, {0.25,  0.25}};
    p->letters[24].curves[1] = {{0.5,  0.5}, {1, 0}, {0.75, 0.25}};
    p->letters[24].curves[2] = {{0.5,  0.5}, {0.5, 1}, {0.5, 0.75}};


    // Z
    p->letters[25].curves = static_cast<curve *>(calloc(3, sizeof(curve)));
    p->letters[25].numberOfCurves = 3;
    p->letters[25].curves[0] = {{0,  0}, {1, 0}, {0.5,  0}};
    p->letters[25].curves[1] = {{1,  0}, {0, 1}, {0.5, 0.5}};
    p->letters[25].curves[2] = {{0,  1}, {1, 1}, {0.5, 1}};

}

/**
 * Génère les trajectoires de toutes les lettres de l'alphabet
 * @param police Un pointeur vers une instance de `police`
 **/
void tracePolice(police *p) {
    for (int index = 0; index < 26; index++) {
        for (int i = 0; i < p->letters[index].numberOfCurves; ++i) {
            traceBezier(p->letters[index].curves + i, p->numberOfPointsPerCurve);
        }
    }

}

#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH 640

/**
 * Dessine un cercle
 * @param[in] renderer Un pointeur vers le SDL_Renderer utilisé pour le rendu.
 * @param[in] x, y Les coordonnées du centre du cercle
 * @param[in] r Le rayon du cercle
 **/
void drawCircle(SDL_Renderer* renderer, int x, int y, int r) {
    int R = r * r;
    for (int w = 0; w < r * 2; w++) {
        for (int h = 0; h < r * 2; h++) {
            int dx = r - w; // horizontal offset
            int dy = r - h; // vertical offset
            if ((dx*dx + dy*dy) <= R)
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
        }
    }
}

/**
 * Dessine à l'écran une lettre
 * @param[in] renderer Un pointeur vers le SDL_Renderer utilisé pour le rendu.
 * @param[in] lettre Un pointeur vers la lettre à afficher.
 * @param[in] index Un index qui incrémente à chaque fois que l'on
 *              recommence l'alphabet.
 * @param[in] nombreDePoints Nombre de points par courbe.
 **/
void drawLetter(SDL_Renderer* renderer, letter* lettre, int index, size_t nombreDePoints) {
    int i, j;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    index %= 3;
    if (index == 2) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
    for (i = 0; i < lettre->numberOfCurves; ++i)
        for(j = 0; j < nombreDePoints; j++)
            drawCircle(renderer,
                (0.25 + (0.50 * lettre->curves[i].points[j].x)) * WINDOW_WIDTH,
                (0.05 + (0.90 * lettre->curves[i].points[j].y)) * WINDOW_HEIGHT, 8);
    if (index == 0) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    } else if (index == 2) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
    if(index != 1)
        for (i = 0; i < lettre->numberOfCurves; ++i)
            for(j = 0; j < nombreDePoints; j++)
                drawCircle(renderer,
                    (0.25 + (0.50 * lettre->curves[i].points[j].x)) * WINDOW_WIDTH,
                    (0.05 + (0.90 * lettre->curves[i].points[j].y)) * WINDOW_HEIGHT, 5);

    SDL_RenderPresent(renderer);
}


int main ( int argc, char** argv ) {
    police p;
    genererPremierePolice(&p);
    tracePolice(&p);
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    atexit(SDL_Quit);

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    if ( !window || !renderer) {printf("Unable to create either window or renderer: %s\n", SDL_GetError());return 1;}

    SDL_Texture* texture;
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
    for(int i = 0;; ++i) {
        drawLetter(renderer, p.letters + (i % 26), i / 26, p.numberOfPointsPerCurve);
        SDL_Delay(TEMPS_AFFICHAGE);
    }
    return 0;
}


























