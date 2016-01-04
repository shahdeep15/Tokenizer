/*Deep Shah
 * CS 214
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Our token has three attributes where type specifies the kind of token, length of the token, and a pointer to
//the actual data with a pointer to the next token

typedef char bool;
typedef struct _token {
    int type; // 1 -> word, 2 -> dec, 3 -> oct, 4 -> hex, 5 -> fpc, 6 -> operators
    int length;
    char *data;
    struct _token *next;
} token;

//Create a new token
token *newToken(char *input, int length, int type) {
    if (type < 0) {
        token *t = malloc(sizeof(token)); //Allocate memory for the token
        t->type = 0;
        t->length = 0;
        t->data = NULL;
        t->next = NULL;
        return t;
    }
    token *t = malloc(sizeof(token));
    t->length = length;
    t->type = type;
    t->data = malloc(length + 1);
    t->next = NULL;
    memcpy(t->data, input, length);
    t->data[length] = 0; // null terminated string
    return t;
}

//This method is used to delete tokens
void delToken(token *t) {
    if (t->next)
        delToken(t->next);
    if (t->length)
        free(t->data); //Free the memory
    free(t);
}

//This method recognizes each token and prints out the case-specific details
//We tried to add as many operators as we can, this function would just print out operator if it doesn't
//recognize the operator

void prettyPrint(token *t) {
    char firstCharacter;
    char secondChar;
    char thirdChar;
    if (!t)
        return;
    switch (t->type) {
        case 1:
            firstCharacter= t->data[0];
            secondChar= t->data[1];
            thirdChar= t->data[2];
            if(firstCharacter=='i' && secondChar=='f'){
                printf("C Keyword");
                break;
            }else if(firstCharacter=='f' && secondChar=='o' && thirdChar == 'r'){
                printf("C Keyword");
                break;
            }
            printf("word");                    break;
        case 2: printf("decimal constant"); break;
        case 3: printf("octal constant");   break;
        case 4: printf("hex constant");     break;
        case 5: printf("float");            break;
        case 6: //if, else-if statements for different operators, if it can't find specific operator it in the list, it defaults to just operator
            firstCharacter= t->data[0];
            secondChar= t->data[1];
            if(firstCharacter == '['){
                printf("left brace");
                break;
            }else if(firstCharacter == ']'){
                printf("right brace");
                break;
            }else if(firstCharacter == '+' && secondChar != '='){
                printf("plus");
                break;
            } else if(firstCharacter == '+' && secondChar == '='){
                printf("plus equals");
                break;
            }else if(firstCharacter == '-'){
                printf("subtract");
                break;
            }else if(firstCharacter == '.'){
                printf("structure member");
                break;
            }else if(firstCharacter == '/'){
                printf("backslash");
                break;
            }else if(firstCharacter == '>' && secondChar=='='){
                printf("greater or equal to");
                break;
            } else if(firstCharacter == '>'){
                printf("greater than sign");
                break;
            }else if(firstCharacter == '<'&& secondChar=='='){
                printf("less than or equal to");
                break;
            }else if(firstCharacter == '<'){
                printf("less than sign");
                break;
            }else if(firstCharacter == '>'&& secondChar=='>'){
                printf("shift right");
                break;
            }else if(firstCharacter == '<'&& secondChar=='<'){
                printf("shift left");
                break;
            }else if(firstCharacter == '&'&& secondChar=='&'){
                printf("logical and");
                break;
            }else if(firstCharacter == '|'&& secondChar=='|'){
                printf("logical or");
                break;
            }else if(firstCharacter == '+'&& secondChar=='+'){
                printf("increment");
                break;
            }else if(firstCharacter == '-'&& secondChar=='-'){
                printf("decrement");
                break;
            }else if(firstCharacter == '('){
                printf("left parenthesis");
                break;
            }else if(firstCharacter == ')'){
                printf("right parenthesis");
                break;
            }else if(firstCharacter == '('&& secondChar==')'){
                printf("cast");
                break;
            }else if(firstCharacter == '!'){
                printf("negate");
                break;
            }else if(firstCharacter == '!'&& secondChar=='='){
                printf("not equals");
                break;
            }else if(firstCharacter == '?'){
                printf("condition");
                break;
            }else if(firstCharacter == '|'){
                printf("bitwise or");
                break;
            }else if(firstCharacter == '&'){
                printf("address");
                break;
            }else if(firstCharacter == ','){
                printf("comma");
                break;
            }else if(firstCharacter == '^'){
                printf("bitwise exclusive");
                break;
            }else if(firstCharacter == '*'){
                printf("multiply");
                break;
            }else if(firstCharacter == '%'){
                printf("modulus");
                break;
            }else if(firstCharacter == '='){
                printf("equals sign");
                break;
            }else if(firstCharacter == '\\' && secondChar == 'n'){
				printf("0x0a");
				break;
			}else if(firstCharacter == '\\' && secondChar == 't'){
				printf("0x09");
				break;
			}else if(firstCharacter == '\\' && secondChar == 'v'){
				printf("0x0b");
				break;
			}else if(firstCharacter == '\\' && secondChar == 'f'){
				printf("0x0c");
				break;
			}else if(firstCharacter == '\\' && secondChar == 'r'){
				printf("0x0d");
				break;
			}else if(firstCharacter == '\\'){
				printf("forward slash");
				break;
			}
            else {
              printf("operator");
                break;
            }
    }
    if (t->length)
        printf(" \"%s\"\n", t->data);
    prettyPrint(t->next);
}

// This method is to find out whether a certain token is an operator or not

bool isOperator(char c, char *i) {
    // these symbols don't have any combinations
    
    if (c == '(' || c == ')' || c == '[' || c == ']' || c == '.' || c == '~'|| c == ',' || c == '?' || c == '\\')
        return 1;
    // These symbols can have combinations
    bool isOp = 0;
    if (c == '<' || c == '>')
        isOp = 3;
    else if (c == '+' || c == '-' || c == '&' || c == '|' || c == '=')
        isOp = 2;
    else if (c == '*' || c == '/' || c == '%' || c == '^' || c == '!')
        isOp = 1;
    else
        return 0;
    if (isOp == 3 && i[1] == c && i[2] == '=')
        return 3;
    else if (isOp >= 2 && i[1] == c)
        return 2;
    else if (i[1] == '=')
        return 2;
    else if (c == '-' && i[1] == '>')
        return 2;
    else
        return 1;
}

// This method is to find out whether a certain token is a letter or not

bool isLetter(char c) {
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
}
// This method is to find out whether a certain token is an alphanumeric or not

bool isAlphaNumeric(char c) {
    return ('0' <= c && c <= '9') || isLetter(c);
}

//This method tokenizes the raw input from the user

token *tokenize(char *i) {
    token *begin = newToken(i, 0, -1);
    token *current = begin;
    int s = 0; // 1 -> word
    char *j;
    char c;
    for (c = *i; c; c = *i) {
        switch (s) {
            case 1:
                if (isAlphaNumeric(c)) {
                    i++;
                    continue;
                }
                // not alphanumeric anymore
                current->next = newToken(j, i - j, 1);
                current = current->next;
                s = 0;
                // we still haven't dealt with the next character, let
                // it just fallthrough to the '0' case
            case 0:
                if (c == '0') { // upcoming set of numbers is oct/hex
                    strtol(i, &j, i[1] == 'x' ? 16 : 8);
                    current->next = newToken(i, j - i, 3 + (i[1] == 'x'));
                    current = current->next;
                    i = j;
                    continue;
                } else if ('1' <= c && c <= '9') { // upcoming is number | float
                    strtol(i, &j, 10);
                    if (*j == '.') { // float
                        j++;
                        strtol(j, &j, 10);
                        if (*j == 'e') {
                            j++;
                            strtol(j, &j, 10);
                        }
                        current->next = newToken(i, j - i, 5);
                    } else {
                        current->next = newToken(i, j - i, 2);
                    }
                    current = current->next;
                    i = j;
                    continue;
                } else if (isLetter(c)) { //if it's letter
                    j = i;
                    i++;
                    s = 1;
                    continue;
                }
                char isOp = isOperator(c, i); 
                
                if (isOp) {
                    current->next = newToken(i, isOp, 6);
                    current = current->next;
                    i += isOp;
                    continue;
                }
                
                // assume everything else is whitespace
                i++;
                break;
        }
    }
    return begin;
}

int main(int argc, char **argv) {
    if (argc != 2) { //error check
        printf("Please input string to tokenized\n");
        return 1;
    }
    
    token *tl = tokenize(argv[1]); //takes the input and runs tokenize method
    printf("tokenizer \"%s\"\n", argv[1]);
    prettyPrint(tl);
    delToken(tl);
    
    return 0;
}
