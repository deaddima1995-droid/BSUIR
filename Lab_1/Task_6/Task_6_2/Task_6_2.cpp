/*Дана строка, состоящая из слов, разделенных пробелами.
Разбить исходную строку на две подстроки, причем первая длиной k символов, 
если на k-ю позицию попадает слово, то его следует отнести ко второй строке. 
Значение k вводится с клавиатуры.*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

int main() {
    int splitter, nextWord;
    char text[] = "My brothers are very smart and work hard in school";
    char *outFirst, *outSecond;
    
    do {
        cout << "Write number of symbol:";
        cin >> splitter;
    } while (splitter < 1 || splitter > sizeof(text));

    for (int i = splitter; i >= 0; i--) {
        if (text[i] == ' ') {
            splitter = i;
            break;
        } else if (i == 0) {
            splitter = 0;
        }
    }

    if (text[splitter] == ' ') {
      for (int i = splitter; i < sizeof(text); i++) {
          if (text[i] != ' ') {
              nextWord = i;
              break;
        }
      }
    } else {
        nextWord = splitter;
    }
    outFirst = new char[nextWord]{};
    outSecond = new char[sizeof(text) - nextWord]{};

    strncat(outFirst, text, nextWord);

    for (int i = nextWord; i < (int) strlen(text); i++) {
        outSecond[i - nextWord] = text[i];
    }

    //outFirst.append(text, 0, splitter);
    //outSecond.append(text, nextWord, text.length() - nextWord);

    cout << text << endl;
    cout << outFirst << endl;
    cout << outSecond << endl;

    delete outFirst;
    delete outSecond;
}
