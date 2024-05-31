#include <stddef.h>
#include "data.h"

static const char *shaders[] = {
    "\n",
    "\n",
};

const char *data_get_shader(unsigned char shader)
{
    if (shader >= SHADER_COUNT)
        return NULL;
    return shaders[shader];
}