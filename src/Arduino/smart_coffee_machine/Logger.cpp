#include "Logger.h"
#include "MsgService.h"

void Logger::log(String message){
  MsgService.sendMsg("lo:" + message);
}
