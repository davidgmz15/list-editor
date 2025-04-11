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
    if (cursor == data.end()) {
        return false;
    }
    char current = *cursor;
    cursor = data.erase(cursor);
    --index;
    if (current == '\n') {
        --row;
        column = compute_column();
    } else {
        --column;
    }
    return true;
}

bool TextBuffer::is_at_end() const {
    return cursor == data.end();
}

char TextBuffer::data_at_cursor() const {
    assert(cursor != data.end());
    return *cursor;
}

int TextBuffer::get_row() const {
    return row;
}

int TextBuffer::get_column() const {
    return column;
}

int TextBuffer::get_index() const {
    if(cursor == data.end()) { return size(); }
    return index;
}

int TextBuffer::size() const {
    return data.size(); 
}

std::string TextBuffer::stringify() const {
    return std::string(data.begin(), data.end());
}


  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the start of the current row (column 0).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  void TextBuffer::move_to_row_start() {
    int c_col = compute_column();
    for (int i = 0; i < c_col; ++i) {
            --cursor;
            --index;
        }
    column = 0;
}
  

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the end of the current row (the
  //          newline character that ends the row, or the past-the-end
  //          position if the row is the last one in the buffer).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  void TextBuffer::move_to_row_end() {
    int c_col = index - (data.size() + 1);

    //could also make copy of the cursor and have it go to the end of the list,
    //that way i could use index to be the number of characters in the list
    //because cursor would at past the end position

    for (int i = 0; i < c_col; ++i) {
            ++cursor;
            ++index;
        }
  }

  //REQUIRES: new_column >= 0
  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the given column in the current row,
  //          if it exists. If the row does not have that many columns,
  //          moves to the end of the row (the newline character that
  //          ends the row, or the past-the-end position if the row is
  //          the last one in the buffer).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  void TextBuffer::move_to_column(int new_column) {

  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the previous row, retaining the
  //          current column if possible. If the previous row is
  //          shorter than the current column, moves to the end of the
  //          previous row (the newline character that ends the row).
  //          Does nothing if the cursor is already in the first row.
  //          Returns true if the position changed, or false if it did
  //          not (i.e. if the cursor was already in the first row).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  bool TextBuffer::up() {

  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the next row, retaining the current
  //          column if possible. If the next row is shorter than the
  //          current column, moves to the end of the next row (the
  //          newline character that ends the row, or the past-the-end
  //          position if the row is the last one in the buffer). Does
  //          nothing if the cursor is already in the last row.
  //          Returns true if the position changed, or false if it did
  //          not (i.e. if the cursor was already in the last row).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  bool TextBuffer::down() {

  }