#include <vector>
#include <string>
#include <random>

class HelloWords {
public:
    explicit HelloWords();

    int addWords(const std::string& path, const std::string& type);
    const std::string& helloWords();

private:
    std::vector<std::string> _words;

    std::mt19937_64 _mt;
    std::uniform_int_distribution<unsigned> _dis;
};
