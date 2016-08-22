/*
* 	file:glog.h
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
#define GLogErr(msg,...)  log2file("[%s:%d][ERR]:"msg,basename(__FILE__),__LINE__, ##__VA_ARGS__)
#define GLogDbg(msg,...)  log2file("[%s:%d][DBG]:"msg,basename(__FILE__),__LINE__, ##__VA_ARGS__)
#define GLogMsg(msg,...)  log2file("[%s:%d][MSG]:"msg,basename(__FILE__),__LINE__, ##__VA_ARGS__)

/**
 * [全局日志结构的初始化]
 * @param  path  [日志路径]
 * @param  level [日志等级]
 * @return       [0:succ;1:fail]
 */
unsigned int init(char* path, int level);

/**
 * [获取日志路径]
 * @return [日志路径]
 */
char* getpath();

/**
 * [写日志]
 */
void log2file(const char *format, ...);

#endif