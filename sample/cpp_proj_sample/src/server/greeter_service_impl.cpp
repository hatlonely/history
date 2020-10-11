//
//  greeter_service_imp.cpp
//  cpp_proj_sample
//
//  Created by hatlonely on 2018/1/4.
//

#include <grpc++/grpc++.h>
#include "greeter_service_impl.hpp"
#include "logger.hpp"

namespace hl {
    
    grpc::Status GreeterServiceImpl::SayHello(grpc::ServerContext* context, const HelloRequest* request, HelloReply* response) {
        std::string prefix("Hello ");
        response->set_message(prefix + request->name());
        ACCESS(request->ShortDebugString() << "\t" << response->ShortDebugString());
        return grpc::Status::OK;
    }

    int GreeterServer::Init(const libconfig::Setting& setting) {
        address = setting.lookup("address").c_str();
        return 0;
    }

    int GreeterServer::Run() {
        std::string serverAddress(address);
        GreeterServiceImpl service;
        
        grpc::ServerBuilder builder;
        builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);
        std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
        INFO("server listening on " << serverAddress);
        server->Wait();
        
        return 0;
    }
}
