#include <iostream>
#include <chrono>
#include <fstream>
#include <string>

void manual_swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void selection_sort(int* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            manual_swap(arr[i], arr[min_idx]);
        }
    }
}

void bubble_sort(int* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j + 1] < arr[j]) {
                manual_swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void insertion_sort(int* arr, int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && key < arr[j]) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void merge(int* arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];
    for (int i = 0; i < n1; ++i) L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    delete[] L;
    delete[] R;
}

void merge_sort_helper(int* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_helper(arr, l, m);
        merge_sort_helper(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge_sort(int* arr, int n) {
    if (n > 1) {
        merge_sort_helper(arr, 0, n - 1);
    }
}

void heapify(int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        manual_swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; --i) {
        manual_swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            manual_swap(arr[i], arr[j]);
            ++i;
        }
    }
    manual_swap(arr[i], arr[high]);
    return i;
}

void quick_sort_helper(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort_helper(arr, low, pi - 1);
        quick_sort_helper(arr, pi + 1, high);
    }
}

void quick_sort(int* arr, int n) {
    quick_sort_helper(arr, 0, n - 1);
}

struct Person {
    char last_name[50];
    char first_name[50];
    char middle_name[50];
};

int str_compare(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] && s2[i]) {
        if (s1[i] < s2[i]) return -1;
        if (s1[i] > s2[i]) return 1;
        ++i;
    }
    if (s1[i]) return 1;
    if (s2[i]) return -1;
    return 0;
}

bool person_compare(const Person& a, const Person& b) {
    int name_cmp = str_compare(a.first_name, b.first_name);
    if (name_cmp != 0) return name_cmp < 0;
    int middle_cmp = str_compare(a.middle_name, b.middle_name);
    if (middle_cmp != 0) return middle_cmp < 0;
    int n = 1; // 2nd letter (0-based index)
    if (a.last_name[n] == '\0' || b.last_name[n] == '\0') {
        return str_compare(a.last_name, b.last_name) < 0;
    }
    if (a.last_name[n] != b.last_name[n]) {
        return a.last_name[n] < b.last_name[n];
    }
    return str_compare(a.last_name, b.last_name) < 0;
}

void manual_swap_person(Person& a, Person& b) {
    Person temp;
    for (int i = 0; i < 50; ++i) {
        temp.last_name[i] = a.last_name[i];
        temp.first_name[i] = a.first_name[i];
        temp.middle_name[i] = a.middle_name[i];
        a.last_name[i] = b.last_name[i];
        a.first_name[i] = b.first_name[i];
        a.middle_name[i] = b.middle_name[i];
        b.last_name[i] = temp.last_name[i];
        b.first_name[i] = temp.first_name[i];
        b.middle_name[i] = temp.middle_name[i];
    }
}

int partition_person(Person* arr, int low, int high) {
    Person pivot = arr[high];
    int i = low;
    for (int j = low; j < high; ++j) {
        if (person_compare(arr[j], pivot)) {
            manual_swap_person(arr[i], arr[j]);
            ++i;
        }
    }
    manual_swap_person(arr[i], arr[high]);
    return i;
}

void quick_sort_person_helper(Person* arr, int low, int high) {
    if (low < high) {
        int pi = partition_person(arr, low, high);
        quick_sort_person_helper(arr, low, pi - 1);
        quick_sort_person_helper(arr, pi + 1, high);
    }
}

void quick_sort_person(Person* arr, int n) {
    quick_sort_person_helper(arr, 0, n - 1);
}

int main() {
    // Reading numeric data from numbers.txt
    std::ifstream num_file("numbers.txt");
    if (!num_file.is_open()) {
        std::cerr << "Error opening numbers.txt" << std::endl;
        return 1;
    }
    int n;
    num_file >> n;
    if (n <= 0) {
        std::cerr << "Invalid array size" << std::endl;
        return 1;
    }
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        num_file >> arr[i];
    }
    num_file.close();
    std::cout << "Array size: " << n << std::endl;

    struct SortInfo {
        const char* name;
        void (*func)(int*, int);
        const char* filename;
    };
    SortInfo sorts[] = {
        {"Selection Sort", selection_sort, "selection_sort.txt"},
        {"Bubble Sort", bubble_sort, "bubble_sort.txt"},
        {"Insertion Sort", insertion_sort, "insertion_sort.txt"},
        {"Merge Sort", merge_sort, "merge_sort.txt"},
        {"Heap Sort", heap_sort, "heap_sort.txt"},
        {"Quick Sort", quick_sort, "quick_sort.txt"}
    };

    for (int i = 0; i < 6; ++i) {
        int* temp = new int[n];
        for (int j = 0; j < n; ++j) temp[j] = arr[j];
        auto start = std::chrono::high_resolution_clock::now();
        sorts[i].func(temp, n);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        // Write sorted array to file
        std::ofstream out_file(sorts[i].filename);
        if (!out_file.is_open()) {
            std::cerr << "Error opening " << sorts[i].filename << std::endl;
            delete[] temp;
            continue;
        }
        for (int j = 0; j < n; ++j) {
            out_file << temp[j] << " ";
        }
        out_file.close();

        std::cout << sorts[i].name << ": " << duration.count() << " ms" << std::endl;
        delete[] temp;
    }
    delete[] arr;

    // Reading data for lexicographic sorting from people.txt
    std::ifstream people_file("people.txt");
    if (!people_file.is_open()) {
        std::cerr << "Error opening people.txt" << std::endl;
        return 1;
    }
    int m;
    people_file >> m;
    if (m <= 0) {
        std::cerr << "Invalid number of records" << std::endl;
        return 1;
    }
    Person* people = new Person[m];
    for (int i = 0; i < m; ++i) {
        people_file >> people[i].last_name >> people[i].first_name >> people[i].middle_name;
    }
    people_file.close();

    // Perform lexicographic sorting and save to file
    auto start = std::chrono::high_resolution_clock::now();
    quick_sort_person(people, m);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::ofstream out_file("quick_sort_person.txt");
    if (!out_file.is_open()) {
        std::cerr << "Error opening quick_sort_person.txt" << std::endl;
        delete[] people;
        return 1;
    }
    for (int i = 0; i < m; ++i) {
        out_file << people[i].last_name << " " << people[i].first_name << " " << people[i].middle_name << std::endl;
    }
    out_file.close();

    std::cout << "Quick Sort (Person): " << duration.count() << " ms" << std::endl;
    delete[] people;
    return 0;
}