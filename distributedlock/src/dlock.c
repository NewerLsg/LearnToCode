#include "dlock.h"
#include <hiredis/hiredis.h>
#include <assert.h>
#include <string.h>


static int execReidsCommand(char* command){
	int ret;
	redisContext *c;
	redisReply *reply;

	c = redisConnect("127.0.0.1", 6379);

	/*连接失败*/
	if (c == NULL || c->err) {	
		printf("fail to connect to redis.err[%d]\n", c->err);
		return 1;
	}

	printf("%s\n", command);

	reply = (redisReply *)redisCommand(c, command);

	printf("type[%d], inter[%lld]\n", reply->type, reply->integer);

	/*执行失败*/
	if (reply->type != REDIS_REPLY_INTEGER || reply->integer != 1) {
		printf("fail to exec command.err[%s]", reply->str);
		freeReplyObject(reply);
		redisFree(c);
		return 1;		
	}		

	freeReplyObject(reply);
	redisFree(c);
	return 0;
}


int getLock(char* name)
{
	char cmdBuf[128] = {0};

	assert(name != NULL);

	snprintf(cmdBuf, sizeof(cmdBuf), "SETNX %s lock", name);

	return execReidsCommand(cmdBuf);
}

int releaseLock(char* name)
{
	char cmdBuf[128] = {0};

	assert(name != NULL);
	
	snprintf(cmdBuf, sizeof(cmdBuf), "DEL %s", name);

	return execReidsCommand(cmdBuf);
}

int testLock(char* name)
{
	char cmdBuf[128] = {0};

	assert(name != NULL);
	
	snprintf(cmdBuf, sizeof(cmdBuf), "EXISTS %s", name);

	return execReidsCommand(cmdBuf);
}