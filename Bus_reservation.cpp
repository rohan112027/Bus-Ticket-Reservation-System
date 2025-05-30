#include <bits/stdc++.h>
using namespace std;

// Struct to store passenger information
struct Passenger {
    string name;
    string phone;
    char gender;
};

// Struct to represent each Bus
struct Bus {
    string busID, from, to, time;
    string seats[5][4];             // 5x4 = 20 seats
    Passenger passengerInfo[5][4];  // Passenger data
    Bus* next;

    Bus(string id,string f, string t, string tm) {
        busID= id;
        from = f;
        to = t;
        time = tm;
        next = nullptr;

        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 4; ++j)
                seats[i][j] = "Empty";
    }

    void showSeats() {
        cout << "\nSeat Map (Bus ID: " << busID << "):\n";
        int seatNumber = 1;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 4; ++j, ++seatNumber) {
                string display = (seats[i][j] == "Empty") ? "Empty" : "Booked";
                cout << "[" << setw(2) << seatNumber << ": " << setw(6) << display << "] ";
            }
            cout << endl;
        }
    }

    bool bookSeat(int seatNum, string name, string phone, char gender) {
        if (seatNum <1 || seatNum > 20) 
        
        return false;

        int row = (seatNum - 1) / 4;
        int col= (seatNum - 1) % 4;

        if (seatNum <= 10 && gender != 'F') {
            cout << " Seat " << seatNum << " is reserved for female passengers\n";
            return false;
        }

        if (seats[row][col] != "Empty") {
            cout << " Seat " << seatNum << " is already booked\n";
            return false;
        }

        seats[row][col] = name;
        passengerInfo[row][col] = {name, phone, gender};
        return true;
    }

    void cancelSeat(int seatNum) {
        int row = (seatNum - 1) / 4;
        int col= (seatNum - 1) % 4;

        if (seats[row][col] == "Empty") {
            cout << "Seat " << seatNum << " is already empty\n";
        } else {
            seats[row][col] = "Empty";
            passengerInfo[row][col] = {"", "", '\0'};
            cout << "Reservation for seat " << seatNum << " has been canceled successfully\n";
        }
    }

    void generateTicket(int seatNum) {
        int row = (seatNum - 1) / 4;
        int col = (seatNum - 1) % 4;

        Passenger p = passengerInfo[row][col];
        cout << "\n========== TICKET ==========\n";
        cout<< "Passenger : " << p.name << "\n";
        cout<< "Gender    : " << ((p.gender == 'F') ? "Female" : "Male") << "\n";
        cout << "Phone No. : " << p.phone << "\n";
        cout << "Seat No.  : " << seatNum << "\n";
        cout << "Bus ID    : " << busID<< "\n";
        cout<< "Route     : " << from << " -> " << to << "\n";
        cout << "Departure : " << time << "\n";
        cout << "=============================\n";
    }
};

class BusSystem {
    Bus* head = NULL;

public:
    void addBus() {
        string id, from, to, time;
        cout << "\nEnter Bus ID: ";
         cin >> id;
        cout <<"From: "; 
        cin >> from;
        cout << "To: ";
         cin >> to;
        cout << "Departure Time: ";
         cin >> time;

        Bus* newBus = new Bus(id, from, to, time);
        if (head==NULL) 
        head = newBus;
        else {
            Bus* temp = head;
            while (temp->next) 
            temp = temp->next;
            temp->next = newBus;
        }
    }

    void showAvailableBuses() {
        Bus* temp = head;
        if (temp== NULL) {
            cout << "\nNo buses available.\n";
            return;
        }

        cout << "\n----------------------------------------------------\n";
        cout << "Bus ID\tFrom\t\tTo\t\tDeparture Time\n";
        cout << "------------------------------------------------------\n";
        while (temp!= NULL) {
            cout << temp->busID << "\t" << temp->from << "\t\t" << temp->to << "\t\t" << temp->time << endl;
            temp = temp->next;
        }
    }

    void bookTicket() {
        string from, to;
        cout << "\nEnter Source: "; cin >> from;
        cout << "Enter Destination: "; cin >> to;
    
        Bus* temp = head;
        bool found = false;
    
        cout << "\nAvailable Buses:\n";
        while (temp!= NULL) {
            if (temp->from == from && temp->to == to) {
                cout << "- Bus ID: " << temp->busID << " | Time: " << temp->time << "\n";
                found = true;
            }
            temp = temp->next;
        }
    
        if (found==false) {
            cout << "No buses found for the given route\n";
            return;
        }
    
        string selectedID;
        cout << "\nEnter Bus ID to book: ";
        cin >> selectedID;
    
        temp = head;
        while (temp != NULL && temp->busID != selectedID)
          temp = temp->next;
    
        if (temp== NULL) {
            cout << "Invalid Bus ID\n";
            return;
        }
    
        temp->showSeats();
    
        int seatNo;
        cout << "\nEnter Seat Number (1-20): ";
        cin >> seatNo;
    
        if (seatNo < 1 || seatNo > 20) {
            cout << "Invalid seat number\n";
            return;
        }
    
        int row = (seatNo - 1) / 4;
        int col = (seatNo - 1) % 4;
    
        if (temp->seats[row][col] != "Empty") {
            cout << " Seat " << seatNo << " is already booked.\n";
            cout << " Booking failed\n";
            return;
        }
    
        string name, phone;
        char gender;
        cout << "Passenger Name: ";
         cin >> name;
        cout << "Phone Number: "; 
        cin >> phone;
        cout << "Gender (M/F): ";
         cin >> gender;
    
        gender = toupper(gender);
        if (gender != 'M' && gender != 'F') {
            cout << "Invalid gender input\n";
            return;
        }
    
        if (seatNo <= 10 && gender != 'F') {
            cout << " Seat " << seatNo << " is reserved for female passengers\n";
            return;
        }
    
        if (temp->bookSeat(seatNo, name, phone, gender)) {
            cout << " Seat booked successfully\n";
            temp->generateTicket(seatNo);
        } else {
            cout << " Booking failed.\n";
        }
    }
    void showTicketsForBusID() {
        string busID;
        cout << "\nEnter Bus ID to view tickets: ";
        cin >> busID;
    
        Bus* temp = head;
        while (temp != NULL && temp->busID != busID)
            temp = temp->next;
    
        if (temp == NULL) {
            cout << "Invalid Bus ID.\n";
            return;
        }
    
        bool found = false;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (temp->seats[i][j] != "Empty") {
                    int seatNo = i * 4 + j + 1;
                    temp->generateTicket(seatNo);
                    found = true;
                }
            }
        }
    
        if (found==false) {
            cout << "\nNo tickets booked yet for Bus ID: " << busID << "\n";
        }
    }
    
    
    void cancelReservation() {
        string busID;
        int seatNo;

        cout << "\nEnter Bus ID: ";
        cin >> busID;

        Bus* temp = head;
        while (temp != NULL && temp->busID != busID)
         temp = temp->next;

        if (temp== NULL) {
            cout << "Invalid Bus ID\n";
            return;
        }

        temp->showSeats();

        cout << "\nEnter Seat Number to cancel (1-20): ";
        cin >> seatNo;

        if (seatNo < 1 || seatNo > 20) {
            cout << "Invalid seat number\n";
            return;
        }

        temp->cancelSeat(seatNo);
    }

    void showAllTickets() {
        Bus* temp = head;
        bool found = false;

        while (temp) {
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (temp->seats[i][j] != "Empty") {
                        int seatNo = i * 4 + j + 1;
                        temp->generateTicket(seatNo);
                        found = true;
                    }
                }
            }
            temp = temp->next;
        }

        if (found==false) {
            cout << "\nNo tickets booked yet.\n";
        }
    }
};

int main() {
    BusSystem system;

    int numBuses;
    cout << "============= Admin ============== \n";
    cout << "Enter the number of buses to add: ";
    cin >> numBuses;

    for (int i = 0; i < numBuses; ++i) {
        cout << "\nAdding Bus " << i + 1 << ":\n";
        system.addBus();
    }

    int choice;
    while (1) {
        cout << "\n====== Bus Reservation System ======\n";
        cout << "1. Show Available Buses\n";
        cout<< "2. Book Ticket (User)\n";
        cout<< "3. View All Booked Tickets\n";
        cout<< "4. Cancel Reservation\n";
        cout<< "5. Add New Bus (Admin)\n"; 
        cout << "6. View Tickets for Specific Bus ID\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
    
        switch (choice) {
            case 1: system.showAvailableBuses();
            break;
            case 2: system.bookTicket(); 
             break;
            case 3: system.showAllTickets();
             break;
            case 4: system.cancelReservation();
             break;
            case 5:
                cout << "\nAdding New Bus:\n";
                system.addBus();
                break;
            case 6:
                system.showTicketsForBusID();
                break;
            case 7:
                cout << "Exit\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
    
}


