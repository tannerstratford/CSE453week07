#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void one(long number);
void two(long number);
void pass() { cout << "You pass :)\n"; }
void fail() { cout << "You've failed :(\n"; }
const char * passMessage = ":)";
const char * failMessage = ":(";

/**********************************************
 * MAIN : The top of the callstack.
 **********************************************/
int main()
{
   char text[8] = "*MAIN**";
   long number = 123456;
   void (*pointerFunction)() = fail;
   const char * message = failMessage;

   // display the initial values of the local variables
   cout << "main() : " << (void *)main << endl;
   cout << "\ttext:             " << text              << endl;
   cout << "\tnumber:           " << number            << endl;
   cout << "\tmessage:          " << message           << endl;
   cout << "\tfunction pointer: ";
   pointerFunction();

   // call the other functions
   one(number + 111111);     // 234567

   // display the new values of the local variables
   cout << "main() - after\n";
   cout << "\ttext:             " << text              << endl;
   cout << "\tnumber:           " << number            << endl;
   cout << "\tmessage:          " << message           << endl;
   cout << "\tfunction pointer: ";
   pointerFunction();

   return 0;
}

/************************************************
 * CONVERT TO STRING
 * Convert the data from p into a human-readable string
 * by removing all the unprintable characters and replacing
 * them with a dot
 ***********************************************/
string displayCharArray(const char * p)
{
   string output;
   for (int i = 0; i < 8; i++)
       output += string(" ") + (p[i] >= ' ' && p[i] <= 'z' ? p[i] : '.');
   return output;
}

/**********************************************
 * ONE : The next item on the call stack
 **********************************************/
void one(long number)               // 234567
{
   char text[8] = "**ONE**";

   cout << "one() : " << (void *)one << endl;
   cout << "\tmessage: " << (void *)failMessage << endl;
   cout << "\tfail():  " << (void *)fail        << endl;

   two(number + 111111);    // 345678
}

/**********************************************
 * TWO : The bottom of the call stack
 **********************************************/
void two(long number)              // 345678
{
   // start your display of the stack from this point
   
   long bow = number + 111111;     // 456789
   char text[8] = "**TWO**";
   long * pLong = &bow;
   char * pChar = &text[8];

   // header for our table. Use these setw() offsets in your table
   cout << '[' << setw(2) << 'i' << ']'
        << setw(15) << "address"
        << setw(20) << "hexadecimal"
        << setw(20) << "decimal"
        << setw(18) << "characters"
        << endl;
   cout << "----+"
        << "---------------+"
        << "-------------------+"
        << "-------------------+"
        << "-----------------+\n";
   std::ios oldState(nullptr);  // These two lines right here may be affecting the results since it is adding 2 local variables to the stack. 
   oldState.copyfmt(std::cout); // I couldn't find a cleaner way to convert from hexadecimal back to decimal Also the reason I changed the 
                                // loop starting and end conditions from (start=24, end=-4) to (start=26, end=-2)
   for (long i = 26; i >= -2; i--)   // You may need to change 24 to another number
   {
      std::cout << '[' << setw(2) << i << ']'
        << setw(15) << (2 * i) + pLong
        << setw(20) << std::hex << *((2 * i) + pLong); //std::hex converts the decimal to hexadecimal
      std::cout.copyfmt(oldState);                     //This line right here converts it back from hexadecimal to decimal, and relies
                                                       //on the two lines that I mentioned above.
      std::cout << setw(20) << *((2 * i) + pLong)
        << setw(18) << displayCharArray((8*i) + pChar)
        << endl;
   }

   ////////////////////////////////////////////////
   // Insert code here to change the variables in main()
                                                                                
   // change text in main() to "*main**"
   *((2 * 18) + pLong + 1) = //Something... Need to figure out how to get long value of *main**;
  

   // change number in main() to 654321
   *((2 * 20) + pLong + 1) = 654321;

   // change pointerFunction in main() to point to pass

   // change message in main() to point to passMessage

   //
   ////////////////////////////////////////////////
}