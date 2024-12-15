#ifndef LR2_MENU_H
#define LR2_MENU_H

#include "help.h"
#include "CBT.h"

void DFSgraph(HashTable<Array<string>>& graph, const string& startNode) {
    Stack<string> stack;
    HashTable<bool> visited;

    Array<string> allKeys = graph.keys();
    for (int i = 0; i < allKeys.size(); i++) {
        visited.put(allKeys.get(i), false);
    }

    stack.push(startNode);
    visited.put(startNode, true);

    while (stack.size() > 0) {
        string currentValue = stack.pop();
        cout << currentValue << " ";

        Array<string> neighbors = graph.get(currentValue);
        for (int i = neighbors.size() - 1; i >= 0; i--) {
            string neighbor = neighbors.get(i);
            if (!visited.get(neighbor)) {
                stack.push(neighbor);
                visited.put(neighbor, true);
            }
        }
    }
    cout << endl;
}

void task1() { // 6
    CompleteBinaryTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);

    cout << "Depth-First Search for tree" << endl;
    tree.printTree();
    cout << endl;
    tree.DFS();

    HashTable<Array<string>> graph;

    Array<string> neighborsA;
    neighborsA.pushBack("B");
    neighborsA.pushBack("C");
    graph.put("A", neighborsA);

    Array<string> neighborsB;
    neighborsB.pushBack("A");
    neighborsB.pushBack("D");
    neighborsB.pushBack("E");
    graph.put("B", neighborsB);

    Array<string> neighborsC;
    neighborsC.pushBack("A");
    graph.put("C", neighborsC);

    Array<string> neighborsD;
    neighborsD.pushBack("B");
    graph.put("D", neighborsD);

    Array<string> neighborsE;
    neighborsE.pushBack("B");
    graph.put("E", neighborsE);

    cout << "Depth-First Search for graph" << endl;
    cout << graph << endl;
    DFSgraph(graph, "A");

}

void setMenu(Array<string> parameters) {
    string command = parameters.get(0);
    string name = parameters.get(1);
    Set<string> set = readSet(name);

    if (command == "SETADD") {
        checkArgumentCount(parameters, 3);
        string element = parameters.get(2);
        validateElement(element);

        set.add(element);
        saveSet(name, set);
    } else if (command == "SETDEL") {
        checkArgumentCount(parameters, 3);
        string element = parameters.get(2);
        validateElement(element);

        set.remove(element);
        saveSet(name, set);
    } else if (command == "SETAT") {
        checkArgumentCount(parameters, 3);
        string element = parameters.get(2);
        validateElement(element);

        if (set.contains(element) == -1) {
            cout << element << " is not in set" << endl;
        } else {
            cout << element << " is in set" << endl;
        }
    } else if (command == "SETPRINT") {
        cout << set << endl;
    } else {
        throw runtime_error("Unknown for stack command");
    }


}

void task2() {
    string input;
    getline(cin, input);
    Array<string> parameters = split(input, ' ');
    setMenu(parameters);
}

int totalSum(Set<int>& s) {
    int sum = 0;
    Array<int> values = s.values();
    for (int i = 0; i < values.size(); i++) {
        sum += values.get(i);
    }
    return sum;
}

bool findSubset(Set<int>& elements, int targetSum, Set<int>& subset) {
    if (targetSum == 0) { // дошли до конца
        return true;
    }
    if (elements.size() == 0 || targetSum < 0) {
        return false;
    }

    Array<int> values = elements.values();
    for (int i = 0; i < values.size(); i++) {
        int value = values.get(i); // берём первый элемент

        subset.add(value); // добавляем элемент в текущее подмножество
        elements.remove(value); // удаляем элемент из исходного множества

        if (findSubset(elements, targetSum - value, subset)) {
            return true; // если нашли подходящее подмножество
        }

        subset.remove(value);
        elements.add(value); // возвращаем элемент в исходное множество
    }

    return false;
}

void splitSet(Set<int> s) {
    int sum = totalSum(s);
    bool isFound = false;

    for (int numSubsets = 2; numSubsets <= s.size(); numSubsets++) {
        Array<Set<int>> result;
        int targetSum = sum / numSubsets; // нужная для текущего количества подмножеств сумма

        if (sum % numSubsets != 0) { // если сумма не делится на кол-во подмножеств
            continue;
        }

        Set<int> elements; // копия множества
        Array<int> values = s.values();
        for (int i = 0; i < values.size(); i++) {
            elements.add(values.get(i));
        }

        bool isFoundSubs = true; // для текущего количества подмножеств
        for (int i = 0; i < numSubsets; i++) {
            Set<int> subset;

            if (!findSubset(elements, targetSum, subset)) {
                isFoundSubs = false;
                break;
            }
            result.pushBack(subset);
        }

        if (isFoundSubs) {
            isFound = true;
            cout << "Subsets of set { " << s << "} with sum " << targetSum << ": "<< endl;
            for (int i = 0; i < result.size(); i++) {
                cout << "{ " << result.get(i) << "}";
                if (i < result.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }

    if (!isFound) {
        throw runtime_error("Cannot divide set into subsets with equal sum.");
    }
}


void task3() { // 1
    // ручной ввод
    /*
    string input;
    cout << "Write your elements separated by spaces: ";
    getline(cin, input);
    Array<string> splitedInput = split(input, ' ');
    Set<int> set;
    for (int i = 0; i < splitedInput.size(); i++) {
        set.add(toInt(splitedInput.get(i)));
    }
    */

    Set<int> set;
    set.add(4);
    set.add(10);
    set.add(10); // тест на повтор
    set.add(5);
    set.add(1);
    set.add(3);
    set.add(7);

    Set<int> set2;
    set2.add(10);
    set2.add(20);
    set2.add(30);
    set2.add(15);
    set2.add(7);
    set2.add(8);

    Set<int> set3;
    set3.add(1);
    set3.add(3);
    set3.add(2);

    try {
        splitSet(set3);
    }
    catch (exception& e) {
        cerr << e.what() << endl;
    }
}

void subarrays(Array<string>& inputArray, Array<Array<string>>& result, Array<string>& currentSubarray, int index) {

    if (index == inputArray.size()) { // достигли конца по индексам
        Array<string> subarray; // переносим все элементы в result
        for (int i = 0; i < currentSubarray.size(); i++) {
            subarray.pushBack(currentSubarray.get(i));
        }
        result.pushBack(subarray);
        return;
    }

    subarrays(inputArray, result, currentSubarray, index + 1); // пропускаем

    currentSubarray.pushBack(inputArray.get(index)); // добавляем в подмножество текущий элемент
    subarrays(inputArray, result, currentSubarray, index + 1);

    currentSubarray.remove(currentSubarray.size() - 1); // убираем последний элемент, чтобы вернуть состояние текущего подмассива
}

void task4() { // 1
    //ручной ввод
    /*
    string input;
    cout << "Write your elements separated by spaces: ";
    getline(cin, input);
    Array<string> arr = split(input, ' ');
     */

    Array<string> arr;
    arr.pushBack("1");
    arr.pushBack("2");
    arr.pushBack("3");

    Array<Array<string>> result;
    Array<string> currentSubarray;

    subarrays(arr, result, currentSubarray, 0);

    for (int i = 0; i < result.size(); i++) {
        cout << "{";
        for (int j = 0; j < result.get(i).size(); j++) {
            cout << result.get(i).get(j);
            if (j != result.get(i).size() - 1) {
                cout << ", ";
            }
        }
        cout << "}" << endl;
    }
}

void task5() { // 5
    BinarySearchTree tree;
    tree.root = new TNode(25);
    tree.root->left = new TNode(18);
    tree.root->right = new TNode(30);
    //tree.root->right->right = new TNode(35);
    //tree.root->right->left = new TNode(27);
    //tree.root->left->right = new TNode(20);
    //tree.root->left->left = new TNode(17);


    if (tree.isBST()) {
        cout << "This tree is binary search tree" << endl;
    } else {
        cout << "This tree is not a binary search tree" << endl;
    }
}

int findMinDelay(HashTable<int>& routes, HashTable<string>& servers, string start, string end) {
    int numServers = servers.size();
    HashTable<int> delays; // задержки

    for (int i = 0; i < numServers; i++) { // для всех большая задержка
        delays.put(servers.get(to_string(i)), 100);
    }

    delays.put(start, 0); // для начального 0

    bool isFoundBetter;
    for (int k = 0; k < numServers - 1; k++) { // идём по каждому серверу
        isFoundBetter = false;

        for (int i = 0; i < numServers; i++) {

            for (int j = 0; j < numServers; j++) {

                string firstRout = servers.get(to_string(i));
                string secondRoute = servers.get(to_string(j));
                string route = firstRout + "-" + secondRoute; // формируем маршрут

                try { // чтобы не выбрасывало исключения :)

                    int delay = routes.get(route); // берём задержку вида route1-route2

                    // если известная задержка до 2 сервера меньше чем через первый
                    if (delays.get(firstRout) + delay < delays.get(secondRoute)) {
                        delays.put(secondRoute, delays.get(firstRout) + delay);
                        isFoundBetter= true;
                    }

                } catch (...) {
                    // маршрут не существует
                }
            }
        }
        if (!isFoundBetter) {
            break; // если улучшений нет
        }
    }

    return delays.get(end);
}

void task6() { // 6
    /*
    HashTable<string> servers;
    servers.put("0", "A");
    servers.put("1", "B");
    servers.put("2", "C");
    servers.put("3", "D");


    HashTable<int> routes;
    routes.put("A-B", 5);
    routes.put("B-C", 3);
    routes.put("C-D", 7);
    routes.put("A-C", 7);

    string start = "A";
    string end = "D";
    */
    HashTable<string> servers;
    servers.put("0", "A");
    servers.put("1", "B");
    servers.put("2", "C");


    HashTable<int> routes;
    routes.put("A-B", 1);
    routes.put("B-C", 2);
    routes.put("A-C", 4);

    string start = "A";
    string end = "C";

    try {
        int minDelay = findMinDelay(routes, servers, start, end);
        cout << "Minimal delay from " << start << " to " << end << ": " << minDelay << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

#endif //LR2_MENU_H