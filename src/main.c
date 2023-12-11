#include "controller.h"

int main() {
    Controller controller;
    const char* fileName = "data/satellites.csv";
    run(&controller, fileName);
}