//
//  greeter_service_imp.hpp
//  cpp_proj_sample
//
//  Created by hatlonely on 2018/1/4.
//

#pragma once

#include "greeter.grpc.pb.h"
#include <grpc/grpc.h>
#include <libconfig.h++>
#include <string>

namespace hl {
    class GreeterServiceImpl final : public Greeter::Service {
    public:
        grpc::Status SayHello(grpc::ServerContext* context, const HelloRequest* request, HelloReply* response);
    };
    
    class GreeterServer final {
    public:
        int Init(const libconfig::Setting& setting);
        int Run();
        
    private:
        std::string address;
    };
}

