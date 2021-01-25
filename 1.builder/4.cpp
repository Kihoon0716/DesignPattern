#include <iostream>
#include <vector>
#include <memory>

using namespace std;

template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params)
{
   return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}


class HtmlElement{
    public:
    string name;
    string text;
    vector<HtmlElement> elements;

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

    static HtmlElement* build(const string& name, const string& text){
        return new HtmlElement(name, text);
    }

    HtmlElement* add_child(string child_name, string child_text){
        elements.push_back(HtmlElement(child_name, child_text));
        return this;
    }


    private:
    HtmlElement(){}
    HtmlElement(const string& name, const string& text): name(name), text(text) {}
};

int main(){
    string words[] = {"hello", "world"};
    auto builder = HtmlElement::build("ul", "");
    // for (auto w: words)
    //     builder.add_child("li", w);
    builder->add_child("li", "hello")->add_child("li", "world");
        
    cout << builder->str().c_str() << endl;
}