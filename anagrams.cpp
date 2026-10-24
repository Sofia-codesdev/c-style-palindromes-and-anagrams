#include <iostream>
#include <cstring>

void mysort(char* str, int len)
{
    for (int i = 0; i < len - 1; ++i)
        for (int j = 0; j < len - 1 - i; ++j)
            if (str[j] > str[j + 1])
                std::swap(str[j], str[j + 1]);
}


bool areAnagrams(const char* a, const char* b)
{
    int len1 = static_cast<int>(std::strlen(a));
    int len2 = static_cast<int>(std::strlen(b));
    if (len1 != len2) return false;

    char* c1 = new char[len1 + 1];
    char* c2 = new char[len2 + 1];
    std::strcpy(c1, a);
    std::strcpy(c2, b);

    mysort(c1, len1);
    mysort(c2, len2);

    bool eq = (std::strcmp(c1, c2) == 0);
    delete[] c1;
    delete[] c2;
    return eq;
}

// Возвращает сигнатуру слова (отсортированную копию) в куче
char* signature(const char* word)
{
    int len = static_cast<int>(std::strlen(word));
    char* s = new char[len + 1];
    std::strcpy(s, word);
    mysort(s, len);
    return s;
}

// Печатает группы анаграмм. Возвращает количество групп (размер > 1).
int printAnagramGroups(char** words, int count)
{
    bool* used = new bool[count]();
    int groups = 0;

    for (int i = 0; i < count; ++i)
    {
        if (used[i]) continue;

        // Собираем всех "соседей" i-го слова, ещё не отмеченных
        int* members = new int[count];
        int m = 0;

        for (int j = i; j < count; ++j)
        {
            if (used[j]) continue;
            if (areAnagrams(words[i], words[j]))
            {
                members[m++] = j;
                used[j] = true;
            }
        }

        if (m > 1)
        {
            ++groups;
            std::cout << "[ ";
            for (int k = 0; k < m; ++k)
            {
                std::cout << words[members[k]];
                if (k + 1 < m) std::cout << ", ";
            }
            std::cout << " ]\n";
        }

        delete[] members;
    }

    delete[] used;
    return groups;
}

int main()
{
    char str[] = "listen silent maadm madam daamm lesson honey nohey";
    const char* delim = " !?,. ";

    char* words[50];
    int count = 0;

    char* token = std::strtok(str, delim);
    while (token != nullptr && count < 50)
    {
        words[count++] = token;
        token = std::strtok(nullptr, delim);
    }

    std::cout << "Слов: " << count << "\n";
    std::cout << "Группы анаграмм:\n";
    int groups = printAnagramGroups(words, count);
    std::cout << "Всего групп: " << groups << "\n";

    return 0;
}