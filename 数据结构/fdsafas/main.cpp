//
//  main.cpp
//  fdsafas
//
//  Created by 刘泊 on 2019/3/13.
//  Copyright © 2019 LB. All rights reserved.
//

#include <iostream>

#include <list>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    std::list<int> s;
    s.push_back(1);
    std::list<int>::iterator it;
    it = s.begin();
    std::cout <<  *it << std::endl;
    *it = 100;
    std::cout <<  *it << std::endl;
    return 0;
}
