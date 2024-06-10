#include <iostream>
#include "catan.hpp"
#include <iomanip>

int main()
{

    ariel::Catan game;

    return 0;
}

// #include <iostream>
// void hexagon(int size)
// {
//     int side = size;
//     int space = 2;
//     space = space > side - 1 ? space : side ;

//     // first row
//     for (int j = 1; j <= space; j++)
//     {
//         std::cout << " ";
//     }
//     for (int i = 1; i <= side; i++)
//     {
//         if(i==1 || i == side){
//             std::cout << "* ";
//         }
//         else{
//             std::cout << "- ";
//         }
//     }
//     cout << endl;
//     space--;
//     // upper rows
//     for (int i = 1; i <= side - 2; i++)
//     {
//         int numChars = side + i-1;
        
//         for (int j = 1; j <= space; j++)
//         {
//             std::cout << " ";
//         }
//         std::cout << "/";
//         for (int k = 1; k <= numChars; k++)
//         {
//             std::cout << "  ";
//         }
//         std::cout << "\\ ";
//         cout << endl;
//         space--;
        
//     }
//     space--;
//     // middle row
//     for (int j = 1; j <= space*2+1; j++)
//     {
//         std::cout << " ";
//     }

//     for (int j = 1; j <= side * 2 ; j++)
//     {
//         if (j == 1 || j == side * 2 )
//         {
//             std::cout << "*";
//         }
//         else{
//             std::cout << "  ";
//         }
//     }
//     cout << endl;
//     space++;
//     // bottom rows
//     for (int i = 1; i <= side - 2; i++)
//     {
//         int numChars = side *2- i - 2;
//         for (int j = 1; j <= space; j++)
//         {
//             std::cout << " ";
//         }
//         std::cout << " \\";
//         for (int k = 1; k <= numChars; k++)
//         {
//             std::cout << "  ";
//         }
//         std::cout << "/ ";
//         cout << endl;
//         space++;
//     }
//     //last row
//     for (int j = 1; j <= space+1; j++)
//     {
//         std::cout << " ";
//     }
//     for (int i = 1; i <= side; i++)
//     {
//         if(i == 1 || i ==side){
//             std::cout << "* ";
//         }
//         else{
//             std::cout << "- ";
//         }
//     }
//     cout << endl;

// }

// int main()
// {
//     hexagon(3);
//     std::string red = "\033[31m";
//     std::string green = "\033[32m";
//     std::string blue = "\033[34m";
//     std::string reset = "\033[0m";
//     cout << red << "Hello, World!";
//     cout<<green<<endl;
//     cout<<"yoni"<<endl;
//     return 0;
// }
