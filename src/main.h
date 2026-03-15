// main.h
#pragma once

#include <stdlib.h>
#include <time.h>

#include <raylib.h>
#include <raygui.h>

typedef struct AppContext {
	Camera2D camera;
} AppContext;

#define ERROR_EXIT(fmt, ...) \
	do { \
		time_t now = time(NULL); \
		struct tm *tm_info = localtime(&now); \
		char time_buffer[20]; \
		strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", tm_info); \
		TraceLog(LOG_ERROR, "[%s] [%s:%d] " fmt, time_buffer, __FILE__, __LINE__, ##__VA_ARGS__); \
		exit(EXIT_FAILURE); \
	} while(0)
