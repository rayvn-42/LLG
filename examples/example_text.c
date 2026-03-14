#include <stdio.h>
#include <string.h>
#include <X11/keysym.h>
#include <LLG/llg.h>

/*
    example_text.c
    Demonstrates text rendering in LLG.
    Press LEFT/RIGHT arrows to cycle between scenes.
    Press ESCAPE or close the window to exit.
*/

#define SCENE_COUNT 4
#define WIN_W       800
#define WIN_H       600

/* forward declarations */
void scene_fonts(LLGContext *ctx);
void scene_colors(LLGContext *ctx);
void scene_sizing(LLGContext *ctx);
void scene_layout(LLGContext *ctx);

typedef void (*SceneFn)(LLGContext *);

static SceneFn scenes[SCENE_COUNT] = {
    scene_fonts,
    scene_colors,
    scene_sizing,
    scene_layout,
};

static const char *scene_names[SCENE_COUNT] = {
    "1/4 — Available Fonts",
    "2/4 — Text Colors",
    "3/4 — Text Sizing (LLG_textSize)",
    "4/4 — Text Layout",
};

/* ------------------------------------------------------------------ */

void scene_fonts(LLGContext *ctx) {
    /* show every built-in alias and what it looks like */
    const char *fonts[] = {
        "fixed",
        "mono-12",
        "mono-14",
        "mono-bold-14",
        "sans-12",
        "sans-14",
        NULL
    };

    const char *labels[] = {
        "fixed          —  ",
        "mono-12        —  ",
        "mono-14        —  ",
        "mono-bold-14   —  ",
        "sans-12        —  ",
        "sans-14        —  ",
        NULL
    };

    LLG_setStroke(ctx, LLG_RGB(180, 180, 180));

    /* section header in default font */
    LLG_setFont(ctx, "mono-14");
    LLG_setStroke(ctx, LLG_RGB(255, 200, 50));
    LLG_drawText(ctx, 60, 60, "Font Aliases");

    /* divider line */
    LLG_drawLine(ctx, 60, 75, 740, 75);

    int y = 130;
    for (int i = 0; fonts[i] != NULL; i++) {
        /* draw the label in mono-12 so it's consistent */
        LLG_setFont(ctx, "mono-12");
        LLG_setStroke(ctx, LLG_RGB(120, 120, 120));
        LLG_drawText(ctx, 60, y, labels[i]);

        /* draw the sample text in the actual font being shown */
        LLG_setFont(ctx, fonts[i]);
        LLG_setStroke(ctx, LLG_RGB(240, 240, 240));
        LLG_drawText(ctx, 340, y, "The quick brown fox jumps over the lazy dog");

        y += 60;
    }

    /* restore to default */
    LLG_setFont(ctx, "fixed");
}

/* ------------------------------------------------------------------ */

void scene_colors(LLGContext *ctx) {
    LLG_setFont(ctx, "mono-14");

    /* header */
    LLG_setStroke(ctx, LLG_RGB(255, 200, 50));
    LLG_drawText(ctx, 60, 60, "Text Colors & Stroke State");
    LLG_drawLine(ctx, 60, 75, 740, 75);

    /* rainbow text — each letter a different color */
    LLGColor rainbow[] = {
        LLG_RGB(255, 80,  80),
        LLG_RGB(255, 160, 80),
        LLG_RGB(255, 255, 80),
        LLG_RGB(80,  255, 80),
        LLG_RGB(80,  200, 255),
        LLG_RGB(120, 80,  255),
        LLG_RGB(255, 80,  200),
    };
    const char *word    = "RAINBOW";
    int         x       = 200;
    int         ncolors = (int)(sizeof(rainbow) / sizeof(rainbow[0]));
    for (int i = 0; word[i] != '\0'; i++) {
        char ch[2] = { word[i], '\0' };
        LLG_setStroke(ctx, rainbow[i % ncolors]);
        LLG_drawText(ctx, x, 160, ch);
        x += 55;
    }

    /* color lerp across a sentence */
    LLG_setFont(ctx, "mono-12");
    const char *sentence = "Color lerp from red to blue";
    int         len      = (int)strlen(sentence);
    x = 60;
    for (int i = 0; i < len; i++) {
        char        ch[2] = { sentence[i], '\0' };
        float       t     = (float)i / (float)(len - 1);
        LLGColor    col   = LLG_colorLerp(LLG_RGB(255, 60, 60), LLG_RGB(60, 60, 255), t);
        LLG_setStroke(ctx, col);
        LLG_drawText(ctx, x, 240, ch);
        x += 13;
    }

    /* strokeEnabled check */
    LLG_setFont(ctx, "mono-14");
    LLG_setStroke(ctx, LLG_RGB(255, 255, 255));
    LLG_drawText(ctx, 60, 320, "Stroke enabled  — this text is visible");

    LLG_noStroke(ctx);
    LLG_drawText(ctx, 60, 380, "Stroke disabled — this text is invisible");

    LLG_setStroke(ctx, LLG_RGB(100, 200, 100));
    LLG_drawText(ctx, 60, 440, "Stroke re-enabled — visible again");

    /* note */
    LLG_setFont(ctx, "mono-12");
    LLG_setStroke(ctx, LLG_RGB(100, 100, 100));
    LLG_drawText(ctx, 60, 520,
        "Note: text respects strokeEnabled — LLG_noStroke() hides text too");
}

/* ------------------------------------------------------------------ */

void scene_sizing(LLGContext *ctx) {
    LLG_setFont(ctx, "mono-14");
    LLG_setStroke(ctx, LLG_RGB(255, 200, 50));
    LLG_drawText(ctx, 60, 60, "LLG_textSize — measuring text bounds");
    LLG_setStroke(ctx, LLG_RGB(80, 80, 80));
    LLG_drawLine(ctx, 60, 75, 740, 75);

    /* measure and visualize bounding boxes */
    const char *samples[] = {
        "Hello",
        "Hello, World!",
        "The quick brown fox",
        "i",
        "MMMMMMMMMM",
        NULL
    };

    LLG_setFont(ctx, "mono-14");
    int y = 140;
    for (int i = 0; samples[i] != NULL; i++) {
        int w = 0, h = 0;
        LLG_textSize(ctx, samples[i], &w, &h);

        /* draw bounding box in muted color */
        LLG_noFill(ctx);
        LLG_setStroke(ctx, LLG_RGB(60, 100, 60));
        LLG_setStrokeWidth(ctx, 1);
        LLG_drawRect(ctx, (LLGRect){100, y - h, w, h});

        /* draw baseline marker */
        LLG_setStroke(ctx, LLG_RGB(80, 80, 150));
        LLG_drawLine(ctx, 100, y, 100 + w, y);

        /* draw the actual text */
        LLG_setStroke(ctx, LLG_RGB(240, 240, 240));
        LLG_drawText(ctx, 100, y, samples[i]);

        /* draw dimensions label */
        char dims[32];
        snprintf(dims, sizeof(dims), "%dx%d", w, h);
        LLG_setFont(ctx, "mono-12");
        LLG_setStroke(ctx, LLG_RGB(100, 180, 100));
        LLG_drawText(ctx, 110 + w, y, dims);
        LLG_setFont(ctx, "mono-14");

        y += 60;
    }

    /* legend */
    LLG_setFont(ctx, "mono-12");
    LLG_setStroke(ctx, LLG_RGB(60, 100, 60));
    LLG_drawText(ctx, 500, 160, "green box = bounding rect");
    LLG_setStroke(ctx, LLG_RGB(80, 80, 150));
    LLG_drawText(ctx, 500, 185, "blue line = baseline (y coord)");
    LLG_setStroke(ctx, LLG_RGB(100, 180, 100));
    LLG_drawText(ctx, 500, 210, "label     = width x height");
}

/* ------------------------------------------------------------------ */

void scene_layout(LLGContext *ctx) {
    /* centered title */
    LLG_setFont(ctx, "mono-bold-14");
    LLG_setStroke(ctx, LLG_RGB(255, 200, 50));

    const char *title = "Text Layout Patterns";
    int tw = 0, th = 0;
    LLG_textSize(ctx, title, &tw, &th);
    LLG_drawText(ctx, (WIN_W - tw) / 2, 55, title);

    LLG_setStroke(ctx, LLG_RGB(80, 80, 80));
    LLG_drawLine(ctx, 60, 70, 740, 70);

    /* left aligned block */
    LLG_setFont(ctx, "mono-12");
    LLG_setStroke(ctx, LLG_RGB(200, 200, 200));
    const char *left_lines[] = {
        "Left aligned text",
        "Each line starts at x=60",
        "Simple and predictable",
        NULL
    };
    int y = 110;
    for (int i = 0; left_lines[i] != NULL; i++) {
        LLG_drawText(ctx, 60, y, left_lines[i]);
        y += 22;
    }

    /* right aligned block */
    LLG_setStroke(ctx, LLG_RGB(180, 220, 255));
    const char *right_lines[] = {
        "Right aligned text",
        "Each line ends at x=740",
        "Width measured per line",
        NULL
    };
    y = 110;
    for (int i = 0; right_lines[i] != NULL; i++) {
        int lw = 0;
        LLG_textSize(ctx, right_lines[i], &lw, NULL);
        LLG_drawText(ctx, 740 - lw, y, right_lines[i]);
        y += 22;
    }

    /* centered block */
    LLG_setStroke(ctx, LLG_RGB(180, 255, 180));
    const char *center_lines[] = {
        "Centered text",
        "Each line is individually centered",
        "Using textSize to compute x offset",
        NULL
    };
    y = 220;
    for (int i = 0; center_lines[i] != NULL; i++) {
        int lw = 0;
        LLG_textSize(ctx, center_lines[i], &lw, NULL);
        LLG_drawText(ctx, (WIN_W - lw) / 2, y, center_lines[i]);
        y += 22;
    }

    /* vertically centered single line */
    LLG_setFont(ctx, "mono-14");
    LLG_setStroke(ctx, LLG_RGB(255, 150, 80));
    const char *vcenter = "Vertically & horizontally centered";
    int vw = 0, vh = 0;
    LLG_textSize(ctx, vcenter, &vw, &vh);
    int cx = (WIN_W - vw) / 2;
    int cy = 380 + vh / 2;
    LLG_drawText(ctx, cx, cy, vcenter);

    /* box around the vertically centered text to prove it */
    LLG_noFill(ctx);
    LLG_setStroke(ctx, LLG_RGB(80, 80, 80));
    LLG_setStrokeWidth(ctx, 1);
    LLG_drawRect(ctx, (LLGRect){cx - 4, cy - vh, vw + 8, vh + 4});

    /* multiline paragraph with manual line wrapping */
    LLG_setFont(ctx, "mono-12");
    LLG_setStroke(ctx, LLG_RGB(150, 150, 150));
    const char *para[] = {
        "Manual line wrapping: split your string into",
        "an array of lines and draw each one offset",
        "by the line height returned from LLG_textSize.",
        NULL
    };
    y = 460;
    int lh = 0;
    LLG_textSize(ctx, "A", NULL, &lh);
    for (int i = 0; para[i] != NULL; i++) {
        LLG_drawText(ctx, 60, y, para[i]);
        y += lh + 6;
    }
}

/* ------------------------------------------------------------------ */

int main(void) {
    LLGContext *ctx = LLG_init("LLG Text Examples", WIN_W, WIN_H);
    if (ctx == NULL) {
        printf("init failed: %s\n", LLG_errorStr(LLG_getError()));
        return 1;
    }

    LLG_setBackground(ctx, LLG_RGB(22, 22, 22));
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