
#pragma once

#include <string>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/loggingmacros.h>

#ifndef PRINT
#ifndef NO_DEBUG
#define PRINT(info) LOG4CPLUS_DEBUG(::hl::Logger::Instance().DebLogger, info)
#else
#define PRINT(info) do {} while(0)
#endif
#endif

#ifndef INFO
#define INFO(info) LOG4CPLUS_INFO(::hl::Logger::Instance().WokLogger, info)
#endif

#ifndef WARN
#define WARN(info) LOG4CPLUS_WARN(::hl::Logger::Instance().WokLogger, info)
#endif

#ifndef ACCESS
#define ACCESS(info) LOG4CPLUS_WARN(::hl::Logger::Instance().AccLogger, info)
#endif

namespace hl {
    
    class Logger {
    public:
        log4cplus::Logger WokLogger;
        log4cplus::Logger AccLogger;
        log4cplus::Logger DebLogger;
        
        static Logger& Instance() {
            static Logger instance;
            return instance;
        }
        
        int Init(const std::string& logini) {
            log4cplus::PropertyConfigurator config(LOG4CPLUS_C_STR_TO_TSTRING(logini));
            config.configure();
            if (!log4cplus::Logger::exists(LOG4CPLUS_C_STR_TO_TSTRING("acclog")) ||
                !log4cplus::Logger::exists(LOG4CPLUS_C_STR_TO_TSTRING("woklog")) ||
                !log4cplus::Logger::exists(LOG4CPLUS_C_STR_TO_TSTRING("deblog"))) {
                std::cerr << "log4cplus init failed. [info | warn | deblog] logger not found" << std::endl;
                return -1;
            }
            
            if (log4cplus::Logger::exists(LOG4CPLUS_C_STR_TO_TSTRING("acclog"))) {
                log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_C_STR_TO_TSTRING("acclog"));
                Instance().AccLogger = logger;
            }
            if (log4cplus::Logger::exists(LOG4CPLUS_C_STR_TO_TSTRING("woklog"))) {
                log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_C_STR_TO_TSTRING("woklog"));
                Instance().WokLogger = logger;
            }
            if (log4cplus::Logger::exists(LOG4CPLUS_C_STR_TO_TSTRING("deblog"))) {
                log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_C_STR_TO_TSTRING("deblog"));
                Instance().DebLogger = logger;
            }
            
            return 0;
        }
        
    private:
        Logger() = default;
        Logger(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator =(const Logger&) = delete;
        Logger& operator =(Logger&&) = delete;
        ~Logger() = default;
    };
    
}
