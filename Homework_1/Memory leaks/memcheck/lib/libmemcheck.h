/*
# Course: MP-6171 High Performance Embedded Systems
# Tecnologico de Costa Rica (www.tec.ac.cr)
# Developer Names:
# 	Eliecer Mora (eliecer@estudiantec.cr)
#	Sergio Guillen (guillen_sergio@hotmail.com)
# General purpose: Header for the returning functions;
*/

#ifndef _LIB_MEM_CHECK_H
#define _LIB_MEM_CHECK_H

#define _GNU_SOURCE

#include <ctype.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void* (*realMalloc)(size_t) = NULL;
static void* (*realFree)(void *) = NULL;
static void* (*realRealloc)(void *, size_t) = NULL;
static void* (*realCalloc)(size_t, size_t) = NULL;

#endif

