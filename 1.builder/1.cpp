#include <iostream>
#include <sstream>

using namespace std;


int main(){
string words[] = {"hellp", "world"};
ostringstream oss;

oss << "<ul>";

for (auto w: words){
    oss << " <li>" << w << "</li>";
    w = "changed";
}

for (auto w: words){
    oss << " <li>" << w << "</li>";
    w = "changed";
}

oss << "/ul";

cout << oss.str().c_str() << endl;

}