#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

int LCS(std::vector<char>& string_1,std::vector<char>& string_2,
                           int size_1, int size_2)
{
    
    if (size_1 == 0 || size_2 == 0)
        return 0;

    if(string_1[size_1 - 1] == string_2[size_2 - 1])
        return 1 + LCS(string_1, string_2, size_1 - 1, size_2 - 1);
    else
        return std::max(LCS(string_1, string_2, size_1 - 1, size_2), 
                        LCS(string_1, string_2, size_1, size_2 - 1));

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


    for(int i = 0; i < 5; i++){
        // std::cout << "Creating substrings... \n";

        //creating the substrings
        std::vector<char> s1(chars.begin(), chars.begin() + string_size);
        std::vector<char> s2(chars.begin() + string_size, chars.end());

        // std::cout << "done \n";

        // std::cout << "Calculating LCS value... \n"; 
        const auto start{std::chrono::high_resolution_clock::now()};
        int lcs_value = LCS(s1, s2, s1.size(), s2.size());
        const auto end{std::chrono::high_resolution_clock::now()};

        auto total_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start );

        // std::cout << "done \n";
        // std::cout << "LCS value is " << lcs_value << "\n";
        // std::cout << "Time for processing the function: " << total_time_ns.count() << " ns\n";
        std::cout <<total_time_ns.count()/1000000.0 << "\n";

    }
    
    input_file.close();

    return 0;
}