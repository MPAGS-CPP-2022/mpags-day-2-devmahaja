#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "TransformChar.hpp"

bool processCommandLine(const std::vector<std::string>& args,
                        bool& helpRequested,
                        bool& versionRequested,
                        std::string& inputFileName,
                        std::string& outputFileName,
                        std::string& cipher_key,
                        bool& encrypt )
{
    const std::size_t nCmdLineArgs{args.size()};

    bool processedStatus(true);

    typedef std::vector<std::string>::size_type size_type;
    const size_type nArgs {args.size()};


    // Process command line arguments - ignore zeroth element, as we know this
    // to be the program name and don't need to worry about it
    for (std::size_t i{1}; i < nCmdLineArgs; ++i) {
        if (args[i] == "-h" || args[i] == "--help") {
            helpRequested = true;
        } else if (args[i] == "--version") {
            versionRequested = true;
        } else if (args[i] == "-i") {
            // Handle input file option
            // Next element is filename unless "-i" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -i requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return 1;
            } else {
                // Got filename, so assign value and advance past it
                inputFileName = args[i + 1];
                ++i;
            }
        } else if (args[i] == "-o") {
            // Handle output file option
            // Next element is filename unless "-o" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -o requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return 1;
            } else {
                // Got filename, so assign value and advance past it
                outputFileName = args[i + 1];
                ++i;
                std::string name {outputFileName};
                std::ofstream out_file {name};
                bool ok_to_write = out_file.good();
            }
        } else {
            // Have an unknown flag to output error message and return non-zero
            // exit status to indicate failure
            std::cerr << "[error] unknown argument '" << args[i]
                      << "'\n";
            return 1;
        }
    }

    // Warn that output file option not yet implemented
    if (!outputFileName.empty()) {
        std::cerr << "[warning] output to file ('" << outputFileName
                 << "') not implemented yet, using stdout\n";
    }

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }
    return true;
}


int main(int argc, char* argv[])
{
    
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};
    std::string cipher_key{""};
    bool encrypt{false};
    std::string name {""};
    bool okay_to_write{false};
    std::ofstream out_file;
    



    if (!processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile, cipher_key, encrypt)) {
        return 1;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }
    
    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

    // Read in user input from stdin/file
    // Warn that input file option not yet implemented
    if (!inputFile.empty()) {
        std::cerr << "[warning] input from file ('" << inputFile
                  << "') not implemented yet, using stdin\n";
    }

    while(std::cin >> inputChar){
        inputText += transformChar(inputChar);
    }
    
    if (okay_to_write = true){
        out_file.open(name);
        out_file << inputText;
    } else {
        std::cout << inputText << std::endl;  
    }
    

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}