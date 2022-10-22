/*Дана строка, состоящая из слов, разделенных пробелами.
Разбить исходную строку на две подстроки, причем первая длиной k символов, 
если на k-ю позицию попадает слово, то его следует отнести ко второй строке. 
Значение k вводится с клавиатуры.*/

#include <iostream>

using namespace std;

int main() {
    int splitter, nextWord;
    string outFirst, outSecond;
    string text = "Hello world hello world";
    
    do {
        cout << "Write number of symbol:";
        cin >> splitter;
    } while (splitter < 1 || splitter > (int) text.length());

    for (int i = splitter; i < (int) text.length(); i++) {
        if (text[i] == ' ') {
            splitter = i;
            break;
        }
    }

    outFirst.append(text, 0, splitter);
    outSecond.append(text, splitter + 1, text.length() - splitter);
    cout << text << endl;
    cout << outFirst << endl;
    cout << outSecond << endl;
}
