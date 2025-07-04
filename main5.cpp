#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

string cap(string &s)
{
    for (char &c : s)
        c = toupper(c);
    return s;
}

bool isEmp(string s)
{
    if (s.empty())
    {
        cout << "    AN EMPTY INPUT :( " << endl;
        return true;
    }
    else
    {
        return false;
    }
}

bool isWhiteSp(string s)
{
    bool res = false;
    for (char ch : s)
    {
        if (isspace(ch))
        {
            cout << "    Whitespaces in the string are not allowed :(. " << endl;
            res = true;
            break;
        }
    }
    return res;
}


string Date_Tomorrow()
{
    time_t now = time(0);           
    tm *tomorrow = localtime(&now); 
    
    tomorrow->tm_mday += 1; 
    mktime(tomorrow);       

    string d = (tomorrow->tm_mday < 10 ? "0" : "") + to_string(tomorrow->tm_mday) + "-" +
               (tomorrow->tm_mon + 1 < 10 ? "0" : "") + to_string(tomorrow->tm_mon + 1) + "-" +
               to_string(1900 + tomorrow->tm_year);

    return d;
}

bool file_exists()
{
    ifstream seats_file("Seats.txt");

    return seats_file.good(); 
}

void view_available_seats()
{
    ifstream in("Seats.txt", ios::in);
    string s;

    for (int i = 0; i < 5; i++) 
    {
        for (int j = 0; j < 5; j++) 
        {
            if (getline(in, s))
            {
                if (s == "0")
                {
                    s = "  ";
                }
                if (s.length() == 1)
                {
                    s = " " + s;
                }
                cout << s << "  ";
            }
        }
        cout << endl << endl ; 
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

void update_seats(int dseat)
{
    string orgfile = "Seats.txt";
    string tempfile = "w.txt";

    ifstream in("Seats.txt", ios::in);
    ofstream out("w.txt", ios::out);
    string s;
    while (in.eof()==0) 
    {    
        getline(in, s);
    
        if (s == to_string(dseat))
        {
            s = "0";
        }
        out << s << endl ;
    }
    in.close();
    out.close();

    remove("Seats.txt");
    rename("w.txt", "Seats.txt");
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
            if (seat_choice > 0 && seat_choice <= 25)
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
            cout << "The seat you entered is not available. " << endl;
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
    string ArrivalTime;
    int Price;

    Booking(int bid, int uid, string pname, string src, string dest, int sno, string date, string deptTime, string arvTime, int p)
    {
        BookingID = bid;
        UserID = uid;
        PassengerName = pname;
        Source = src;
        Destination = dest;
        SeatNo = sno;
        Date = date;
        DepartureTime = deptTime;
        ArrivalTime = arvTime;
        Price = p;
    }

    Booking()
    {
    }

    void add(ofstream &file)
    {
        file << BookingID << " " << UserID << " " << PassengerName << " " << Source << " " << Destination << " " << SeatNo << " " << Date << " " << DepartureTime << " " << ArrivalTime << " " << Price << "\n";
    }

    bool load(ifstream &file)
    {
        return !!(file >> BookingID >> UserID >> PassengerName >> Source >> Destination >> SeatNo >> Date >> DepartureTime >> ArrivalTime >> Price); 
    }

    void print(int a, int b, int c, int d, int e, int f)
    {
        cout << "|  " << BookingID << "   |" << string(a - 1, ' ') << UserID << " | " << PassengerName << string(b - 1, ' ') << "| " << Source << string(c - 1, ' ') << "| " << Destination << string(d - 1, ' ') << "|" << string(e - 1, ' ') << SeatNo << " | " << Date << " |     " << DepartureTime << "     |     " << ArrivalTime << "     | " << Price << string(f - 1, ' ') << "|" << endl;
    }
};

class User
{
  public:
    int UserID;
    string UserName;
    long long int MobileNo;
    string City;
    
    User()
    {
    }

    User(int uid, string uname, long long int mbno, string cty)
    {
        UserID = uid;
        UserName = uname;
        MobileNo = mbno;
        City = cty;
    }

    void add(ofstream &writer)
    {
        writer << UserID << " " << UserName << " " << MobileNo << " " << City << "\n";
    }

    bool load(ifstream &reader)
    {
        return !!(reader >> UserID >> UserName >> MobileNo >> City);
    }
    
    void print(int a, int b, int c)
    {
        cout << "|" << string(a - 1, ' ') << UserID << " |    " << UserName << string(b - 4, ' ') << " | " << MobileNo << " |   " << City << string(c - 3, ' ') << "|" << endl;
    }
};

bool is_copy_booking(int r, Booking k, ifstream &file)
{
    while (k.load(file))
    {
        if (r == k.BookingID)
        {
            return true;
        }
    }
}

bool is_copy_user(int r, User k, ifstream &file)
{
    while (k.load(file))
    {
        if (r == k.UserID)
        {
            return true;
        }
    }
}

bool num_format(long int num)
{
    int count = 0;
    while (num)
    {
        num = num / 10;
        ++count;
    }
    if (count == 10)
    {
        return true;
    }
    return false;
}

bool valid_NameFormat(string a)
{
    for (char &c : a)
    {
        if (c == '_')
        {
            continue;
        }
        if (isalpha(c))
        {
            continue;
        }
        else
        {
            cout << "Numbers or Special characters are not allowed except ( _ ) . " << endl ;
            return false;
        }
    }
    return true;
}

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

void menu_dest()
{
    cout << "Choose your destination:\n"
         << "\t\t1. Ahmedabad\n"
         << "\t\t2. Surat\n"
         << "\t\t3. Mumbai\n"
         << "\t\t4. Bangaluru\n";
    cout << "Enter your choice (1-4): ";
}

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

string get_arrivalTime(int c)
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

void AddBooking()
{
    int bid, uid, sno, p;
    string pname, src, dest, date, deptTime, arvTime;

    cout << "Enter User ID : ";
    cin >> uid;

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

        bool copy;
        int randomNo;
        do
        {
            ifstream in;
            in.open("bookingDetails.txt", ios::in);
            Booking k;
            srand(time(0));
            randomNo = 100000 + (rand() % (999999 - 100000 + 1));
            copy = is_copy_booking(randomNo, k, in);
            in.close();
        } while (copy);

        bid = randomNo;
        cout << "Your Unique Booking ID is : " << bid << endl;

        cout << "Boarding point is : Jodhpur " << endl;
        src = "Jodhpur";

        date = Date_Tomorrow();
        cout << "Date : " << date << endl;

        int choice;

        menu_dest();
        cin >> choice;

        dest = get_dest(choice);

        deptTime = "02:00";

        arvTime = get_arrivalTime(choice);

        p = get_price(choice);

        cout << "Destination : " << dest << endl;
        cout << "Departure Time (in 24 hr format) :  " << deptTime << endl;
        cout << "Arrival Time (in 24 hr format) :  " << arvTime << endl;

        cout << " Ticket Price : " << p << endl;

        Booking b(bid, uid, pname, src, dest, sno, date, deptTime, arvTime, p);

        ofstream out("bookingDetails.txt", ios::app);
        b.add(out);
        out.close();
    }
}

void EditBooking()
{
    int p;
    string src, dest, date, deptTime, arvTime;

    cout << "\033[1m \033[4mNOTE :\033[0m \033[0m";
    cout << "\t \nYou can only change destination point " << endl;
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

            arvTime = get_arrivalTime(choice);

            p = get_price(choice);
            cout << "Source  : " << b.Source << endl;
            cout << "Destination : " << dest << endl;
            cout << "Departure Time (in 24 hr format) :  " << deptTime << endl;
            cout << "Arrival Time (in 24 hr format) :  " << arvTime << endl;

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
        remove("bookingDetails.txt");
        rename("tempBooking.txt", "bookingDetails.txt");
        cout << " Your booking details updated successfully ";
    }
    else
    {
        remove("tempBooking.txt");
        cout << "No such Booking ID. " << endl;
    }
}

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
        
        if (b_id == b.BookingID)
        {
            rewrite_seat = b.SeatNo;
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
        rename("tempBooking.txt", "bookingDetails.txt");        cout << "Successfully Cancelled \n\n";

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
        remove("tempBooking.txt");
        cout << "No such Booking ID. " << endl;
    }
    return 0;
}

void ViewAllBookings()
{
    ifstream in("bookingDetails.txt", ios::in);

    cout << string(136, '-') << endl;

    cout << "| BookingID | UserID |  PassengerName  |    Source     |  Destination  | SeatNo |    Date    | DepartureTime |  ArrivalTime  |  Price  |" << endl;
    cout << string(136, '-') << endl;

    Booking b;
    while (b.load(in))
    {
        int uid_spaces = 8 - (to_string(b.UserID)).length();

        int pname_spaces = 17 - ((b.PassengerName)).length();

        int src_spaces = 15 - ((b.Source)).length();

        int dest_spaces = 15 - ((b.Destination)).length();

        int sno_spaces = 8 - (to_string(b.SeatNo)).length();

        int p_spaces = 9 - (to_string(b.Price)).length();

        b.print(uid_spaces, pname_spaces, src_spaces, dest_spaces, sno_spaces, p_spaces);
    }
    cout << string(136, '-') << endl;
    in.close();
}

void SearchBooking()
{
    string k;

    int counter = 0;

    while (true)
    {
        cout << "Enter Passenger Name or Destination to search a booking(s): ";

        if (counter == 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            counter++;
        }

        getline(cin, k);

        if (isEmp(k))
        {
            cout << "Invalid Input. Try again.\n";
            continue;
        }

        if (isWhiteSp(k))
        {
            cout << "Invalid Input. Try again.\n";
            continue;
        }
        
        if (!valid_NameFormat(k))
        {
           cout << "Invalid Input. Try again. \n";
           continue ;
        }

        break; 
    }

    bool found = false, print_fields = true;

    ifstream fin("bookingDetails.txt", ios::in);

    Booking b;
    while (b.load(fin))
    {
        if (cap(k) == cap(b.PassengerName) || cap(k) == cap(b.Destination))
        {
            found = true;

            if (print_fields)
            {
                cout << string(136, '-') << endl;
                cout << "| BookingID | UserID |  PassengerName  |    Source     |  Destination  | SeatNo |    Date    | DepartureTime |  ArrivalTime  |  Price  |" << endl;
                cout << string(136, '-') << endl;
                print_fields = false;
            }

            int uid_spaces = 8 - (to_string(b.UserID)).length();

            int pname_spaces = 17 - ((b.PassengerName)).length();

            int src_spaces = 15 - ((b.Source)).length();

            int dest_spaces = 15 - ((b.Destination)).length();

            int sno_spaces = 8 - (to_string(b.SeatNo)).length();

            int p_spaces = 9 - (to_string(b.Price)).length();

            b.print(uid_spaces, pname_spaces, src_spaces, dest_spaces, sno_spaces, p_spaces);

            cout << string(136, '-') << endl;
        }
    }
    if (found == false)
    {
        cout << "No such booking with this PassengerName or Destination.  :( " << endl;
    }
    fin.close();
}

void AddUser()
{
    int uid;
    string uname, cty;
    long long int mbno;

    bool copy;
    bool negative = false;
    int count = 0;

    do
    {
        ifstream uin;
        uin.open("UserDetails.txt", ios::in);
        if (count)
        {
            cout << "Invalid UserID (already exists or should always be positive)  :( " << endl;
        }
        User u;
        cout << "Enter UserID (a valid positive number between 1 and 99999 ) :  ";
        cin >> uid;
        if (uid<=0){
            negative = true ;
        }
        copy = is_copy_user(uid, u, uin);
        uin.close();
        count++;
    } while (copy || negative);

    int counter = 0;

    while (true)
    {
        cout << "Enter User Name : ";

        if (counter == 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            counter++;
        }

        getline(cin, uname);

        if (isEmp(uname))
        {
            cout << "Invalid Input. Try again.\n";
            continue;
        }

        if (isWhiteSp(uname))
        {
            cout << "Invalid Input. Try again.\n";
            continue;
        }
        
        if (!valid_NameFormat(uname))
        {
           cout << "Invalid Input. Try again. \n";
           continue ;
        }

        break; 
    }
    
    
    bool res = false;
    int n = 0;
    do
    {
        if (n)
        {
            cout << "Invalid Mobile Number format :( \n Again ";
        }
        cout << "Enter MobileNo :  ";
        cin >> mbno;
        res = num_format(mbno);
        n++;
    } while (res == false);
    
    
    int ct = 0;

    while (true)
    {
        cout << "Enter City : ";

        if (ct == 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ct++;
        }

        getline(cin, cty);

        if (isEmp(cty))
        {
            cout << "Invalid Input. Try again.\n";
            continue;
        }

        if (isWhiteSp(cty))
        {
            cout << "Invalid Input. Try again.\n";
            continue;
        }
        break; 
    }

    

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
        int uid_spaces = 6 - (to_string(u.UserID)).length();

        int uname_spaces = 25 - ((u.UserName)).length();

        int cty_spaces = 25 - ((u.City)).length();

        u.print(uid_spaces, uname_spaces, cty_spaces);
    }
    cout << string(74, '-') << endl;
    in.close();
}

void display_available_seats()
{
    if (zero_seats())
    {
        cout << "All seats are booked (1—25) " << endl;
    }
    else
    {
        int counter = 1;
        vector<string> booked;
        vector<string> free;

        ifstream in("Seats.txt", ios::in);
        string s;
        while (in.eof() == 0)
        {
            getline(in, s);

            if (s == "0")
            {
                booked.push_back(to_string(counter));
            }
            else
            {
                free.push_back((s));
            }
            counter++;
        }
        in.close();
        

        cout << "\nBooked Seats are : " << endl;

        for (int i = 0; i < booked.size(); i++)
        {
            if (booked[i] == booked.back())
            {
                cout << booked[i];
            }
            else
            {
                cout << booked[i] << ", ";
            }
        }
        cout << "\n";

        cout << "\nFree Seats are : " << endl;
        for (int i = 0; i < free.size(); i++)
        {
            if (free[i] == free.back())
            {
                cout << free[i];
            }
            else
            {
                cout << free[i] << ", ";
            }
        }
        cout << "\n";
    }
}

int main()
{
    if (!file_exists())
    {
        ofstream out("Seats.txt", ios::out);
        if (out.is_open())
        {
            for (int i = 1; i <= 25; i++)
            {
                if (i < 25)
                    out << i << endl;
                else
                    out << i;
            }
            out.close();
        }
    }
    cout << string(85, ':') << "\n"
         << endl;
    cout << "\t\t\t   TRAVEL BOOKING SYSTEM \n";
    cout << "\t\t\t WELCOME TO LOGIC EXPRESS \n";
    cout << "\t\t\t   -(Bus Travel Agency)  " << endl;
    
    int choice;
    do
    {
        cout << " 1.Add user \n 2.View All Users \n 3.Add booking \n 4.Cancel booking \n 5.Edit booking \n 6.Search a booking \n 7.View all bookings \n 8.Show available seats \n 9.Exit \n"
             << endl;

        cout << "\n Choose an option to continue :  ";
        cin >> choice;

        cout << "\n"
             << string(85, '~') << "\n"
             << endl;

        switch (choice)
        {
        case 1:
            AddUser();
            cout << "\nUSER ADDED SUCCESSFULLY\n\n";
            break;
        case 2:
            ViewAllUser();
            cout << "\n\n";
            break;
        case 3:
            AddBooking();
            cout << "Booking done successfully \n Thanks for Choosing Us :) \n";
            break;
        case 4:
            CancelBooking();
            break;
        case 5:
            EditBooking();
            break;
        case 6:
            SearchBooking();
            break;
        case 7:
            ViewAllBookings();
            break;
        case 8:
            display_available_seats();
            break;
        case 9:
            cout << "\n"
                 << string(58, ' ') << "Program Exited !! " << endl;
            break;

        default:
            cout << "Invalid input \n Choose again \n";
        }

        cout << "\n"  << string(85, ':') << "\n\n"  << endl;

    } while (choice != 9);

    return 0;
}