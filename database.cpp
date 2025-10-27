#include "database.h"
#include <fstream>
#include <sstream>
#include <iostream>

Database db;
string dataFile = "";

void SaveDatabase() {
    if (dataFile.empty()) return;
    ofstream file(dataFile);

    for (auto& p : db.arrays) {
        file << "ARRAY " << p.first << " " << p.second -> size << "\n";
        for (int i = 0; i < p.second -> size; i++) {
            file << p.second -> data[i] << "\n";
        }
    }

    for (auto& p : db.flists) {
        file << "FLIST " << p.first << " " << p.second -> size << "\n";
        FNode* current = p.second -> head;
        while (current) {
            file << current -> data << "\n";
            current = current -> next;
        }
    }

    for (auto& p : db.llists) {
        file << "LLIST " << p.first << " " << p.second -> size << "\n";
        LNode* current = p.second -> head;
        while (current) {
            file << current -> data << "\n";
            current = current -> pNext;
        }
    }

    for (auto& p : db.stacks) {
        file << "STACK " << p.first << " " << p.second -> size << "\n";
        SNode* current = p.second -> top;
        int count = p.second -> size;
        SNode** temp = new SNode*[count];
        for (int i = 0; i < count; i++) {
            temp[i] = current;
            current = current -> next;
        }
        for (int i = count - 1; i >= 0; i--) {
            file << temp[i] -> data << "\n";
        }
        delete[] temp;
    }

    for (auto& p : db.queues) {
        file << "QUEUE " << p.first << " " << p.second -> size << "\n";
        QNode* current = p.second -> head;
        while (current) {
            file << current -> data << "\n";
            current = current -> next;
        }
    }

    for (auto& p : db.trees) {
        file << "TREE " << p.first << " " << p.second -> size << "\n";
        if (p.second -> root) {
            Queue q;
            CreateQueue(&q);
            QPush(&q, to_string((long long)p.second -> root));

            while (q.size > 0) {
                string ptrStr = QPop(&q);
                TNode* current = (TNode*)(stoll(ptrStr));
                file << current -> data << "\n";

                if (current -> left)
                    QPush(&q, to_string((long long)current -> left));
                if (current -> right)
                    QPush(&q, to_string((long long)current -> right));
            }
            DestroyQueue(&q);
        }
    }

    file.close();
}

void LoadDatabase() {
    if (dataFile.empty()) return;
    ifstream file(dataFile);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string type, name;
        int count;
        ss >> type >> name >> count;

        if (type == "ARRAY") {
            MArray* arr = new MArray;
            CreateMArray(arr);
            for (int i = 0; i < count; i++) {
                getline(file, line);
                MPushBack(arr, line);
            }
            db.arrays[name] = arr;
        } else if (type == "FLIST") {
            FList* flist = new FList;
            CreateFList(flist);
            for (int i = 0; i < count; i++) {
                getline(file, line);
                FPushBack(flist, line);
            }
            db.flists[name] = flist;
        } else if (type == "LLIST") {
            LList* llist = new LList;
            CreateLList(llist);
            for (int i = 0; i < count; i++) {
                getline(file, line);
                LPushTail(llist, line);
            }
            db.llists[name] = llist;
        } else if (type == "STACK") {
            Stack* stack = new Stack;
            CreateStack(stack);
            vector<string> tempStack;
            for (int i = 0; i < count; i++) {
                getline(file, line);
                tempStack.push_back(line);
            }
            for (int i = count - 1; i >= 0; i--) {
                SPush(stack, tempStack[i]);
            }
            db.stacks[name] = stack;
        } else if (type == "QUEUE") {
            Queue* queue = new Queue;
            CreateQueue(queue);
            for (int i = 0; i < count; i++) {
                getline(file, line);
                QPush(queue, line);
            }
            db.queues[name] = queue;
        } else if (type == "TREE") {
            BinaryTree* tree = new BinaryTree;
            CreateTree(tree);
            for (int i = 0; i < count; i++) {
                getline(file, line);
                TPush(tree, line);
            }
            db.trees[name] = tree;
        }
    }
    file.close();
}

void ExecuteQuery(string query) {
    stringstream ss(query);
    string command, name, arg1, arg2;
    ss >> command >> name >> arg1 >> arg2;

    if (command == "MCREATE") {
        if (db.arrays.find(name) == db.arrays.end()) {
            db.arrays[name] = new MArray;
            CreateMArray(db.arrays[name]);
            cout << " -> Выполнено" << endl;
        }
    }
    else if (command == "FCREATE") {
        if (db.flists.find(name) == db.flists.end()) {
            db.flists[name] = new FList;
            CreateFList(db.flists[name]);
            cout << " -> Выполнено" << endl;
        }
    }
    else if (command == "LCREATE") {
        if (db.llists.find(name) == db.llists.end()) {
            db.llists[name] = new LList;
            CreateLList(db.llists[name]);
            cout << " -> Выполнено" << endl;
        }
    }
    else if (command == "SCREATE") {
        if (db.stacks.find(name) == db.stacks.end()) {
            db.stacks[name] = new Stack;
            CreateStack(db.stacks[name]);
            cout << " -> Выполнено" << endl;
        }
    }
    else if (command == "QCREATE") {
        if (db.queues.find(name) == db.queues.end()) {
            db.queues[name] = new Queue;
            CreateQueue(db.queues[name]);
            cout << " -> Выполнено" << endl;
        }
    }
    else if (command == "TCREATE") {
        if (db.trees.find(name) == db.trees.end()) {
            db.trees[name] = new BinaryTree;
            CreateTree(db.trees[name]);
            cout << " -> Выполнено" << endl;
        }
    }

        // ================================== Массив ==================================

    else if (command == "MPUSH") {
        if (db.arrays.find(name) != db.arrays.end()) {
            MPushBack(db.arrays[name], arg1);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: массив не создан" << endl;
        }
    }
    else if (command == "MPUSHINDEX") {
        if (db.arrays.find(name) != db.arrays.end()) {
            MPushIndex(db.arrays[name], arg1, stoi(arg2));
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: массив не создан" << endl;
        }
    }
    else if (command == "MGET") {
        if (db.arrays.find(name) != db.arrays.end()) {
            string element = MGet(db.arrays[name], stoi(arg1));
            if (element.empty()) {
                cout << " -> Ошибка: неверный индекс" << endl;
            } else {
                cout << " -> " << element << endl;
            }
        } else {
            cout << " -> Ошибка: массив не создан" << endl;
        }
    }
    else if (command == "MPOPINDEX") {
        if (db.arrays.find(name) != db.arrays.end()) {
            MPopIndex(db.arrays[name], stoi(arg1));
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: массив не создан" << endl;
        }
    }
    else if (command == "MREPLACE") {
        if (db.arrays.find(name) != db.arrays.end()) {
            MReplace(db.arrays[name], arg1, stoi(arg2));
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: массив не создан" << endl;
        }
    }
    else if (command == "MSIZE") {
        if (db.arrays.find(name) != db.arrays.end()) {
            cout << " -> " << MGetSize(db.arrays[name]) << endl;
        } else {
            cout << " -> Ошибка: массив не создан" << endl;
        }
    }

        // ================================== Односвязный список ==================================

    else if (command == "FPUSHHEAD") {
        if (db.flists.find(name) != db.flists.end()) {
            FPushHead(db.flists[name], arg1);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: список не создан" << endl;
        }
    }
    else if (command == "FPUSHTAIL") {
        if (db.flists.find(name) != db.flists.end()) {
            FPushBack(db.flists[name], arg1);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: список не создан" << endl;
        }
    }
    else if (command == "FPUSHBEFORE") {
        if (db.flists.find(name) != db.flists.end()) {
            FPushBefore(db.flists[name], arg1, arg2);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: список не создан" << endl;
        }
    }
    else if (command == "FPUSHAFTER") {
        if (db.flists.find(name) != db.flists.end()) {
            FPushAfter(db.flists[name], arg1, arg2);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: список не создан" << endl;
        }
    }
    else if (command == "FPOPHEAD") {
        if (db.flists.find(name) != db.flists.end()) {
            FPopHead(db.flists[name]);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: список не создан" << endl;
        }
    }
    else if (command == "FPOPTAIL") {
        if (db.flists.find(name) != db.flists.end()) {
            FPopTail(db.flists[name]);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: список не создан" << endl;
        }
    }
    else if (command == "FPOPELEM") {
        if (db.flists.find(name) != db.flists.end()) {
            FPopElement(db.flists[name], arg1);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: список не создан" << endl;
        }
    }
    else if (command == "FSEARCH") {
        if (db.flists.find(name) != db.flists.end()) {
            bool found = FSearch(db.flists[name], arg1);
            cout << " -> " << (found ? "TRUE" : "FALSE") << endl;
        } else {
            cout << " -> Ошибка: список не создан" << endl;
        }
    }

        // ================================== Двусвязный список ==================================

    else if (command == "LPUSHHEAD") {
        if (db.llists.find(name) != db.llists.end()) {
            LPushHead(db.llists[name], arg1);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: список не создан" << endl;
        }
    }
    else if (command == "LPUSHTAIL") {
        if (db.llists.find(name) != db.llists.end()) {
            LPushTail(db.llists[name], arg1);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: список не создан" << endl;
        }
    }
    else if (command == "LPUSHBEFORE") {
        if (db.llists.find(name) != db.llists.end()) {
            LPushBefore(db.llists[name], arg1, arg2);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: список не создан" << endl;
        }
    }
    else if (command == "LPUSHAFTER") {
        if (db.llists.find(name) != db.llists.end()) {
            LPushAfter(db.llists[name], arg1, arg2);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: список не создан" << endl;
        }
    }
    else if (command == "LPOPHEAD") {
        if (db.llists.find(name) != db.llists.end()) {
            LPopHead(db.llists[name]);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: список не создан" << endl;
        }
    }
    else if (command == "LPOPTAIL") {
        if (db.llists.find(name) != db.llists.end()) {
            LPopTail(db.llists[name]);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: список не создан" << endl;
        }
    }
    else if (command == "LPOPELEM") {
        if (db.llists.find(name) != db.llists.end()) {
            LPopElement(db.llists[name], arg1);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: список не создан" << endl;
        }
    }
    else if (command == "LSEARCH") {
        if (db.llists.find(name) != db.llists.end()) {
            bool found = LSearch(db.llists[name], arg1);
            cout << " -> " << (found ? "TRUE" : "FALSE") << endl;
        } else {
            cout << " ->  Ошибка: список не создан" << endl;
        }
    }

        // ================================== Стек ==================================

    else if (command == "SPUSH") {
        if (db.stacks.find(name) != db.stacks.end()) {
            SPush(db.stacks[name], arg1);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: стек не создан" << endl;
        }
    }
    else if (command == "SPOP") {
        if (db.stacks.find(name) != db.stacks.end()) {
            string result = SPop(db.stacks[name]);
            cout << " -> " << result << endl;
        } else {
            cout << " -> Ошибка: стек не создан" << endl;
        }
    }

        // ================================== Очередь ==================================

    else if (command == "QPUSH") {
        if (db.queues.find(name) != db.queues.end()) {
            QPush(db.queues[name], arg1);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: очередь не создана" << endl;
        }
    }
    else if (command == "QPOP") {
        if (db.queues.find(name) != db.queues.end()) {
            string result = QPop(db.queues[name]);
            cout << " -> " << result << endl;
        } else {
            cout << " -> Ошибка: очередь не создана" << endl;
        }
    }

    // ================================== Дерево ==================================

    else if (command == "TPUSH") {
        if (db.trees.find(name) != db.trees.end()) {
            TPush(db.trees[name], arg1);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: дерево не создано" << endl;
        }
    }
    else if (command == "TDELETE") {
        if (db.trees.find(name) != db.trees.end()) {
            TDelete(db.trees[name], arg1);
            cout << " -> Выполнено" << endl;
        } else {
            cout << " -> Ошибка: дерево не создано" << endl;
        }
    }
    else if (command == "TSEARCH") {
        if (db.trees.find(name) != db.trees.end()) {
            bool found = TSearch(db.trees[name], arg1);
            cout << " -> " << (found ? "Найдено" : "Не найдено") << endl;
        } else {
            cout << " -> Ошибка: дерево не создано" << endl;
        }
    }

    // ================================== Вывод ==================================

    else if (command == "PRINT") {
        if (db.arrays.find(name) != db.arrays.end()) {
            PrintMArray(db.arrays[name]);
        } else if (db.flists.find(name) != db.flists.end()) {
            PrintFList(db.flists[name]);
        } else if (db.llists.find(name) != db.llists.end()) {
            PrintLList(db.llists[name]);
        } else if (db.stacks.find(name) != db.stacks.end()) {
            PrintStack(db.stacks[name]);
        } else if (db.queues.find(name) != db.queues.end()) {
            PrintQueue(db.queues[name]);
        } else if (db.trees.find(name) != db.trees.end()) {
            cout << "\nЧтение в ширину:\n";
            PrintTree(db.trees[name] -> root);
            cout << "\nЧтение в глубину(прямой):\n";
            preOrder(db.trees[name] -> root);
            cout << "\nЧтение в глубину(симметричный):\n";
            inOrder(db.trees[name] -> root);
            cout << "\nЧтение в глубину(обратный):\n";
            postOrder(db.trees[name] -> root);
            cout << endl;
        } else {
            cout << " -> Ошибка: структура данных не создана" << endl;
        }
    }
    else {
        cout << " -> Ошибка: неизвестная команда" << endl;
    }

    SaveDatabase();
}

void CleanupDatabase() {
    for (auto& p : db.arrays) {
        DestroyMArray(p.second);
        delete p.second;
    }
    db.arrays.clear();

    for (auto& p : db.flists) {
        DestroyFList(p.second);
        delete p.second;
    }
    db.flists.clear();

    for (auto& p : db.llists) {
        DestroyLList(p.second);
        delete p.second;
    }
    db.llists.clear();

    for (auto& p : db.stacks) {
        DestroyStack(p.second);
        delete p.second;
    }
    db.stacks.clear();

    for (auto& p : db.queues) {
        DestroyQueue(p.second);
        delete p.second;
    }
    db.queues.clear();

    for (auto& p : db.trees) {
        DestroyTree(p.second -> root);
        delete p.second;
    }
    db.trees.clear();
}