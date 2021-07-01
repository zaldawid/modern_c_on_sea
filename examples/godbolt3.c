// -std=c17 -O0 -Wall -Wextra -pedantic

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

typedef enum blur_type {
    box,
    gauss
} blur_type;

typedef struct blur_params {
    size_t width;
    blur_type type;
    int compute_hw;
    _Bool in_place;
} blur_params_s;

typedef struct image{ int data[1]; } image_s;

image_s* _blur(image_s* img, blur_params_s params){
    // initializes a new image 
    // with a value of width * old image's data
    img->data[0] *= params.width;
    return img;
}

#define DEF_ARGS_ON \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Woverride-init\"")

#define DEF_ARGS_OFF \
    _Pragma("GCC diagnostic pop")

#if defined(__clang__)

#define blur(img, ...) \
    DEF_ARGS_ON \
    _blur((img), (blur_params_s){.width=64, __VA_ARGS__}) \
    DEF_ARGS_OFF

#elif defined(__GNUC__)

// _Pragma("GCC diagnostic ignored \"-Woverride-init\"")

#define blur(img, ...) \
  _blur((img), (blur_params_s){.width=64, __VA_ARGS__});

#endif

int main(void){
    image_s img = {{10}};

    printf("Before blur (default): %d\n", img.data[0]);
    blur(&img, .in_place=true);
    printf("After blur (default): %d\n", img.data[0]);

    img = (image_s){{10}};
    printf("Before blur (manual): %d\n", img.data[0]);
    blur(&img, .in_place=true, .width=42);
    printf("After blur (manual): %d\n", img.data[0]);


    return img.data[0];
}

