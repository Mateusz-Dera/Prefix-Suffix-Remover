//  Prefix-Suffix-Remover
//  Copyright © 2022 Mateusz Dera

//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.

//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>

#include <iostream>
#include <fstream>

using namespace std;

// Version
string version = "2022.03.31";

// Errors
string error_input_flag            = "Wrong or missing input file.";
string error_input_multiple        = "Multiple input values.";
string error_output_flag           = "Wrong or missing output file.";
string error_output_create         = "Can not create or write to output file.";
string error_output_multiple       = "Multiple output values.";
string error_prefix_or_suffix_flag = "Wrong or missing prefix or suffix.";
string error_prefix_flag           = "Wrong or missing prefix value.";
string error_prefix_multiple       = "Multiple prefix values.";
string error_suffix_multiple       = "Multiple suffix values.";
string error_suffix_flag           = "Wrong or missing suffix value.";
string error_unknown_parameter     = "Unknown parameter: ";

// Other
string writing_test = "Writing test.";

// Help
string help_title   = "Program removes suffix and/or prefix from file";
string help_help    = "-h     --help      Show help";
string help_version = "-v     --version   Show version";
string help_input   = "-i     --input     Input file";
string help_output  = "-o     --output    Output file";
string help_prefix  = "-p     --prefix    Prefix to remove";
string help_suffix  = "-s     --suffix     Suffix to remove";

int get_help(){
    cout 
    << help_title << endl 
    << help_help << endl 
    << help_version << endl 
    << help_input << endl 
    << help_output << endl 
    << help_prefix << endl 
    << help_suffix << endl; 
    exit(0);
    return 0;
}

int get_version(){
    cout << "Version: " << version << endl;
    exit(0);
    return 0;
}

bool file_exist(char* file)
{
    ifstream f(file);
    return f.good();
}

bool file_writable(char* file)
{
    ofstream f(file);
    f << writing_test << endl;
    return f.good();
}

int main(int argc,char* argv[]){
    bool prefix_flag = false;
    bool suffix_flag = false;

    bool input_flag = false;
    bool output_flag = false;

    string input_name;
    string output_name;
    string prefix_name;
    string suffix_name;

    fstream input;
    ofstream output;

    for (int a = 1; a < argc; ++a){
        string s = argv[a];
        if(s == "-h" || s == "--help"){
            get_help();
        }
        else if(s == "-v" || s == "--version"){
            get_version();
        }
        else if(s == "-i" || s == "--input"){
            if(input_flag == true){
                cout << error_input_multiple << endl;
                exit(1);
                return 1; 
            }
            a = a + 1;
            if(a < argc){
                if(file_exist(argv[a])){
                    input_name = argv[a];
                    input_flag = true;
                }
                else{
                    cout << error_input_flag << endl;
                    exit(1);
                    return 1;
                }
            }
            else{
                cout << error_input_flag << endl;
                exit(1);
                return 1;
            }
        }
        else if(s == "-o" || s == "--output"){
            if(output_flag == true){
                cout << error_output_multiple << endl;
                exit(1);
                return 1; 
            }
            a = a + 1;
            if(a < argc){
                if(file_writable(argv[a])){
                    output_name = argv[a];
                    output_flag = true;
                }
                else{
                    cout << error_output_create << endl;
                    exit(1);
                    return 1;
                }
            }
            else{
                cout << error_output_flag << endl;
                exit(1);
                return 1;
            }
        }
        else if(s == "-p" || s == "--prefix"){
            if(prefix_flag == true){
                cout << error_prefix_multiple << endl;
                exit(1);
                return 1; 
            }
            a = a + 1;
            if(a < argc){
                prefix_name = argv[a];
                prefix_flag = true;
            }
            else{
                cout << error_prefix_flag << endl;
                exit(1);
                return 1;
            }
        }
        else if(s == "-s" || s == "--suffix"){
            if(suffix_flag == true){
                cout << error_suffix_multiple << endl;
                exit(1);
                return 1; 
            }
            a = a + 1;
            if(a < argc){
                suffix_name = argv[a];
                suffix_flag = true;
            }
            else{
                cout << error_suffix_flag << endl;
                exit(1);
                return 1;
            }
        }
        else{
            cout << error_unknown_parameter << argv[a] << endl;
            exit(1);
            return 1;
        }
    }

    if(input_flag == false){
        cout << error_input_flag << endl;
        exit(1);
        return 1;
    }

    else if(output_flag == false){
        cout << error_output_flag << endl;
        exit(1);
        return 1;
    }

    else if(prefix_flag == false and suffix_flag == false){
        cout << error_prefix_or_suffix_flag << endl;
        exit(1);
        return 1;
    }

    else{
        input.open(input_name, ifstream::in);
        output.open(output_name, ios::trunc);
        
        string l;
        while (getline(input, l)){

            if(prefix_flag){
                int prefix_lenght = prefix_name.length();
                if(prefix_lenght <= l.length()){
                    if(l.substr(0,prefix_lenght)==prefix_name){
                        l = l.substr(prefix_lenght,-1);
                    }
                }
            }

            if(suffix_flag){
                int suffix_lenght = suffix_name.length();
                if(suffix_lenght <= l.length()){
                    if(l.substr(l.length()-suffix_lenght,-1)==suffix_name){
                        l = l.substr(0,l.length()-suffix_lenght);
                    }
                }
            }
            
            if(input.eof()){
                output << l;
            }
            else{
                output << l << endl;
            }
        }
        output.close();
        input.close();
    }
}
