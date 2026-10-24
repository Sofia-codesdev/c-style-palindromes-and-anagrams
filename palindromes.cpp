#include <iostream>
#include <cstring>

bool isPalindrom(const char* str, int len)
{
    if (len <= 1) return true;

    const char* left = str;
    const char* right = str + len - 1;

    while (left < right)
    {
        if (*left != *right) return false;
        left++;
        right--;
    }
    return true;
}

int palindromCount(char** words, int count)
{
    int palCount = 0;
    for (int i = 0; i < count; ++i)
    {
        int len = static_cast<int>(std::strlen(words[i]));
        if (isPalindrom(words[i], len))
            ++palCount;
    }
    return palCount;
}

char** palindromArr(char** words, int count, int palCount)
{
    char** arr = new char*[palCount];
    int j = 0;
    
    for (int i = 0; i < count; ++i)
    {
        int len = static_cast<int>(std::strlen(words[i]));
        if (isPalindrom(words[i], len))
        {
            arr[j] = new char[len + 1];
            std::strcpy(arr[j], words[i]);
            ++j;
        }
    }
    return arr;
}

void deletePalindromArr(char** arr, int palCount)
{
    for (int i = 0; i < palCount; ++i)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

int main()
{
    const char original[] = "madam listen level noon";
    const char delim[] = "! ,?";

    char str[256];
    std::strcpy(str, original);

    char* words[50];
    int count = 0;

    char* token = strtok(str, delim);
    while (token != nullptr && count < 50)
    {
        words[count++] = token;
        token = strtok(nullptr, delim);
    }

    int palCount = palindromCount(words, count);

    char** palindromes = palindromArr(words, count, palCount);

    std::cout << "Слова-палиндромы (" << palCount << " шт.): [ ";
    for (int i = 0; i < palCount; ++i)
    {
        std::cout << palindromes[i];
        if (i + 1 < palCount) std::cout << ", ";
    }
    std::cout << " ]\n";

    deletePalindromArr(palindromes, palCount);
    return 0;
}