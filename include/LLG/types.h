#pragma once

#include <stdint.h>

// RGBA colors type(s)
typedef struct {
    uint8_t r, g, b, a;
} LLGColor;

// Geometrical shapes type(s)
typedef struct {
    int x, y;
} LLGPoint;

typedef struct {
    int x, y;
    int width, height;
} LLGRect;

typedef struct {
    int x, y;
    int rx, ry;
} LLGEllipse;

typedef struct {
    LLGPoint* points;
    int count;
} LLGPolygon;

// Geometrical constructors
#define LLG_Point(x, y) ((LLGPoint){x, y})
#define LLG_Rect(x, y, width, height) ((LLGRect){x, y, width, height})
#define LLG_Ellipse(x, y, rx, ry) ((LLGEllipse){x, y, rx, ry})
#define LLG_Polygon(points, count) ((LLGPolygon){points, count})

// Draw state
typedef struct {
    LLGColor    fillColor;
    LLGColor    strokeColor;
    int         fillEnabled;
    int         strokeEnabled;
} LLGDrawState;

typedef enum {
    LLG_ERR_SEVERITY_OK,
    LLG_ERR_SEVERITY_RECOVERABLE,
    LLG_ERR_SEVERITY_FATAL,
} LLGSeverity;

// Error type(s)
typedef enum {
    LLG_OK = 0,
    LLG_ERR_DISPLAY,
    LLG_ERR_WINDOW,
    LLG_ERR_GC,
    LLG_ERR_ALLOC,
    LLG_ERR_COLOR,
    LLG_ERR_FONT,
    LLG_ERR_BADARG,
    LLG_ERR_ATOM,
    LLG_ERR_CURSOR,
    LLG_ERR_DRAWABLE,
    LLG_ERR_UNKNOWN,
} LLGError;

extern const LLGSeverity LLG__errorSeverity[];

extern const char *LLG__errorStrings[];