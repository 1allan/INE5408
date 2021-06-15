#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unistd.h>

#include "./include/linked_stack.hpp"
#include "./include/linked_queue.hpp"
#include "./include/xml_tools.hpp"

using namespace std;


class Point {
 public:
    Point(int x_, int y_) :
        x{x_},
        y{y_}
    {}
    ~Point() {}

    int x;
    int y;

};


void sweep(int** matrix, int rows, int columns, Point first_p) {
    structures::LinkedStack<Point> points;

    points.push(first_p);

    while(!points.empty()) {
        Point p = points.pop();

        int i = p.x;
        int j = p.y;

        matrix[i][j] = 0;

        if (j > 0 && matrix[i][j - 1] == 1) {
            points.push(Point(i, j - 1));
        }
        if (j < columns - 1 && matrix[i][j + 1] == 1) {
            points.push(Point(i, j + 1));
        }
        if (i > 0 && matrix[i - 1][j] == 1) {
            points.push(Point(i - 1, j));
        }
        if (i < rows - 1 && matrix[i + 1][j] == 1) {
            points.push(Point(i + 1, j));
        }
    }
}


structures::LinkedQueue<string> split(const string &string_, string separator) {
    structures::LinkedQueue<string> output;
    int last_sprt = string_.find(separator);
    while (last_sprt != -1) {
        int next_sprt = string_.find(separator, last_sprt + 1);
        string s = string_.substr(last_sprt + 1, next_sprt - last_sprt -1);
        if (s.size() == 0) break;
        output.enqueue(s);
        last_sprt = next_sprt;
    }
    return output;
}

int** create_matrix(const structures::LinkedQueue<string> &matrix_str) {
    int rows = matrix_str.size();
    int columns = matrix_str[0].size();

    int** output = new int*[rows];

    for (int i = 0; i < rows; i++) {
        output[i] = new int[columns];
        string line = matrix_str[i];
        for (int j = 0; j < columns; j++) {
            output[i][j] = (line[j] == '1');
        }
    }
    return output;
}

int count_regions(const string &data) {
    structures::LinkedQueue<string> d = split(data, " ");

    int rows = d.size();
    size_t columns = d[0].size(); // must be size_t because string uses it
	
    int** matrix_int = create_matrix(d);

    int regions = 0;
    for (int i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            if (matrix_int[i][j] == 1) {
                sweep(matrix_int, rows, columns, Point(i, j));
                regions++;
            }
        }
    }
    for (int i = 0; i < rows; i++) {
        delete matrix_int[i];
    }
    delete[] matrix_int;

    return regions;
}


int main() {

    // char xmlfilename[100];
    string xml = XML::read("./datasets/dataset01.xml");
    structures::LinkedQueue<string> images = XML::get_tag_all(xml, "img");

	for (int i = 0; i < images.size(); i++) {
		string name = XML::get_tag(images[i], "name", 0);
		string data = XML::get_tag(images[i], "data", 0);
		int a = count_regions(data);
        cout << name << ' ' << a << "\n";
	}

    return 0;
}