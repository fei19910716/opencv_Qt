
#pragma once

#include <qDebug>

class LogManager{
 public:
  LogManager() = default;
  ~LogManager() = default;

  static LogManager &getInstance() {
    static LogManager instance;
    return instance;
  }

  static void init() {
    // 重定向SDK日志
    LogManager::getInstance().install();
  }

  static void destroy() { logShutdown(); }


  void setupLog4QT();

  static void logStartup();

  static void logShutdown();

 private:
  void install();
};
