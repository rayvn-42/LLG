#pragma once

typedef struct LLGContext LLGContext;

typedef enum {
    LLG_EVENT_NONE = 0,
    LLG_EVENT_KEY_PRESS,
    LLG_EVENT_KEY_RELEASE,
    LLG_EVENT_MOUSE_PRESS,
    LLG_EVENT_MOUSE_RELEASE,
    LLG_EVENT_MOUSE_MOVE,
    LLG_EVENT_MOUSE_SCROLL,
    LLG_EVENT_RESIZE,
    LLG_EVENT_CLOSE,
    LLG_EVENT_EXPOSE,
} LLGEventType;

typedef struct {
    LLGEventType type;
    union {
        struct {int key; int mod;} key;
        struct {int x, y; int button; int mod;} mouse;
        struct {int dx, dy;} scroll;
        struct {int width, height;} resize;
    };
} LLGEvent;

int     LLG_waitEvent(LLGContext *ctx, LLGEvent *event);
int     LLG_pollEvent(LLGContext *ctx, LLGEvent *event);
int     LLG_keyDown(const LLGContext *ctx, int key);
int     LLG_mouseDown(const LLGContext *ctx, int button);
void    LLG_mousePos(const LLGContext *ctx, int *x, int*y);