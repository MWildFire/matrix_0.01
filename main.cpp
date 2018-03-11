//
//  main.cpp
//  Matrox_0.0.1
//
//  Created by Сурков Дмитрий Валерьевич on 26.02.2018.
//  Copyright © 2018 Сурков Дмитрий Валерьевич. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "matrix.hpp"

int main()
{
    matrix_t matrix1;
    std::string line, filename1, filname2;
    char op;
    if (getline(std::cin, line))
    {
        std::istringstream stream (line);
        if(stream >> filename1 && stream >> op)
        {
            if (stream >> filname2)
            {
                std::ifstream file1(filename1);
                std::ifstream file2(filename2);
                matrix1.read(file1);
                matrix_t matrix2;
                matrix_t result;
                switch (op)
                {
                    case '+':
                        matrix2.read(file2);
                        result = matrix1.add(matrix2);
                        return result.write(std::cout);
                        break;
                    case '-':
                        matrix2.read(file2);
                        result = matrix1.sub(matrix2);
                        return result.write(std::cout);
                        break;
                    case '*':
                        matrix2.read(file2);
                        result = matrix1.mult(matrix2);
                        return result.write(std::cout);
                        break;
                    case 'T':
                        matrix2.read(file2);
                        result = matrix2.mult(matrix2);
                        return result.write(std::cout);
                        break;
                }
            }
            else std::cout << "An error has occured while reading input data";
        }
        else std::cout << "An error has occured while reading input data";
    }
    else cout << "An error has occured while reading input data";
    std::cin.get();
    std::cin.get();
    return 0;
}
