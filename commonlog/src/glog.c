/**
 *
 * 
 */

#include "glog.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>

log_t *g_log;

static void vlog2file(const char* path, const char* format,va_list vp);
static char* getTime();

unsigned int init(char* path, int level){

	g_log = (log_t *)malloc(sizeof(log_t) + 64);

	g_log->level = level;

	strncpy(g_log->path, path, 64);

	return 0;
}

char* getpath(){
	return g_log->path;
}

void log2file(const char *format, ...){
	va_list vp;

	va_start(vp,format);
	vlog2file(g_log->path,format,vp);
	va_end(vp);

	return;
}


static void vlog2file(const char* path, const char* format,va_list vp){

	FILE* fp = fopen(path, "a+");

	if(fp == NULL){
		return ;
	}

	fprintf(fp, "[%s][PID:%d]", getTime(), getpid());
	vfprintf(fp, format, vp);
	fprintf(fp, "\n");

	fclose(fp);
}

static char* getTime(){
	struct timeval now;
	struct tm *tm;
	size_t len = 0;
	static char timestr[64] = {0};

	gettimeofday(&now, NULL);

	tm = localtime(&now.tv_sec);

	len = strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", tm);

	snprintf(timestr + len, sizeof(timestr) -  len, ".%03.0f", now.tv_usec/(double)1000);

	return timestr;
}
