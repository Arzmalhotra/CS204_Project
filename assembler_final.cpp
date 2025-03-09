#include <bits/stdc++.h>
#include <bitset>

using namespace std;

bool initial_parse(string input_filename, map<string, int> &Label_map);
void final_parse(string input_filename, string output_filename, map<string, int> Label_map, map<string, string> &Data_segment);

int main()
{
    const string input_filename = "input.asm"; // Update this path if necessary
    const string output_filename = "output.mc";

    // Print the current working directory

    // A map to store the address of Labels with respect to PC
    map<string, int> Label_map;

    // Debugging statement to check file path
    cout << "Trying to open input file: " << input_filename << endl;

    bool error = initial_parse(input_filename, Label_map);
    if (error)
    {
        cout << "Error during initial parse." << endl;
        return 1;
    }

    // Checking if all labels are present
    for (auto it = Label_map.begin(); it != Label_map.end(); ++it)
    {
        if (it->second == -1)
        {
            cout << "Error: Didn't mention Label - " << it->first << endl;
            return 1;
        }
    }

    map<string, string> Data_segment;
    final_parse(input_filename, output_filename, Label_map, Data_segment);

    return 0;
}
// Auxiliary Functions

string remove_leading_spaces(string input)
{
    size_t pos = input.find_first_not_of(' ');
    if (pos != string::npos)
    {
        input.erase(0, pos);
    }
    return input;
}

string remove_trailing_spaces(string input)
{
    size_t pos = input.find_last_not_of(' ');
    if (pos != string::npos)
    {
        input.erase(pos + 1);
    }
    return input;
}

vector<string> preprocess(string line)
{
    string word = "";
    vector<string> words;

    size_t pos = line.find_first_of('#');
    if (pos != string::npos)
    {
        line.erase(pos);
    }

    for (int i = 0; i <= line.length(); i++)
    {
        if ((line[i] != ' ') & (line[i] != ',') & (line[i] != '(') & (line[i] != ')') & (line[i] != '\0'))
        {
            word += line[i];
        }
        else
        {
            word = remove_leading_spaces(word);
            word = remove_trailing_spaces(word);
            if (!word.empty())
            {
                words.push_back(word);
            }
            word = "";
        }
    }
    return words;
}

// string binTohex(string binary){
//     string hex = "";
//     for (int i = 0; i < binary.length(); i += 4){
//         string group = binary.substr(i, 4);
//         int value = stoi(group, nullptr, 2);
//         char hex_char = value + (value < 10 ? '0' : 'A' - 10);
//         hex += hex_char;
//     }
//     return hex;
// }

string binTohex(string binary) {
    bool negative = false;
    
    // Check for a negative sign at the beginning.
    if (!binary.empty() && binary[0] == '-') {
        negative = true;
        binary = binary.substr(1); // Remove the negative sign.
    }
    
    // Pad with leading zeros so that the length is a multiple of 4.
    while (binary.length() % 4 != 0) {
        binary = '0' + binary;
    }
    
    string hex = "";
    
    // Process the binary string 4 bits at a time.
    for (size_t i = 0; i < binary.length(); i += 4) {
        string group = binary.substr(i, 4);
        
        // Convert the 4-bit binary group to its integer value manually.
        int value = 0;
        for (char c : group) {
            value = value * 2 + (c - '0');
        }
        
        // Map the value to a hexadecimal character.
        char hex_char = (value < 10) ? (value + '0') : (value - 10 + 'A');
        hex += hex_char;
    }
    
    // Prepend the minus sign if the original number was negative.
    if (negative) {
        hex = "-" + hex;
    }
    
    return hex;
}

// string decTobin(string decimal){
//     int value = stoi(decimal);
//     bitset<32> bits(value);
//     string str = bits.to_string();
//     return str;
// }

// string decTobin(string decimal)
// {
//     // Convert string to integer manually
//     int value = 0;
//     for (char c : decimal)
//     {
//         value = value * 10 + (c - '0'); // Convert character to digit and build the number
//     }

//     // Convert integer to binary manually
//     string binary = "";
//     if (value == 0)
//         return "00000000000000000000000000000000"; // Ensure 32-bit representation

//     while (value > 0)
//     {
//         binary = char((value % 2) + '0') + binary; // Get remainder and prepend to string
//         value /= 2;
//     }

//     // Ensure 32-bit format by padding with leading zeros
//     while (binary.length() < 32)
//     {
//         binary = '0' + binary;
//     }

//     return binary;
// }

string decTobin(string decimal) {
    // Manually convert the string to an integer.
    bool isNegative = false;
    int i = 0;
    if (!decimal.empty() && decimal[0] == '-') {
        isNegative = true;
        i++; // Skip the '-' sign
    }
    
    int value = 0;
    for (; i < decimal.size(); i++) {
        char c = decimal[i];
        // Assuming the input string is valid (contains only digits after optional sign)
        value = value * 10 + (c - '0');
    }
    
    if (isNegative)
        value = -value;  // Apply the negative sign

    // Cast to unsigned to get the 32-bit two's complement representation.
    unsigned int uvalue = static_cast<unsigned int>(value);
    
    // Manually build the binary string.
    string binary;
    for (int bit = 31; bit >= 0; bit--) {
        binary.push_back((uvalue & (1u << bit)) ? '1' : '0');
    }
    
    return binary;
}

string hexTobin(string hexadecimal)
{
    string bin = "";
    for (char c : hexadecimal)
    {
        int value = isdigit(c) ? c - '0' : c - 'A' + 10;
        string bin_group = decTobin(to_string(value));
        bin_group = bin_group.substr(28, 4);
        bin += bin_group;
    }
    return bin;
}

string binTodec(string binary)
{
    bool isNegative = binary[0] == '1';
    int value = 0;

    for (int i = 1; i < binary.length(); ++i)
    {
        char bit_char = binary[i];
        int digit = bit_char - '0';
        value += digit * (1 << (binary.length() - 1 - i));
    }

    if (isNegative)
    {
        value = -value - 1;
    }
    return to_string(value);
}

// Main Functions

// unordered_map<string, string> opcode = {
//     {"add", "0110011"}, {"sub", "0110011"}, {"and", "0110011"}, {"or", "0110011"},
//     {"xor", "0110011"}, {"sll", "0110011"}, {"srl", "0110011"}, {"sra", "0110011"},
//     {"slt", "0110011"}, {"mul", "0110011"}, {"div", "0110011"}, {"rem", "0110011"},
//     {"addi", "0010011"}, {"andi", "0010011"}, {"ori", "0010011"},
//     {"lb", "0000011"}, {"lh", "0000011"}, {"lw", "0000011"}, {"ld", "0000011"},
//     {"sb", "0100011"}, {"sh", "0100011"}, {"sw", "0100011"}, {"sd", "0100011"},
//     {"jalr", "1100111"}, {"beq", "1100011"}, {"bne", "1100011"},
//     {"blt", "1100011"}, {"bge", "1100011"}, {"lui", "0110111"}, {"auipc", "0010111"},
//     {"jal", "1101111"}
// };

// unordered_map<string, string> func3 = {
//     {"add", "000"}, {"sub", "000"}, {"and", "111"}, {"or", "110"},
//     {"xor", "100"}, {"sll", "001"}, {"srl", "101"}, {"sra", "101"},
//     {"slt", "010"}, {"mul", "000"}, {"div", "100"}, {"rem", "110"},
//     {"addi", "000"}, {"andi", "111"}, {"ori", "110"},
//     {"lb", "000"}, {"lh", "001"}, {"lw", "010"}, {"ld", "011"},
//     {"sb", "000"}, {"sh", "001"}, {"sw", "010"}, {"sd", "011"},
//     {"jalr", "000"}, {"beq", "000"}, {"bne", "001"},
//     {"blt", "100"}, {"bge", "101"}
// };

// unordered_map<string, string> func7 = {
//     {"add", "0000000"}, {"sub", "0100000"}, {"and", "0000000"}, {"or", "0000000"},
//     {"xor", "0000000"}, {"sll", "0000000"}, {"srl", "0000000"}, {"sra", "0100000"},
//     {"slt", "0000000"}, {"mul", "0000001"}, {"div", "0000001"}, {"rem", "0000001"}
// };

unordered_map<string, string> opcode = {
    {"add", "0110011"}, {"sub", "0110011"}, {"and", "0110011"}, {"or", "0110011"}, {"xor", "0110011"}, {"sll", "0110011"}, {"srl", "0110011"}, {"sra", "0110011"}, {"slt", "0110011"}, {"mul", "0110011"}, {"div", "0110011"}, {"rem", "0110011"}, {"addi", "0010011"}, {"andi", "0010011"}, {"ori", "0010011"}, {"lb", "0000011"}, {"lh", "0000011"}, {"lw", "0000011"}, {"ld", "0000011"}, {"sb", "0100011"}, {"sh", "0100011"}, {"sw", "0100011"}, {"sd", "0100011"}, {"jalr", "1100111"}, {"beq", "1100011"}, {"bne", "1100011"}, {"blt", "1100011"}, {"bge", "1100011"}, {"lui", "0110111"}, {"auipc", "0010111"}, {"jal", "1101111"}};

unordered_map<string, string> func3 = {
    {"add", "000"}, {"sub", "000"}, {"and", "111"}, {"or", "110"}, {"xor", "100"}, {"sll", "001"}, {"srl", "101"}, {"sra", "101"}, {"slt", "010"}, {"mul", "000"}, {"div", "100"}, {"rem", "110"}, {"addi", "000"}, {"andi", "111"}, {"ori", "110"}, {"lb", "000"}, {"lh", "001"}, {"lw", "010"}, {"ld", "011"}, {"sb", "000"}, {"sh", "001"}, {"sw", "010"}, {"sd", "011"}, {"jalr", "000"}, {"beq", "000"}, {"bne", "001"}, {"blt", "100"}, {"bge", "101"}, {"lui", "000"}, {"auipc", "000"}, {"jal", "000"}};

unordered_map<string, string> func7 = {
    {"add", "0000000"}, {"sub", "0100000"}, {"and", "0000000"}, {"or", "0000000"}, {"xor", "0000000"}, {"sll", "0000000"}, {"srl", "0000000"}, {"sra", "0100000"}, {"slt", "0000000"}, {"mul", "0000001"}, {"div", "0000001"}, {"rem", "0000001"}};

unordered_map<string, string> registers;
int stringToInt(string imm)
{
    int value = 0;
    int sign = 1;
    size_t i = 0;

    // Handle negative numbers
    if (imm[0] == '-')
    {
        sign = -1;
        i = 1;
    }

    // Convert string to integer manually
    for (; i < imm.length(); i++)
    {
        if (imm[i] < '0' || imm[i] > '9')
        {
            cout << "Invalid number" << endl;
            return 0; // Handle invalid input gracefully
        }
        value = value * 10 + (imm[i] - '0');
    }

    return value * sign; // Apply sign and return
}

string toMC(vector<string> words, map<string, string> registers, map<string, int> Label_map, int PC)
{
    string word_1 = words[0];
    string result = "";
    // R-format words
    if (word_1 == "add" || word_1 == "and" || word_1 == "or" || word_1 == "sll" || word_1 == "slt" || word_1 == "srl" || word_1 == "sra" || word_1 == "sub" || word_1 == "xor" || word_1 == "mul" || word_1 == "div" || word_1 == "rem")
    {
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end()) || (registers.find(words[3]) == registers.end()))
        {
            return "1";
        }

        result += (func7[word_1] + registers[words[3]] + registers[words[2]] + func3[word_1] + registers[words[1]] + opcode[word_1]);
    }
    // I - format words
    else if (word_1 == "addi" || word_1 == "andi" || word_1 == "ori")
    {
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end()))
        {
            return "1";
        }
        string imm;
        if (words[3].substr(0, 2) == "0x")
        {
            imm = binTodec(hexTobin(words[3].substr(2)));
        }
        else
        {
            imm = words[3];
        }

        int value = stringToInt(imm);
        if ((value > 2047) || (value < -2048))
        {
            cout << "immediate value doesn't lie in the range -2048 to 2047 " << endl;
            return "";
        }
        imm = decTobin(imm);
        imm = imm.substr(20, 12);
        result += imm + registers[words[2]] + func3[word_1] + registers[words[1]] + opcode[word_1];
    }
    else if (word_1 == "lb" || word_1 == "ld" || word_1 == "lh" || word_1 == "lw")
    {
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[3]) == registers.end()))
        {
            return "1";
        }
        string imm;
        if (words[2].size() > 2 && words[2].substr(0, 2) == "0x")
        {
            imm = binTodec(hexTobin(words[2].substr(2)));
        }
        else
        {
            imm = words[2];
        }

        cout << imm << endl;
        int value = 0;
        for (auto i : imm)
        {
            if (!isdigit(i))
            {
                value = 1000;
            }
        }

        if ((value > 2047) || (value < -2048))
        {
            cout << "immediate value doesn't lie in the range -2048 to 2047 " << endl;
            return "";
        }
        imm = decTobin(imm);
        imm = imm.substr(20, 12);
        result += imm + registers[words[3]] + func3[word_1] + registers[words[1]] + opcode[word_1];
    }
    else if (word_1 == "jalr")
    {
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end()))
        {
            return "1";
        }
        string imm;
        if (words[3].substr(0, 2) == "0x")
        {
            imm = binTodec(hexTobin(words[3].substr(2)));
        }
        else
        {
            imm = words[3];
        }
        // cout<<imm<<endl;
        int value = stringToInt(imm);
        if ((value > 2047) || (value < -2048))
        {
            cout << "immediate value doesn't lie in the range -2048 to 2047 " << endl;
            return "";
        }
        imm = decTobin(imm);
        // imm = imm.substr(20, 12);
        imm = imm.substr(imm.size() - 12); // Extract last 12 bits
        result += imm + registers[words[2]] + func3[word_1] + registers[words[1]] + opcode[word_1];
    }
    else if (word_1 == "sb" || word_1 == "sw" || word_1 == "sd" || word_1 == "sh")
    {
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[3]) == registers.end()))
        {
            return "1";
        }
        string imm;
        if (words[2].substr(0, 2) == "0x")
        {
            imm = binTodec(hexTobin(words[2].substr(2)));
        }
        else
        {
            imm = words[2];
        }

        int value = stringToInt(imm);
        if ((value > 2047) || (value < -2048))
        {
            cout << "immediate value doesn't lie in the range -2048 to 2047 " << endl;
            return "";
        }
        imm = decTobin(imm);
        imm = imm.substr(20, 12);
        result += imm.substr(0, 7) + registers[words[1]] + registers[words[3]] + func3[word_1] + imm.substr(7, 5) + opcode[word_1];
    }
    else if (word_1 == "beq" || word_1 == "bne" || word_1 == "blt" || word_1 == "bge")
    {
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end()))
        {
            return "1";
        }
        string imm;
        int label = Label_map[words[3]];
        int offset = (label - PC);

        imm = decTobin(to_string(offset));

        imm = imm.substr(19, 12);

        result += imm[0] + imm.substr(2, 6) + registers[words[2]] + registers[words[1]] + func3[word_1] + imm.substr(8, 4) + imm[1] + opcode[word_1];
    }
    else if (word_1 == "auipc" || word_1 == "lui")
    {
        if ((registers.find(words[1]) == registers.end()))
        {
            return "1";
        }
        string imm;
        if (words[2].substr(0, 2) == "0x")
        {
            imm = (words[2].substr(2));
            imm = binTodec("0" + hexTobin(imm));
        }
        else
        {
            imm = words[2];
        }
        int value = stringToInt(imm);
        if ((value > 1048575) || (value < 0))
        {
            cout << "immediate value doesn't lie in the range 0 to 1048575.Limit exceeded. " << endl;
            return "";
        }
        imm = decTobin(imm);
        imm = imm.substr(12, 20);
        result += imm + registers[words[1]] + opcode[word_1];
    }
    else if (word_1 == "jal")
    {
        if ((registers.find(words[1]) == registers.end()))
        {
            return "1";
        }
        string imm;
        int label = Label_map[words[2]];
        int offset = (label - PC);
        imm = decTobin(to_string(offset));
        imm = imm.substr(11, 20);

        result += imm[0] + imm.substr(10, 10) + imm[9] + imm.substr(1, 8) + registers[words[1]] + opcode[word_1];
    }
    else
    {
        return "1";
    }

    return result;
}
bool initial_parse(string input_filename, map<string, int> &Label_map)
{
    set<string> instructions = {"add", "and", "or", "sll", "slt", "sra", "srl", "sub", "xor", "mul", "div", "rem", "addi", "andi", "ori", "lb", "ld", "lh", "lw", "jalr", "sb", "sw", "sd", "sh", "beq", "bne", "bge", "blt", "auipc", "lui", "jal"};

    ifstream input_file(input_filename);
    int PC = 0;
    bool ignore_line = 0;

    string line;
    while (std::getline(input_file, line))
    {
        line = remove_leading_spaces(line);
        line = remove_trailing_spaces(line);
        if ((line.empty()) || (line[0] == '#'))
            continue;

        vector<string> words = preprocess(line);
        if (words.empty())
        {
            continue;
        }
        string first_word = words[0];

        if (first_word == ".data")
        {
            ignore_line = 1;
            continue;
        }
        if (first_word == ".text")
        {
            ignore_line = 0;
            continue;
        }

        if (first_word.back() == ':')
        {
            if (ignore_line)
            {
                continue;
            }
            string Label_name = first_word.substr(0, first_word.length() - 1);
            Label_map[Label_name] = PC;
            continue;
        }

        if (!ignore_line)
        {
            PC += 4;
        }

        // Finding if all the instructions are ISA or not.
        auto it = instructions.find(first_word);
        if (it == instructions.end())
        {
            cout << "Error: Using instruction - " << first_word << " not in ISA" << endl;
            input_file.close();
            return 1;
        }

        // Checking for labels
        if ((first_word == "beq") || (first_word == "bne") || (first_word == "bge") || (first_word == "blt") || (first_word == "jal"))
        {
            auto it = Label_map.find(words.back());
            if (it == Label_map.end())
            {
                Label_map.insert({words.back(), -1});
            }
        }
    }

    input_file.close();
    return 0;
}

string getOpcodeBreakdown(vector<string> &words, map<string, string> &register_map)
{
    if (words.empty())
        return "NULL";

    string operation = words[0];
    string opcode, func3 = "NULL", func7 = "NULL", rd = "NULL", rs1 = "NULL", rs2 = "NULL", imm = "NULL";

    // Define opcode, func3, and func7 mappings
    map<string, pair<string, pair<string, string>>> instruction_format = {
        // R-format: opcode, (func3, func7)
        {"add", {"0110011", {"000", "0000000"}}},
        {"sub", {"0110011", {"000", "0100000"}}},
        {"and", {"0110011", {"111", "0000000"}}},
        {"or", {"0110011", {"110", "0000000"}}},
        {"xor", {"0110011", {"100", "0000000"}}},
        {"sll", {"0110011", {"001", "0000000"}}},
        {"srl", {"0110011", {"101", "0000000"}}},
        {"sra", {"0110011", {"101", "0100000"}}},
        {"slt", {"0110011", {"010", "0000000"}}},
        {"mul", {"0110011", {"000", "0000001"}}},
        {"div", {"0110011", {"100", "0000001"}}},
        {"rem", {"0110011", {"110", "0000001"}}},

        // I-format: opcode, (func3, func7=NULL)
        {"addi", {"0010011", {"000", "NULL"}}},
        {"andi", {"0010011", {"111", "NULL"}}},
        {"ori", {"0010011", {"110", "NULL"}}},
        {"lb", {"0000011", {"000", "NULL"}}},
        {"lh", {"0000011", {"001", "NULL"}}},
        {"lw", {"0000011", {"010", "NULL"}}},
        {"ld", {"0000011", {"011", "NULL"}}},
        {"jalr", {"1100111", {"000", "NULL"}}},

        // S-format: opcode, (func3, func7=NULL)
        {"sb", {"0100011", {"000", "NULL"}}},
        {"sh", {"0100011", {"001", "NULL"}}},
        {"sw", {"0100011", {"010", "NULL"}}},
        {"sd", {"0100011", {"011", "NULL"}}},

        // SB-format: opcode, (func3, func7=NULL)
        {"beq", {"1100011", {"000", "NULL"}}},
        {"bne", {"1100011", {"001", "NULL"}}},
        {"blt", {"1100011", {"100", "NULL"}}},
        {"bge", {"1100011", {"101", "NULL"}}},

        // U-format: opcode, (func3=NULL, func7=NULL)
        {"auipc", {"0010111", {"NULL", "NULL"}}},
        {"lui", {"0110111", {"NULL", "NULL"}}},

        // UJ-format: opcode, (func3=NULL, func7=NULL)
        {"jal", {"1101111", {"NULL", "NULL"}}}};

    // Check if the instruction exists
    if (instruction_format.find(operation) != instruction_format.end())
    {
        opcode = instruction_format[operation].first;
        func3 = instruction_format[operation].second.first;
        func7 = instruction_format[operation].second.second;
    }
    else
    {
        return "UNKNOWN";
    }

    // R-Type: rd, rs1, rs2
    if (opcode == "0110011")
    {
        rd = register_map[words[1]];
        rs1 = register_map[words[2]];
        rs2 = register_map[words[3]];
    }
    // I-Type: rd, rs1, imm
    else if (opcode == "0010011" || opcode == "0000011" || opcode == "1100111")
    {
        rd = register_map[words[1]];
        rs1 = register_map[words[2]];
        imm = decTobin(words[3]).substr(20, 12);
    }
    // S-Type: rs1, rs2, imm
    else if (opcode == "0100011")
    {
        rs1 = register_map[words[2]];
        rs2 = register_map[words[1]];
        imm = decTobin(words[3]).substr(20, 12);
    }
    // SB-Type: rs1, rs2, imm
    else if (opcode == "1100011")
    {
        rs1 = register_map[words[1]];
        rs2 = register_map[words[2]];
        imm = decTobin(words[3]).substr(20, 12);
    }
    // U-Type: rd, imm
    else if (opcode == "0010111" || opcode == "0110111")
    {
        rd = register_map[words[1]];
        imm = decTobin(words[2]).substr(12, 20);
    }
    // UJ-Type: rd, imm
    else if (opcode == "1101111")
    {
        rd = register_map[words[1]];
        imm = decTobin(words[2]).substr(11, 20);
    }

    // Format the breakdown
    return opcode + "-" + func3 + "-" + func7 + "-" + rd + "-" + rs1 + "-" + rs2 + "-" + imm;
}

void final_parse(string input_file_name, string output_file_name, map<string, int> label_map, map<string, string> &data_memory)
{
    ifstream input_file(input_file_name);
    ofstream output_file(output_file_name);

    if (!input_file.is_open())
    {
        cout << "Error: Could not open input file " << input_file_name << endl;
        return;
    }

    if (!output_file.is_open())
    {
        cout << "Error: Could not open output file " << output_file_name << endl;
        return;
    }

    int instruction_address = 0;
    bool is_in_data_section = false;

    // For data segment
    long long data_address = 0x10000000;
    long long data_size = 0;

    map<string, string> register_map = {
        {"zero", "00000"}, {"ra", "00001"}, {"sp", "00010"}, {"gp", "00011"}, {"tp", "00100"}, {"t0", "00101"}, {"t1", "00110"}, {"t2", "00111"}, {"s0", "01000"}, {"s1", "01001"}, {"a0", "01010"}, {"a1", "01011"}, {"a2", "01100"}, {"a3", "01101"}, {"a4", "01110"}, {"a5", "01111"}, {"a6", "10000"}, {"a7", "10001"}, {"s2", "10010"}, {"s3", "10011"}, {"s4", "10100"}, {"s5", "10101"}, {"s6", "10110"}, {"s7", "10111"}, {"s8", "11000"}, {"s9", "11001"}, {"s10", "11010"}, {"s11", "11011"}, {"t3", "11100"}, {"t4", "11101"}, {"t5", "11110"}, {"t6", "11111"}};

    for (int i = 0; i <= 31; i++)
    {
        string reg_name = "x" + to_string(i);
        register_map[reg_name] = (decTobin(to_string(i))).substr(27, 5);
    }

    string line;
    while (getline(input_file, line))
    {
        line = remove_leading_spaces(line);
        line = remove_trailing_spaces(line);
        if (line.empty() || line[0] == '#')
            continue;

        vector<string> words = preprocess(line);
        if (words.empty())
            continue;

        string first_word = words[0];

        if (first_word == ".data")
        {
            is_in_data_section = true;
            continue;
        }
        if (first_word == ".text")
        {
            is_in_data_section = false;
            data_size = 0;
            continue;
        }

        if (is_in_data_section)
        {
            if (words[1] == ".byte")
            {
                data_size = 1;
            }
            else if (words[1] == ".half")
            {
                data_size = 2;
            }
            else if (words[1] == ".word")
            {
                data_size = 4;
            }
            else if (words[1] == ".dword")
            {
                data_size = 8;
            }
            else
            {
                words[2] = words[2].substr(1, words[2].length() - 2);
                data_size = 1;
            }

            for (int i = 2; i < words.size(); i++)
            {
                if (words[1] == ".asciiz")
                {
                    string text = words[2];
                    for (char c : text)
                    {
                        int ascii_value = static_cast<int>(c);
                        string hex_value = binTohex(decTobin(to_string(ascii_value)));
                        data_memory["0x" + binTohex(decTobin(to_string(data_address)))] = "0x" + hex_value.substr(6, 2);
                        data_address += data_size;
                    }
                    data_address += data_size;
                    continue;
                }
                data_memory["0x" + binTohex(decTobin(to_string(data_address)))] = "0x" + binTohex(decTobin(words[i])).substr(8 - 2 * data_size, 2 * data_size);
                data_address += data_size;
            }
            continue;
        }

        if (first_word.back() == ':')
            continue;

        string machine_code = "0x" + binTohex(toMC(words, register_map, label_map, instruction_address));

        if (machine_code == "0x1")
        {
            cout << "Register not found in " << first_word << " operation at instruction address - "
                 << "0x" + binTohex(decTobin(to_string(instruction_address))) << endl;
        }

        if (machine_code == "0x" || machine_code == "0x1")
        {
            cout << "Error: Invalid machine code for instruction at address 0x"
                 << binTohex(decTobin(to_string(instruction_address))) << endl;
            output_file.close();
            ofstream output_file(output_file_name);
            output_file.close();
            return;
        }

        // Convert PC to hex address
        string address_hex = "0x" + binTohex(decTobin(to_string(instruction_address)));

        // Convert assembly instruction back to a string
        string assembly_instr = line;

        // Get opcode breakdown (dummy representation for now)
        string opcode_breakdown = getOpcodeBreakdown(words, register_map); // Implement this function separately

        // Write to output file in new format
        cout << "Writing to output file: " << address_hex << " " << machine_code << " , " << assembly_instr << " # " << opcode_breakdown << endl;
        output_file << address_hex << " " << machine_code << " , " << assembly_instr << " # " << opcode_breakdown << endl;

        instruction_address += 4;
    }

    // Mark end of text segment
    cout << "Marking end of text segment" << endl;
    output_file << "0x" << binTohex(decTobin(to_string(instruction_address))) << " 0xFFFFFFFF , END # NULL" << endl;

    // Writing data segment
    cout << "Writing data segment" << endl;
    for (auto it = data_memory.begin(); it != data_memory.end(); ++it)
    {
        output_file << it->first << " " << it->second << endl;
    }

    input_file.close();
    output_file.close();
}
