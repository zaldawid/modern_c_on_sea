// -std=c17 -O0 -Wall -Wextra -pedantic

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

typedef struct Point2D {
    double x, y;
} Point2D_s;

typedef struct Circle {
    Point2D_s center;
    double radius;
} Circle_s;

typedef struct Rectangle {
    Point2D_s center;
    double w, h;
} Rectangle_s;

void scale_circ_1p(Circle_s* c, double scale){
    c->radius *= scale;
}

void scale_rect_1p(Rectangle_s* r, double scale){
    r->w *= scale;
    r->h *= scale;
}

void scale_rect_2p(Rectangle_s* r, double wscale, double hscale){
    r->w *= wscale;
    r->h *= hscale;
}

#define scale2p(obj, ...) \
    _Generic( (obj), \
        Rectangle_s* : scale_rect_2p \
    )((obj), __VA_ARGS__)

#define scale1p(obj, ...) \
    _Generic( (obj), \
        Rectangle_s* : scale_rect_1p, \
        Circle_s* : scale_circ_1p \
     )((obj), __VA_ARGS__)


#define INVOKE(_1, _2, _3, NAME, ...) NAME
#define scale(...) INVOKE(__VA_ARGS__, scale2p, scale1p,)(__VA_ARGS__)

int main(void){
    Circle_s circ = {{4, 3}, 2};
    Rectangle_s rect = {{1, 2}, 5, 10};

    scale(&circ, 20);

    scale(&rect, 2, 3);
    scale(&rect, 2);

}
