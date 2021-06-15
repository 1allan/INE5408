#ifndef XML_TOOLS_H
#define XML_TOOLS_H

#include <string>

#include "linked_queue.hpp"

using namespace std;

namespace XML {

string read(const char* path) {
    string output;
    structures::LinkedStack<string> tag_stack;
    ifstream file(path);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            int opener = line.find('<');
            while (opener != -1) {
                int closer = line.find('>', opener);
                if (line[opener + 1] == '/') {
                    string last_tag = tag_stack.pop();
                    if (line.substr(opener + 2, last_tag.size()) != last_tag) {
                        throw out_of_range("Bad XML format");
                    }
                } else {
                    string tag = line.substr(opener + 1, closer - opener - 1);
                    tag_stack.push(tag);
                }
                opener = line.find('<', closer);
            }
            output += line + ' ';
        }
        file.close();
    } else {
        throw out_of_range("Unable to open file");
    }
    if (tag_stack.size() != 0) {
        throw out_of_range("Bad XML format");
    }
    return output;
}

string get_tag(const string &xml_string, string tag, int start) {
    int opener = xml_string.find('<' + tag + '>', start);
    int closer = xml_string.find("</" + tag + '>', opener);
    int opener_end = opener + tag.size() + 2;
    return xml_string.substr(opener_end, closer - opener_end);
}

structures::LinkedQueue<string> get_tag_all(const string &xml_string, string tag) {
    structures::LinkedQueue<string> output;
    
    string last;
    int start = 0;
    bool remain = true;
    while (remain) {
        last = get_tag(xml_string, tag, start);
        output.enqueue(last);
        start += last.size();
        remain = (int)xml_string.find('<' + tag + '>', start) != -1;
    }
    return output;
}

}

#endif