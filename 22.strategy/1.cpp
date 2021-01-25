#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

using namespace std;

enum OutputFormat{
    Markdown = 1,
    Html,
};

class ListStrategy{
    public:
        virtual void start(ostringstream& oss){}
        virtual void add_list_item(ostringstream& oss, const string& item){}
        virtual void end(ostringstream& oss){}
};

class HtmlListStrategy: public ListStrategy{
    void start(ostringstream& oss) override{
        oss << "<ul>\n";
    }

    void add_list_item(ostringstream& oss, const string& item) override{
        oss << "\t<li>" << item << "</li>";
    }

    void end(ostringstream& oss) override{
        oss << "</ul>";
    }
};

class MarkdownListStrategy: public ListStrategy{
    void add_list_item(ostringstream& oss, const string& item) override{
        oss << "* " << item;
    }
};

class TextProcessor{
    public:
    void append_list(const vector<string> items){
        list_strategy->start(oss);
        for (auto& item: items){
            list_strategy->add_list_item(oss, item);
        }
        list_strategy->end(oss);
    }

    void set_output_format(const OutputFormat format){
        switch (format)
        {
        case Markdown:
            list_strategy = new MarkdownListStrategy();
            break;
        
        case Html:
            list_strategy = new HtmlListStrategy();

        default:
            break;
        }
    }

    string str() const{
        return oss.str();
    }

    private:
        ostringstream oss;
        ListStrategy* list_strategy;
};

int main(){
    TextProcessor tp;
    vector<string> text;
    text.push_back("foo");
    text.push_back("bar");
    text.push_back("baz");

    tp.append_list(text);
    tp.set_output_format(Html);
    cout << tp.str();

    tp.set_output_format(Markdown);
    cout << tp.str();
}