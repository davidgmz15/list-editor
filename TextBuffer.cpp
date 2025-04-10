#include <list>
#include <string>
#include <iterator>
#include <algorithm>
#include "TextBuffer.hpp"

using namespace std;

// compute index of the column starting at 0
int TextBuffer::compute_column() const {
    int col = 0;
    for (auto it = data.begin(); it != cursor; ++it) {
        if (*it == '\n') {
            col = 0;
        }
        else {
            col++;
        }
    }
    return col;
}

// default constructor
TextBuffer::TextBuffer() : data(), row(1), column(0), index(0) {
    cursor = data.end();
}

// move TextBuffer forward - increment cursor and index
bool TextBuffer::forward() {
    if (cursor == data.end()) { // if cursor is at end, do nothing
        return false;
    }
    char current = *cursor;
    ++cursor;
    ++index;
    if (current == '\n') { // if newline is found, reset column and increment row
        row++;
        column = 0;
    }
    else {
        column++;
    }
    return true;
}

// move TextBuffer backward - decrement cursor and index
bool TextBuffer::backward() {
    if (cursor == data.begin()) { // if cursor is at beggining, do nothing
        return false;
    }
    --cursor;
    --index;
    if (column == 0) { // if at end of current row, go to previous row's last column
        row--;
        column = compute_column();
    }
    else {
        column--;
    }
    return true;
}

// insert char before cursor and increment index
void TextBuffer::insert(char c) {
    data.insert(cursor, c);
    ++index;
    if (c == '\n') { // if char is a newline, go to next row and reset column
        row++;
        column = 0;
    }
    else {
        column++;
    }
}

// remove the char that the cursor is pointing at
bool TextBuffer::remove() {
    data.erase(cursor);
    --index;
    char current = *cursor;
    // if deleted char is a newline, go to previous row and reset column
    if (current == '\n') {
        row--;
        column = compute_column();
    }
    else {
        column--;
    }
}

// moves cursor to start of current row
void TextBuffer::move_to_row_start() {
    auto temp = cursor;
}

// moves cursor to end of current row
void TextBuffer::move_to_row_end() {

}

// moves cursor to given column in 
void TextBuffer::move_to_column(int new_column) {

}

// 
bool TextBuffer::up() {

}

// 
bool TextBuffer::down() {

}

// check if cursor is at past-the-end position
bool TextBuffer::is_at_end() const {
    return cursor == data.end();
}

// return the char at the current cursor position
char TextBuffer::data_at_cursor() const {
    assert(cursor != data.end());
    return *cursor;
}

// return current row number
int TextBuffer::get_row() const {
    return row;
}

// return current column number
int TextBuffer::get_column() const {
    return column;
}

// return current index of the char teh cursor is pointing to
int TextBuffer::get_index() const {
    return index;
}

// returns number of chars in buffer
int TextBuffer::size() const {
    return data.size();
}

// returns the entire contents of the text buffer as a string
std::string TextBuffer::stringify() const {
    return std::string(data.begin(), data.end());
}

