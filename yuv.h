#ifndef YUV_H
#define YUV_H

#include <stdio.h>
#include <stdint.h>
#include <cv.h>

enum YUV_ReturnValue
{
    YUV_OK = 0,
    YUV_PARAMETER_ERROR,
    YUV_OUT_OF_MEMORY,
    YUV_IO_ERROR,
    YUV_EOF
};

struct YUV_Capture
{
    FILE *fin;
    size_t width;
    size_t height;
    
    IplImage *y;
    IplImage *cb;
    IplImage *cr;
    IplImage *cb_half;
    IplImage *cr_half;
    IplImage *ycrcb;

    uint8_t *buf;
};

enum YUV_ReturnValue
YUV_init(FILE *fin, size_t w, size_t h, struct YUV_Capture *out);

enum YUV_ReturnValue
YUV_read(struct YUV_Capture *cap);

void
YUV_cleanup(struct YUV_Capture *cap);

#endif
