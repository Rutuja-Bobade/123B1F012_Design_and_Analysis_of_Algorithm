#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Movie {
    string title;
    double rating;
    int releaseYear;
    double popularity;
};

vector<Movie> readMoviesCSV(const string &filename) {
    vector<Movie> movies;
    ifstream file(filename);
    string line;
    getline(file, line);
    while (getline(file, line)) {
        istringstream iss(line);
        Movie m;
        string field;
        getline(iss, m.title, ',');
        getline(iss, field, ',');
        m.rating = stod(field);
        getline(iss, field, ',');
        m.releaseYear = stoi(field);
        getline(iss, field, ',');
        m.popularity = stod(field);

        movies.push_back(m);
    }
    return movies;
}

template <typename T>
int partition(vector<Movie> &movies, int low, int high, T Movie::*key, bool descending=false) {
    T pivot = movies[high].*key;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        bool cond = descending ? (movies[j].*key > pivot) : (movies[j].*key < pivot);
        if (cond) {
            i++;
            swap(movies[i], movies[j]);
        }
    }
    swap(movies[i + 1], movies[high]);
    return i + 1;
}

template <typename T>
void quickSort(vector<Movie> &movies, int low, int high, T Movie::*key, bool descending=false) {
    if (low < high) {
        int pi = partition(movies, low, high, key, descending);
        quickSort(movies, low, pi - 1, key, descending);
        quickSort(movies, pi + 1, high, key, descending);
    }
}

void printMovies(const vector<Movie>& movies, int limit = 10) {
    cout << left << setw(35) << "Title"
         << setw(12) << "Rating"
         << setw(12) << "Year"
         << setw(12) << "Popularity" << endl;
    cout << string(70, '-') << endl;
    for (int i = 0; i < min(limit, (int)movies.size()); ++i) {
        cout << left << setw(35) << movies[i].title
             << setw(12) << movies[i].rating
             << setw(12) << movies[i].releaseYear
             << setw(12) << movies[i].popularity << endl;
    }
    if(movies.size() > limit)
        cout << "... (" << movies.size()-limit << " more movies not shown)\n";
}


int main() {
    string filename = "movies.csv";
    vector<Movie> movies = readMoviesCSV(filename);
    if (movies.empty()) {
        cout << "No movies loaded." << endl;
        return 1;
    }
    bool running = true;
    while (running) {
        cout << "\nSort Movies by:\n";
        cout << "1. IMDB Rating\n";
        cout << "2. Release Year\n";
        cout << "3. Popularity\n";
        cout << "4. Exit\n";
        int choice;
        cout << "Enter choice (1-4): ";
        cin >> choice;

        bool descending = true; 

        switch (choice) {
            case 1:
                quickSort(movies, 0, movies.size() - 1, &Movie::rating, descending);
                printMovies(movies);
                break;
            case 2:
                quickSort(movies, 0, movies.size() - 1, &Movie::releaseYear, descending);
                printMovies(movies);
                break;
            case 3:
                quickSort(movies, 0, movies.size() - 1, &Movie::popularity, descending);
                printMovies(movies);
                break;
            case 4:
                running = false;
                cout << "Exiting Movie Recommender." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
