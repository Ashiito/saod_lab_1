#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

void write_string(std::ofstream& out, const char* str) {
    int i = 0;
    while (str[i] != '\0' && i < 49) {
        out << str[i];
        ++i;
    }
    out << ' ';
}

int main() {
    // Generation of numbers.txt
    std::ofstream num_file("numbers.txt");
    if (!num_file.is_open()) {
        std::cerr << "Error creating numbers.txt" << std::endl;
        return 1;
    }

    const int n = 100000; // 11 million numbers
    num_file << n << '\n';

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 1000000);

    std::cout << "Generating numbers.txt started" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    const int progress_step = n / 10; // 10% of total numbers

    for (int i = 0; i < n; ++i) {
        num_file << dis(gen) << '\n';
        if ((i + 1) % progress_step == 0) {
            auto now = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = now - start;
            std::cout << "Generated " << (i + 1) << " numbers ("
                << (i + 1) * 100 / n << "%) in " << elapsed.count() << " seconds" << std::endl;
        }
    }

    num_file.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> num_duration = end - start;
    std::cout << "Generating numbers.txt completed in " << num_duration.count() << " seconds" << std::endl;

    // Generation of people.txt
    std::ofstream people_file("people.txt");
    if (!people_file.is_open()) {
        std::cerr << "Error creating people.txt" << std::endl;
        return 1;
    }

    people_file << n << '\n';

    const char* surnames[] = {
        "Ivanov", "Petrov", "Sidorov", "Smirnov", "Kuznetsov",
        "Popov", "Vasiliev", "Mikhailov", "Novikov", "Fedorov"
    };
    const char* names[] = {
        "Aleksey", "Boris", "Sergey", "Dmitry", "Ivan",
        "Anna", "Maria", "Elena", "Olga", "Natalia"
    };
    const char* patronymics[] = {
        "Petrovich", "Ivanovich", "Alekseevich", "Dmitrievich", "Sergeevich",
        "Mikhailovich", "Fedorovich", "Andreevich", "Nikolaevich", "Viktorovich"
    };

    const int surname_count = 10;
    const int name_count = 10;
    const int patronymic_count = 10;

    std::uniform_int_distribution<int> surname_dist(0, surname_count - 1);
    std::uniform_int_distribution<int> name_dist(0, name_count - 1);
    std::uniform_int_distribution<int> patronymic_dist(0, patronymic_count - 1);

    std::cout << "\nGenerating people.txt started" << std::endl;
    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n; ++i) {
        write_string(people_file, surnames[surname_dist(gen)]);
        write_string(people_file, names[name_dist(gen)]);
        write_string(people_file, patronymics[patronymic_dist(gen)]);
        people_file << '\n';
        if ((i + 1) % progress_step == 0) {
            auto now = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = now - start;
            std::cout << "Generated " << (i + 1) << " records ("
                << (i + 1) * 100 / n << "%) in " << elapsed.count() << " seconds" << std::endl;
        }
    }

    people_file.close();
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> people_duration = end - start;
    std::cout << "Generating people.txt completed in " << people_duration.count() << " seconds" << std::endl;

    return 0;
}
