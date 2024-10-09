#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Movie
{
    string title;
    string showtiming;
    double rating;
    long long availableseat;
    vector<int> seats;

public:
    Movie(string t, string sh, double r, long long av)
    {
        title = t;
        showtiming = sh;
        rating = r;
        availableseat = av;

        for (int i = 0; i < availableseat; i++)
        {
            seats.push_back(i);
        }
    }
    string gettitle()
    {
        return title;
    }
    double getRating()
    {
        return rating;
    }
    string getshowtiming()
    {
        return showtiming;
    }
    long long getavailableseat()
    {
        return availableseat;
    }

    void displayAvailableSeats()
    {
        cout << "Available seats: ";
        for (int seat : seats)
        {
            if (seat != -1)
                cout << seat << " ";
        }
        cout << endl;
    }

    // Book a seat
    bool bookSeat(int seatChoice)
    {
        auto it = find(seats.begin(), seats.end(), seatChoice);
        if (it != seats.end())
        {
            *it = -1;
            availableseat--;
            return true;
        }
        return false;
    }

    bool cancelSeat(int seatChoice)
    {
        auto it = find(seats.begin(), seats.end(), -1);
        if (it != seats.end())
        {
            *it = seatChoice;
            availableseat++;
            return true;
        }
        return false;
    }

    void displayMovieInfo()
    {
        cout << title << " (" << rating << "/5) - " << showtiming << " - Available Seats: " << availableseat << endl;
    }
};
class Booking
{
private:
    string username;
    string movieTitle;
    int seatNUmber;

public:
    Booking(string user, string movie, int seat)
    {
        username = user;
        movieTitle = movie;
        seatNUmber = seat;
    }

    string getUsername()
    {
        return username;
    }
    string getMovieTitle()
    {
        return movieTitle;
    }
    int getSeatNumber()
    {
        return seatNUmber;
    }
};

class BookingSystem
{
    vector<Movie> movies;
    vector<Booking> bookingseats;

public:
    void addmovie(Movie movie)
    {
        movies.push_back(movie);
    }

    void display_all_movie_by_rating()
    {
        sort(movies.begin(), movies.end(), [](Movie &a, Movie &b)
             { return a.getRating() > b.getRating(); });
        cout << "Available Movies:\n";
        for (int i = 0; i < movies.size() ; i++)
        {
            cout << i + 1 << ".";
            movies[i].displayMovieInfo();
        }
    }
    void bookseat(string username)
    {
        int moviename_number;
        int seatnumber;

        display_all_movie_by_rating();
        cout << "Select a movie by number to book a seat: ";
        cin >> moviename_number;

        if (moviename_number < 1 || moviename_number > movies.size())
        {
            cout << " Invalid Number please enter valid movie number.\n";
            return;
        }

        Movie &selectedMovie = movies[moviename_number - 1];
        selectedMovie.displayAvailableSeats();

        cout << "Select a seat: ";
        cin >> seatnumber;

        if (selectedMovie.bookSeat(seatnumber))
        {
            bookingseats.push_back(Booking(username, selectedMovie.gettitle(), seatnumber));
            cout << "Seat " << seatnumber << " booked successfully for " << selectedMovie.gettitle() << "!\n";
        }
        else
        {
            cout << "Seat is not available.\n";
        }
    }
    void cancelBooking(string userName, string movieTitle) {
        bool found = false;
        for (auto it = bookingseats.begin(); it != bookingseats.end(); ++it) {
            if (it->getUsername() == userName && it->getMovieTitle() == movieTitle) {
                int seatNumber = it->getSeatNumber();
                // Find the movie and cancel the seat
                for (Movie& movie : movies) {
                    if (movie.gettitle() == movieTitle) {
                        if (movie.cancelSeat(seatNumber)) {
                            bookingseats.erase(it);
                            cout << "Booking canceled successfully!\n";
                            found = true;
                        }
                        break;
                    }
                }
                break;
            }
        }

        if (!found) {
            cout << "No booking found for user " << userName << " in movie " << movieTitle << ".\n";
        }
    }
};

int main() {
    BookingSystem system;

    // Adding some movies to the system
    system.addmovie(Movie("Avengers", "12:00 PM",4.5, 5));
    system.addmovie(Movie("Inception", "2:00 PM",4.8, 3));
    system.addmovie(Movie("Titanic",  "4:00 PM", 4.0,2));

    int choice;
    string userName, movieTitle;

    while (true) {
        cout << "\n--- Movie Ticket Booking System ---\n";
        cout << "1. Display Available Movies\n";
        cout << "2. Book a Seat\n";
        cout << "3. Cancel Booking\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system.display_all_movie_by_rating();
                break;
            case 2:
                cout << "Enter your name: ";
                cin >> userName;
                system.bookseat(userName);
                break;
            case 3:
                cout << "Enter your name: ";
                cin >> userName;
                cout << "Enter movie title: ";
                cin.ignore();
                getline(cin, movieTitle);
                system.cancelBooking(userName, movieTitle);
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }

    return 0;
}

