#ifndef EZFILE_H
#define EZFILE_H

#include "vec.h"

#include "eztypes.h"

strvec_t ezfile_read(const char* path);

void ezfile_write(const char* path, const char* data);

void ezfile_append(const char* path, const char* data);

void ezfile_delete(const char* path);

#endif // EZFILE_H