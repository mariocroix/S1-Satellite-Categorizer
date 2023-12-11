#include "vector.h"
#include "satellite.h"

void createVector(Vector* this) {
    this->arr = NULL;
    this->size = 0;
    this->cap = 0;
}

void freeVector(Vector* this) {
    free(this->arr);
}

Pair* at(Vector* this, size_t id) {
    return &this->arr[id];
}

size_t size(Vector* this) {
    return this->size;
}

void pushBack(Vector* this, Pair pair) {
    if (this->size == this->cap) {
        this->cap = this->cap ? this->cap * 2 : 1;
        Pair* tmp = (Pair*)malloc(sizeof(Pair) * this->cap);
        for (int i = 0; i < this->size; ++i) {
            tmp[i] = this->arr[i];
        }
        free(this->arr);
        this->arr = tmp;
    }
    this->arr[this->size] = pair;
    ++this->size;
}

void sort(Vector* this) {
    quickSort(this, 0, (int)this->size - 1);
}

void swap(Pair* p1, Pair* p2) {
    Pair tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

int partition(Vector* this, int low, int high) {
    uint pivot = this->arr[low].first;
    int i = low + 1;
    int j = high;

    while (i <= j) {
        while (i <= j && this->arr[i].first <= pivot) {
            ++i;
        }
        while (this->arr[j].first > pivot) {
            --j;
        }
        if (i < j) {
            swap(&this->arr[i], &this->arr[j]);
        }
    }

    swap(&this->arr[low], &this->arr[j]);

    return j;
}

void quickSort(Vector* this, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(this, low, high);
        quickSort(this, low, pivotIndex - 1);
        quickSort(this, pivotIndex + 1, high);
    }
}

void createContainer(Container* this) {
    this->arr = NULL;
    this->size = 0;
    this->cap = 0;
}

void freeContainer(Container* this) {
    for (int i = 0; i < this->size; ++i) {
        free(this->arr[i]);
    }
    free(this->arr);
}

void add(Container* this, Satellite* satellite) {
    if (this->size == this->cap) {
        this->cap = this->cap ? this->cap * 2 : 1;
        Satellite** tmp = (Satellite**)malloc(sizeof(Satellite*) * this->cap);
        for (int i = 0; i < this->size; ++i) {
            tmp[i] = this->arr[i];
        }
        free(this->arr);
        this->arr = tmp;
    }
    this->arr[this->size] = satellite;
    ++this->size;
}

void createDates(Dates* this) {
    this->arr = NULL;
    this->size = 0;
    this->cap = 0;
}

void freeDates(Dates* this) {
    for (int i = 0; i < this->size; ++i) {
        free(this->arr[i]);
    }
    free(this->arr);
}

void addDate(Dates* this, Date* date) {
    if (this->size == this->cap) {
        this->cap = this->cap ? this->cap * 2 : 1;
        Date** tmp = (Date**)malloc(sizeof(Date*) * this->cap);
        for (int i = 0; i < this->size; ++i) {
            tmp[i] = this->arr[i];
        }
        free(this->arr);
        this->arr = tmp;
    }
    this->arr[this->size] = date;
    ++this->size;
}

void sortDates(Dates* dates) {
    quickSortDates(dates, 0, (int)dates->size - 1);
}

void swapDates(Date* d1, Date* d2) {
    Date tmp = *d1;
    *d1 = *d2;
    *d2 = tmp;
}

int compareDates(Date* date1, Date* date2) {
    if (date1->year != date2->year) {
        return (int)(date1->year - date2->year);
    } else if (date1->month != date2->month) {
        return (int)(date1->month - date2->month);
    } else {
        return (int)(date1->day - date2->day);
    }
}

int partitionDates(Dates* dates, int low, int high) {
    Date* pivot = dates->arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compareDates(dates->arr[j], pivot) < 0) {
            i++;
            swapDates(dates->arr[i], dates->arr[j]);
        }
    }

    swapDates(dates->arr[i + 1], dates->arr[high]);
    return i + 1;
}

void quickSortDates(Dates* dates, int low, int high) {
    if (low < high) {
        int pivotIndex = partitionDates(dates, low, high);

        quickSortDates(dates, low, pivotIndex - 1);
        quickSortDates(dates, pivotIndex + 1, high);
    }
}