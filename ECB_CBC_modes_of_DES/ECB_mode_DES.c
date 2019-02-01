#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"
#include "des_encrypt.c"

int main(int argc, char **argv)
{
    char *filename;
    int key[64], pixel[8], tmp[64], encrypted_tmp[64];

    if (argc == 1)
    {
        printf("filename: ");
        filename = (char *)malloc(20);
        scanf("%s", filename);
    }
    else
        filename = argv[1];

    genkey(key, 64);
    printf("generated key: ");
    print(key, 64);

    Image *img = ImageRead(filename);

    for (int j = 0; j < img->height; j++)
    {
        for (int i = 0; i < img->width; i += 8)
        {

            int k, t = (img->width - i < 8) ? img->width - i : 8;
            for (k = 0; k < t; k++)
                pixel[k] = ImageGetPixel(img, i + k, j, 0);
            for (; k < 8; k++)
                pixel[k] = 0;

            intto64bitstring(pixel, tmp, 64, t);
            encrypt(tmp, key, encrypted_tmp);
            bitstringtoint(pixel, encrypted_tmp, 64, t);

            for (k = 0; k < 8; k++)
            {
                ImageSetPixel(img, i + k, j, 0, pixel[k]);
                ImageSetPixel(img, i + k, j, 1, pixel[k]);
                ImageSetPixel(img, i + k, j, 2, pixel[k]);
            }
        }
    }
    ImageWrite(img, "image_after_ECB.ppm");

    return 0;
}
