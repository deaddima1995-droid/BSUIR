/*Дана строка, состоящая из слов, разделенных пробелами.
Разбить исходную строку на две подстроки, причем первая длиной k символов, 
если на k-ю позицию попадает слово, то его следует отнести ко второй строке. 
Значение k вводится с клавиатуры.*/

#include <iostream>

using namespace std;

int main() {
    int splitter, nextWord;
    string text = "My brothers are very smart and work hard in school";
    string outFirst, outSecond;
    
    do {
        cout << "Write number of symbol:";
        cin >> splitter;
    } while (splitter < 1 || splitter > (int) text.length());

    for (int i = splitter; i >= 0; i--) {
        if (text[i] == ' ') {
            splitter = i;
            break;
        } else if (i == 0) {
            splitter = 0;
        }
    }

    if (text[splitter] == ' ') {
      for (int i = splitter; i < (int) text.length(); i++) {
          if (text[i] != ' ') {
              nextWord = i;
              break;
        }
      }
    } else {
        nextWord = splitter;
    }

    outFirst.append(text, 0, splitter);
    outSecond.append(text, nextWord, text.length() - splitter);
    cout << text << endl;
    cout << outFirst << endl;
    cout << outSecond << endl;
}
