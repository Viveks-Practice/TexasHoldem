//
//  handData.hpp
//  poker
//
//  Created by Vivek Sharma on 2020-11-19.
//  Copyright © 2020 Vivek. All rights reserved.
//

#ifndef handData_hpp
#define handData_hpp

#include <stdio.h>
#include <string>

struct handData{
    int handScore = 0;
    std::string card1Face = "";
    std::string card2Face = "";
};

#endif /* handData_hpp */
