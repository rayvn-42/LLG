#include <X11/keysym.h>
#include <LLG/llg.h>
#include <stdio.h>
#include <math.h>

/*
    example_drawing.c
    Demonstrates all drawing primitives available in LLG.
    Press LEFT/RIGHT arrows to cycle between scenes.
    Press ESCAPE or close the window to exit.
*/

#define SCENE_COUNT 5

/* forward declarations */
void scene_primitives(LLGContext *ctx);
void scene_fill_stroke(LLGContext *ctx);
void scene_circles(LLGContext *ctx);
void scene_polygons(LLGContext *ctx);
void scene_arcs(LLGContext *ctx);

typedef void (*SceneFn)(LLGContext *);

static SceneFn scenes[SCENE_COUNT] = {
    scene_primitives,
    scene_fill_stroke,
    scene_circles,
    scene_polygons,
    scene_arcs,
};

static const char *scene_names[SCENE_COUNT] = {
    "1/5 — Primitives (pixel, line, rect)",
    "2/5 — Fill vs Stroke",
    "3/5 — Circles",
    "4/5 — Polygons",
    "5/5 — Arcs & Ellipses",
};

/* ------------------------------------------------------------------ */

void scene_primitives(LLGContext *ctx) {
    /* single pixels */
    LLG_setStroke(ctx, LLG_RGB(255, 255, 255));
    for (int i = 0; i < 800; i += 10)
        LLG_drawPixel(ctx, i, 80);

    /* lines — various colors */
    LLG_setStroke(ctx, LLG_RGB(255, 80, 80));
    LLG_setStrokeWidth(ctx, 1);
    LLG_drawLine(ctx, 50, 150, 750, 150);

    LLG_setStroke(ctx, LLG_RGB(80, 255, 80));
    LLG_setStrokeWidth(ctx, 3);
    LLG_drawLine(ctx, 50, 200, 750, 200);

    LLG_setStroke(ctx, LLG_RGB(80, 80, 255));
    LLG_setStrokeWidth(ctx, 6);
    LLG_drawLine(ctx, 50, 260, 750, 260);

    /* diagonal lines */
    LLG_setStroke(ctx, LLG_RGB(200, 200, 50));
    LLG_setStrokeWidth(ctx, 2);
    for (int i = 0; i < 10; i++)
        LLG_drawLine(ctx, 50 + i * 70, 320, 50 + i * 70 + 50, 420);

    /* outlined rects */
    LLG_setStroke(ctx, LLG_RGB(255, 255, 255));
    LLG_setStrokeWidth(ctx, 1);
    LLG_drawRect(ctx, (LLGRect){100, 460, 150, 80});

    LLG_setStroke(ctx, LLG_RGB(255, 120, 0));
    LLG_setStrokeWidth(ctx, 4);
    LLG_drawRect(ctx, (LLGRect){320, 460, 150, 80});

    LLG_setStroke(ctx, LLG_RGB(0, 200, 255));
    LLG_setStrokeWidth(ctx, 8);
    LLG_drawRect(ctx, (LLGRect){540, 460, 150, 80});
}

/* ------------------------------------------------------------------ */

void scene_fill_stroke(LLGContext *ctx) {
    /* fill only */
    LLG_setFill(ctx, LLG_RGB(220, 60, 60));
    LLG_noStroke(ctx);
    LLG_rect(ctx, (LLGRect){60, 80, 180, 120});

    /* stroke only */
    LLG_noFill(ctx);
    LLG_setStroke(ctx, LLG_RGB(60, 220, 60));
    LLG_setStrokeWidth(ctx, 3);
    LLG_rect(ctx, (LLGRect){310, 80, 180, 120});

    /* fill + stroke */
    LLG_setFill(ctx, LLG_RGB(60, 120, 220));
    LLG_setStroke(ctx, LLG_RGB(255, 255, 255));
    LLG_setStrokeWidth(ctx, 4);
    LLG_rect(ctx, (LLGRect){560, 80, 180, 120});

    /* same pattern for filled rects directly */
    LLG_setFill(ctx, LLG_RGB(180, 60, 180));
    LLG_noStroke(ctx);
    LLG_fillRect(ctx, (LLGRect){60, 280, 180, 120});

    LLG_noFill(ctx);
    LLG_setStroke(ctx, LLG_RGB(180, 180, 60));
    LLG_setStrokeWidth(ctx, 5);
    LLG_drawRect(ctx, (LLGRect){310, 280, 180, 120});

    LLG_setFill(ctx, LLG_RGB(60, 180, 180));
    LLG_setStroke(ctx, LLG_RGB(255, 80, 80));
    LLG_setStrokeWidth(ctx, 6);
    LLG_rect(ctx, (LLGRect){560, 280, 180, 120});

    /* color lerp demo */
    LLG_noStroke(ctx);
    for (int i = 0; i < 20; i++) {
        float    t   = (float)i / 19.0f;
        LLGColor col = LLG_colorLerp(LLG_RGB(255, 0, 0), LLG_RGB(0, 0, 255), t);
        LLG_setFill(ctx, col);
        LLG_fillRect(ctx, (LLGRect){60 + i * 34, 460, 34, 80});
    }
}

/* ------------------------------------------------------------------ */

void scene_circles(LLGContext *ctx) {
    /* fill only */
    LLG_setFill(ctx, LLG_RGB(255, 80, 80));
    LLG_noStroke(ctx);
    LLG_circle(ctx, 130, 150, 80);

    /* stroke only */
    LLG_noFill(ctx);
    LLG_setStroke(ctx, LLG_RGB(80, 255, 80));
    LLG_setStrokeWidth(ctx, 3);
    LLG_circle(ctx, 400, 150, 80);

    /* fill + stroke */
    LLG_setFill(ctx, LLG_RGB(80, 80, 255));
    LLG_setStroke(ctx, LLG_RGB(255, 255, 255));
    LLG_setStrokeWidth(ctx, 5);
    LLG_circle(ctx, 670, 150, 80);

    /* concentric circles */
    LLG_noFill(ctx);
    LLG_setStrokeWidth(ctx, 2);
    for (int i = 1; i <= 6; i++) {
        float    t   = (float)i / 6.0f;
        LLGColor col = LLG_colorLerp(LLG_RGB(255, 200, 0), LLG_RGB(255, 0, 100), t);
        LLG_setStroke(ctx, col);
        LLG_drawCircle(ctx, 200, 380, i * 30);
    }

    /* filled circles grid */
    LLG_noStroke(ctx);
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            LLGColor c = LLG_RGB(
                80  + col * 50,
                80  + row * 60,
                200 - col * 30
            );
            LLG_setFill(ctx, c);
            LLG_fillCircle(ctx, 430 + col * 80, 310 + row * 80, 28);
        }
    }
}

/* ------------------------------------------------------------------ */

void scene_polygons(LLGContext *ctx) {
    /* triangle — fill only */
    LLGPoint triangle[] = {
        {400, 60},
        {220, 280},
        {580, 280},
    };
    LLG_setFill(ctx, LLG_RGB(255, 180, 0));
    LLG_noStroke(ctx);
    LLG_polygon(ctx, (LLGPolygon){triangle, 3});

    /* triangle — stroke only */
    LLG_noFill(ctx);
    LLG_setStroke(ctx, LLG_RGB(255, 255, 255));
    LLG_setStrokeWidth(ctx, 2);
    LLG_drawPolygon(ctx, (LLGPolygon){triangle, 3});

    /* hexagon */
    LLGPoint hex[6];
    for (int i = 0; i < 6; i++) {
        double angle = (3.14159265 / 180.0) * (60.0 * i - 30.0);
        hex[i].x = (int)(180 + 100 * cos(angle));  /* needs #include <math.h> */
        hex[i].y = (int)(440 + 100 * sin(angle));
    }
    LLG_setFill(ctx, LLG_RGB(80, 180, 255));
    LLG_setStroke(ctx, LLG_RGB(255, 255, 255));
    LLG_setStrokeWidth(ctx, 3);
    LLG_polygon(ctx, (LLGPolygon){hex, 6});

    /* arrow shape */
    LLGPoint arrow[] = {
        {480, 360}, {580, 410}, {540, 410},
        {540, 500}, {500, 500}, {500, 410}, {460, 410},
    };
    LLG_setFill(ctx, LLG_RGB(255, 80, 120));
    LLG_setStroke(ctx, LLG_RGB(255, 255, 255));
    LLG_setStrokeWidth(ctx, 2);
    LLG_polygon(ctx, (LLGPolygon){arrow, 7});
}

/* ------------------------------------------------------------------ */

void scene_arcs(LLGContext *ctx) {
    /* draw arc — partial ellipse outlines */
    LLG_noFill(ctx);
    LLG_setStrokeWidth(ctx, 3);

    LLG_setStroke(ctx, LLG_RGB(255, 100, 100));
    LLG_drawArc(ctx, (LLGEllipse){60, 60, 160, 160}, 0, 90);

    LLG_setStroke(ctx, LLG_RGB(100, 255, 100));
    LLG_drawArc(ctx, (LLGEllipse){60, 60, 160, 160}, 90, 120);

    LLG_setStroke(ctx, LLG_RGB(100, 100, 255));
    LLG_drawArc(ctx, (LLGEllipse){60, 60, 160, 160}, 210, 150);

    /* filled arc — pie slices */
    LLG_noStroke(ctx);
    LLGColor pie_colors[] = {
        LLG_RGB(255, 80,  80),
        LLG_RGB(80,  255, 80),
        LLG_RGB(80,  80,  255),
        LLG_RGB(255, 255, 80),
        LLG_RGB(255, 80,  255),
    };
    int slices[]  = {72, 90, 60, 80, 58};  /* must sum to 360 */
    int start     = 0;
    for (int i = 0; i < 5; i++) {
        LLG_setFill(ctx, pie_colors[i]);
        LLG_fillArc(ctx, (LLGEllipse){480, 60, 240, 240}, start, slices[i]);
        start += slices[i];
    }

    /* ellipses */
    LLG_setFill(ctx, LLG_RGB(60, 160, 220));
    LLG_setStroke(ctx, LLG_RGB(255, 255, 255));
    LLG_setStrokeWidth(ctx, 2);
    LLG_ellipse(ctx, (LLGEllipse){60, 340, 280, 140});

    LLG_setFill(ctx, LLG_RGB(220, 100, 60));
    LLG_setStroke(ctx, LLG_RGB(255, 255, 255));
    LLG_ellipse(ctx, (LLGEllipse){420, 380, 120, 180});
}

/* ------------------------------------------------------------------ */

int main(void) {
    LLGContext *ctx = LLG_init("LLG Drawing Examples", 800, 600);
    if (ctx == NULL) {
        printf("init failed: %s\n", LLG_errorStr(LLG_getError()));
        return 1;
    }

    LLG_setBackground(ctx, LLG_RGB(30, 30, 30));
    LLG_setFpsCap(ctx, 60);

    int      scene = 0;
    LLGEvent ev;

    while (LLG_isRunning(ctx)) {
        while (LLG_pollEvent(ctx, &ev)) {
            if (ev.type == LLG_EVENT_CLOSE)
                LLG_quit(ctx);

            if (ev.type == LLG_EVENT_KEY_PRESS) {
                if (ev.key.key == XK_Escape)
                    LLG_quit(ctx);
                if (ev.key.key == XK_Right)
                    scene = (scene + 1) % SCENE_COUNT;
                if (ev.key.key == XK_Left)
                    scene = (scene - 1 + SCENE_COUNT) % SCENE_COUNT;
            }
        }

        LLG_setTitle(ctx, scene_names[scene]);
        LLG_clear(ctx);
        scenes[scene](ctx);
        LLG_present(ctx);
    }

    LLG_destroy(ctx);
    return 0;
}