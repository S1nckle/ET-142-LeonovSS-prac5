#include <iostream>

using namespace std;

enum comfort_enum {LUX, STANDART, ECO};
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

string str_comf(comfort_enum comf) {
    string names[] = {"Lux", "Standart", "Eco"};
    return names[comf];
}

string str_opt(options_enum opt) {
    string names[] = {
        "Single bed", "Twin bed", "Bath", "Cliamte control", "TV",
        "Fan", "Gels", "Teapot", "Coffee machine", "Microwave",
        "Iron", "Minibar", "Roomservice", "Internet", "Health care"
    };
    return names[opt];
}

void print_options(room_t room) {
    options_t opt = room.opt;
    cout << "Basic options: ";
    for (int i = 0; i < opt.basic_count; i++) {
        cout << str_opt(opt.basic[i]) << ", ";
    }
    cout << "\nAdvanced options: ";
    for (int i = 0; i < opt.advanced_count; i++) {
        cout << str_opt(opt.advanced[i]) << ", ";
    }
    cout << "\nLuxury options: ";
    for (int i = 0; i < opt.luxury_count; i++) {
        cout << str_opt(opt.luxury[i]) << ", ";
    }

}

void print_room(room_t room) {
    cout << "Room ID: " << room.id << endl;
    cout << "Hotel name: " << room.name;
    cout << ", Comfort: " << str_comf(room.comf);
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

int ishouse(room_t room) {
    string name = room.name;
    return (name.rfind("house") == name.length() - 5);
}

int islux(room_t room) {
    return room.comf == LUX;
}

int hasbath(room_t room) {
    for (int j = 0; j < 5; j++) {
        if (room.opt.basic[j] == BATH) return 1;
    }
    return 0;
}

int copy_condition(room_t parent[], room_t child[], int size, int (*condition)(room_t)) {
    int count = 0;
    for (int i = 0; i < size; i++) {
             if (condition(parent[i])) {
                 child[count] = parent[i];
                 count++;
             }
    }
    return count;
}

int capacity_cmp(room_t room1, room_t room2) {
    return room1.capacity > room2.capacity;
}

int cost_cmp(room_t room1, room_t room2) {
    return room1.cost < room2.cost;
}

void cmp_sort(room_t arr[], int size, int (*cmp)(room_t, room_t)) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i; j < size; j++) {
            if (cmp(arr[i], arr[j])) {
                room_t temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void choose(room_t arr[], int size, int id) {
    for (int i = 0; i < size; i++) {
        if (arr[i].id == id) {
            print_room(arr[i]);
            return;
        }
    }
    cout << "No room found with ID: " << id << endl;
}

void delete_option(options_t *options, int opt, int param) {
    if (param < 0) return;
    options_enum arr[5];
    switch (opt) {
        case 0:
            for (int i = param; i < 4; i++) {
                options->basic[i] = options->basic[i + 1];
            }
            options->basic_count--;
            break;
        case 1:
            for (int i = param; i < 4; i++) {
                options->advanced[i] = options->advanced[i + 1];
            }
            options->advanced_count--;
            break;
        case 2:
            for (int i = param; i < 4; i++) {
                options->luxury[i] = options->luxury[i + 1];
            }
            options->luxury_count--;
            break;
    }
}

void append_option(options_t *options, int opt, int param) {
    if (param < 0 || param > 5) return;
    int len;
    switch (opt) {
        case 0:
            len = options->basic_count;
            if (len > 4) return;
            options->basic[options->basic_count] = (options_enum) param;
            options->basic_count++;
            break;
        case 1:
            len = options->advanced_count;
            if (len > 4) return;
            options->advanced[options->advanced_count] = (options_enum) (param + 5);
            options->advanced_count++;
        case 2:
            len = options->luxury_count;
            if (len > 4) return;
            options->luxury[options->luxury_count] = (options_enum) (param + 10);
            options->luxury_count++;
    }
}

void edit(room_t *room) {
    print_room(*room);
    cout << "Choose parameter:" << endl;
    cout << "[0] ID" << '\t' << "[1] Hotel name" << '\t' << "[2] Comfort" << '\t';
    cout << "[3] Capacity" << '\t' << "[4] Cost" << '\t' << "[5] Options" << endl;
    int target;

    if (scanf("%i", &target) != 1) return;
    if (target > 5 || target < 0) {
        cout << "Wrong parameter: " << target;
        return;
    }

    int opt, act;
    if (target == 5) {
        cout << "Choose options. Example: 0 1 -> Basic, append" << endl;
        cout << "[0] Basic" << '\t' << "[1] Advanced" << '\t' << "[2] Luxury" << endl;
        cout << "[0] Delete" << '\t' << "[1] Append" << endl;

        if (scanf("%i %i", &opt, &act) != 2) return;
        if (opt < 0 || opt > 2 || act < 0 || act > 1) {
            cout << "Wrong paramters";
            return;
        }
    }

    cout << "Enter parameter: " << endl;
    cout << "For ID, Comfort, Cost, Capacity: integer to swap for" << endl;
    cout << "For Hotel name: string to swap for" << endl;
    cout << "For Options Delete: index of an option to delete" << endl;
    cout << "For Options Append: index of an enum element to add" << endl;
    string param;
    int int_param;
    if (target == 1) {
        cin.ignore();
        getline(cin, param);
    } else {
        if (scanf("%i", &int_param) != 1) return;
    }

    switch (target) {
        case 0:
            room->id = int_param;
            break;
        case 1:
            room->name = param;
            break;
        case 2:
            room->comf = (comfort_enum) int_param;
            break;
        case 3:
            room->capacity = int_param;
            break;
        case 4:
            room->cost = int_param;
            break;
        default:
            if (act == 0) {
                delete_option(&room->opt, opt, int_param);
            } else {
                append_option(&room->opt, opt, int_param);
            }
    }
    print_room(*room);
}

void edit_choose(room_t arr[], int size, int id) {
    for (int i = 0; i < size; i++) {
        if (arr[i].id == id) {
            edit(&arr[i]);
            return;
        }
    }
    cout << "No room found with ID: " << id << endl;
}

int main() {
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
            "My house", 32513245, STANDART, 3, 100,
            { 3, {TWIN_BED, CLIMATE_CONTROL, TV},
                2, {GELS, COFFEE_MACHINE},
                1, {INTERNET} }
        },
        {
            "Living house", 5327346, STANDART, 1, 1400,
            { 4, {SINGLE_BED, BATH, FAN, IRON},
                1, {MICROWAVE},
                2, {MINIBAR, ROOM_SERVICE} }
        },
        {
            "New Jersey ", 8675321, STANDART, 8, 6500,
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
            "Hotel California", 723453245, STANDART, 6, 1231,
            { 3, {TWIN_BED, BATH, TV},
                1, {IRON},
                4, {COFFEE_MACHINE, TEAPOT, INTERNET, HEALTH_CARE} }
        },
        {
            "Hotel 3", 624354, STANDART, 3, 15000,
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
            "Hotel of houses", 4632123, STANDART, 7, 17500,
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
            "Idk how to name", 767394, STANDART, 6, 1200,
            { 4, {BATH, FAN, GELS, TEAPOT},
                1, {MICROWAVE},
                2, {INTERNET, ROOM_SERVICE} }
        },
        {
            "BimBimBamBam", 32456239, STANDART, 3, 9000,
            { 1, {TWIN_BED},
                3, {TV, COFFEE_MACHINE, MINIBAR},
                2, {SINGLE_BED, IRON} }
        },
        {
            "THE house", 2135214, STANDART, 8, 1800,
            { 2, {CLIMATE_CONTROL, INTERNET},
                4, {BATH, GELS, MICROWAVE, HEALTH_CARE},
                1, {FAN} }
        },
        {
            "Hotel 10", -88634, STANDART, 1, 1450,
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
    print_rooms_arr(rooms, size(rooms), print_room);

    cout << "===== 1) Name ends with <house> =====" << endl << endl;
    room_t rooms_to_fill[size(rooms)];
    int house_count = copy_condition(rooms, rooms_to_fill, size(rooms), ishouse);
    print_rooms_arr(rooms_to_fill, house_count, print_room);

    cout << "===== 2) Capacity sort =====" << endl << endl;
    cmp_sort(rooms_to_fill, house_count, capacity_cmp);
    print_rooms_arr(rooms_to_fill, house_count, print_room);

    cout << "===== 3) Showcase by ID =====" << endl;
    cout << "Enter the id: ";
    int target;
    if (scanf("%d", &target) != 1) {
        cout << "n/a";
    } else {
        choose(rooms, size(rooms), target);
    }

    cout << "===== 4) 3 most expensive Luxes =====" << endl << endl;
    room_t luxes[20];
    int lux_count = copy_condition(rooms, luxes, size(rooms), islux);
    cmp_sort(luxes, lux_count, cost_cmp);
    print_rooms_arr(luxes, 3, print_room);

    cout << "===== 5) Change room data ===" << endl;
    int target2;
    cout << "Enter the id" << endl;
    if (scanf("%d", &target2) != 1) {
        cout << "n/a";
    } else {
        edit_choose(rooms, size(rooms), target2);
    }

    cout << "===== 6) Copy bath rooms =====" << endl;
    room_t bath_rooms[20];
    int bath_count = copy_condition(rooms, bath_rooms, size(rooms), hasbath);
    print_rooms_arr(bath_rooms, bath_count, print_room);


    return 0;
}