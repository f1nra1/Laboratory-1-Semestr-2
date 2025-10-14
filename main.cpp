#include "database.h"

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--file" && i + 1 < argc) {
            dataFile = argv[++i];
            LoadDatabase();
        }
        else if (string(argv[i]) == "--query" && i + 1 < argc) {
            ExecuteQuery(argv[++i]);
        }
    }
    CleanupDatabase();
    return 0;
}