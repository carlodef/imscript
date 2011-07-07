#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "iio.h"

#define xmalloc malloc

int main(int c, char *v[])
{
	if (c != 1 && c != 2 && c != 3) {
		fprintf(stderr, "usage:\n\t%s [in [out]]\n", *v);
		//                          0  1   2
		return EXIT_FAILURE;
	}
	char *in = c > 1 ? v[1] : "-";
	char *out = c > 2 ? v[2] : "-";

	int w, h, pd;
	float *x = iio_read_image_float_vec(in, &w, &h, &pd);
	if (pd != 2) return -1;
	float *y = xmalloc(w*h*sizeof*y);
	for (int i = 0; i < w * h; i++)
		y[i] = hypot(x[2*i], x[2*i+1]);
	iio_save_image_float_vec(out, y, w, h, 1);
	return EXIT_SUCCESS;
}