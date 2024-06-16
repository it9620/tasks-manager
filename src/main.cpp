#include <userver/engine/run.hpp>
#include <userver/http/server.hpp>

int main(int argc, char* argv[]) {
    userver::engine::run(argc, argv, [] {
        userver::http::Server server;
        server.SetPort(8080);
        server.AddHandler("/hello", [](const auto& request) {
            return userver::http::Response(200, "Hello, world!");
        });
        server.Run();
    });
    return 0;
}
