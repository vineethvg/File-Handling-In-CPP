#include <iostream>
#include <fstream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ios;
using std::ofstream;

class account_query
{
private:
    char account_number[20];
    char first_Name[10];
    char last_Name[20];
    char total_Balance[20];

public:
    void read_data();
    void show_data();
    void write_rec();
    void read_rec();
    void search_rec();
    void edit_rec();
    void delete_rec();
};

void account_query::read_data()
{
    cout << "\nEnter Account Number: ";
    cin >> account_number;
    cout << "Enter First Name: ";
    cin >> first_Name;
    cout << "Enter Last Name: ";
    cin >> last_Name;
    cout << "Enter Balance: ";
    cin >> total_Balance;
}

void account_query::show_data()
{
    cout << "Account Number: " << account_number << endl;
    cout << "First Name: " << first_Name << endl;
    cout << "Last Name: " << last_Name << endl;
    cout << "Total Balance: Rs.  " << total_Balance << endl;
    cout << "--------------------------------------" << endl;
}

void account_query::write_rec()
{
    ofstream outfile;
    outfile.open("record.bank", ios::binary | ios::app);
    read_data();
    outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
    outfile.close();
}

void account_query::read_rec()
{
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if (!infile)
    {
        cout << "Error in Opening! File Not Found!" << endl;
        return;
    }
    cout << "\n*******Data From File*******" << endl;
    while (!infile.eof())
    {
        if (infile.read(reinterpret_cast<char *>(this), sizeof(*this)) > 0)
        {
            show_data();
        }
    }
    infile.close();
}

void account_query::search_rec()
{
    int n;
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if (!infile)
    {
        cout << "\n Error in Opening File! File Not Found!!" << endl;
        return;
    }
    infile.seekg(0, ios::end);
    int count = infile.tellg() / sizeof(*this);
    cout << "\n There are " << count << "record in the file";
    cout << "\n Enter Record Number to Search: ";
	cin >> n;
    infile.seekg((n - 1) * sizeof(*this));
    infile.read(reinterpret_cast<char *>(this), sizeof(*this));
    show_data();
}

void account_query::edit_rec()
{
    int n;
    fstream iofile;
    iofile.open("record.bank", ios::in | ios::binary);
    if (!iofile)
    {
        cout << "\nError in Opening! File Not Found" << endl;
        return;
    }
    iofile.seekg(0, ios::end);
    int count = iofile.tellg() / sizeof(*this);
    cout << "\nThere are " << count << " records in the file";
    cout << "\n Enter the record number to edit: ";
    cin >> n;
    iofile.seekg((n - 1)*sizeof(*this));
    iofile.read(reinterpret_cast<char *>(this), sizeof(*this));
    cout << "Record" << n << " has following data" << endl;
    show_data();
    iofile.close();
    iofile.open("record.bank", ios::out | ios::in | ios::binary);
    iofile.seekp((n - 1) * sizeof(*this));
    cout << "\nEnter data to Modify " << endl;
    read_data();
    iofile.write(reinterpret_cast<char *>(this), sizeof(*this));
}

void account_query::delete_rec()
{
    int n;
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if (!infile)
    {
        cout << "\nError in opening! File not found!!" << endl;
        return;
    }
    infile.seekg(0, ios::end);
    int count = infile.tellg() / sizeof(*this);
    cout << "\nThere are " << count << " records in the file";
    cout << "\n Enter the record number to delete: ";
    cin >> n;
    fstream tmpfile;
    tmpfile.open("tmpfile.bank", ios::out |ios::binary);
    infile.seekg(0);
    for (int i = 0; i < count;  i++)
    {
        infile.read(reinterpret_cast<char *>(this), sizeof(*this));
        if (i == (n - 1))
            continue;
        tmpfile.write(reinterpret_cast<char *>(this), sizeof(*this));
    }
    infile.close();
    tmpfile.close();
    remove("record.bank");
    rename("tmpfile.bank", "record.bank");
}

int main()
{
    account_query A;
    int choice;
    cout << "*** Account Information System***" << endl;
    while (true)
    {
        cout << "Select one option below ";
        cout << "\n\t1-->Add record to file";
        cout << "\n\t2-->Show record from file";
        cout << "\n\t3-->Search record from file";
        cout << "\n\t4-->Update Record";
        cout << "\n\t5-->Delete Record";
        cout << "\n\t6-->Quit";
        cout << "\nEnter Your Choice";
        cin >> choice;
        switch (choice)
        {
        case 1:
            A.write_rec();
            break;
        case 2:
            A.show_data();
            break;
        case 3:
            A.search_rec();
            break;
        case 4:
            A.edit_rec();
            break;
        case 5:
            A.delete_rec();
            break;
        case 6:
            exit(0);
            break;
        default:
            cout << "\nEnter correct choice";
            exit(0);
        }
    }
    system("pause");
    return 0;
}
