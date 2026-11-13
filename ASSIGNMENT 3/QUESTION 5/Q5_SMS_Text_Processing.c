/* Q5 - Process text without string.h: word count and palindrome check. */
#include <stdio.h>
#include <ctype.h>

int word_count(const char s[]) {
    int count = 0, inside = 0;
    for (int i = 0; s[i] != '\\0'; i++) {
        if (isspace((unsigned char)s[i])) inside = 0;
        else if (!inside) { count++; inside = 1; }
    }
    return count;
}
int is_palindrome(const char s[]) {
    int left = 0, right = 0;
    while (s[right] != '\\0') right++;
    right--;
    while (left < right) {
        while (left < right && !isalpha((unsigned char)s[left])) left++;
        while (left < right && !isalpha((unsigned char)s[right])) right--;
        if (tolower((unsigned char)s[left]) != tolower((unsigned char)s[right]))
            return 0;
        left++; right--;
    }
    return 1;
}
void to_uppercase(char s[]) {
    for (int i = 0; s[i] != '\\0'; i++) s[i] = (char)toupper((unsigned char)s[i]);
}
void reverse_string(char s[]) {
    int left = 0, right = 0;
    while (s[right] != '\\0') right++;
    right--;
    while (left < right) {
        char t = s[left]; s[left] = s[right]; s[right] = t;
        left++; right--;
    }
}
int main(void) {
    char message[] = "Meet at the library at 5 PM";
    char reversed[] = "College Feedback";
    printf("Words: %d\\n", word_count(" Meet at the library at 5 PM "));
    printf("Palindrome results: %d %d\\n",
           is_palindrome("Madam, I'm Adam"), is_palindrome("Hello"));
    to_uppercase(message);
    printf("Uppercase: %s\\n", message);
    reverse_string(reversed);
    printf("Reversed: %s\\n", reversed);
    return 0;
}
