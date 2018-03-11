//
//  matrix.hpp
//  Matrox_0.0.1
//
//  Created by Сурков Дмитрий Валерьевич on 26.02.2018.
//  Copyright © 2018 Сурков Дмитрий Валерьевич. All rights reserved.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <iostream>

class matrix_t
{
private:
    float ** elements_;
    std::size_t rows_;
    std::size_t collumns_;
public:
    matrix_t();
    matrix_t( matrix_t const & other );
    ~matrix_t();
    matrix_t add( matrix_t const &other);
    matrix_t sub( matrix_t const &other);
    matrix_t mult( matrix_t const &other);
    matrix_t trans();
    
    std::ostream & write( std::ostream & stream ) const;
    std::ifstream & read( std::ifstream & stream );
};

#endif /* matrix_hpp */


