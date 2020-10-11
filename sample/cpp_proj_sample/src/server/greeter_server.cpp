#include <libconfig.h++>
#include "greeter_service_impl.hpp"
#include "logger.hpp"

int main(int argc, const char* argv[]) {
    libconfig::Config config;
    config.readFile("conf/greeter.cfg");
    
    if (hl::Logger::Instance().Init(config.lookup("logger").c_str()) != 0) {
        std::cerr << "logger init failed." << std::endl;
    }
    
    hl::GreeterServer greeterServer;
    if (greeterServer.Init(config.lookup("greeter")) != 0) {
        WARN("server init failed.");
    }
    
    INFO("greeter server init success.");
    
    if (greeterServer.Run() != 0) {
        WARN("server run failed.");
    }
}
