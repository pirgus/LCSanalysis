#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

const int BLANK = -1;

int lcs (std::vector<char>& string_1,std::vector<char>& string_2,
                           int size_1, int size_2, 
                           std::vector<std::vector<int>>& table)
{
    if(size_1 == 0 || size_2 == 0)
        return 0;

    if(table[size_1][size_2] == BLANK){
        if (string_1[size_1 - 1 ] == string_2[size_2 - 1]){
            table[size_1][size_2] = 1 + lcs(string_1, string_2, size_1 - 1, size_2 - 1, table);
        }else{
            table[size_1][size_2] = std::max(lcs(string_1, string_2, size_1 - 1, size_2, table),
                                             lcs(string_1, string_2, size_1, size_2 - 1, table));
        }
    }

    return table[size_1][size_2];
}

int LCS(std::vector<char>& string_1,std::vector<char>& string_2,
        int size_1, int size_2)
{
    std::vector<std::vector<int>> table(size_1 + 1, std::vector<int>(size_2 + 1, BLANK));
    int lcs_size = lcs(string_1, string_2, size_1, size_2, table);
    return lcs_size;
}

int main(int argc, char **argv){

    std::string file_name = "entries/Strings" + std::string(argv[1]) + ".txt";
    std::ifstream input_file(file_name);
    int string_size = atoi(argv[1]);

    std::vector<char> chars;

    std::cout << "Reading entries... \n";

    //read characteres ignoring invalid caracters
    char temp = input_file.get();
    while(temp != EOF){
        if(temp >= 'A' && temp <= 'Z'){
            chars.push_back(temp);
        }
        temp = input_file.get();
    }

    std::cout << "done \n";
    std::cout << "Creating substrings... \n";

    //creating the substrings
    std::vector<char> s1(chars.begin(), chars.begin() + string_size);
    std::vector<char> s2(chars.begin() + string_size, chars.end());

    std::cout << "done \n";

    std::cout << "Calculating LCS value... \n"; 

    const auto start{std::chrono::steady_clock::now()};
    int lcs_value = LCS(s1, s2, s1.size(), s2.size());
    const auto end{std::chrono::steady_clock::now()};

    auto total_time = start - end;

    std::cout << "done \n";
    std::cout << "LCS value is " << lcs_value << "\n";
    std::cout << "Time for processing the function: " << std::chrono::seconds(total_time).count() << "\n";
    input_file.close();
    return 0;
}