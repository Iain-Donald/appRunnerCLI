#include "appRunner.hpp"

#include <iostream>
#include <string>

int main(int argc, char* argv[]){
    
    bool runRunner = true;
    AppRunner runner("apps.txt");
    runner.loadApps();

    std::string help;
    help = R"(Commands:
                add <app> <alias>
                run <app> <params>
                <app>\n)";

    if(argc == 1){
        std::cout << help;
        return 0;
    } else if (argc == 2){
        if(std::string(argv[1]) == "help") std::cout << help;
        if(std::string(argv[1]) == "motorcycle") std::cout << "motorcycle: sv650";
        return 0;
    }

    std::vector<std::string> params;
    for (int i = 3; i < argc; i++){
        params.push_back(argv[i]);
    }
    
    std::string command = argv[1];
    std::string appname = argv[2];

    if(command == "add") {
        if(argc < 4){
            std::cout << "Usage: add <app> <alias>\n";
            return 0;
        }

        runner.addApp(argv[2], argv[3]);
        std::cout << "App added\n";

    } else if(command == "run" || command == "r") {
        runner.runApp(appname, params);
    }

    return 0;
}