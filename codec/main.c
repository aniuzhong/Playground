#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main()
{
    int width, height, num_components;
    unsigned char* data = stbi_load("/workspaces/Playground/codec/z_char_8x8.png",
                                    &width, &height, &num_components, 1);
    if (!data) {
        puts("Couldn't open file.");
        return 1;
    }

    printf("width:%d, height:%d, num_components:%d\n", width, height, num_components);

    uint32_t* result = malloc(width * height);
    memset(result, 0, width * height * sizeof(uint32_t));

    int i, j;

    // for (int c = 0; c < num_components; ++c) {
    //     for (i = 0; i < width; ++i)
    //         for (j = 0; j < height; ++j)
    //             result[i * width + j] += data[i * width + j];
    //     i = j = 0;
    // }

    for (i = 0; i < width; ++i) {
        for (j = 0; j < height; ++j) {
            printf("%d\t", data[i * width + j] > 128 ? 1 : 9999);
        }
        printf("\n");
    }

    return 0;
}