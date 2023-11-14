#include "core.h"
#include "string.h"


const char *get_file_extencion(const char *file_name) {
  const char *dot = strrchr(file_name, '.');
  if (!dot || dot == file_name) {
    return NULL;
  }
  return dot;
}
