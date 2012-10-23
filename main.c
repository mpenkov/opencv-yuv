#include <stdlib.h>
#include <assert.h>
#include <highgui.h>

#include "yuv.h"

int
main(int argc, char **argv)
{
    int width;
    int height;
    FILE *fin = NULL;
    struct YUV_Capture cap;
    enum YUV_ReturnValue ret;
    IplImage *bgr;
    if (argc != 4)
    {
        fprintf(stderr, "usage: %s file.yuv width height\n", argv[0]);
        return 1;
    }
    width = atoi(argv[2]);
    height = atoi(argv[3]);
    if (width <= 0 || height <= 0)
    {
        fprintf(stderr, "error: bad frame dimensions: %d x %d\n", width, height);
        return 1;
    }
    fin = fopen(argv[1], "rb");
    if (!fin)
    {
        fprintf(stderr, "error: unable to open file: %s\n", argv[1]);
        return 1;
    }
    ret = YUV_init(fin, width, height, &cap);
    assert(ret == YUV_OK);

    bgr = cvCreateImage(cvSize(width,height), IPL_DEPTH_8U, 3);
    assert(bgr);

    for (; ;)
    {
        ret = YUV_read(&cap);
        if (ret == YUV_EOF)
        {
            cvWaitKey(0);
            break;
        }
        else if (ret == YUV_IO_ERROR)
        {
            fprintf(stderr, "I/O error\n");
            break;
        }
        cvCvtColor(cap.ycrcb, bgr, CV_YCrCb2BGR);
        cvShowImage(argv[1], bgr);
        cvWaitKey(35);
    }

    return 0;
}
