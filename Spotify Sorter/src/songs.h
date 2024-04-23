#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

// structure to represent a single song and all its data points
struct Song {
    // data points per song (naming follows the header line in used .csv file)
    std::string _track_id;
    std::string _track_name;
    std::string _track_artist;
    double _track_popularity;
    std::string _track_album_id;
    std::string _track_album_name;
    std::string _track_album_release_date;
    std::string _playlist_name;
    std::string _playlist_id;
    std::string _playlist_genre;
    std::string _playlist_subgenre;
    double _danceability;
    double _energy;
    double _key;
    double _loudness;
    double _mode;
    double _speechiness;
    double _acousticness;
    double _instrumentalness;
    double _liveness;
    double _valence;
    double _tempo;
    double _duration_ms;
};

class Songs_List {
private:
    // stores all songs in Song struct format
    std::vector<Song> _songs;

    // member pointer for sortable values in Song struct
    using member_pointer = double Song::*;
    member_pointer _data = nullptr;

    void store_songs(std::string& filename); // creates and fills song vector
    void print_n(int& n); // prints first n songs in vector
    void merge_call(int& by, bool& ascending); // calls merge sort
    void quick_call(int& by, bool& ascending); // calls quick sort
    int partition(int low, int high, bool ascending); // called by quick_sort
    void quick_sort(int low, int high, bool ascending); // quick sort
    void merge(int left, int mid, int right, bool ascending); // called by merge_sort
    void merge_sort(int left, int right, bool ascending); // merge sort

public:
    void initialize(std::string& filename); // calls store_songs, called in main
    void print(int& n); // calls print_n, called in main
    void sort(std::string& type, int& by, bool& ascending); // calls chosen sort and passes arguements for it
};

// ----------------------- Start Program -----------------------

// initializes sorter by calling the method to create and fill _songs vector (store_songs)
void Songs_List::initialize(std:: string& filename) {
    store_songs(filename);
}

// reads .csv file with songs and there data points and fills _songs vector
void Songs_List::store_songs(std::string& filename) {
    // prepare to read file and skip header line
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);

    // check for file open
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }


    // finds .csv file size to create proper sized vector to avoiding resizing every time (would be O(n^2) vs O(2n) = O(n))
    int count = 0;
    while (getline(file, line)) {
        ++count;
    }

    // reset file pointer, skip header, and adjust count
    file.clear();
    file.seekg(0);
    getline(file, line);
    count--;

    // sets _song size to exact size needed
    _songs.reserve(count);

    // reads .csv file line by line and pushes back song structs to vector
    while (std::getline(file, line)) {
        // prepares for file reading and creates new Song struct
        std::istringstream sstream(line);
        Song song;
        std::string field;

        // reads track_id
        std::getline(sstream, song._track_id, ',');

        // checks for quotes in track_name
        std::getline(sstream, field, ',');
        if (field[0] == '\"') {
            // checks for layered quotes instance
            if (field.back() != '\"') {
                std::string field_two;
                std::getline(sstream, field_two, '\"');
                field = field + field_two + "\"";
                std::getline(sstream, field_two, ',');
                
                // runs through all layers of quotes within quotes
                while (field_two[0] == '\"') {
                    field = field + field_two + "\"";
                    std::getline(sstream, field_two, ',');
                }
                song._track_name = field;
            } 
            else {
                song._track_name = field;
            }

        } 
        else {
            song._track_name = field;
        }

        // checks for quotes in track_artist
        std::getline(sstream, field, ',');
        if (field[0] == '\"') {
            // checks for layered quotes instance
            if (field.back() != '\"') {
                std::string field_two;
                std::getline(sstream, field_two, '\"');
                field = field + field_two + "\"";
                std::getline(sstream, field_two, ',');
                
                // runs through all layers of quotes within quotes
                while (field_two[0] == '\"') {
                    field = field + field_two + "\"";
                    std::getline(sstream, field_two, ',');
                }
                song._track_artist = field;
            } 
            else {
                song._track_artist = field;
            }

        } 
        else {
            song._track_artist = field;
        }

        // reads track_popularity
        std::getline(sstream, field, ','); 
        song._track_popularity = std::stod(field);

        // reads track_album_id
        std::getline(sstream, song._track_album_id, ',');

        // checks for quotes in track_album_name
        std::getline(sstream, field, ',');
        if (field[0] == '\"') {
            // checks for layered quotes instance
            if (field.back() != '\"') {
                std::string field_two;
                std::getline(sstream, field_two, '\"');
                field = field + field_two + "\"";
                std::getline(sstream, field_two, ',');
                
                // runs through all layers of quotes within quotes
                while (field_two[0] == '\"') {
                    field = field + field_two + "\"";
                    std::getline(sstream, field_two, ',');
                }
                song._track_album_name = field;
            } 
            else {
                song._track_album_name = field;
            }

        } 
        else {
            song._track_album_name = field;
        }

        // reads track_album_release_date
        std::getline(sstream, song._track_album_release_date, ',');

        // checks for quotes in playlist_name
        std::getline(sstream, field, ',');
        if (field[0] == '\"') {
            // checks for layered quotes instance
            if (field.back() != '\"') {
                std::string field_two;
                std::getline(sstream, field_two, '\"');
                field = field + field_two + "\"";
                std::getline(sstream, field_two, ',');
                
                // runs through all layers of quotes within quotes
                while (field_two[0] == '\"') {
                    field = field + field_two + "\"";
                    std::getline(sstream, field_two, ',');
                }
                song._playlist_name = field;
            } 
            else {
                song._playlist_name = field;
            }

        } 
        else {
            song._playlist_name = field;
        }


        // reads playlist_id
        std::getline(sstream, song._playlist_id, ',');

        // checks for quotes in playlist_genre
        std::getline(sstream, field, ',');
        if (field[0] == '\"') {
            // checks for layered quotes instance
            if (field.back() != '\"') {
                std::string field_two;
                std::getline(sstream, field_two, '\"');
                field = field + field_two + "\"";
                std::getline(sstream, field_two, ',');
                
                // runs through all layers of quotes within quotes
                while (field_two[0] == '\"') {
                    field = field + field_two + "\"";
                    std::getline(sstream, field_two, ',');
                }
                song._playlist_genre = field;
            } 
            else {
                song._playlist_genre = field;
            }

        } 
        else {
            song._playlist_genre = field;
        }

        // checks for quotes in playlist_subgenre
        std::getline(sstream, field, ',');
        if (field[0] == '\"') {
            // checks for layered quotes instance
            if (field.back() != '\"') {
                std::string field_two;
                std::getline(sstream, field_two, '\"');
                field = field + field_two + "\"";
                std::getline(sstream, field_two, ',');
                
                // runs through all layers of quotes within quotes
                while (field_two[0] == '\"') {
                    field = field + field_two + "\"";
                    std::getline(sstream, field_two, ',');
                }
                song._playlist_subgenre = field;
            } 
            else {
                song._playlist_subgenre = field;
            }

        } 
        else {
            song._playlist_subgenre = field;
        }

        // reads danceability
        std::getline(sstream, field, ',');
        song._danceability = std::stod(field);     

        // reads energy
        std::getline(sstream, field, ',');
        song._energy = std::stod(field);
        
        // reads key
        std::getline(sstream, field, ',');
        song._key = std::stod(field);
        
        // reads loudness
        std::getline(sstream, field, ',');
        song._loudness = std::stod(field);
        
        // reads mode
        std::getline(sstream, field, ',');
        song._mode = std::stod(field);
        
        // reads speechiness
        std::getline(sstream, field, ',');
        song._speechiness = std::stod(field);
        
        // reads acousticness
        std::getline(sstream, field, ',');
        song._acousticness = std::stod(field);
        
        // reads instrumentalness
        std::getline(sstream, field, ',');
        song._instrumentalness = std::stod(field);

        // reads liveness
        std::getline(sstream, field, ',');
        song._liveness = std::stod(field);
        
        // reads valence
        std::getline(sstream, field, ',');
        song._valence = std::stod(field);
        
        // reads tempo
        std::getline(sstream, field, ',');
        song._tempo = std::stod(field);
        
        // reads duration_ms
        std::getline(sstream, field, ',');
        song._duration_ms = std::stod(field);


        // push back song struct to vector of songs
        _songs.push_back(song);
    }
}

// --------------------------- Print ---------------------------

// calls private method print (print_n)
void Songs_List::print(int& n) {
    print_n(n);
}

// prints first n songs and skips over duplicates
void Songs_List::print_n(int& n) {

    // creates printed vector to skip duplicate songs and counter to track prints
    std::vector<std::string> songs;
    songs.reserve(n);
    int j = 0;

    // sets index at start
    int i = 0;
    
    // print boundary upper
    std::cout << "-----------------------------------------------------" << std::endl;

    // runs until n songs have printed
    while (j < n && i < _songs.size()) {
        // creates reference to songs[i] to pass into prints and increments i by 1
        Song& song = _songs[i];
        i++;

        // prints songname, artist, and data used for sorting
        std::string print = song._track_name + ", by " + song._track_artist + " --- ";
        if (std::find(songs.begin(), songs.end(), print) != songs.end()) {
            continue;
        }
        else {
            songs.push_back(print);
            std::cout << print << song.*_data << std::endl;
            j++;
        }
    }

    // print boundary lower
    std::cout << "-----------------------------------------------------" << std::endl;

}

// ------------------------ Main Helpers -----------------------

// sort method called in main that calls more specfic sorty type and data to be sorted by
void Songs_List::sort(std::string& type, int& by, bool& ascending) {
    // checks and calls chosen sort
    if (type == "1") {
        merge_call(by, ascending);
    } 
    else if (type == "2") {
        quick_call(by, ascending);
    } // unexpected error
    else {
        std::cout << "Something has gone wrong :(" << std::endl;
    }
}

// ------------------------- Quick Sort ------------------------

// calls quick sort ascending or descending
void Songs_List::quick_call(int& by, bool& ascending) {
    // set member pointer to wanted data
    if (by == 1) {
        _data = &Song::_track_popularity;
    }
    else if (by == 2) {
        _data = &Song::_danceability;
    }
    else if (by == 3) {
        _data = &Song::_energy;        
    }
    else if (by == 4) {
        _data = &Song::_key;       
    }
    else if (by == 5) {
        _data = &Song::_loudness;       
    }
    else if (by == 6) {
        _data = &Song::_mode;
    }
    else if (by == 7) {
        _data = &Song::_speechiness;
    }
    else if (by == 8) {
        _data = &Song::_acousticness;
    }
    else if (by == 9) {
        _data = &Song::_instrumentalness;
    }
    else if (by == 10) {
        _data = &Song::_liveness;
    }
    else if (by == 11) {
        _data = &Song::_valence;
    }
    else if (by == 12) {
        _data = &Song::_tempo;
    }
    else if (by == 13) {
        _data = &Song::_duration_ms;
    } // unexpected error 
    else {
        std::cout << "Something has gone wrong :(" << std::endl;
    }
    quick_sort(0, _songs.size() - 1, ascending);
}

// called by quick_sort to move data around the pivot
int Songs_List::partition(int low, int high, bool ascending) {
    // stores pivot and initializes index of smaller element
    double pivot = _songs[high].*_data;
    int i = low - 1;

    // loops through
    for (int j = low; j < high; j++) {
        // bool to determine swap or no swap
        bool should_swap = false;

        // check if ascending or descending
        if (ascending) {
            // compare to pipvot
            if (_songs[j].*_data < pivot) {
                // if less we move to left
                should_swap = true;
            }
        } // descending
        else {
            // compare to pivot
            if (_songs[j].*_data > pivot) {
                // if greater we move it left
                should_swap = true;
            }
        }

        // check swap bool
        if (should_swap) {
            // incremeent smaller index and swap
            i++;
            std::swap(_songs[i], _songs[j]);
        }
    }
    
    // swap pivot with i+1
    std::swap(_songs[i + 1], _songs[high]);
    
    // return partition index
    return (i + 1);
}

// quick sort method
void Songs_List::quick_sort(int low, int high, bool ascending) {
    // base case check
    if (low < high) {
        // pivot index
        int pi = partition(low, high, ascending);

        // recursive call
        quick_sort(low, pi - 1, ascending);
        quick_sort(pi + 1, high, ascending);
    }
}

// ------------------------- Merge Sort ------------------------

// calls merge sort ascending or descending
void Songs_List::merge_call(int& by, bool& ascending) {
    // set member pointer to wanted data
    if (by == 1) {
        _data = &Song::_track_popularity;
    }
    else if (by == 2) {
        _data = &Song::_danceability;
    }
    else if (by == 3) {
        _data = &Song::_energy;        
    }
    else if (by == 4) {
        _data = &Song::_key;       
    }
    else if (by == 5) {
        _data = &Song::_loudness;       
    }
    else if (by == 6) {
        _data = &Song::_mode;
    }
    else if (by == 7) {
        _data = &Song::_speechiness;
    }
    else if (by == 8) {
        _data = &Song::_acousticness;
    }
    else if (by == 9) {
        _data = &Song::_instrumentalness;
    }
    else if (by == 10) {
        _data = &Song::_liveness;
    }
    else if (by == 11) {
        _data = &Song::_valence;
    }
    else if (by == 12) {
        _data = &Song::_tempo;
    }
    else if (by == 13) {
        _data = &Song::_duration_ms;
    } // unexpected error 
    else {
        std::cout << "Something has gone wrong :(" << std::endl;
    }
    merge_sort(0, _songs.size() - 1, ascending);
}

// creates and sorts sub arrays for merge sort
void Songs_List::merge(int left, int mid, int right, bool ascending) {
    // gets sub array sizes
    int sub_1 = mid - left + 1;
    int sub_2 = right - mid;

    // creates temporary arrays
    auto *left_array = new Song[sub_1];
    auto *right_array = new Song[sub_2];

    // copy data into temporary arrays
    for (int i = 0; i < sub_1; i++) {
        left_array[i] = _songs[left + i];
    }
    for (int j = 0; j < sub_2; j++) {
        right_array[j] = _songs[mid + 1 + j];
    }

    int index_left = 0; // left array index
    int index_right = 0; // right array index
    int index_merged = left; // merged array index (_songs)

    // Merge the temporary arrays back into the main array (_songs vector)
    while (index_left < sub_1 && index_right < sub_2) {
        // check for ascending and value comparison
        if ((ascending && left_array[index_left].*_data <= right_array[index_right].*_data) ||
            (!ascending && left_array[index_left].*_data >= right_array[index_right].*_data)) {
            _songs[index_merged] = left_array[index_left];
            index_left++;
        } 
        else {
            _songs[index_merged] = right_array[index_right];
            index_right++;
        }

        // increment _songs index
        index_merged++;
    }

    // copy over whats left of left_array
    while (index_left < sub_1) {
        _songs[index_merged] = left_array[index_left];
        index_left++;
        index_merged++;
    }

    // copy over whats left of right_array
    while (index_right < sub_2) {
        _songs[index_merged] = right_array[index_right];
        index_right++;
        index_merged++;
    }

    // free allocated memory
    delete[] left_array;
    delete[] right_array;
}

// merge sort method, splits into left and right sub arrays
void Songs_List::merge_sort(int left, int right, bool ascending) {
    // base case
    if (left >= right) {
        return; // returns recursively
    }
    
    // find middle
    int mid = left + (right - left) / 2;

    // recursive calls
    merge_sort(left, mid, ascending);
    merge_sort(mid + 1, right, ascending);
    merge(left, mid, right, ascending);
}



// --- Citations ---
// .csv file reading:  https://www.geeksforgeeks.org/csv-file-management-using-c/
// merge sort:         https://www.geeksforgeeks.org/merge-sort/#
// quick sort:         https://www.geeksforgeeks.org/quick-sort/?ref=shm
// .csv file:          https://www.kaggle.com/datasets/joebeachcapital/30000-spotify-songs
// member pointer:     https://stackoverflow.com/questions/670734/what-is-a-pointer-to-class-data-member-and-what-is-its-use


