/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

/*
 * Sort read-in 7 digits number with bitset
 */
#include <string>
#include <fstream>
#include <bitset>
#include <iostream>
#include <iomanip>
#include <cstdio>

auto sort_to = [](auto writeFile, auto& readFile)
{
    std::bitset<10'000'000> bs; // 1,250,000 bytes

    char tmp_val[8];

    while(!readFile.getline(tmp_val, 8).eof())
    {
        bs[std::stoi(tmp_val)] = true;
    }

    for(decltype(bs.size()) i = 0; i < bs.size() ; ++i)
    {
        if (bs[i])
        {
            writeFile(i);
        }
    }

};


int main()
{
    static std::string filename {R"(/tmp/record.txt)"};
    static std::string sorted_filename {R"(/tmp/sorted_record.txt)"};

    std::remove(sorted_filename.c_str());

    static std::fstream fs{filename, std::ios::in};
    static std::fstream sorted_fs{sorted_filename, std::ios::out};

    auto writer = [](const auto& val)
    {
        sorted_fs << std::setfill('0') << std::setw(7) << val << std::endl;
    };

    sort_to(writer, fs);


    fs.close();
    sorted_fs.close();
}
