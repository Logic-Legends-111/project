SPARK Project 01 : Travel Booking System

---

🚌 Travel Booking System – Logic Express

Project Overview


---

🔧 1. Objective

To build a console-based seat reservation system for a fictional bus travel agency named Logic Express. The system enables:

Adding and managing users.

Booking and managing travel tickets.

Viewing and updating seat availability.

Persisting data using plain text files (Seats.txt, UserDetails.txt, bookingDetails.txt).



---

🧩 2. Core Functionalities

A. User Management

Add User: Register a user with a unique UserID, UserName, MobileNo, and City.

View All Users: Display all registered users in a tabular format.

Validation: Ensures UserID uniqueness and correct mobile number format.


B. Booking Management

Add Booking:

Validates user existence using UserID.

Displays available seats (1–25).

Assigns a random unique BookingID.

Sets source as Jodhpur and destination based on user choice.

Automatically sets tomorrow's date as the journey date.

Calculates ticket price and reporting time based on destination.

Updates the Seats.txt file to mark the seat as booked.

Saves booking details to bookingDetails.txt.


Edit Booking:

Allows updating the destination only.

Updates corresponding ticket price and reporting time.


Cancel Booking:

Deletes booking based on BookingID.

Frees the corresponding seat in Seats.txt.


Search Booking:

Search by Passenger Name or Destination.

Case-insensitive matching.

Displays matching bookings.


View All Bookings:

Lists all bookings in a formatted table.



C. Seat Management

View Available Seats: Displays the seat matrix with available (numbered) and booked (0) seats.

Display Available/Booked Lists: Lists both free and booked seats as numbered lists.


D. File Handling

Uses text files to persist data:

UserDetails.txt for user data.

bookingDetails.txt for booking records.

Seats.txt to track seat availability.




---

📂 File Structure

File Name	Purpose

Seats.txt	Stores seat status (1–25 or 0)
UserDetails.txt	Stores all registered users
bookingDetails.txt	Stores booking records
tempBooking.txt, p.txt, w.txt	Used as temporary files for updating



---

🧠 Important Concepts Used

Object-Oriented Programming:

Classes: User, Booking

Encapsulation of data and methods


File Handling:

Read/write operations using ifstream, ofstream


Standard Template Library:

vector<string> used to store and display available/booked seats.


Input Validation:

Unique IDs, valid mobile number format, valid seat and destination choices.


Random Number Generation:

For creating unique BookingID using rand() with srand(time(0))


Date Handling:

Uses ctime library to automatically set tomorrow’s date.




---

🖥️ Main Menu Features

1. Add user
2. View All Users
3. Add booking
4. Cancel booking
5. Edit booking
6. Search a booking
7. View all bookings
8. Show available seats
9. Exit


---

✅ Advantages

Easy to understand and extend.

Data persistence through text files.

Modular structure with clearly defined responsibilities.

Simulates a real-world booking system with essential features.



---

⚠️ Limitations & Suggestions for Improvement

Limitation	Suggestion

No login or authentication	Add login system using UserID/Password
Text file usage only	Upgrade to use database (e.g., SQLite)
Linear seat storage	Use 2D vector for cleaner matrix representation
Not thread-safe	Not critical now, but important in a multi-user environment
No input sanitization (e.g., string names)	Add getline() and string validations



---

🔚 Conclusion

This Travel Booking System serves as a solid foundation for understanding C++ concepts like file handling, class-based design, and user interaction. With some enhancements, it can evolve into a fully functional travel booking platform.

Let me know if you’d like a UML diagram, flowchart, or specific module breakdown.
