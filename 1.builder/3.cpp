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

class HtmlBuilder{
    public:
    HtmlElement root;

    HtmlBuilder (string root_name) {root.name = root_name;}

    HtmlBuilder& add_child(string child_name, string chind_text){
        root.elements.push_back(HtmlElement(child_name, chind_text));
        return *this;
    }

    string str(){return root.str();}
};

int main(){
    string words[] = {"hello", "world"};
    HtmlBuilder builder("ul");
    // for (auto w: words)
    //     builder.add_child("li", w);

    builder.add_child("li", "hello").add_child("li", "world");
        
    cout << builder.str().c_str() << endl;
}