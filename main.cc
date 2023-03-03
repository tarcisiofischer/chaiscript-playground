#define CHAISCRIPT_NO_THREADS
#define CHAISCRIPT_NO_DYNLOAD
#include <chaiscript/chaiscript.hpp>

#include <iostream>
#include <chrono>

int main()
{
    // Is it cheap to create ChaiScripts? (It is not! This loop takes ~3s on my machine with only 100 iterations)
    {
        auto start = std::chrono::steady_clock::now();
        for (auto i = 0; i < 100; ++i) {
            chaiscript::ChaiScript chai;
            (void) chai;
        }
        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Elapsed time: " << elapsed << " ms" << std::endl;
    }

    // Is it cheap to eval a simple function? (Loop below takes ~4s with 100000 iterations)
    {
        auto start = std::chrono::steady_clock::now();
        chaiscript::ChaiScript chai;
        chai.eval("var x = 1;");
        for (auto i = 0; i < 100000; ++i) {
            chai.eval("x = 1;");
        }
        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Elapsed time: " << elapsed << " ms" << std::endl;
    }

    // Is it cheap to run the same from file? (Loop below takes ~5s with 100000 iterations)
    {
        auto start = std::chrono::steady_clock::now();
        chaiscript::ChaiScript chai;
        chai.eval("var x = 1;");
        for (auto i = 0; i < 100000; ++i) {
            chai.eval_file("test1.chai");
        }
        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Elapsed time: " << elapsed << " ms" << std::endl;
    }

    // Is it cheap to send simple variables and get return values? (Loop below takes ~5s with 100000 iterations)
    {
        auto start = std::chrono::steady_clock::now();
        chaiscript::ChaiScript chai;
        chai.eval_file("test2.chai");
        for (auto i = 0; i < 100000; ++i) {
            auto r = chai.eval<double>("some_f(" + std::to_string(i) + ")");
            (void) r;
        }
        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Elapsed time: " << elapsed << " ms" << std::endl;
    }
}
