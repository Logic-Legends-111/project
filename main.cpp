#include <iostream>
#include <string>
#include <fstream>

#include <cctype>

#include <cstdlib>
#include <ctime>

using namespace std;

// Function to capatalize a given string

string cap(string &s)
{
    for (char &c : s) // reference to actual character
        c = toupper(c);
    return s;
}

// Function to return tomorrow's date

string Date_Tomorrow()
{
    time_t now = time(0);           // Get current time
    tm *tomorrow = localtime(&now); // Convert to local time

    tomorrow->tm_mday += 1; // Add one day
    mktime(tomorrow);       //Normalize the structure

    // Create string in DD-MM-YYYY format
    string d = (tomorrow->tm_mday < 10 ? "0" : "") + to_string(tomorrow->tm_mday) + "-" +
               (tomorrow->tm_mon + 1 < 10 ? "0" : "") + to_string(tomorrow->tm_mon + 1) + "-" +
               to_string(1900 + tomorrow->tm_year);

    return d;
}

void view_available_seats()
{
    ifstream in("Seats.txt", ios::in);
    string s;
    while (in.eof() == 0)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int i = 0; i < 5; i++)
            {
                getline(in, s);

                if (s == "0")
                {
                    s = " ";
                }
                if (s.length() == 1)
                {
                    s = " " + s;
                }

                cout << s << "  ";
            }
            cout << endl
                 << endl;
        }
        cout << endl;
    }
    in.close();
}

bool zero_seats()
{
    int counter = 0;
    ifstream in("Seats.txt", ios::in);
    string s;
    while (in.eof() == 0)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int i = 0; i < 5; i++)
            {
                getline(in, s);

                if (s == "0")
                {
                    counter += 1;
                }
            }
        }
    }
    in.close();

    if (counter == 25)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int update_seats(int dseat)
{
    string orgfile = "Seats.txt";
    string tempfile = "w.txt";

    ifstream in(orgfile, ios::in);
    ofstream out(tempfile, ios::out);
    string s;
    while (in.eof() == 0)
    {
        getline(in, s);

        if (s == to_string(dseat))
        {
            s = "0";
        }
        if (dseat != 25)
        {
            out << s << endl;
        }
        else
        {
            out << s;
        }
    }

    // Replace the original file
    if (remove(orgfile.c_str()) != 0)
    {
        cerr << "Error deleting original file." << endl;
        return 1;
    }
    if (rename(tempfile.c_str(), orgfile.c_str()) != 0)
    {
        cerr << "Error renaming temporary file." << endl;
        return 1;
    }
    cout << "File updated successfully." << endl;
    return 0;
}

bool seat_available(int seat)
{
    string seatno = to_string(seat);
    bool flag = false;
    ifstream in("Seats.txt", ios::in);
    string s;
    while (in.eof() == 0)
    {
        getline(in, s);

        if (s == seatno)
        {
            flag = true;
        }
    }
    return flag;
}

int seats()
{
    if (!zero_seats())
    {
        int seat_choice;
        view_available_seats();
        cout << "Enter a seat from the available choices : ";
        cin >> seat_choice;

        bool k = false;
        do
        {
            if (seat_choice > 0 || seat_choice <= 25)
            {
                k = true;
            }
            else
            {
                cout << "Invalid input for the seats " << endl;
                cout << "Enter your seat choice (1-25) again : ";
                cin >> seat_choice;
            }
        } while (k == false);

        if (seat_available(seat_choice))
        {
            update_seats(seat_choice);
        }
        else
        {
            seats();
        }
        return seat_choice;
    }
    else
    {
        cout << "All seats booked :) ";
        return 0;
    }
}

class Booking
{
  public:
    int BookingID;
    int UserID;
    string PassengerName;
    string Source;
    string Destination;
    int SeatNo;
    string Date;
    string DepartureTime;
    string ReportingTime;
    int Price;

    // constructor

    Booking(int bid, int uid, string pname, string src, string dest, int sno, string date, string deptTime, string repTime, int p)
    {
        BookingID = bid;
        UserID = uid;
        PassengerName = pname;
        Source = src;
        Destination = dest;
        SeatNo = sno;
        Date = date;
        DepartureTime = deptTime;
        ReportingTime = repTime;
        Price = p;
    }

    Booking()
    {
    }

    void add(ofstream &file)
    {
        file << BookingID << " " << UserID << " " << PassengerName << " " << Source << " " << Destination << " " << SeatNo << " " << Date << " " << DepartureTime << " " << ReportingTime << " " << Price << "\n";
    }

    bool load(ifstream &file)
    {
        return !!(file >> BookingID >> UserID >> PassengerName >> Source >> Destination >> SeatNo >> Date >> DepartureTime >> ReportingTime >> Price); // Convert stream state to bool
    }

    void print()
    {
        cout << this->BookingID << " " << this->UserID << " " << this->PassengerName << " " << this->Source << " " << this->Destination << " " << this->SeatNo << " " << this->Date << " " << this->DepartureTime << " " << this->ReportingTime << " " << this->Price << " " << endl;
    }
};

class User
{
  public:
    int UserID;
    string UserName;
    long long int MobileNo;
    string City;

    // constructor to be used for update function

    User()
    {
    }

    // constructor for adding new user

    User(int uid, string uname, long long int mbno, string cty)
    {
        UserID = uid;
        UserName = uname;
        MobileNo = mbno;
        City = cty;
    }

    // function for add user to UserDetails file

    void add(ofstream &writer)
    {
        writer << UserID << " " << UserName << " " << MobileNo << " " << City << "\n";
    }

    // function to load the contents of UserDetails file

    bool load(ifstream &reader)
    {
        return !!(reader >> UserID >> UserName >> MobileNo >> City);
    }

    // Function to print the users

    void print(int a, int b, int c)
    {
        cout << "|" << string(a, ' ') << UserID << "|    " << UserName << string(b - 4, ' ') << "| " << MobileNo << " |   " << City << string(c - 3, ' ') << " |" << endl;
    }
};

// Ensuring Unique BookingID

bool is_copy(int r, Booking k, ifstream &file)
{
    while (k.load(file))
    {
        if (r == k.BookingID)
        {
            return true;
        }
    }
}

// Function to verify user

bool verify_user(int uid)
{
    ifstream in("UserDetails.txt", ios::in);
    bool flag = false;
    User u;
    while (u.load(in))
    {
        if (uid == u.UserID)
        {
            cout << "Verified :) " << endl;
            flag = true;
        }
    }
    return flag;
    in.close();
}

// selecting destination based on choice

string select_dest(int c)
{
    switch (c)
    {
    case 1:
        return "Ahmedabad";
    case 2:
        return "Surat";
    case 3:
        return "Mumbai";
    case 4:
        return "Bengaluru";
    default:
        return "Invalid";
    }
}

// menu for destination
void menu_dest()
{
    cout << "Choose your destination:\n"
         << "\t\t1. Ahmedabad\n"
         << "\t\t2. Surat\n"
         << "\t\t3. Mumbai\n"
         << "\t\t4. Bangaluru\n";
    cout << "Enter your choice (1-4): ";
}

// to get destination

string get_dest(int choice)
{
    string d;
    d = select_dest(choice);

    while (d == "Invalid")
    {
        cout << "Invalid choice. Please enter a number between 1 and 4: ";
        cin >> choice;
        d = select_dest(choice);
    }
    return d;
}

// to get reporting time

string get_reportingTime(int c)
{
    switch (c)
    {
    case 1:
        return "11:00";
    case 2:
        return "15:00";
    case 3:
        return "19:00";
    case 4:
        return "23:00";
    default:
        return "Invalid";
    }
}

// to get price of ticket

int get_price(int c)
{
    switch (c)
    {
    case 1:
        return 1000;
    case 2:
        return 2000;
    case 3:
        return 4000;
    case 4:
        return 7000;
    default:
        cout << "Error occur while allocating price ";
        return 1000;
    }
}

// Functions related to Booking Details

void AddBooking()
{
    int bid, uid, sno, p;
    string pname, src, dest, date, deptTime, repTime;

    cout << "Enter User ID : ";
    cin >> uid;

    // Verifying User

    bool verified = verify_user(uid);

    do
    {
        if (!verified)
        {
            cout << "\n Invalid UserID. \n Enter again :  ";
            cin >> uid;
            verified = verify_user(uid);
        }
    } while (!verified);

    // show the available seats and choose one

    sno = seats();

    if (sno != 0)
    {
        ifstream uin;
        uin.open("UserDetails.txt", ios::in);
        User u;
        while (u.load(uin))
        {
            if (uid == u.UserID)
                pname = u.UserName;
        }
        uin.close();

        // Ensuring Unique BookingID

        bool copy;
        int randomNo;
        do
        {
            ifstream in;
            in.open("bookingDetails.txt", ios::in);
            Booking k;
            srand(time(0));
            randomNo = 100000 + (rand() % (999999 - 100000 + 1));
            copy = is_copy(randomNo, k, in);
            in.close();
        } while (copy);

        bid = randomNo;
        cout << "Your Unique Booking ID is : " << bid << endl;

        cout << "Boarding point is : Jodhpur " << endl;
        src = "Jodhpur";

        // Setting date as tomorrow's date
        date = Date_Tomorrow();
        cout << "Date : " << date << endl;

        int choice;

        menu_dest();
        cin >> choice;

        dest = get_dest(choice);

        deptTime = "02:00";

        repTime = get_reportingTime(choice);

        p = get_price(choice);

        cout << "Destination : " << dest << endl;
        cout << "Departure Time (in 24 hr format) :  " << deptTime << endl;
        cout << "Reporting Time (in 24 hr format) :  " << repTime << endl;

        cout << " Ticket Price : " << p << endl;

        // declaring the object b for class Booking

        Booking b(bid, uid, pname, src, dest, sno, date, deptTime, repTime, p);

        // opening file bookingDetails

        ofstream out("bookingDetails.txt", ios::app);
        b.add(out);
        out.close();
    }
}

// to edit a booking (seatNo or destination)

void EditBooking()
{
    int p;
    string src, dest, date, deptTime, repTime;

    cout << "\033[1m \033[4mNOTE :\033[0m \033[0m";
    cout << "\t You can only change destination point ";
    int b_id;

    cout << "Enter BookingID to edit booking : ";
    cin >> b_id;

    bool found = false;
    int rewrite_seat = -1;

    ifstream fin("bookingDetails.txt", ios::in);
    ofstream fout("tempBooking.txt", ios::out);

    Booking b;
    while (b.load(fin))
    {
        if (b_id == b.BookingID)
        {
            found = true;
            int choice;

            menu_dest();
            cin >> choice;

            dest = get_dest(choice);

            deptTime = "02:00";

            repTime = get_reportingTime(choice);

            p = get_price(choice);
            cout << "Source  : " << b.Source << endl;
            cout << "Destination : " << dest << endl;
            cout << "Departure Time (in 24 hr format) :  " << deptTime << endl;
            cout << "Reporting Time (in 24 hr format) :  " << repTime << endl;

            cout << " Date : " << b.Date << endl;

            cout << " Ticket Price : " << p << endl;

            b.Destination = dest;
            b.DepartureTime = deptTime;
            b.Price = p;
        }

        b.add(fout);
    }

    fin.close();
    fout.close();

    if (found)
    {
        cout << " Your booking details updated successfully ";
    }
    else
    {
        cout << "No such Booking ID. " << endl;
    }
}

// to cancel a booking

int CancelBooking()
{
    int b_id;
    cout << "Enter BookingID to cancel booking : ";
    cin >> b_id;

    bool found = false;
    int rewrite_seat = -1;

    ifstream fin("bookingDetails.txt", ios::in);
    ofstream fout("tempBooking.txt", ios::out);

    Booking b;
    while (b.load(fin))
    {
        cout << b.BookingID << endl;
        if (b_id == b.BookingID)
        {
            rewrite_seat = b.SeatNo;
            //cout << "Verified :) " <<endl <<rewrite_seat << endl;
            found = true;
        }
        else
        {
            b.add(fout);
        }
    }

    fin.close();
    fout.close();

    if (found)
    {
        remove("bookingDetails.txt");
        rename("tempBooking.txt", "bookingDetails.txt");

        ifstream sin("Seats.txt", ios::in);
        ofstream sout("p.txt", ios::out);
        string t;
        int counter = 1;
        while (getline(sin, t))
        {
            if (counter != 25)
            {
                if (counter == rewrite_seat)
                {
                    sout << rewrite_seat << endl;
                }
                else
                {
                    sout << t << endl;
                }
            }
            else
            {
                if (counter == rewrite_seat)
                {
                    sout << rewrite_seat;
                }
                else
                {
                    sout << t;
                }
            }
            counter++;
        }

        sin.close();
        sout.close();
        remove("Seats.txt");
        rename("p.txt", "Seats.txt");
    }
    else
    {
        cout << "No such Booking ID. " << endl;
    }
    return 0;
}

// Functions related to User Details

void AddUser()
{
    int uid;
    string uname, cty;
    long long int mbno;

    cout << "Enter UserID :  ";
    cin >> uid;

    cout << "Enter UserName :  ";
    cin >> uname;

    cout << "Enter MobileNo :  ";
    cin >> mbno;

    cout << "Enter City :  ";
    cin >> cty;

    ofstream out("UserDetails.txt", ios::app);
    User u(uid, uname, mbno, cty);
    u.add(out);
    out.close();
}

void ViewAllUser()
{
    ifstream in("UserDetails.txt", ios::in);

    cout << string(74, '_') << endl;
    cout << "|UserID|" << string(9, ' ') << "UserName" << string(9, ' ') << "|  MobileNo  |" << string(10, ' ') << "City" << string(11, ' ') << "|" << endl;
    cout << string(74, '-') << endl;

    User u;
    while (u.load(in))
    {
        //cout << u.UserID << endl ;
        int uid_spaces = 6 - (to_string(u.UserID)).length();
        //cout << uid_spaces << endl ;

        //cout << u.UserName << endl ;
        int uname_spaces = 25 - ((u.UserName)).length();
        // cout << uname_spaces << endl ;

        //cout << u.City << endl ;
        int cty_spaces = 25 - ((u.City)).length();
        // cout << cty_spaces << endl ;

        u.print(uid_spaces, uname_spaces, cty_spaces);
    }
    cout << string(74, '-') << endl;
    in.close();
}

int main()
{
    int choice;
    User add;
    do
    {
        cout << "TRAVEL BOOKING SYSTEM\n";
        cout << "WELCOME TO LOGIC EXPRESS\n";
        cout << "CHOOSE AN OPTION TO CONTINUE\n";
        cout << "1.Add user \n 2.View All Users \n3.Add booking\n4.Cancel booking\n5.Edit booking\n6.Search bookings\n6.View all bookings\n7.Exit\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            AddUser();
            cout << "USER ADDED SUCCESSFULLY\n";
            break;
        case 2:
            ViewAllUser();
            break;
        case 3:
            AddBooking();
            cout << "BOOKING DONE SUCCESSFULLY\nTHANKS FOR CHOOSING US\n";
            break;
        case 4:
            CancelBooking();
            cout << "SUCCESSFULLY CANCLED";
            break;
        case 5:
            EditBooking();
            break;
        case 6:

            break;
        case 7:
            break;
        default:
            cout << "invalid input\nChoose again\n";
        }
    } while (choice != 7);

    return 0;
}
