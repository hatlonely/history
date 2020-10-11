//
//  greeter_client.cpp
//  cpp_proj_sample
//
//  Created by hatlonely on 2018/1/4.
//

#include <iostream>
#include <grpc/grpc.h>
#include <grpc++/grpc++.h>
#include "greeter.grpc.pb.h"

int main(int argc, const char* argv[]) {
    if (argc < 3) {
        std::cout << argv[0] << " <address> <name> " << std::endl;
        return 0;
    }
    
    auto channel = grpc::CreateChannel(argv[1], grpc::InsecureChannelCredentials());
    std::unique_ptr<Greeter::Stub> stub = Greeter::NewStub(channel);
    grpc::ClientContext context;
    HelloRequest request;
    HelloReply response;

    request.set_name(argv[2]);
    if (!stub->SayHello(&context, request, &response).ok()) {
        std::cout << "SayHello failed." << std::endl;
        return -1;
    }

    std::cout << response.DebugString() << std::endl;
}
