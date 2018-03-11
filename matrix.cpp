//
//  matrix.cpp
//  Matrox_0.0.1
//
//  Created by Сурков Дмитрий Валерьевич on 26.02.2018.
//  Copyright © 2018 Сурков Дмитрий Валерьевич. All rights reserved.
//

#include "matrix.hpp"
#include <assert.h>
#include <fstream>
#include <sstream>

matrix_t::matrix_t() : elements_{ nullptr }, rows_{ 0 }, collumns_{ 0 }
{
}

matrix_t::matrix_t( matrix_t const & other )
{
    elements_ = new float *[other.rows_];
    for (std::size_t i = 0; i < other.rows_; i++)
    {
        elements_[i] = new float [other.collumns_];
        for (std::size_t j = 0; j < other.collumns_; j++)
        {
            elements_[i][j] = other.elements_[i][j];
        }
        rows_ = other.rows_;
        collumns_ = other.collumns_;
    }
    
}

matrix_t matrix_t::add( matrix_t const &other)
{
    assert(rows_ == other.rows_ && collumns_ == other.collumns_);
    elements_ = new float *[other.rows_];
    for (std::size_t i = 0; i < other.rows_; i++)
    {
        elements_[i] = new float [other.collumns_];
        for (std::size_t j = 0; j < other.collumns_; j++)
        {
            elements_[i][j] += other.elements_[i][j];
        }
        rows_ = other.rows_;
        collumns_ = other.collumns_;
    }
    return *this;
}

matrix_t matrix_t::sub( matrix_t const &other)
{
    assert(rows_ == other.rows_ && collumns_ == other.collumns_);
    elements_ = new float *[other.rows_];
    for (std::size_t i = 0; i < other.rows_; i++)
    {
        elements_[i] = new float [other.collumns_];
        for (std::size_t j = 0; j < other.collumns_; j++)
        {
            elements_[i][j] -= other.elements_[i][j];
        }
        rows_ = other.rows_;
        collumns_ = other.collumns_;
    }
    return *this;
}

matrix_t matrix_t::mult( matrix_t const &other)
{
    assert(collumns_ == other.rows_);
    matrix_t result;
    result.elements_ = new float * [rows_];
    for (std::size_t i = 0; i < rows_; i++)
    {
        result.elements_[i] = new float [collumns_];
        for (std::size_t j = 0; j < collumns_; j++)
        {
            result.elements_[i][j] = 0;
        }
    }
    for (std::size_t i = 0; i < rows_; i++)
    {
        for (std::size_t j = 0; j < other.collumns_; j++)
        {
            for (std::size_t z = 0; z < collumns_; z++)
            {
                result.elements_[i][j] += elements_[i][z] * other.elements_[z][j];
            }
        }
    }
    /* умножение строку первой матрицы на столбец второй, чтобы получить столбец третьей*/
    result.rows_ = rows_;
    result.collumns_ = other.collumns_;
    return result;
}

matrix_t matrix_t::trans()
{
    matrix_t result;
    result.elements_ = new float *[result.rows_];
    for (int i = 0; i < result.rows_; i++)
    {
        result.elements_[i] = new float[result.collumns_];
        for (int j = 0; j < result.collumns_; j++)
        {
            result.elements_[i][j] = elements_[j][i];
        }
    }
    result.rows_ = collumns_;
    result.collumns_ = rows_;
    return result;
}

matrix_t::~matrix_t()
{
    for( std::size_t i = 0; i < rows_; ++i )
    {
        delete [] elements_[ i ];
    }
    delete [] elements_;
}

std::ifstream & matrix_t::read( std::ifstream & file )
{
    std::size_t rows;
    std::size_t collumns;
    char symbol;
    bool success = true;
    std::string line;
    if (getline (file, line)) //считывает неформатированные данные из потока в строку, ост., как только исчерпан поток
    {
        std::istringstream sstream (line); //прикрепляет создаваемый объект потока к строке line
        if( sstream >> rows && sstream >> symbol && symbol == ',' && sstream >> collumns )
        {
            float ** elements = new float *[ rows ];
            for( std::size_t i = 0; success && i < rows; ++i )
            {
                elements[ i ] = new float[ collumns ];
                for( std::size_t j = 0; j < collumns; ++j )
                {
                    if( !( sstream >> elements[ i ][ j ] ) )
                    {
                        success = false;
                        break;
                    }
                }
            }
        
        if( success )
        {
            for( std::size_t i = 0; i < rows_; ++i )
            {
                delete [] elements_[ i ];
            }
            delete [] elements_;
            
            rows_ = rows;
            collumns_ = collumns;
            elements_ = elements;
        }
        else
        {
            for( std::size_t i = 0; i < rows; ++i )
            {
                delete [] elements[ i ];
            }
            delete [] elements;
        }
    }
    else
    {
        success = false;
    }
    if( !success )
    {
        sstream.setstate( std::ios_base::failbit );
    }
    return file;
}
    

std::ostream & matrix_t::write( std::ostream & stream ) const
{
    stream << rows_ << ", " << collumns_;
    for( std::size_t i = 0; i < rows_; ++i )
    {
        stream << endl;
        for( std::size_t j = 0; j < collumns_; ++j )
        {
            stream << elements_[ i ][ j ];
        }
    }
    return stream;
}
