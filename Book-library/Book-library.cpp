#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>   
#include <set>
#include <fstream>
#include <sstream>
using namespace std;

class Book
{
private:
    string title;
    string author;
    int year;
    string ISBN;
    string genre;
    bool isAvailable;

public:
    Book(){}
    Book(string n, string a, int y, string i, string g, bool e)
        : title(n.empty() ? "Unknown" : n),
        author(a.empty() ? "Unknown" : a),
        year(y > -2000 && y <= 2025 ? y : 0),
        ISBN(i.empty() ? "Unknown" : i),
        genre(g.empty() ? "Unknown" : g)
    {
        isAvailable = true;
    }

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    string getIsbn() const { return ISBN; }
    string getGenre() const { return genre; }
    bool getIsAvailable() const { return isAvailable; }

    void setTitle(string nt)
    {
        if (!nt.empty())
        {
            title = nt;
        }
    }
    void setAuthor(string na)
    {
        if (!na.empty())
        {
            author = na;
        }
    }
    void setYear(int ny)
    {
        if (ny>-2000&&ny<=2025)
        {
            year = ny;
        }
    }
    void setIsbn(string ni)
    {
        if (!ni.empty())
        {
            ISBN = ni;
        }
    }
    void setGenre(string ng)
    {
        if (!ng.empty())
        {
            genre = ng;
        }        
    }
    void setIsAvailable(bool nv)
    {
        isAvailable = nv;
    }

    void displayInfo()
    {
        cout << "Название: " << getTitle() << endl << "Автор: " << getAuthor() << endl << "Год написания: " << getYear() << endl;
        cout << "ISBN: " << getIsbn() << endl << "Жанр: " << getGenre() << endl << "Есть в наличии: " << (getIsAvailable() ? "Да" : "Нет") << endl;
        cout << "-----" << endl;
    }
};

class Library
{
private:
    vector<Book> books;
    unordered_map<string, Book*> booksByISBN;
    map<string, set<Book*>> booksByAuthor;
    map<string, set<Book*>> booksByGenre;

public:
    Library() {}
   
    Book* findBookByISBN(const string& isbn)
    {   
        auto it = booksByISBN.find(isbn);
        if (it!=booksByISBN.end())
        {
            return it->second;
        }
        return nullptr;   
    }
    vector<Book*> findBooksByAuthor(string author)
    {
        vector<Book*> boks;
        if (booksByAuthor.find(author)!=booksByAuthor.end())
        {
            for (Book* bok : booksByAuthor[author])
            {
                boks.push_back(bok);
            }
        }
        return boks;
    }
    vector<Book*> findBooksByGenre(string genre)
    {
        vector<Book*> boks;
        if (booksByGenre.find(genre) != booksByGenre.end())
        {
            for (Book* bok : booksByGenre[genre])
            {
                boks.push_back(bok);
            }
        }
        return boks;
    }

    void addBook(Book book)
    {
        string tisbn = book.getIsbn();
        if (booksByISBN.find(tisbn) == booksByISBN.end())
        {
            books.push_back(move(book));
            Book& newBook = books.back();
            booksByISBN[newBook.getIsbn()] = &newBook;
            booksByAuthor[newBook.getAuthor()].insert(&newBook);
            booksByGenre[newBook.getGenre()].insert(&newBook);
        }
    }
    void borrowBook(string isbn)
    {
        if(booksByISBN.find(isbn)!=booksByISBN.end())
        {
            if (booksByISBN[isbn]->getIsAvailable())
            {
                booksByISBN[isbn]->setIsAvailable(false);
            }
        }
    }
    void returnBook(string isbn)
    {
        if (booksByISBN.find(isbn) != booksByISBN.end())
        {
            if (!booksByISBN[isbn]->getIsAvailable())
            {
                booksByISBN[isbn]->setIsAvailable(true);
            }
        }
    }
    void removeBook(string isbn)
    {
        auto it = booksByISBN.find(isbn);
        if (it!=booksByISBN.end())
        {
            Book* booktr = it->second;
            booksByISBN.erase(it);

            string author = booktr->getAuthor();
            auto authorIt = booksByAuthor.find(author);
            if (authorIt!=booksByAuthor.end())
            {
                authorIt->second.erase(booktr);
                if (authorIt->second.empty())
                {
                    booksByAuthor.erase(authorIt);
                }
            }
            string genre = booktr->getGenre();
            auto genreIt = booksByGenre.find(genre);
            if (genreIt!=booksByGenre.end())
            {
                genreIt->second.erase(booktr);
                if (genreIt->second.empty())
                {
                    booksByGenre.erase(genreIt);
                }
            }
            for (auto bookIt = books.begin(); bookIt!=books.end() ; ++bookIt)
            {
                if (&(*bookIt)==booktr)
                {
                    books.erase(bookIt);
                    break;
                }
            }



        }
    }

    vector<Book*>getAvailableBooks()
    {
        vector<Book*>boks;

        for (Book& bok : books)
        {
            if (bok.getIsAvailable())
            {
                boks.push_back(&bok);
            }
        }
        return boks;
    }
    vector<Book*>getBorrowedBooks()
    {
        vector<Book*>boks;

        for (Book& bok : books)
        {
            if (!bok.getIsAvailable())
            {
                boks.push_back(&bok);
            }
        }
        return boks;
    }
    map<string, int> getStatistics()
    {
        map<string, int>stats;
        for (auto& [genre, num] : booksByGenre)
        {
            stats[genre] = num.size();
        }
        return stats;
    }

    void saveToFile(const string& filename)
    {
        ofstream file(filename);
        for (const Book& book : books)
        {
            file << book.getTitle() << "," << book.getAuthor() << "," << book.getYear() << ",";
            file << book.getIsbn() << "," << book.getGenre() << "," << (book.getIsAvailable() ? "1" : "0") << "\n";
        }
    }
    vector<Book>loadFromFile(const string& filename)
    {
        ifstream file(filename);
        vector<Book>books;      
        string line;
        while (getline(file, line))
        {
            string title, author, syear, isbn, genre, savi;
            stringstream st(line);
            getline(st, title, ',');
            getline(st, author, ',');
            getline(st, syear, ',');
            getline(st, isbn, ',');
            getline(st, genre, ',');
            getline(st, savi);
            int year=stoi(syear);
            bool avi;
            if (savi == "1") { avi = true; }
            Book book(title, author, year, isbn, genre, avi);
            books.push_back(book);
        }
        return books;
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
   
   
}

