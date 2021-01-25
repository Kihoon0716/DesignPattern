#include <iostream>
#include <vector>

using namespace std;

class HtmlElement{
    public:
        string name;
        string text;
        vector<HtmlElement> elements;

    HtmlElement(){}
    HtmlElement(const string& name, const string& text): name(name), text(text) {}

    string str(int indent = 0) const{
        string contents = "";
        if (elements.empty()){
            for (int i = 0; i < indent; i++){
                contents += "\t";
            }
            contents += ("<" + name + "> " + text + " </" + name + ">\n");
        }
        else{
            for (int i = 0; i < indent; i++){
                contents += "\t";
            }
            contents += ("<" + name + ">\n");
            
            for (auto e: elements){
                contents += e.str(indent + 1);
            }

            for (int i = 0; i < indent; i++){
                contents += "\t";
            }
            contents += ("</" + name + ">");
        }
        return contents;
    }

};

int main(){
    string words[] = {"hello", "world"};
    HtmlElement list("ul", "");
    for (auto w: words)
        list.elements.push_back(HtmlElement("li", w));
    cout << list.str().c_str() << endl;
}