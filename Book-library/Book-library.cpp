#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>   
#include <set>   
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

    string getTitle() { return title; }
    string getAuthor() { return author; }
    int getYear() { return year; }
    string getIsbn() { return ISBN; }
    string getGenre() { return genre; }
    bool getIsAvailable() { return isAvailable; }

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
};

int main()
{
    setlocale(LC_ALL, "ru");
    
    
}

