#ifndef OPENGL_PRAKTIKUM_CUBE_H
#define OPENGL_PRAKTIKUM_CUBE_H



static const float cubeVert[] =  {0.5, -0.5, -0.5, 1, 0, 0,
                                  0.5, -0.5, 0.5, 0, 1, 0,
                                  -0.5, -0.5, 0.5, 0, 0, 1,
                                  -0.5, -0.5, -0.5, 1, 1, 0,
                                  0.5, 0.5, -0.5, 1, 0, 1,
                                  0.5, 0.5, 0.5, 0, 1, 1,
                                  -0.5, 0.5, 0.5, 1, 1, 1,
                                  -0.5, 0.5, -0.5, 0.5, 1, 0.5};

static const int cubeInd[] = {1, 2, 3,
                              7, 6, 5,
                              4, 5, 1,
                              5, 6, 2,
                              2, 6, 7,
                              0, 3, 7,
                              0, 1, 3,
                              4, 7, 5,
                              0, 4, 1,
                              1, 5, 2,
                              3, 2, 7,
                              4, 0, 7};



#endif //OPENGL_PRAKTIKUM_CUBE_H