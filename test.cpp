#include <iostream>
   #include <unistd.h>

   using namespace std;
int main()
{
	char ch; //or 'int ch;' (it doesn't really matter)

	//the program pauses here until a key is pressed
	ch = getchar();

	if(ch == 'a')
		std::cout << "You pressed a!" << std::endl;
	else
		std::cout << "You did not press a!" << std::endl;
    cout<<"t"<<ch<<endl;
	return 0;
}