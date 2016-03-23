/*
日志
 */
#ifndef GLOG_H
#define GLOG_H 

#include <libgen.h>
/**
 * 日志等级
 */
enum GLOGLEVEL
{
	GLOG_ERR = 0,
	GLOG_DBG = 1,
	GLOG_MSG = 2
};

/**
 * 日志结构
 */
typedef struct _log_t
{
	int level;
	char path[0];
}log_t;


#define GLogInit(path, level) init(path, level)

#define GlogGetPath() getpath()

/**
 * 错误、调试、提示
 */
#define GLogErr(msg,...)  log2file("[FILE:%s][LINE:%d][ERR]:"msg,basename(__FILE__),__LINE__, ##__VA_ARGS__)
#define GLogDbg(msg,...)  log2file("[FILE:%s][LINE:%d][DBG]:"msg,basename(__FILE__),__LINE__, ##__VA_ARGS__)
#define GLogMsg(msg,...)  log2file("[FILE:%s][LINE:%d][MSG]:"msg,basename(__FILE__),__LINE__, ##__VA_ARGS__)


unsigned int init(char* path, int level);

char* getpath();

void log2file(const char *format, ...);

#endif