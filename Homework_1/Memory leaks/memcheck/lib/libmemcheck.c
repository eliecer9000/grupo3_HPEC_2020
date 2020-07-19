
#include <libmemcheck.h>

int mallocCount = 0;
int freeCount = 0;

void* malloc(size_t size){
  mallocCount++;
  //FILE *fptr = fopen("malloc.txt","w");
  //fprintf(fptr,"%d", mallocCount);
  //fclose(fptr);
  realMalloc = dlsym(RTLD_NEXT, "malloc");
  return realMalloc(size);
}

void free(void *pointer){
  freeCount++;
  //FILE *fptr = fopen("free.txt","w");
  //fprintf(fptr,"%d", freeCount);
  //fclose(fptr);
  realFree = dlsym(RTLD_NEXT, "free");
  realFree(pointer);
  return;
}

void* realloc(void *ptr, size_t size){
  realRealloc = dlsym(RTLD_NEXT, "realloc");
  return realRealloc(ptr, size);
}

void *calloc(size_t nitems, size_t size){
  realCalloc =  dlsym(RTLD_NEXT, "calloc");
  return realCalloc(nitems, size);
}

