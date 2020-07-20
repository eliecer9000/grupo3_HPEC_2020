
#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>

static void* (*realMalloc)(size_t) = NULL;
static void* (*realFree)(void *) = NULL;
static void* (*realRealloc)(void *, size_t) = NULL;
static void* (*realCalloc)(size_t, size_t) = NULL;

int mallocCount = 0;
int freeCount = 0;

void* malloc(size_t size){
  mallocCount++;
  //printf("Malloc count %d\n", mallocCount);
  //FILE *fptr = fopen("malloc.txt","w");
  //fprintf(fptr,"%d", mallocCount);
  //fclose(fptr);
  //realMalloc = dlsym(RTLD_NEXT, "malloc");
  return realMalloc(size);
}

void free(void *pointer){
  freeCount++;
  //printf("Free count %d\n", freeCount);
  //FILE *fptr = fopen("free.txt","w");
  //fprintf(fptr,"%d", freeCount);
  //fclose(fptr);
  realFree = dlsym(RTLD_NEXT, "free");
  realFree(pointer);
}

void* realloc(void *ptr, size_t size){
  realRealloc = dlsym(RTLD_NEXT, "realloc");
  return realRealloc(ptr, size);
}

void *calloc(size_t nitems, size_t size){
  realCalloc =  dlsym(RTLD_NEXT, "calloc");
  return realCalloc(nitems, size);
}

