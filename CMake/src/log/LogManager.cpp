
#include "LogManager.h"
#include "log4qt/consoleappender.h"
#include "log4qt/dailyrollingfileappender.h"
#include "log4qt/logger.h"
#include "log4qt/loggerrepository.h"
#include "log4qt/logmanager.h"
#include "log4qt/rollingfileappender.h"
#include "log4qt/ttcclayout.h"

#include <QCoreApplication>

void LogManager::install() {
  setupLog4QT();
  logStartup();
//  google::AddLogSink(&LogManager::getInstance());
}

void LogManager::setupLog4QT() {
  // Create a layout
  auto logger = Log4Qt::Logger::rootLogger();
  auto *layout = new Log4Qt::TTCCLayout();
  layout->setName(QStringLiteral("Log Layout"));
  layout->setDateFormat(Log4Qt::TTCCLayout::DateFormat::ISO8601);
  layout->setThreadPrinting(false);
  layout->activateOptions();

  // 打印到控制台
  auto *consoleAppender =
      new Log4Qt::ConsoleAppender(layout, Log4Qt::ConsoleAppender::STDOUT_TARGET);
  consoleAppender->setName(QStringLiteral("Console Appender"));
  consoleAppender->activateOptions();
  logger->addAppender(consoleAppender);

  // 打印到文件
  // 日志存储路径
  QString logFilePath = QCoreApplication::applicationDirPath() + "/log/application.log";
  //  auto *fileAppender = new Log4Qt::DailyRollingFileAppender();
  //  fileAppender->setName(QStringLiteral("File appender"));
  //  fileAppender->setLayout(layout);
  //  fileAppender->setFile(logFilePath);
  //  // 按天新建日志文件
  //  fileAppender->setDatePattern(Log4Qt::DailyRollingFileAppender::DAILY_ROLLOVER);
  //  fileAppender->activateOptions();
  //  logger->addAppender(fileAppender);

  auto *fileAppender = new Log4Qt::RollingFileAppender(layout, logFilePath, true);
  fileAppender->setName(QStringLiteral("File appender"));
  fileAppender->setMaxFileSize("10mb");  //单个日志文件最大存储容量
  fileAppender->setMaxBackupIndex(20);
  fileAppender->activateOptions();
  logger->addAppender(fileAppender);

  logger->setLevel(Log4Qt::Level::ALL_INT);
  Log4Qt::LogManager::setHandleQtMessages(true);
}

void LogManager::logStartup() {
  auto logger = Log4Qt::Logger::rootLogger();
  logger->info(QStringLiteral("################################################################"));
  logger->info(QStringLiteral("#                     Application START                        #"));
  logger->info(QStringLiteral("################################################################"));
}

void LogManager::logShutdown() {
  auto logger = Log4Qt::Logger::rootLogger();

  logger->info(QStringLiteral("################################################################"));
  logger->info(QStringLiteral("#                     Application STOP                         #"));
  logger->info(QStringLiteral("################################################################"));

  logger->removeAllAppenders();
  logger->loggerRepository()->shutdown();
}
