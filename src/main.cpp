#include "core/application.h"
#include "core/logger.h"
#include <iostream>
#include <exception>

int main(int argc, char* argv[]) {
    try {
        AutoCoder::Core::Application app(argc, argv);

        auto logger = app.getLogger();
        logger->info("AutoCoder starting...");
        logger->info("Version: 1.0.0");
        logger->info("Self-Improving AI-Powered Code Generator");

        return app.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown fatal error occurred" << std::endl;
        return 1;
    }
}
