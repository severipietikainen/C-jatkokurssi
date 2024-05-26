
// a)
#include <iostream>
#include <string>

int main() {
    std::string s1 = "kissa";
    std::string s2;
    
    s1 = s2;
    
    std::cout << "s1: " << s1 << std::endl;  // Tulostaa: s1:
    std::cout << "s2: " << s2 << std::endl;  // Tulostaa: s2:
    
    return 0;
}

// Debuggerilla tarkasteltuna huomataan, että s1 ja s2 molemmat osoittavat tyhjään merkkijonoon. s1 alkuperäinen merkkijono "kissa" on poistettu.

// b) 

#include <iostream>
#include <string>
#include <utility>  // std::move

int main() {
    std::string s1 = "kissa";
    std::string s2;
    
    s1 = std::move(s2);
    
    std::cout << "s1: " << s1 << std::endl;  // Tulostaa: s1:
    std::cout << "s2: " << s2 << std::endl;  // Tulostaa: s2:
    
    return 0;
}

//  havaitaan, että s2 on tyhjä eikä osoita mihinkään varsinaiseen merkkijonoon. s1 ei ole osoittanut mihinkään uuteen merkkijonoon, koska s2 oli tyhjä.
´
// c)

#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> vec;
    std::string s3 = "koira";
    
    vec.push_back(s3);  
    std::cout << "push_back(s3):" << std::endl;
    std::cout << "s3: " << s3 << std::endl;  
    std::cout << "vec[0]: " << vec[0] << std::endl;  

    vec.push_back(std::move(s3));  
    std::cout << " push_back(std::move(s3)):" << std::endl;
    std::cout << "s3: " << s3 << std::endl;  
    std::cout << "vec[1]: " << vec[1] << std::endl;  
    
    return 0;
}

// ensimmäisen push_back-operaation jälkeen sekä s3 että vec[0] osoittavat eri merkkijonoon. Toisen push_back-operaation jälkeen s3 on tyhjä, ja vec[1] osoittaa alkuperäiseen s3 jonoon.