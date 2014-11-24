#include <string>
#include <fstream>
#include <random>
#include <bitset>
#include <iostream>
#include <iomanip>
#include <cstdio>

auto genInt = [](auto writeFile)
{
    std::bitset<10'000'000> bs; // 1,250,000 bytes
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 9'999'999);
    std::mt19937 g{rd()};

    std::cout << sizeof(bs) << std::endl;

    for (int i = 0; i < 1'000'000; ++i)
    {
        while(true)
        {
            auto val = dist(g);

            if (bs[val] == true)
            {
                continue;
            }
            else
            {
                bs[val] = true;
                writeFile(val);
                break;
            }
        }
    }
};


int main()
{
    static std::string filename {R"(/tmp/record.txt)"};

    std::remove(filename.c_str());

    static std::fstream fs{filename, std::ios::out};

    auto writer = [](const auto& val)
    {
        fs << std::setfill('0') << std::setw(7) << val << '\n';
    };

    genInt(writer);

    fs.close();
}
