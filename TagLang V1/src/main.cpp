#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "lexer.h"
#include "lexer.cpp"         
#include "label_dispatcher.h"
#include "codegen/cpp_generator.h"

void printUsage(const char* prog) {
    std::cerr << "TagLang Compiler v1.0\n\n";
    std::cerr << "Usage:\n";
    std::cerr << "  " << prog << " <source.tl> [options]\n\n";
    std::cerr << "Options:\n";
    std::cerr << "  -o <file>    Output C++ file (default: out.cpp)\n";
    std::cerr << "  --tokens     Print token list and exit\n";
    std::cerr << "  --help       Show this help\n\n";
    std::cerr << "Example:\n";
    std::cerr << "  " << prog << " examples/hello.tl -o hello.cpp\n";
    std::cerr << "  g++ hello.cpp -o hello && hello\n";
}

std::string readFile(const std::string& path) {
    std::ifstream f(path);
    if (!f.is_open())
        throw std::runtime_error("Cannot open file: " + path);
    std::ostringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

void writeFile(const std::string& path, const std::string& content) {
    std::ofstream f(path);
    if (!f.is_open())
        throw std::runtime_error("Cannot write file: " + path);
    f << content;
}

int main(int argc, char* argv[]) {
    if (argc < 2) { printUsage(argv[0]); return 1; }

    std::string inputFile;
    std::string outputFile = "out.cpp";
    bool printTokens = false;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--help" || arg == "-h") { printUsage(argv[0]); return 0; }
        else if (arg == "--tokens") printTokens = true;
        else if (arg == "-o" && i+1 < argc) outputFile = argv[++i];
        else if (arg[0] != '-') inputFile = arg;
        else { std::cerr << "Unknown option: " << arg << "\n"; return 1; }
    }

    if (inputFile.empty()) {
        std::cerr << "Error: No input file specified.\n";
        printUsage(argv[0]);
        return 1;
    }

    try {
  
        std::string source = readFile(inputFile);
        std::cout << "[TagLang] Compiling: " << inputFile << "\n";

        Lexer lexer(source);
        auto tokens = lexer.tokenize();

        if (printTokens) {
            std::cout << "\n=== TOKENS ===\n";
            for (auto& t : tokens)
                std::cout << "  [" << t.typeStr() << "] " << t.value
                          << "  (line " << t.line << ")\n";
            return 0;
        }

        LabelDispatcher dispatcher(tokens);
        auto program = dispatcher.dispatch();

        CppGenerator gen;
        std::string cppCode = gen.generate(*program);

        writeFile(outputFile, cppCode);
        std::cout << "[TagLang] Output written to: " << outputFile << "\n";
        std::cout << "[TagLang] Compile with: g++ " << outputFile
                  << " -o program -lm\n";

    } catch (const std::exception& e) {
        std::cerr << "\n[TagLang ERROR] " << e.what() << "\n";
        return 1;
    }

    return 0;
}
