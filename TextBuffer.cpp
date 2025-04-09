#include <list>
#include <string>
#include <iterator>
#include <algorithm>
#include "TextBuffer.hpp"

using namespace std;

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

TextBuffer::TextBuffer() : data(), row(1), column(0), index(0) {
    cursor = data.end();
}

bool TextBuffer::forward() {
    if (cursor == data.end()) {
        return false;
    }
    char current = *cursor;
    ++cursor;
    ++index;
    if (current == '\n') {
        row++;
        column = 0;
    }
    else {
        column++;
    }
    return true;
}

bool TextBuffer::backward() {
    if (cursor == data.begin()) {
        return false;
    }
    char current = *cursor;
    --cursor;
    --index;
    if (column == 0) {
        row--;
        column = compute_column();
    }
    else {
        column--;
    }
    return true;
}

void TextBuffer::insert(char c) {
    data.insert(cursor, c);
    ++index;
    if (c == '\n') {
        row++;
        column = 0;
    }
    else {
        column++;
    }
}

bool TextBuffer::remove() {
    data.remove(cursor);
}

