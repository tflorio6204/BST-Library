/*
 * Thomas Florio
 * Leighanne Hsu
 * CISC 220, 011
 * 11/2/23
 */

#include "Book.hpp"
#include <iostream>
#include <string>
using namespace std;


Book::Book(string t, string auth, int yr, string pub, long long isbn, float rate) { // set book attributes
	title = t;
	author = auth;
	year = yr;
	publisher = pub;
	isbn13 = isbn;
	rating = rate;
	checked_out = false;
}

Book::Book() { // empty book object
	title = "";
	author = "";
	year = 0;
	publisher = "";
	isbn13 = 0;
	rating = 0;
	checked_out = false;
}

float Book::getRating() {
	return rating;
}

void Book::printBook() {
    cout << "---------------------" << endl;
    cout << title << "\nAuthor: " << author << "\t\tYear: " << year << endl;
    cout << "Publisher: " << publisher << "\tISBN-13: " << isbn13 << "\tRating: " << rating << endl;
    cout << "Currently Available: " << (checked_out ? "No" : "Yes") << endl;
}

bool Book::operator<(Book b2) { // checks whether a book is smaller than the other by author (alphabetical)
    if(author < b2.author)
    {
        return true;
    }
    else if(author == b2.author)
    {
        if(title < b2.title)
        {
            return true;
        }
    }
	return false;
}

bool Book::operator>(Book b2) { // greater than
    if(author > b2.author)
    {
        return true;
    }
    else if(author == b2.title)
    {
        if(title < b2.title)
        {
            return true;
        }
    }
	return false;
}

bool Book::operator==(Book b2) { // equal to
    if(author == b2.author && title == b2.title)
    {
        return true;
    }
	return false;
}

bool Book::operator!=(Book b2) { // not equal to
    if(title != b2.title || author != b2.author)
    {
        return true;
    }
	return false;
}

bool Book::operator<=(Book b2) // less than or equal to
{
    if(author == b2.author) // if authors are equal, arrange books by title
    {
        return title <= b2.title;
    }
    else
    {
        return author <= b2.author;
    }
}

bool Book::operator>=(Book b2) {  // greater than or equal to
    if(author == b2.author)
    {
        return title >= b2.title; // if authors are equal, arrange books by title
    }
    else
    {
        return author >= b2.author;
    }
}