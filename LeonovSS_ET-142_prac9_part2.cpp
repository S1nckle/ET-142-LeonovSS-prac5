#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

enum comfort_enum {LUX, STANDARD, ECO};
enum options_enum {
    SINGLE_BED, TWIN_BED, BATH, CLIMATE_CONTROL, TV,
    FAN,  GELS, TEAPOT, COFFEE_MACHINE, MICROWAVE,
    IRON, MINIBAR, ROOM_SERVICE, INTERNET, HEALTH_CARE
};

struct options_t {
    int basic_count;
    options_enum basic[5];
    int advanced_count;
    options_enum advanced[5];
    int luxury_count;
    options_enum luxury[5];
};

struct room_t {
    string name;
    int id;
    comfort_enum comf;
    int capacity;
    int cost;
    options_t opt;
};

string comftos(comfort_enum comf) {
    string names[] = {"Lux", "Standard", "Eco"};
    return names[comf];
}

string opttos(options_enum opt) {
    string names[] = {
        "Single bed", "Twin bed", "Bath", "Climate control", "TV",
        "Fan", "Gels", "Teapot", "Coffee machine", "Microwave",
        "Iron", "Minibar", "Roomservice", "Internet", "Health care"
    };
    return names[opt];
}

comfort_enum stocomf(string comf) {
    string names[] = {"Lux", "Standard", "Eco"};
    for (int i = 0; i < 3; i++) {
        if (comf == names[i]) {
            return (comfort_enum) i;
        }
    }
    return (comfort_enum) -1;
}

options_enum stoopt(string opt) {
    string names[] = {
        "Single bed", "Twin bed", "Bath", "Climate control", "TV",
        "Fan", "Gels", "Teapot", "Coffee machine", "Microwave",
        "Iron", "Minibar", "Roomservice", "Internet", "Health care"
    };

    for (int i = 0; i < 15; i++) {
        if (opt == names[i]) return (options_enum) i;
    }
    return (options_enum) -1;
}

void print_options(room_t room) {
    options_t opt = room.opt;
    cout << "Basic options: ";
    for (int i = 0; i < opt.basic_count; i++) {
        cout << opttos(opt.basic[i]) << ", ";
    }
    cout << "\nAdvanced options: ";
    for (int i = 0; i < opt.advanced_count; i++) {
        cout << opttos(opt.advanced[i]) << ", ";
    }
    cout << "\nLuxury options: ";
    for (int i = 0; i < opt.luxury_count; i++) {
        cout << opttos(opt.luxury[i]) << ", ";
    }

}

void print_room(room_t room) {
    cout << "Room ID: " << room.id << endl;
    cout << "Hotel name: " << room.name;
    cout << ", Comfort: " << comftos(room.comf);
    cout << ", Capacity: " << room.capacity;
    cout << ", Cost: " << room.cost << endl;
    print_options(room);
    cout << endl << endl;
}

void print_rooms_arr(room_t rooms[], int size, void (*print_func)(room_t)) {
    for (int i = 0; i < size; i++) {
        print_func(rooms[i]);
    }
    cout << size << " rooms total" << endl;
}

void read_txt_arr(string path, room_t room[], int arr_size) {
    ifstream fin;
    string str;
    fin.open(path);
    if (fin.is_open()) {
        for (int i = 0; i < arr_size; i++) {
            getline(fin, room[i].name);

            getline(fin, str);
            room[i].id = stoi(str);

            getline(fin, str);
            room[i].comf = stocomf(str);

            getline(fin, str);
            room[i].capacity = stoi(str);

            getline(fin, str);
            room[i].cost = stoi(str);

            getline(fin, str);
            room[i].opt.basic_count = stoi(str);
            for (int j = 0; j < room[i].opt.basic_count; j++) {
                getline(fin, str);
                room[i].opt.basic[j] = stoopt(str);
            }

            getline(fin, str);
            room[i].opt.advanced_count = stoi(str);
            for (int j = 0; j < room[i].opt.advanced_count; j++) {
                getline(fin, str);
                room[i].opt.advanced[j] = stoopt(str);
            }

            getline(fin, str);
            room[i].opt.luxury_count = stoi(str);
            for (int j = 0; j < room[i].opt.luxury_count; j++) {
                getline(fin, str);
                room[i].opt.luxury[j] = stoopt(str);
            }
        }
    }
    fin.close();
}


void write_binary_arr(string path, room_t room[], int arr_size) {
    ofstream out(path, ios::binary | ios::out);
    for (int i = 0; i < arr_size; i++) {
        out.write((char *)&(room[i]), sizeof(room[i]));
    }
    out.close();
}


void read_binary_arr(string path, room_t room[], int arr_size) {
    ifstream in(path, ios::binary | ios::in);
    for (int i = 0; i < arr_size; i++) {
        in.read((char*)&room[i], sizeof(room[i]));
        print_room(room[i]);
    }
    in.close();
}

int main() {
    cout << "===== TXT File =====" << '\n' << '\n';
    room_t readrooms[20];
    read_txt_arr("data/read_struct_arr.txt", readrooms, size(readrooms));
    print_rooms_arr(readrooms, size(readrooms), print_room);

    cout << '\n' << "===== BINARIES =====" << '\n' << '\n';

    room_t rooms[20] = {
        {
            "House in New Orleans", 123123, LUX, 4, 12500,
            { 2, {TV, BATH},
                3, {GELS, COFFEE_MACHINE, MICROWAVE},
                1, {MINIBAR} }
        },
        {
            "Hotel 1", 235421234, ECO, 5, 81000,
            { 1, {SINGLE_BED},
                4, {FAN, TEAPOT, INTERNET, HEALTH_CARE},
                2, {IRON, ROOM_SERVICE} }
        },
        {
            "My house", 32513245, STANDARD, 3, 100,
            { 3, {TWIN_BED, CLIMATE_CONTROL, TV},
                2, {GELS, COFFEE_MACHINE},
                1, {INTERNET} }
        },
        {
            "Living house", 5327346, STANDARD, 1, 1400,
            { 4, {SINGLE_BED, BATH, FAN, IRON},
                1, {MICROWAVE},
                2, {MINIBAR, ROOM_SERVICE} }
        },
        {
            "New Jersey ", 8675321, STANDARD, 8, 6500,
            { 2, {TV, TEAPOT},
                3, {COFFEE_MACHINE, INTERNET, HEALTH_CARE},
                2, {TWIN_BED, BATH} }
        },
        {
            "Superhouse", 9857465, LUX, 1, 6666,
            { 3, {CLIMATE_CONTROL, GELS, MINIBAR},
                4, {SINGLE_BED, FAN, MICROWAVE, IRON},
                1, {ROOM_SERVICE} }
        },
        {
            "Infinite hotel", 1232551, ECO, 4, 9861,
            { 1, {TV},
                3, {BATH, COFFEE_MACHINE, TEAPOT},
                2, {INTERNET, HEALTH_CARE} }
        },
        {
            "House HAHAhouse", 75435, ECO, 2, 6553,
            { 2, {SINGLE_BED, FAN},
                2, {GELS, MICROWAVE},
                3, {CLIMATE_CONTROL, MINIBAR, ROOM_SERVICE} }
        },
        {
            "Hotel California", 723453245, STANDARD, 6, 1231,
            { 3, {TWIN_BED, BATH, TV},
                1, {IRON},
                4, {COFFEE_MACHINE, TEAPOT, INTERNET, HEALTH_CARE} }
        },
        {
            "Hotel 3", 624354, STANDARD, 3, 15000,
            { 0, {},
                3, {SINGLE_BED, FAN, GELS},
                2, {BATH, MINIBAR} }
        },
        {
            "Basic hotel", 3643, LUX, 5, 15000,
            { 2, {CLIMATE_CONTROL, TV},
                4, {TWIN_BED, COFFEE_MACHINE, MICROWAVE, ROOM_SERVICE},
                1, {INTERNET} }
        },
        {
            "Hotel of houses", 4632123, STANDARD, 7, 17500,
            { 4, {SINGLE_BED, BATH, FAN, IRON},
                2, {GELS, TEAPOT},
                2, {MINIBAR, HEALTH_CARE} }
        },
        {
            "Hotel Hotel house :)", 1, ECO, 2, 20000,
            { 1, {TV},
                3, {CLIMATE_CONTROL, COFFEE_MACHINE, INTERNET},
                2, {TWIN_BED, ROOM_SERVICE} }
        },
        {
            "Hotel Hazbin", 0, ECO, 3, 5000,
            { 3, {TWIN_BED, BATH, MICROWAVE},
                2, {FAN, GELS},
                1, {TEAPOT} }
        },
        {
            "Has been hotel", -123124, LUX, 8, 3500,
            { 2, {SINGLE_BED, IRON},
                3, {CLIMATE_CONTROL, COFFEE_MACHINE, HEALTH_CARE},
                2, {TV, MINIBAR} }
        },
        {
            "Idk how to name", 767394, STANDARD, 6, 1200,
            { 4, {BATH, FAN, GELS, TEAPOT},
                1, {MICROWAVE},
                2, {INTERNET, ROOM_SERVICE} }
        },
        {
            "BimBimBamBam", 32456239, STANDARD, 3, 9000,
            { 1, {TWIN_BED},
                3, {TV, COFFEE_MACHINE, MINIBAR},
                2, {SINGLE_BED, IRON} }
        },
        {
            "THE house", 2135214, STANDARD, 8, 1800,
            { 2, {CLIMATE_CONTROL, INTERNET},
                4, {BATH, GELS, MICROWAVE, HEALTH_CARE},
                1, {FAN} }
        },
        {
            "Hotel 10", -88634, STANDARD, 1, 1450,
            { 3, {SINGLE_BED, TV, TEAPOT},
                2, {COFFEE_MACHINE, ROOM_SERVICE},
                2, {TWIN_BED, MINIBAR} }
        },
        {
            "Last Hotel", 999999, ECO, 4, 5000,
            { 2, {BATH, IRON},
                3, {CLIMATE_CONTROL, FAN, GELS},
                2, {MICROWAVE, INTERNET} }
        }
    };

    write_binary_arr("data/struct_arr.txt", rooms, size(rooms));
    read_binary_arr("data/struct_arr.txt", rooms, size(rooms));

    return 0;
}