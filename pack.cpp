#include <iostream>
#include <fstream>
#include <string.h>
#define MAXSZ 100

using namespace std;

class Record {
    string usn, name, sem;
    string packed;
public:
    Record() {}
    Record(string usn_, string name_, string sem_) : usn(usn_), name(name_), sem(sem_) {}

    void pack();
    void unpack();
    void read(fstream &f);
    void write(fstream &f);
    void print();
    string getUSN() {
        return usn;
    }
};

void Record::print() {
    cout << "USN :" << usn << '\n' << "Name : " << name << '\n' << "Semester : " << sem << '\n';
}

void Record::pack() {
    packed = usn + "|" + name + "|" + sem + "|";
}

void Record::unpack() {
    char *dst = new char[MAXSZ];
    strcpy(dst, packed.c_str());
    usn = strsep(&dst, "|");
    name = strsep(&dst, "|");
    sem = strsep(&dst, "|");

}

void Record::read(fstream &f) {
    f.seekg(0, ios::cur);
    char dst[MAXSZ];
    f.read(dst, MAXSZ);
    packed = dst;
}

void Record::write(fstream &f) {
    f.seekp(0, ios::cur);
    f.write(packed.c_str(), MAXSZ);
}

Record* newRecord() {
    string usn,name,sem;
    cout << "Enter USN, Name, Sem" << '\n';
    cin >> usn >> name >> sem;
    return new Record(usn, name, sem);
}

Record* find(fstream &f, string usn) {
    f.seekg(0, ios::beg);
    Record *r = new Record();
    while (1) {
        r->read(f);
        if (!f.eof()) {
            r->unpack();
            if (r->getUSN() == usn)
                return r;
        } else
            break;
    }
    return nullptr;
}

Record* search(fstream& f) {
    string usn;
    cout << "Enter the USN of the record : ";
    cin >> usn;

    Record* r;
    if ((r = find(f, usn)) == nullptr)
        cout << "Record not found\n";
     else
        r->print();
    return r;
}

int main(int argc, char const *argv[]) {
    char ch = 1;
    fstream f;
    f.open("file", ios::binary | ios::out | ios::in);

    if (!f.good()) {
        f.open("file", ios::binary | ios::out | ios::in | ios::trunc);
    }

    while (ch != '4') {
        cout << "1. Write\n2. Read\n3. Modify\n4. Exit" << '\n';
        cin >> ch;
        switch (ch) {
            case '1':
            {
                Record *r = newRecord();
                f.seekp(0, ios::end);
                r->pack();
                r->write(f);
                break;
            }
            case '2':
                search(f);
                break;
            case '3':
            {
                Record* r = search(f);
                cout << "Searched \n";
                if (r) {
                    cout << "Modifications : \n";
                    Record *nr = newRecord();
                    nr->pack();
                    f.seekp(-MAXSZ, ios::cur);
                    nr->write(f);
                }
                break;
            }
        }
    }

    f.close();
    return 0;
}
